#include "validateSensors.h"

bool SensorValidator::validateGPSData() {
    // Basic checks
    GPSModule *data = new GPSModule(5,3);
    double latitude = data -> getLatitude();
    double longitude = data -> getLongitude();
    double altitude = data -> getAltitude();
    double velocity = data -> getVelocity();

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
    delete data;
    return true;
}

bool SensorValidator::validateIMUData() {
    MPU6050 *data = new MPU6050();
    double pitch = data -> getPitch();
    double roll = data -> getRoll();
    double yaw = data -> getYaw();

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

    delete data;
    return true;
}

bool SensorValidator::validateBMP280Data() {
    double temperature;
    double pressure;
    double altitude;
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