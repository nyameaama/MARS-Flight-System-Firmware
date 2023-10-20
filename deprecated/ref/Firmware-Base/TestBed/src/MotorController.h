#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Servo.h>
#include<Arduino.h>

class MotorController {
private:
  Servo esc;  // Create a Servo object
  int throttlePin;  // Digital pin connected to ESC control signal
private:
  int map(int value, int fromLow, int fromHigh, int toLow, int toHigh);

public:
  MotorController(int pin);
  void begin();
  void setThrottle(int throttleValue);
  void stop();
};

#endif