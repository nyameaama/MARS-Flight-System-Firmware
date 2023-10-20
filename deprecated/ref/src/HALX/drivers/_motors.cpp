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

#include "_motors.h"

Servo servo_1;
Servo servo_2; 
Servo servo_3; 
Servo servo_4; 

void ServoController::setupServo(){
  servo_1.attach(servo_pin1);
  servo_2.attach(servo_pin2);
  servo_3.attach(servo_pin3);
  servo_4.attach(servo_pin4);
}

uint8_t ServoController::moveToAngleFL(uint8_t angle) {
  //Hardware Check
  if(angle < 0 || angle > 180){
    return 0;
  }
  if(SERVO_POS_1 != angle){
    if(angle < SERVO_POS_1){
      for (uint8_t pos = SERVO_POS_1; pos >= angle; pos -= 1) { 
        // in steps of 1 degree
        servo_1.write(pos);           
        delay(10); 
      }
      SERVO_POS_1 = angle;
    }
    if(angle > SERVO_POS_1){
      for (uint8_t pos = SERVO_POS_1; pos <= angle; pos += 1) { 
        // in steps of 1 degree
        servo_1.write(pos);             
        delay(10);
      }
      SERVO_POS_1 = angle;
    }
  }
  return angle;
}

uint8_t ServoController::moveToAngleFR(uint8_t angle) {
  //Hardware Check
  if(angle < 0 || angle > 180){
    return 0;
  }
  if(SERVO_POS_2 != angle){
    if(angle < SERVO_POS_2){
      for (uint8_t pos = SERVO_POS_2; pos >= angle; pos -= 1) { 
        // in steps of 1 degree
        servo_2.write(pos);           
        delay(10); 
      }
      SERVO_POS_2 = angle;
    }
    if(angle > SERVO_POS_2){
      for (uint8_t pos = SERVO_POS_2; pos <= angle; pos += 1) { 
        // in steps of 1 degree
        servo_2.write(pos);             
        delay(10);
      }
      SERVO_POS_2 = angle;
    }
  }
  return angle;
}

uint8_t ServoController::moveToAngleRL(uint8_t angle) {
  //Hardware Check
  if(angle < 0 || angle > 180){
    return 0;
  }
  if(SERVO_POS_3 != angle){
    if(angle < SERVO_POS_3){
      for (uint8_t pos = SERVO_POS_3; pos >= angle; pos -= 1) { 
        // in steps of 1 degree
        servo_3.write(pos);           
        delay(10); 
      }
      SERVO_POS_3 = angle;
    }
    if(angle > SERVO_POS_3){
      for (uint8_t pos = SERVO_POS_3; pos <= angle; pos += 1) { 
        // in steps of 1 degree
        servo_3.write(pos);             
        delay(10);
      }
      SERVO_POS_3 = angle;
    }
  }
  return angle;
}

uint8_t ServoController::moveToAngleRR(uint8_t angle) {
  //Hardware Check
  if(angle < 0 || angle > 180){
    return 0;
  }
  if(SERVO_POS_4 != angle){
    if(angle < SERVO_POS_4){
      for (uint8_t pos = SERVO_POS_4; pos >= angle; pos -= 1) { 
        // in steps of 1 degree
        servo_4.write(pos);           
        delay(10); 
      }
      SERVO_POS_4 = angle;
    }
    if(angle > SERVO_POS_4){
      for (uint8_t pos = SERVO_POS_4; pos <= angle; pos += 1) { 
        // in steps of 1 degree
        servo_4.write(pos);             
        delay(10);
      }
      SERVO_POS_4 = angle;
    }
  }
  return angle;
}