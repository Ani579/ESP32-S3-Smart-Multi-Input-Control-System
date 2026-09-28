# ESP32-S3 Smart Multi-Input Control System

![IoT](https://img.shields.io/badge/IoT-Project-blue?style=for-the-badge)
![Arduino](https://img.shields.io/badge/Arduino-C++-lightblue?style=for-the-badge)

A compact embedded control and human-machine interface project built using the **ESP32-S3**, featuring **dual analog joysticks, a potentiometer, and an I2C LCD display**.

The system demonstrates real-time analog input acquisition, digital button detection, ADC-based voltage measurement, I2C communication, and display of sensor/control data. It can serve as a foundation for advanced applications such as robotic controllers, gaming interfaces, wireless control systems, and smart audio control panels.

---

## Project Overview

The **ESP32-S3 Smart Multi-Input Control System** is designed to demonstrate how multiple input devices can be interfaced with an ESP32-S3 microcontroller.

Two joystick modules provide independent X-axis and Y-axis analog inputs along with push-button functionality. A potentiometer provides an additional variable analog input. The ESP32-S3 processes these inputs and displays the collected data on a **16×2 I2C LCD** while simultaneously transmitting the values to the Serial Monitor.

The project provides a practical introduction to **ADC, GPIO, I2C, analog input processing, and embedded-system interfacing**.

---

## Features

* Dual analog joystick interface
* Four independent analog joystick axes
* Two joystick push buttons
* One analog potentiometer input
* 12-bit ADC measurement
* Approximate potentiometer voltage calculation
* Potentiometer percentage calculation
* 16×2 I2C LCD display
* Real-time Serial Monitor output
* ESP32-S3 based control architecture
* Expandable for robotics, IoT, gaming, and audio applications

---

## Hardware Requirements

| Component                  |    Quantity |
| -------------------------- | ----------: |
| ESP32-S3 Development Board |           1 |
| Analog Joystick Module     |           2 |
| 10KΩ Potentiometer         |           1 |
| 16×2 I2C LCD               |           1 |
| Jumper Wires               | As required |
| Breadboard                 |           1 |
| USB Cable                  |           1 |

---

## Pin Configuration

### Joystick 1

| Joystick Pin | ESP32-S3 GPIO | Function            |
| ------------ | ------------: | ------------------- |
| VRx          |        GPIO 1 | X-axis Analog Input |
| VRy          |        GPIO 2 | Y-axis Analog Input |
| SW           |        GPIO 3 | Push Button         |
| VCC          |          3.3V | Power               |
| GND          |           GND | Ground              |

### Joystick 2

| Joystick Pin | ESP32-S3 GPIO | Function            |
| ------------ | ------------: | ------------------- |
| VRx          |        GPIO 4 | X-axis Analog Input |
| VRy          |        GPIO 5 | Y-axis Analog Input |
| SW           |        GPIO 6 | Push Button         |
| VCC          |          3.3V | Power               |
| GND          |           GND | Ground              |

### Potentiometer

| Potentiometer Pin  | ESP32-S3 |
| ------------------ | -------- |
| Outer Pin 1        | 3.3V     |
| Wiper / Middle Pin | GPIO 7   |
| Outer Pin 3        | GND      |

The potentiometer acts as a variable voltage divider. Its wiper voltage is read by the ESP32-S3 ADC.

### I2C LCD

| LCD Pin | ESP32-S3 |
| ------- | -------: |
| SDA     |   GPIO 8 |
| SCL     |   GPIO 9 |
| VCC     |     3.3V |
| GND     |      GND |

The LCD commonly uses the I2C address **0x27**. Some modules may use **0x3F**.

---

## System Architecture

```text
                    ESP32-S3
                       │
        ┌──────────────┼──────────────┐
        │              │              │
        ▼              ▼              ▼
   Joystick 1     Joystick 2    Potentiometer
    X / Y / SW     X / Y / SW      Analog
        │              │              │
        └──────────────┼──────────────┘
                       │
                       ▼
                 ADC / GPIO
                       │
                       ▼
                Data Processing
                       │
              ┌────────┴────────┐
              │                 │
              ▼                 ▼
          I2C LCD          Serial Monitor
```

---

## Working Principle

The two joystick modules contain potentiometric mechanisms that generate variable analog voltages according to the position of the joystick along the X and Y axes.

The ESP32-S3 reads these analog voltages through its ADC channels. The joystick push buttons are connected to digital GPIO pins and are configured using internal pull-up resistors.

The potentiometer produces another variable voltage between approximately 0 V and 3.3 V. The ESP32-S3 reads this voltage through its ADC and converts the raw ADC value into an approximate voltage and percentage level.

The processed information is displayed on the 16×2 I2C LCD. The same information is also transmitted through the Serial Monitor at 115200 baud for debugging and monitoring.

---

## ADC Measurement

The ESP32-S3 is configured for **12-bit ADC resolution**.

Therefore:

```text
ADC Range = 0 to 4095
```

Approximate relationship:

```text
0 V       → 0
1.65 V    → 2048
3.3 V     → 4095
```

The potentiometer voltage is calculated using:

```text
Voltage = (ADC Value / 4095) × 3.3
```

The potentiometer level is mapped to:

```text
0% → 0
100% → 4095
```

---

## LCD Display

The LCD cycles through information from the different input devices.

### Joystick 1

```text
J1 X:2048 Y:2035
SW:OPEN     J2
```

### Joystick 2

```text
J2 X:2050 Y:2010
SW:OPEN
```

### Potentiometer

```text
POT:52%
V:1.72V
```

---

## Software Requirements

* Arduino IDE
* ESP32 board package
* LiquidCrystal_I2C library

### Required Library

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

Select the appropriate **ESP32-S3 development board** from:

```text
Arduino IDE
→ Tools
→ Board
→ ESP32 Arduino
→ ESP32-S3 Board
```

---

## Project Pin Summary

| Device        | GPIO   |
| ------------- | ------ |
| Joystick 1 X  | GPIO 1 |
| Joystick 1 Y  | GPIO 2 |
| Joystick 1 SW | GPIO 3 |
| Joystick 2 X  | GPIO 4 |
| Joystick 2 Y  | GPIO 5 |
| Joystick 2 SW | GPIO 6 |
| Potentiometer | GPIO 7 |
| LCD SDA       | GPIO 8 |
| LCD SCL       | GPIO 9 |

---

## Applications

This project can be extended into:

* Robotic control systems
* Wireless joystick controllers
* RC vehicle controllers
* Gaming controllers
* Drone control interfaces
* Smart music control systems
* IoT control panels
* Human-machine interfaces
* Embedded navigation systems
* ESP32-based automation systems

---

## Future Improvements

The current system can be expanded by adding:

* Bluetooth joystick control
* Wi-Fi based remote control
* Motor control
* Servo control
* Wireless robotic vehicle control
* OLED graphical interface
* RGB status indicators
* Battery monitoring
* Web-based control dashboard
* Audio/music control functionality
* Multiple control modes
* Custom joystick calibration
* Dead-zone implementation
* EEPROM-based configuration storage

---

## Project Structure

```text
ESP32-S3-Smart-Multi-Input-Control-System/
│
├── ESP32_S3_Joystick_Controller.ino
├── README.md
└── images/
    ├── circuit.jpg
    ├── prototype.jpg
    └── lcd-display.jpg
```

---

## Author

**Aniruddha Chakraborty**

Electronics & Communication Engineering

---

## License

This project is open-source and intended for educational, experimental, and personal development purposes.
