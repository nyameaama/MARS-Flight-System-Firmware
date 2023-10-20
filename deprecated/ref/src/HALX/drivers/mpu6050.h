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

#ifndef MPU6050_H
#define MPU6050_H

class MPU6050 {
public:
    MPU6050();
    void initialize();
    void update();
    float getPitch();
    float getRoll();
    float getYaw();

private:
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float pitch, roll, yaw;

    float fastAtan(float x);
    float fastSqrt(float x);
};

#endif

/*
    Sample:
    #include <Wire.h>
#include "mpu.h"

MPU6050 mpu;

void setup() {
  Serial.begin(9600);

  // Initialize MPU6050
  mpu.initialize();
}

void loop() {
  // Update sensor data
  mpu.update();

  // Get pitch, roll, and yaw angles
  float pitch = mpu.getPitch();
  float roll = mpu.getRoll();
  float yaw = mpu.getYaw();

  // Print the angles
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" degrees\t");

  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print(" degrees\t");

  Serial.print("Yaw: ");
  Serial.print(yaw);
  Serial.println(" degrees");

  delay(500);  // Delay for readability
}





*/