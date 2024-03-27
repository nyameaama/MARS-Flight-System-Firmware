/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef BMI_IMU
#define BMI_IMU

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include "bmi270.h"
#include "bmi270_config_file.h"

#define PITCH (uint8_t)0
#define ROLL (uint8_t)1
#define YAW (uint8_t)2

/**
 * @brief Initializes the BMI270 sensor.
 * 
 * Sets up the BMI270 sensor for reading accelerometer and gyroscope
 * data, including configuring registers and setting default states.
 */
static void bmi270_init();

/**
 * @brief Reads raw X-axis acceleration data from BMI270.
 * 
 * @return double Returns the raw X-axis acceleration value.
 */
static double bmi270_read_accel_rawX();

/**
 * @brief Reads raw Y-axis acceleration data from BMI270.
 * 
 * @return double Returns the raw Y-axis acceleration value.
 */
static double bmi270_read_accel_rawY();

/**
 * @brief Reads raw Z-axis acceleration data from BMI270.
 * 
 * @return double Returns the raw Z-axis acceleration value.
 */
static double bmi270_read_accel_rawZ();

/**
 * @brief Reads raw X-axis gyroscope data from BMI270.
 * 
 * @return double Returns the raw X-axis gyroscope value.
 */
static double bmi270_read_gyro_rawX();

/**
 * @brief Reads raw Y-axis gyroscope data from BMI270.
 * 
 * @return double Returns the raw Y-axis gyroscope value.
 */
static double bmi270_read_gyro_rawY();

/**
 * @brief Reads raw Z-axis gyroscope data from BMI270.
 * 
 * @return double Returns the raw Z-axis gyroscope value.
 */
static double bmi270_read_gyro_rawZ();

#endif  // BMI_IMU
