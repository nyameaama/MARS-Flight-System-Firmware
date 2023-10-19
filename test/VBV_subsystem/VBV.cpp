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
 * @brief Verifies the value within GPScheck register and returns a 1 OR 0
 *
 * This function is queries the GPScheck PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::gps_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> gps_sensor_validate = obj.getDoubleData("GPScheck");
    double gps_data = gps_sensor_validate[0];

    if(gps_data > 0.0)
    {
        obj.storeInt("gps_sensor_check", 0);
        return 0;
    }
    else if(gps_data == 0)
    {
        obj.storeInt("gps_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Verifies the value within IMUcheck register and returns a 1 OR 0
 *
 * This function is queries the IMUcheck PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::imu_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> imu_sensor_validate = obj.getDoubleData("IMUcheck");
    double imu_data = imu_sensor_validate[0];

    if(imu_data > 0.0)
    {
        obj.storeInt("imu_sensor_check", 0);
        return 0;
    }
    else if(imu_data == 0)
    {
        obj.storeInt("imu_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Verifies the value within BMPcheck register and returns a 1 OR 0
 *
 * This function is queries the BMPcheck PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::bmp_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> bmp_sensor_validate = obj.getDoubleData("BMPcheck");
    double bmp_data = bmp_sensor_validate[0];

    if(bmp_data > 0.0)
    {
        obj.storeInt("bmp_sensor_check", 0);
        return 0;
    }
    else if(bmp_data == 0)
    {
        obj.storeInt("bmp_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Verifies the value within ALTITUDE_CHECK register and returns a 1 OR 0
 *
 * This function is queries the ALTITUDE_CHECK PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::alt_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> alt_sensor_validate = obj.getDoubleData("ALTITUDE_CHECK");
    double alt_data = alt_sensor_validate[0];

    if(alt_data > 0.0)
    {
        obj.storeInt("alt_sensor_check", 0);
        return 0;
    }
    else if(alt_data == 0)
    {
        obj.storeInt("alt_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Verifies the value within LATITUDE_CHECK register and returns a 1 OR 0
 *
 * This function is queries the LATITUDE_CHECK PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::lat_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> lat_sensor_validate = obj.getDoubleData("LATITUDE_CHECK");
    double lat_data = lat_sensor_validate[0];

    if(lat_data > 0.0)
    {
        obj.storeInt("lat_sensor_check", 0);
        return 0;
    }
    else if(lat_data == 0)
    {
        obj.storeInt("lat_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Verifies the value within LONGITUDE_CHECK register and returns a 1 OR 0
 *
 * This function is queries the LONGITUDE_CHECK PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::lon_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> lon_sensor_validate = obj.getDoubleData("LONGITUDE_CHECK");
    double lon_data = lon_sensor_validate[0];

    if(lon_data > 0.0)
    {
        obj.storeInt("lon_sensor_check", 0);
        return 0;
    }
    else if(lon_data == 0)
    {
        obj.storeInt("lon_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Verifies the value within VELOCITY_CHECK register and returns a 1 OR 0
 *
 * This function is queries the VELOCITY_CHECK PTAM register, assigns a variable the value,
 * then it checked to see if it has bad data or good data.
 * It then returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::vel_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> vel_sensor_validate = obj.getDoubleData("VELOCITY_CHECK");
    double vel_data = vel_sensor_validate[0];

    if(vel_data > 0.0)
    {
        obj.storeInt("alt_sensor_check", 0);
        return 0;
    }
    else if(vel_data == 0)
    {
        obj.storeInt("alt_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Pitch sensor data
 *
 * This function queries the PITCH_CHECK PTAM register, assigns a variable the value,
 * then checks if it has bad data or good data.
 * It returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::pit_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> pit_sensor_validate = obj.getDoubleData("PITCH_CHECK");
    double pit_data = pit_sensor_validate[0];

    if (pit_data > 0.0)
    {
        obj.storeInt("pit_sensor_check", 0);
        return 0;
    }
    else if (pit_data == 0)
    {
        obj.storeInt("pit_sensor_check", 1);
        return 1;
    }
    return 1;
}

/**
 * @brief Validates Roll sensor data
 *
 * This function queries the ROLL_CHECK PTAM register, assigns a variable the value,
 * then checks if it has bad data or good data.
 * It returns 0 on success and 1 on failure.
 *
 * @return uint8_t
 */
uint8_t VBV::roll_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> roll_sensor_validate = obj.getDoubleData("ROLL_CHECK");
    double roll_data = roll_sensor_validate[0];

    if (roll_data > 0.0)
    {
        obj.storeInt("roll_sensor_check", 0);
        return 0;
    }
    else if (roll_data == 0)
    {
        obj.storeInt("roll_sensor_check", 1);
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
uint8_t VBV::yaw_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> yaw_sensor_validate = obj.getDoubleData("YAW_CHECK");
    double yaw_data = yaw_sensor_validate[0];

    if (yaw_data > 0.0)
    {
        obj.storeInt("yaw_sensor_check", 0);
        return 0;
    }
    else if (yaw_data == 0)
    {
        obj.storeInt("yaw_sensor_check", 1);
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
uint8_t VBV::temp_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> temp_sensor_validate = obj.getDoubleData("TEMPERATURE_CHECK");
    double temp_data = temp_sensor_validate[0];

    if (temp_data > 0.0)
    {
        obj.storeInt("temp_sensor_check", 0);
        return 0;
    }
    else if (temp_data == 0)
    {
        obj.storeInt("temp_sensor_check", 1);
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
uint8_t VBV::pres_sensor_check()
{
    SharedMemory &obj = SharedMemory::getInstance();
    std::vector<double> pres_sensor_validate = obj.getDoubleData("PRESSURE_CHECK");
    double pres_data = pres_sensor_validate[0];

    if (pres_data > 0.0)
    {
        obj.storeInt("pres_sensor_check", 0);
        return 0;
    }
    else if (pres_data == 0)
    {
        obj.storeInt("pres_sensor_check", 1);
        return 1;
    }
    return 1;
}