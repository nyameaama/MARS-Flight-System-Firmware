#include "_motors.h"

ServoController::ServoController() {
  servo_1.attach(servo_pin1); // start servo control
  servo_2.attach(servo_pin2);
  servo_3.attach(servo_pin3);
  servo_4.attach(servo_pin4);
}

void ServoController::moveToAngleFL(int angle) {
  servo_1.write(angle);
  delay(15);
}

void ServoController::moveToAngleFR(int angle) {
  servo_2.write(angle);
  delay(15);
}

void ServoController::moveToAngleRL(int angle) {
  servo_3.write(angle);
  delay(15);
}

void ServoController::moveToAngleRR(int angle) {
  servo_4.write(angle);
  delay(15);
}