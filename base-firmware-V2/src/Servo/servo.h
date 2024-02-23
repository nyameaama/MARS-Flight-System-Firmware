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

#ifndef _SERVO_H
#define _SERVO_H

#include <cstdint>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include "drivers/nrf_servo.h"

#define SPEED_DEFAULT 1
#define SPEED_FAST 20

#define SERVO_FL 32
#define SERVO_FR 33
#define SERVO_RL 26
#define SERVO_RR 27

//____________________________________________________________
/* Utillity subroutine -> linear interpolation method
===========================================================================
===========================================================================
*/
static double linearInterpolate(double input, double input_start, double input_end,
                                    double output_start, double output_end);

//____________________________________________________________
/* Initializes Servo
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
static void actuateServo(double targetPos, uint8_t pin);

//____________________________________________________________
/* Main API routine
===========================================================================
|    motor target angle   The motor rotation angle bounded between 0 deg to 90 deg
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
static uint8_t servo_control(double angle, uint8_t pin);

//____________________________________________________________
/* Utillity subroutine -> retrieve current motor position
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
static uint8_t GET_SERVO_POS(uint8_t pin);

//____________________________________________________________
/* Utillity subroutine -> update current motor position after movement change
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
|    updated servo position      New motor position to be updated
===========================================================================
*/
static void UPDATE_SERVO_POS(uint8_t pin, uint8_t updatedValue);


#endif  //_SERVO_H