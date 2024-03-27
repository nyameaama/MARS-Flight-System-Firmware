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

static void bmi270_init();

static double bmi270_read_accel_rawX();

static double bmi270_read_accel_rawY();

static double bmi270_read_accel_rawZ();

static double bmi270_read_gyro_rawX();

static double bmi270_read_gyro_rawY();

static double bmi270_read_gyro_rawZ();

static double linearInterpolate(double input, double input_start, double input_end,
                                double output_start, double output_end);

static double readAugmentedIMUData(uint8_t angle_type);

#endif  // BMI_IMU
