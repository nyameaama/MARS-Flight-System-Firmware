#ifndef SENSOR_VALIDATOR_HPP
#define SENSOR_VALIDATOR_HPP

#include <iostream>
#include <string>

#include"../../util/defi.h"

class SensorValidator {
    public:
        bool validateGPSData();

        bool validateIMUData();
        
        bool validateBMP280Data();
};

#endif // SENSOR_VALIDATOR_HPP