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

#include "validateSensors.h"

bool SensorValidator::validateGPSData() {
    // Basic checks
    double latitude = 5;
    double longitude = 5;
    double altitude = 5;
    double velocity = 5;

    if (latitude < -90.0 || latitude > 90.0) {
        return false;
    }

    if (longitude < -180.0 || longitude > 180.0) {
        return false;
    }

    if (velocity < 0.0) {
        return false;
    }

    if (altitude < -1000.0 || altitude > 10000.0) {
        return false;
    }

    // Additional validation logic for GPS data
    return true;
}

bool SensorValidator::validateIMUData() {
    double pitch = 5;
    double roll = 5;
    double yaw = 5;

    // Basic checks
    if (pitch < -90.0 || pitch > 90.0) {
        return false;
    }

    if (roll < -180.0 || roll > 180.0) {
        return false;
    }

    if (yaw < -180.0 || yaw > 180.0) {
        return false;
    }

    return true;
}

bool SensorValidator::validateBMP280Data() {
    double temperature = 5;
    double pressure = 5;
    double altitude = 5;
    // Basic checks
    if (temperature < -40.0 || temperature > 85.0) {
        return false;
    }

    if (pressure < 300.0 || pressure > 1100.0) {
        return false;
    }

    if (altitude < -1000.0 || altitude > 10000.0) {
        return false;
    }

    return true;
}
