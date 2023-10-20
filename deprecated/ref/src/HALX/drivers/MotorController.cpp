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

#include "MotorController.h"

MotorController::MotorController(int pin) {
  throttlePin = pin;
}

void MotorController::begin() {
  esc.attach(throttlePin);  // Attach the ESC control signal to the specified pin
}

void MotorController::setThrottle(int throttleValue) {
  int mappedValue = map(throttleValue, 0, 180, 1000, 2000);  // Map throttle value to pulse width range
  esc.writeMicroseconds(mappedValue);  // Set the motor speed by adjusting the pulse width
  Serial.println(mappedValue);
}

void MotorController::stop() {
  esc.writeMicroseconds(1500);  // Stop the motor (neutral position)
}

int MotorController::map(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
  // Check if the value is within the input range
  if (value <= fromLow) {
    return toLow;
  }
  else if (value >= fromHigh) {
    return toHigh;
  }
  
  // Calculate the scaled value
  long mappedValue = (long)(value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
  
  // Return the mapped value as an integer
  return (int)mappedValue;
}