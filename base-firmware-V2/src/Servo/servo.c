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

#include "servo.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define ServoMsMin 0.06
#define ServoMsMax 2.1
#define ServoMsAvg ((ServoMsMax-ServoMsMin)/2.0)

uint8_t SERVO_POS_1 = 0;

uint8_t SERVO_POS_2 = 0;

uint8_t SERVO_POS_3 = 0;

uint8_t SERVO_POS_4 = 0;

//____________________________________________________________
/* Utillity subroutine -> linear interpolation method
===========================================================================
===========================================================================
*/
double linearInterpolate(double input, double input_start, double input_end, 
                                        double output_start, double output_end) {
    // Map input range to output range
    double slope = (output_end - output_start) / (input_end - input_start);
    double output = output_start + slope * (input - input_start);
    return output;
}

//____________________________________________________________
/* Initializes Servo 
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
void actuateServo(double targetPos, uint8_t pin) {
    
}

//____________________________________________________________
/* Main API routine
===========================================================================
|    motor target angle   The motor rotation angle bounded between 0 deg to 90 deg
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
uint8_t servo_control(double target, uint8_t pin){
    //Map target in the 0 - 360 range to ServoMsMin and ServoMsMax
    double mapped_target = linearInterpolate(target, 0, 360, ServoMsMin, ServoMsMax);
    actuateServo(mapped_target, pin);
    UPDATE_SERVO_POS(pin,target);
    return mapped_target;
}

//____________________________________________________________
/* Utillity subroutine -> retrieve current motor position 
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
uint8_t GET_SERVO_POS(uint8_t pin)
{
     switch(pin) {
        case 0:
            return SERVO_POS_1;
        break;
        case 1:
            return SERVO_POS_2;
        break;
        case 2:
            return SERVO_POS_3;
        break;
        case 3:
            return SERVO_POS_4;
        break;
    }
    return 0;
}

//____________________________________________________________
/* Utillity subroutine -> update current motor position after movement change
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
|    updated servo position      New motor position to be updated
===========================================================================
*/
void UPDATE_SERVO_POS(uint8_t pin, uint8_t updatedValue){
    switch(pin) {
        case 0:
            SERVO_POS_1 = updatedValue;
        break;
        case 1:
            SERVO_POS_2 = updatedValue;
        break;
        case 2:
            SERVO_POS_3 = updatedValue;
        break;
        case 3:
            SERVO_POS_4 = updatedValue;
        break;
    }
}