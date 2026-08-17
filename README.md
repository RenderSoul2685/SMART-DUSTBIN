# Smart Dustbin – Industry-Oriented Embedded System

## 1. Project Overview

The **Smart Dustbin – Industry-Oriented Embedded System** is an embedded-system project designed to automate waste-bin operation and monitor the amount of waste inside the bin.

The system uses an **ESP32 microcontroller**, ultrasonic sensors, a servo motor, LEDs, and a buzzer. An ultrasonic sensor can detect an approaching hand/object and trigger automatic lid operation. A second distance measurement can be used to monitor the waste level inside the dustbin.

When the waste reaches a predefined threshold, the system generates an alert using an LED and/or buzzer.

The project can be implemented using real hardware or tested virtually using a simulator such as **Wokwi**.


## 🚀 Live Demo

Run and explore the Smart Dustbin project directly in Wokwi:

👉 [Open Smart Dustbin Live Demo](https://wokwi.com/projects/472601871673951233)
---

## 2. Problem Statement

Traditional dustbins require users to touch the lid and generally do not provide information about how full the bin is.

Common waste-management problems include:

* Overfilled dustbins
* Manual monitoring
* Waste overflow
* Poor hygiene
* Unnecessary collection trips
* Lack of real-time waste-level information

The Smart Dustbin addresses these problems by introducing automatic lid operation and waste-level monitoring.

---

## 3. Project Objectives

The main objectives are:

1. Detect an approaching hand/object.
2. Automatically open the dustbin lid.
3. Automatically close the lid after a delay.
4. Measure the distance between the sensor and waste.
5. Calculate the approximate bin fill percentage.
6. Detect when the bin reaches a defined threshold.
7. Activate an LED/buzzer alert.
8. Demonstrate embedded-system sensor interfacing and actuator control.
9. Provide a virtual simulation for testing without physical hardware.

---

## 4. Industry Relevance

Smart waste-management systems are relevant to:

* Smart cities
* Hospitals
* Airports
* Railway stations
* Shopping malls
* Offices
* Educational campuses
* Industrial facilities
* Public spaces

The project demonstrates concepts that are applicable to automated and IoT-enabled waste-management systems.

Potential business benefits include:

* Touchless operation
* Improved hygiene
* Reduced manual monitoring
* Reduced overflow
* Better collection efficiency
* Better maintenance planning

The project documentation identifies smart-city waste management and automated monitoring as important applications of this type of system.

---

## 5. Features

### Automatic Lid

An ultrasonic sensor detects an approaching hand/object. When the object is within the configured detection range, the ESP32 commands the servo motor to open the lid.

### Waste-Level Monitoring

A distance sensor measures the distance between the top of the bin and the waste surface.

As waste increases, this distance decreases.

### Fill-Level Calculation

The measured distance is converted into an approximate fill percentage.

### Full-Bin Alert

When the fill level reaches the configured threshold:

* Red LED is activated.
* Buzzer is activated.
* The system reports that the bin requires attention.

### Serial Monitoring

Sensor readings, fill percentage, and system status can be displayed through the Serial Monitor.

### Virtual Simulation

The system can be tested in Wokwi without requiring physical hardware.

---

## 6. Components Used

| Component                 | Purpose                   |
| ------------------------- | ------------------------- |
| ESP32                     | Main microcontroller      |
| HC-SR04 Ultrasonic Sensor | Distance/object detection |
| Second Ultrasonic Sensor  | Waste-level monitoring    |
| SG90 Servo Motor          | Automatic lid control     |
| Green LED                 | Normal status indication  |
| Red LED                   | Full-bin indication       |
| Buzzer                    | Audible alert             |
| Breadboard                | Circuit prototyping       |
| Jumper Wires              | Electrical connections    |
| Power Supply              | Powers the system         |

The project specification identifies ESP32, ultrasonic sensing, servo control, buzzer/LED alerts, power supply, and wiring/prototyping components as the main hardware requirements.

---

## 7. Embedded Systems Concepts Used

This project demonstrates:

* Microcontroller programming
* GPIO
* Digital input/output
* Ultrasonic sensor interfacing
* Distance measurement
* Servo motor control
* PWM-based actuator control
* LED control
* Buzzer control
* Threshold-based decision making
* Sensor calibration
* Serial communication
* Embedded C/C++ programming
* Optional Wi-Fi communication
* Optional IoT/cloud monitoring

These concepts correspond to the embedded-system concepts specified for the project.

---

## 8. System Architecture

```text
                ┌─────────────────────┐
                │  Object/Hand Sensor │
                └──────────┬──────────┘
                           │
                           ▼
                    ┌─────────────┐
                    │    ESP32    │
                    │ Microcontroller
                    └──────┬──────┘
                           │
             ┌─────────────┼─────────────┐
             │             │             │
             ▼             ▼             ▼
        Servo Motor   Waste Sensor    Alert System
             │             │          ┌────┴────┐
             ▼             ▼          ▼         ▼
        Automatic Lid   Fill Level   LED      Buzzer
                           │
                           ▼
                    Fill Percentage
```

### Inputs

* Object/hand distance
* Waste-level distance

### Processing

* Read sensor values
* Compare detection threshold
* Control servo
* Calculate fill percentage
* Compare fill threshold
* Generate alerts

### Outputs

* Servo position
* Lid status
* Fill percentage
* LED status
* Buzzer status

The input-processing-output architecture follows the project specification.

---

## 9. Circuit Connections

The project documentation specifies the following example ESP32 connections for the ultrasonic sensor, servo, and alert system.

### Ultrasonic Sensor

```text
HC-SR04 VCC   → ESP32 power
HC-SR04 GND   → ESP32 GND
HC-SR04 TRIG  → ESP32 GPIO
HC-SR04 ECHO  → ESP32 GPIO
```

### Servo Motor

```text
Servo VCC     → 5V power
Servo GND     → GND
Servo Signal  → ESP32 GPIO
```

### Buzzer

```text
Buzzer +      → ESP32 GPIO
Buzzer -      → GND
```

### LED

```text
ESP32 GPIO → Resistor → LED Anode
LED Cathode → GND
```

For a real ESP32 circuit, ensure that sensor signal voltage and power connections are appropriate for the specific hardware being used.

---

## 10. Project Folder Structure

```text
SMART-DUSTBIN/
│
├── .pio/
├── .vscode/
│
├── arduino_code/
│   ├── libraries.txt
│   └── smart_dustbin.ino
│
├── circuit_diagram/
│
├── data/
│   ├── bin_level_data.csv
│   ├── sensor_readings.csv
│   └── test_data.csv
│
├── docs/
│
├── include/
│   └── README
│
├── lib/
│
├── outputs/
│   ├── serial_monitor.txt
│   └── test_results.csv
│
├── reports/
│
├── screenshots/
│
├── simulation/
│   └── libraries.txt
│
├── src/
│   └── main.cpp
│
├── test/
│   └── README
│
├── .gitignore
├── diagram.json
├── platformio.ini
├── README.md
└── wokwi.toml

This follows the folder structure specified in the project document.

---

## 11. Installation

### Software

Install:

1. Arduino IDE
2. ESP32 board support
3. Required libraries for the selected implementation
4. Wokwi account/browser access for virtual simulation

The original project specification identifies Arduino IDE as the development environment and lists libraries for sensor, servo, and ESP32 functionality.

### Hardware

For a physical implementation, prepare:

* ESP32
* Ultrasonic sensor(s)
* Servo motor
* Buzzer
* LEDs
* Resistors
* Breadboard
* Jumper wires
* Suitable power supply

---

## 12. Wokwi Simulation

The project can be tested virtually before building the physical circuit.

### Steps

1. Create an ESP32 project in Wokwi.
2. Add the required ultrasonic sensors.
3. Add the servo motor.
4. Add red and green LEDs.
5. Add the buzzer.
6. Connect the components.
7. Add the project source code.
8. Configure `wokwi.toml`.
9. Start the simulation.
10. Change the simulated sensor distance.
11. Verify automatic lid operation.
12. Test different waste levels.
13. Verify the full-bin alert.
14. Record the Serial Monitor output.
15. Capture screenshots for the repository.

The project specification describes this simulation workflow and specifically calls for testing different fill levels.

---

## 13. Wokwi Configuration

The Wokwi configuration should use the correct field names:

```toml
[wokwi]
version = 1

[build]
firmware = '../src/smart_dustbin.ino'
elf = '../build/smart_dustbin.elf'
```

The `firmware` and `elf` fields must contain string paths.

---

## 14. How to Run

### Virtual Simulation

```text
1. Open the Wokwi project.
2. Verify the circuit.
3. Verify the source code.
4. Verify wokwi.toml.
5. Start the simulation.
6. Open the Serial Monitor.
7. Change the object sensor distance.
8. Observe the servo.
9. Change the waste-level sensor distance.
10. Observe the calculated fill percentage.
11. Test the full-bin threshold.
12. Verify LED and buzzer alerts.
```

### Physical Hardware

```text
1. Assemble the circuit.
2. Connect the ESP32 to the computer.
3. Open Arduino IDE.
4. Select the ESP32 board.
5. Select the correct COM port.
6. Compile the program.
7. Upload the program.
8. Open Serial Monitor.
9. Test object detection.
10. Test the servo.
11. Test waste-level measurement.
12. Test LED/buzzer alerts.
```

The original project documentation provides the same general hardware and simulation execution sequence.

---

## 15. Bin-Level Formula

Let:

* `H` = total usable bin height
* `D` = measured distance from sensor to waste

Then:

```text
Fill Level = H - D
```

and:

```text
Fill Percentage = (Fill Level / H) × 100
```

### Example

If:

```text
Bin Height = 40 cm
Measured Distance = 20 cm
```

Then:

```text
Fill Level = 40 - 20
           = 20 cm

Fill Percentage = (20 / 40) × 100
                 = 50%
```

### Example table

| Waste Level | Approx. Sensor Distance* |  Fill |
| ----------- | -----------------------: | ----: |
| Empty       |                    40 cm |    0% |
| 25%         |                    30 cm |   25% |
| 50%         |                    20 cm |   50% |
| 75%         |                    10 cm |   75% |
| 90%         |                     4 cm |   90% |
| Full        |                Near 0 cm | ~100% |

*These are example values for a 40 cm bin. Replace them with your actual calibrated simulation/hardware readings.

---

## 16. Automatic Lid Operation

The automatic lid follows this logic:

```text
Object detected?
      │
   ┌──┴──┐
   │     │
  YES    NO
   │     │
   ▼     ▼
Open    Keep
lid     closed
   │
   ▼
Wait
   │
   ▼
Close lid
```

The project specification describes the ultrasonic sensor detecting an approaching object and the servo opening and subsequently closing the lid.

---

## 17. Full-Bin Alert

The system compares the calculated fill percentage with a configured threshold.

Example:

```text
Fill < threshold
      ↓
Normal
Green LED ON
Buzzer OFF

Fill >= threshold
      ↓
FULL
Red LED ON
Buzzer ON
```

The project documentation describes a threshold-based full-bin alert using the red LED and buzzer.

---

## 18. Screenshots

Add your actual screenshots here.

Recommended images:

```text
screenshots/
├── 01_wokwi_circuit.png
├── 02_code.png
├── 03_lid_closed.png
├── 04_hand_detected.png
├── 05_lid_open.png
├── 06_25_percent.png
├── 07_50_percent.png
├── 08_75_percent.png
├── 09_90_percent.png
├── 10_full_bin.png
├── 11_alert.png
└── 12_serial_monitor.png
```

In this README, you can later add:

```markdown
![Wokwi Circuit](screenshots/01_wokwi_circuit.png)

![Automatic Lid](screenshots/05_lid_open.png)

![Full Bin Alert](screenshots/11_alert.png)

![Serial Monitor](screenshots/12_serial_monitor.png)
```

Only add screenshots after you have actually captured them.

---

## 19. Test Results

The system should be tested under different conditions.

| Test | Condition              | Expected Result     | Status    |
| ---- | ---------------------- | ------------------- | --------- |
| 1    | No object              | Lid remains closed  | PASS/FAIL |
| 2    | Hand detected          | Lid opens           | PASS/FAIL |
| 3    | After delay            | Lid closes          | PASS/FAIL |
| 4    | Empty bin              | Normal status       | PASS/FAIL |
| 5    | 50% bin                | Normal status       | PASS/FAIL |
| 6    | 75% bin                | Normal status       | PASS/FAIL |
| 7    | 90% bin                | Full warning        | PASS/FAIL |
| 8    | Full bin               | Red LED + buzzer    | PASS/FAIL |
| 9    | Invalid sensor reading | Safe handling       | PASS/FAIL |
| 10   | Repeated detection     | Stable lid behavior | PASS/FAIL |

The test cases are based on the testing requirements specified in the project document.

**Replace PASS/FAIL with your actual results after running the simulation.**

---

## 20. Results

The final results should document:

* Whether object detection worked
* Whether the servo opened the lid
* Whether the servo closed the lid
* Whether waste-level measurement worked
* Whether fill percentage was calculated correctly
* Whether the full-bin threshold worked
* Whether the red LED activated
* Whether the buzzer activated
* Whether Serial Monitor output was correct

Do not claim successful results until the corresponding tests have actually been performed.

---

## 21. Future Improvements

Possible future improvements include:

* ESP32 Wi-Fi monitoring
* Blynk mobile application
* Cloud dashboard
* Remote notifications
* Multiple smart-dustbin monitoring
* GPS-based bin location
* Waste-type classification
* Camera-based waste detection
* Solar-powered operation
* Battery monitoring
* Automatic collection-route optimization
* Historical waste-level data
* Predictive maintenance

The uploaded project document also proposes Wi-Fi, Blynk, cloud monitoring, GPS, multiple-bin monitoring, waste classification and solar-powered operation as possible extensions.

---

## 22. Learning Outcomes

Through this project, I learned:

* Embedded C/C++ programming
* ESP32 microcontroller programming
* GPIO configuration
* Ultrasonic sensor interfacing
* Distance measurement
* Servo motor control
* PWM concepts
* LED and buzzer control
* Threshold-based control logic
* Sensor calibration
* Serial debugging
* Virtual hardware simulation
* Embedded-system testing
* Git and GitHub project organization
* Technical documentation

The project demonstrates practical embedded-system concepts rather than only theoretical knowledge.

---

## 23. Limitations

The prototype has several limitations:

* Ultrasonic readings can be affected by irregular waste surfaces.
* Sensor readings may contain noise.
* The fill percentage depends on correct bin-height calibration.
* Physical servo loading may differ from simulation.
* Wi-Fi/cloud functionality is optional and requires additional configuration.
* Real-world deployment requires appropriate power and mechanical protection.

These limitations should be considered when moving from simulation to physical implementation.

---

## 24. Project Development

The project can be developed in stages:

```text
Day 1 → Project setup
Day 2 → Ultrasonic sensor
Day 3 → Servo and automatic lid
Day 4 → Waste-level detection
Day 5 → LED and buzzer
Day 6 → System integration
Day 7 → Wokwi simulation and testing
Day 8 → Documentation and GitHub
```

This follows the development/proof-building plan described in the project document.

---

## 25. Conclusion

The Smart Dustbin project demonstrates how an embedded microcontroller can combine sensors, actuators, and decision-making logic to automate a common waste-management task.

The system provides:

* Touchless lid operation
* Waste-level monitoring
* Fill-level calculation
* Full-bin alerts
* Embedded sensor/actuator integration
* Virtual simulation capability

The project provides a beginner-friendly foundation that can later be extended into a connected IoT waste-management system.

---

## 26. Author

**Name:** Kishan GK

**Project:** Smart Dustbin – Industry-Oriented Embedded System

**Domain:** Embedded Systems

**Platform:** ESP32 / Arduino

**Simulation:** Wokwi

**Repository:** `Smart-Dustbin-Embedded-System`

---
