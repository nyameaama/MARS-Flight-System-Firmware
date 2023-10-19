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
#include <vector>

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
     * @brief Validates GPS sensor data
     *
     * @return uint8_t
     */
    static uint8_t gps_sensor_check();

    /**
     * @brief Validates IMU sensor data
     *
     * @return uint8_t
     */
    static uint8_t imu_sensor_check();

    /**
     * @brief Validates BMP sensor data
     *
     * @return uint8_t
     */
    static uint8_t bmp_sensor_check();

    /**
     * @brief Validates Altitude sensor data
     *
     * @return uint8_t
     */
    static uint8_t alt_sensor_check();

    /**
     * @brief Validates Latitude sensor data
     *
     * @return uint8_t
     */
    static uint8_t lat_sensor_check();

    /**
     * @brief Validates Longitude sensor data
     *
     * @return uint8_t
     */
    static uint8_t lon_sensor_check();

    /**
     * @brief Validates Velocity sensor data
     *
     * @return uint8_t
     */
    static uint8_t vel_sensor_check();

    /**
     * @brief Validates Pitch sensor data
     *
     * @return uint8_t
     */
    static uint8_t pit_sensor_check();

    /**
     * @brief Validates Roll sensor data
     *
     * @return uint8_t
     */
    static uint8_t roll_sensor_check();

    /**
     * @brief Validates Yaw sensor data
     *
     * @return uint8_t
     */
    static uint8_t yaw_sensor_check();

    /**
     * @brief Validates Temperature sensor data
     *
     * @return uint8_t
     */
    static uint8_t temp_sensor_check();

    /**
     * @brief Validates Pressure sensor data
     *
     * @return uint8_t
     */
    static uint8_t pres_sensor_check();
};


#endif /* VBV_HPP */