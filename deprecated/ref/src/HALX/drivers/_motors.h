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

#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include<Arduino.h>
#include <ESP32Servo.h>


class ServoController {
    public:
        uint8_t moveToAngleFL(uint8_t angle);

        uint8_t moveToAngleFR(uint8_t angle);

        uint8_t moveToAngleRL(uint8_t angle);

        uint8_t moveToAngleRR(uint8_t angle);

        void setupServo();

    public:
        //FRONT LEFT
        uint8_t servo_pin1 = 3; 
        //FRONT RIGHT
        uint8_t servo_pin2 = 2;
        //REAR LEFT
        uint8_t servo_pin3 = 6;
        //REAR RIGHT
        uint8_t servo_pin4 = 5;

    public:
        uint8_t SERVO_POS_1 = 0;

        uint8_t SERVO_POS_2 = 0;

        uint8_t SERVO_POS_3 = 0;

        uint8_t SERVO_POS_4 = 0;
};

#endif  // SERVOCONTROLLER_H