| Supported Targets | ESP32 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- |

# I2C driver for BM1088

## Overview

This I2C driver demonstrates  how to interface with BM1088 Module.

## How to use example

### Hardware Required

To run this example, you should have one ESP32, ESP32-S, ESP32-C or ESP32-H based development board as well as a BM1088. BM1088 is a inertial measurement unit, which contains a accelerometer and gyroscope , for more information about it, you can read the [datasheet of the BM1088 sensor](https://www.allaboutcircuits.com/electronic-components/datasheet/BMI088--Bosch-Sensortec/).

#### Pin Assignment:

**Note:** The following pin assignments are used by default, you can change these in the `menuconfig` .

|                  | SDA (21)       | SCL (22)       |
| ---------------- | -------------- | -------------- |
| ESP I2C Master   | I2C_MASTER_SDA | I2C_MASTER_SCL |
| BM1088  Sensor   | SDA            | SCL            |


For the actual default value of `I2C_MASTER_SDA` and `I2C_MASTER_SCL` see `Example Configuration` in `menuconfig`.

**Note:** There's no need to add an external pull-up resistors for SDA/SCL pin, because the driver will enable the internal pull-up resistors.

**Note:**  
Accelerometer Pin Configuration: 
SD01 pin pulled to 'GND'.

Gyroscope Pin Configuration: 
SD02 pin pulled to 'GND'.   

Connect PS = 'VDDI0' for I2C interface
BM1088 Data sheet 

### Build and Flash

Enter `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Driver Output

You will recieve Yaw, Roll, and pitch values as an output Information LOG

## Troubleshooting

(For any technical queries, please open an [issue](https://github.com/espressif/esp-idf/issues) on GitHub. We will get back to you as soon as possible.)
