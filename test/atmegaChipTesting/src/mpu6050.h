#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>

class MPU6050 {
    public:
        MPU6050();

        void setup();

        void readData();

        int16_t getAccelerationX();

        int16_t getAccelerationY();

        int16_t getAccelerationZ();

        double getTemperature();

        int16_t getGyroscopeX();

        int16_t getGyroscopeY();

        int16_t getGyroscopeZ();

        double calculatePitch();
        
        double calculateRoll();

        double calculateYaw();

    private:
        const int MPU_ADDR = 0x68;
        int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
};

#endif