/**
 * @file VBV.hpp
 * @brief Vehicle-boot up sensor subsystem(VBV) prototypes
 *
 *
 * @date October 19th, 2023
 * @copyright Copyright (c) 2023 limitless Aeronautics
 *
 * @author Lukas Jackson
 *
 * @license MIT License
 *          Copyright (c) 2023 limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */

#ifndef VBV_HPP
#define VBV_HPP

#include "../statemachine/_ptam.h"
#include "../Logging/logger.hpp"


#define ALT_LIMIT               12001.0  // Altitude limit in feet

#define LATITUDE_THRESHOLD      90.0     // Latitude threshold in degrees
#define LONGITUDE_THRESHOLD     180.0    // Longitude threshold in degrees

#define PITCH_THRESHOLD         90.0     // Pitch threshold in degrees

#define ROLL_THRESHOLD          180.0    // Roll threshold in degrees

#define LOWER_PASCAL_THRES      101325   // Lower pressure threshold in pascals
#define HIGHER_PASCAL_THRES     97716.57 // Higher pressure threshold in pascals


class VBV: public SharedMemory
{
    /**
     * @brief Returns a bool depending if sensors are operating correctly
     *
     * @return true
     * @return false
     */
    static bool validate_reg_data();

    /**
     * @brief Validates Altitude sensor data
     *
     * @return uint8_t
     */
    static uint8_t alt_sensor_check(double sensor_data);

    /**
     * @brief Validates Latitude sensor data
     *
     * @return uint8_t
     */
    static uint8_t lat_sensor_check(double sensor_data);

    /**
     * @brief Validates Longitude sensor data
     *
     * @return uint8_t
     */
    static uint8_t lon_sensor_check(double sensor_data);

    /**
     * @brief Validates Velocity sensor data
     *
     * @return uint8_t
     */
    static uint8_t vel_sensor_check(double sensor_data);

    /**
     * @brief Validates Pitch sensor data
     *
     * @return uint8_t
     */
    static uint8_t pit_sensor_check(double sensor_data);

    /**
     * @brief Validates Roll sensor data
     *
     * @return uint8_t
     */
    static uint8_t roll_sensor_check(double sensor_data);

    /**
     * @brief Validates Yaw sensor data
     *
     * @return uint8_t
     */
    static uint8_t yaw_sensor_check(double sensor_data);

    /**
     * @brief Validates Temperature sensor data
     *
     * @return uint8_t
     */
    static uint8_t temp_sensor_check(double sensor_data);

    /**
     * @brief Validates Pressure sensor data
     *
     * @return uint8_t
     */
    static uint8_t pres_sensor_check(double sensor_data);
};


#endif /* VBV_HPP */