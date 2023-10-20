#include "mpu6050.h"
#include<Arduino.h>

void setup() {
    Serial.begin(9600);
}

void loop() {
    MPU6050 *obj = new MPU6050();
    obj -> readData();

    int16_t accelerationX = obj -> getAccelerationX();
    int16_t accelerationY = obj -> getAccelerationY();
    int16_t accelerationZ = obj -> getAccelerationZ();
    double temperature = obj -> getTemperature();
    int16_t gyroscopeX = obj -> getGyroscopeX();
    int16_t gyroscopeY = obj -> getGyroscopeY();
    int16_t gyroscopeZ = obj -> getGyroscopeZ();
    double pitch = obj -> calculatePitch();
    double roll = obj -> calculateRoll();
    double yaw = obj -> calculateYaw();

    // Use the sensor data as needed
    Serial.print("Pitch ");
    Serial.println(String(pitch));
    Serial.print("Yaw ");
    Serial.println(String(yaw));
    Serial.print("Roll ");
    Serial.println(String(roll));
    delay(1000); // Delay between readings
}