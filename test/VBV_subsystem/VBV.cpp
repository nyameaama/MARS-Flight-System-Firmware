/**
 * @file VBV.cpp
 * @brief Vehicle-boot up sensor subsystem(VBV) definitions
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

#include "VBV.hpp"

bool VBV::validate_reg_data()
{

}


/**
 * @brief Pass sensor data to verify altitude data
 *
 * This function takes sensor data as a parameter and compares it to ALT_LIMIT
 * to verify if it is within the 5000 feet threshold.
 *
 *
 * @return uint8_t
 */
uint8_t VBV::alt_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    /* Check if sensor data is below altitude limit*/
    if(sensor_data < ALT_LIMIT && sensor_data > 0)
    {
        obj.storeInt("ALTITUDE_CHECK", 0);
        return 0;
    }
    /* Check if the sensor data is above the altitude limit */
    else if(sensor_data > ALT_LIMIT)
    {
        obj.storeInt("ALTITUDE_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Pass sensor data to verify latitude data
 *
 * This function takes sensor data as a parameter and compares it to LATITUDE_THRESHOLD
 * to verify if it is within the 90.0 degree threshold
 *
 * @return uint8_t
 */
uint8_t VBV::lat_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if(sensor_data < LATITUDE_THRESHOLD)
    {
        obj.storeInt("LATITUDE_CHECK", 0);
        return 0;
    }
    /* Since Latitude cannot be higher than 90 degrees*/
    else
    {
        obj.storeInt("LATITUDE_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Pass sensor data to verify longitude data
 *
 * This function takes sensor data as a parameter and compares it to LONGITUDE_THRESHOLD
 * to verify if it is within the 180 and -180 degree threshold
 *
 * @return uint8_t
 */
uint8_t VBV::lon_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if(sensor_data < LONGITUDE_THRESHOLD && sensor_data > -LONGITUDE_THRESHOLD)
    {
        obj.storeInt("LONGITUDE_CHECK", 0);
        return 0;
    }
    else
    {
        obj.storeInt("LONGITUDE_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Pass sensor data to verify velocity data
 *
 * This function takes sensor data as a parameter and compares it to velocity data
 * to verify if it is valid
 *
 * @return uint8_t
 */
uint8_t VBV::vel_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if(sensor_data > 0)
    {
        obj.storeInt("VELOCITY_CHECK", 0);
        return 0;
    }
    else
    {
        obj.storeInt("VELOCITY_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Pitch sensor data
 *
 * This function takes sensor data as a parameter and compares it to a pitch
 * threshold to verify its validity
 *
 * @return uint8_t
 */
uint8_t VBV::pit_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if (sensor_data <= PITCH_THRESHOLD)
    {
        obj.storeInt("PITCH_CHECK", 0);
        return 0;
    }
    else if (sensor_data < -PITCH_THRESHOLD)
    {
        obj.storeInt("PITCH_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Roll sensor data
 *
 * This function takes sensor data as a parameter and simply calculates where the roll
 * is angled at
 * Since there technically isn't a roll threshold nor is 0 a failing condition, we only
 * check the data
 *
 * @return uint8_t
 */
uint8_t VBV::roll_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if (sensor_data >= 0.0 || sensor_data < 0.0)
    {
        obj.storeInt("ROLL_CHECK", 0);
        return 0;
    }
    else
    {
        obj.storeInt("ROLL_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Yaw sensor data
 *
 * This function queries the YAW_CHECK PTAM register, assigns a variable the value,
 * then checks if it has bad data or good data.
 * It returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::yaw_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if (sensor_data >= -180 && sensor_data <= 180)
    {
        obj.storeInt("YAW_CHECK", 0);
        return 0;
    }
    else
    {
        obj.storeInt("YAW_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Temperature sensor data
 *
 * This function queries the TEMPERATURE_CHECK PTAM register, assigns a variable the value,
 * then checks if it has bad data or good data.
 * It returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::temp_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if (sensor_data >= 0 || sensor_data <= 0)
    {
        obj.storeInt("TEMPERATURE_CHECK", 0);
        return 0;
    }
    else
    {
        obj.storeInt("TEMPERATURE_CHECK", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Pressure sensor data
 *
 * This function queries the PRESSURE_CHECK PTAM register, assigns a variable the value,
 * then checks if it has bad data or good data.
 * It returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::pres_sensor_check(double sensor_data)
{
    SharedMemory &obj = SharedMemory::getInstance();

    if (sensor_data <= PRESSURE_CHECK)
    {
        obj.storeInt("PRESSURE_CHECK", 0);
        return 0;
    }
    else if (sensor_data > PRESSURE_CHECK)
    {
        obj.storeInt("PRESSURE_CHECK", 1);
        return 1;
    }
    return 1;
}