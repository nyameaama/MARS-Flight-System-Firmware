#include<Arduino.h>
#include"drivers/_motors.h"
#include"drivers/MotorController.h"
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

#include <iostream>
#include "StringParser.h"

#define THROTTLE_PIN 2

MotorController motor(THROTTLE_PIN);

void setup(){
    Serial.begin(9600);
    motor.begin();
}

void loop(){
    ServoController *mov = new ServoController();

    std::string values[] = {"MOTOR-FL", "MOTOR-FR", "MOTOR-RR", "MOTOR-RL", "IMU", "GPS", "THROTTLE"};
    std::string input = "MOTOR-FL:90";

    StringParser parser(input);
    parser.parse();

    std::string extractedString = parser.getExtractedString();
    int extractedNumber = parser.getExtractedNumber();
    if(extractedString == values[0]){
        mov -> moveToAngleFL(extractedNumber);
    }
    if(extractedString == values[1]){
        mov -> moveToAngleFR(extractedNumber);
    }
    if(extractedString == values[2]){
        mov -> moveToAngleRR(extractedNumber);
    }
    if(extractedString == values[3]){
        mov -> moveToAngleRL(extractedNumber);
    }
    if(extractedString == values[4]){

    }
    if(extractedString == values[5]){

    }
    if(extractedString == values[6]){
        motor.setThrottle(extractedNumber);
    }
    delete mov;
}