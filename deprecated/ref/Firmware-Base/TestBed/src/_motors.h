#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include<Arduino.h>
#include <Servo.h>

class ServoController {
    public:
        ServoController();
    public:
        void moveToAngleFL(int angle);
        void moveToAngleFR(int angle);
        void moveToAngleRL(int angle);
        void moveToAngleRR(int angle);

private:
    Servo servo_1;
    Servo servo_2; // servo controller (multiple can exist)
    Servo servo_3; // servo controller (multiple can exist)
    Servo servo_4; // servo controller (multiple can exist)

    int servo_pin1 = 3; // PWM pin for servo control
    int servo_pin2 = 2;
    int servo_pin3 = 6;
    int servo_pin4 = 5;
};

#endif  // SERVOCONTROLLER_H