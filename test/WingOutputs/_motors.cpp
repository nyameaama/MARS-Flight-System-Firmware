/*MIT License

Copyright (c) 2020 Nyameaama Gambrah

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

#include "_motors.h"

uint8_t servoPos = 0;

_motors::_motors(){
    _init();
}

uint8_t _motors::adjustServoFWLEFT(uint8_t range){
    uint8_t _outPin = 0;
    //uint16_t opT = computeOptimumDelay(range - returnServoPos());
    //digitalWrite(_outPin,HIGH);
    //delay(opT);
    //PTAM *ptObject = new PTAM();
    //ptObject -> PTAM_ADD_BASE_8("SFL",range);
    //delete ptObject;
    return (1);
}

uint8_t _motors::adjustServoFWRIGHT(uint8_t range){
    uint8_t outPin = 0;
    //uint16_t opT = computeOptimumDelay(range - returnServoPos());
    //digitalWrite(outPin, HIGH);
    //delay(opT);
    //PTAM *ptObject = new PTAM();
    //ptObject -> PTAM_ADD_BASE_8("SFR",range);
    //delete ptObject;
    return (1);
}

uint8_t _motors::adjustServoRWLEFT(uint8_t range){
    uint8_t outPin = 0;
    //uint16_t opT = computeOptimumDelay(range - returnServoPos());
    //digitalWrite(outPin, HIGH);
    //delay(opT);
    //PTAM *ptObject = new PTAM();
    //ptObject -> PTAM_ADD_BASE_8("SRL",range);
    //delete ptObject;
    return (1);
}

uint8_t _motors::adjustServoRWRIGHT(uint8_t range){
    uint8_t outPin = 0;
    //uint16_t opT = computeOptimumDelay(range - returnServoPos());
    //digitalWrite(outPin, HIGH);
    //delay(opT);
    //PTAM *ptObject = new PTAM();
    //ptObject -> PTAM_ADD_BASE_8("SRR",range);
    //delete ptObject;
    return (1);
}

uint8_t _motors::mainThrottle(uint8_t range){
    //PTAM *ptObject = new PTAM();
    //ptObject -> PTAM_ADD_BASE_8("Throttle",range);
    //delete ptObject;
}

uint8_t _motors::_init(){
    //Init Pins
    uint8_t FL = 0;
    uint8_t FR = 0;
    uint8_t RL = 0;
    uint8_t RR = 0;
    //pinMode(FL,OUTPUT);
    //pinMode(FR,OUTPUT);
    //pinMode(RL,OUTPUT);
    //pinMode(RR,OUTPUT);
}

uint8_t _motors::returnServoPos(){
    return 1;
}

uint8_t _motors::computeOptimumDelay(uint8_t delta){
    uint8_t motorDrag = 0.01; 
    return motorDrag * delta;
}