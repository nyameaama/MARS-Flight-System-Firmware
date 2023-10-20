#include "mpu6050.h"
#include <Arduino.h>

MPU6050::MPU6050(){
    setup();
}

void MPU6050::setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void MPU6050::readData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers

  AcX = Wire.read() << 8 | Wire.read(); // combine high and low bytes for X-axis acceleration
  AcY = Wire.read() << 8 | Wire.read(); // combine high and low bytes for Y-axis acceleration
  AcZ = Wire.read() << 8 | Wire.read(); // combine high and low bytes for Z-axis acceleration

  Tmp = Wire.read() << 8 | Wire.read(); // combine high and low bytes for temperature

  GyX = Wire.read() << 8 | Wire.read(); // combine high and low bytes for X-axis gyroscope
  GyY = Wire.read() << 8 | Wire.read(); // combine high and low bytes for Y-axis gyroscope
  GyZ = Wire.read() << 8 | Wire.read(); // combine high and low bytes for Z-axis gyroscope
}

int16_t MPU6050::getAccelerationX() {
  return AcX;
}

int16_t MPU6050::getAccelerationY() {
  return AcY;
}

int16_t MPU6050::getAccelerationZ() {
  return AcZ;
}

double MPU6050::getTemperature() {
  return Tmp / 340.00 + 36.53;
}

int16_t MPU6050::getGyroscopeX() {
  return GyX;
}

int16_t MPU6050::getGyroscopeY() {
  return GyY;
}

int16_t MPU6050::getGyroscopeZ() {
  return GyZ;
}

double MPU6050::calculatePitch() {
  double pitch = atan2(AcY, sqrt(AcX * AcX + AcZ * AcZ)) * (180.0 / PI);
  return pitch;
}

double MPU6050::calculateRoll() {
  double roll = atan2(-AcX, AcZ) * (180.0 / PI);
  return roll;
}

double MPU6050::calculateYaw() {
  double yaw = atan2(GyX, sqrt(GyY * GyY + GyZ * GyZ)) * (180.0 / PI);
  return yaw;
}

