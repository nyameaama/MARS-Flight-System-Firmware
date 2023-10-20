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