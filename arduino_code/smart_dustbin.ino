#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int PIN_HAND_TRIG   = 2;
const int PIN_HAND_ECHO   = 3;
const int PIN_WASTE_TRIG  = 4;
const int PIN_WASTE_ECHO  = 5;
const int PIN_LED_GREEN   = 6;
const int PIN_LED_RED     = 7;
const int PIN_BUZZER      = 8;
const int PIN_SERVO       = 9;

const float BIN_HEIGHT_CM = 30.0;
const int HAND_DETECTION_DISTANCE_CM = 15;
const int FULL_THRESHOLD_PERCENT = 90;

const int LID_CLOSED_ANGLE = 0;
const int LID_OPEN_ANGLE   = 90;

const unsigned long LID_OPEN_TIME_MS   = 3000;
const unsigned long LID_COOLDOWN_MS    = 1000;
const unsigned long SENSOR_READ_INT    = 150;
const unsigned long WASTE_READ_INT     = 1000;
const unsigned long LCD_UPDATE_INT     = 500;
const unsigned long SERIAL_PRINT_INT   = 1000;

Servo lidServo;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

enum LidState {
  LID_CLOSED,
  LID_OPEN,
  LID_COOLDOWN
};

LidState currentLidState = LID_CLOSED;

unsigned long lastHandReadTime    = 0;
unsigned long lastWasteReadTime   = 0;
unsigned long lastLcdUpdateTime   = 0;
unsigned long lastSerialPrintTime = 0;
unsigned long lidOpenedTimestamp  = 0;
unsigned long lidClosedTimestamp  = 0;

float measuredHandDistance   = -1.0;
float measuredWasteDistance  = -1.0;
int calculatedFillPercentage = 0;
bool isBinFull               = false;
bool isHandDetected          = false;

float readDistance(int trigPin, int echoPin);
void processLidStateMachine();
void processWasteLevel();
void updateIndicators();
void updateDisplay();
void printSerialDebug();
void openLid();
void closeLid();

void setup() {
  Serial.begin(9600);
  Serial.println(F("==========================================="));
  Serial.println(F("Smart Dustbin System Initializing..."));
  Serial.println(F("==========================================="));

  pinMode(PIN_HAND_TRIG, OUTPUT);
  pinMode(PIN_HAND_ECHO, INPUT);
  pinMode(PIN_WASTE_TRIG, OUTPUT);
  pinMode(PIN_WASTE_ECHO, INPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_BUZZER, LOW);

  lidServo.attach(PIN_SERVO);
  closeLid();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED INIT FAILED"));
    while (true) {}
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Smart Dustbin"));
  display.setCursor(0, 16);
  display.println(F("System Ready"));
  display.display();

  Serial.println(F("OLED INIT OK"));
  delay(1500);
  display.clearDisplay();
  display.display();

  Serial.println(F("System Initialization Complete. Running main loop."));
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastHandReadTime >= SENSOR_READ_INT) {
    lastHandReadTime = currentMillis;
    measuredHandDistance = readDistance(PIN_HAND_TRIG, PIN_HAND_ECHO);

    if (measuredHandDistance > 0 && measuredHandDistance < HAND_DETECTION_DISTANCE_CM) {
      isHandDetected = true;
    } else {
      isHandDetected = false;
    }
  }

  processLidStateMachine();

  if (currentLidState == LID_CLOSED) {
    if (currentMillis - lastWasteReadTime >= WASTE_READ_INT) {
      lastWasteReadTime = currentMillis;
      processWasteLevel();
    }
  }

  updateIndicators();

  if (currentMillis - lastLcdUpdateTime >= LCD_UPDATE_INT) {
    lastLcdUpdateTime = currentMillis;
    updateDisplay();
  }

  if (currentMillis - lastSerialPrintTime >= SERIAL_PRINT_INT) {
    lastSerialPrintTime = currentMillis;
    printSerialDebug();
  }
}

float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 26000);
  if (duration == 0) {
    return -1.0;
  }
  float distance = (duration * 0.0343) / 2.0;
  return distance;
}

void processLidStateMachine() {
  unsigned long currentMillis = millis();
  switch (currentLidState) {
    case LID_CLOSED:
      if (isHandDetected) {
        openLid();
        currentLidState = LID_OPEN;
        lidOpenedTimestamp = currentMillis;
        Serial.println(F("[SYSTEM] Object detected. Lid Opened."));
      }
      break;
    case LID_OPEN:
      if (currentMillis - lidOpenedTimestamp >= LID_OPEN_TIME_MS) {
        closeLid();
        currentLidState = LID_COOLDOWN;
        lidClosedTimestamp = currentMillis;
        Serial.println(F("[SYSTEM] Open delay completed. Closing Lid."));
      }
      break;
    case LID_COOLDOWN:
      if (currentMillis - lidClosedTimestamp >= LID_COOLDOWN_MS) {
        currentLidState = LID_CLOSED;
      }
      break;
  }
}

void processWasteLevel() {
  measuredWasteDistance = readDistance(PIN_WASTE_TRIG, PIN_WASTE_ECHO);
  if (measuredWasteDistance <= 0) {
    return;
  }
  float distance = measuredWasteDistance;
  if (distance > BIN_HEIGHT_CM) {
    distance = BIN_HEIGHT_CM;
  }
  if (distance < 2.0) {
    distance = 2.0;
  }
  float fillLevel = BIN_HEIGHT_CM - distance;
  float fillPercent = (fillLevel / BIN_HEIGHT_CM) * 100.0;
  calculatedFillPercentage = (int)constrain(fillPercent, 0, 100);
  if (calculatedFillPercentage >= FULL_THRESHOLD_PERCENT) {
    isBinFull = true;
  } else {
    isBinFull = false;
  }
}

void updateIndicators() {
  if (isBinFull) {
    digitalWrite(PIN_LED_RED, HIGH);
    digitalWrite(PIN_LED_GREEN, LOW);
    unsigned long pulseCycle = millis() % 3000;
    if (pulseCycle < 100) {
      digitalWrite(PIN_BUZZER, HIGH);
    } else {
      digitalWrite(PIN_BUZZER, LOW);
    }
  } else {
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_GREEN, HIGH);
    digitalWrite(PIN_BUZZER, LOW);
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Smart Dustbin"));
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print(F("Fill Level: "));
  display.print(calculatedFillPercentage);
  display.println(F("%"));
  display.setCursor(0, 32);
  display.print(F("Status: "));
  if (isBinFull) {
    display.println(F("FULL"));
  } else {
    display.println(F("NORMAL"));
  }
  display.setCursor(0, 48);
  display.print(F("Lid State: "));
  switch (currentLidState) {
    case LID_CLOSED:   display.println(F("CLOSED")); break;
    case LID_OPEN:     display.println(F("OPEN")); break;
    case LID_COOLDOWN: display.println(F("COOLDOWN")); break;
  }
  display.display();
}

void printSerialDebug() {
  Serial.print(F("Hand Dist: "));
  if (measuredHandDistance < 0) {
    Serial.print(F("ERR "));
  } else {
    Serial.print(measuredHandDistance, 1);
    Serial.print(F(" cm "));
  }
  Serial.print(F("| Waste Dist: "));
  if (measuredWasteDistance < 0) {
    Serial.print(F("ERR "));
  } else {
    Serial.print(measuredWasteDistance, 1);
    Serial.print(F(" cm "));
  }
  Serial.print(F("| Fill: "));
  Serial.print(calculatedFillPercentage);
  Serial.print(F("% | Status: "));
  Serial.print(isBinFull ? F("FULL ") : F("NORMAL "));
  Serial.print(F("| Lid: "));
  switch (currentLidState) {
    case LID_CLOSED:   Serial.println(F("CLOSED")); break;
    case LID_OPEN:     Serial.println(F("OPEN")); break;
    case LID_COOLDOWN: Serial.println(F("COOLDOWN")); break;
  }
}

void openLid() {
  lidServo.write(LID_OPEN_ANGLE);
}

void closeLid() {
  lidServo.write(LID_CLOSED_ANGLE);
}