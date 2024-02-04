/**
 * @file VBV_unittest.cpp
 * @brief Vehicle-boot up sensor subsystem(VBV) Unit test suites
 *
 *
 * @date November 1st, 2023
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas Jackson (LukasJacksonEG@gmail.com)
 *
 * @license MIT License
 *          Copyright (c) 2023 Limitless Aeronautics
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

#include "gtest/gtest.h"
#include "VBV.hpp"
#include <iostream>


class VBV_Test : public ::testing::Test
{
protected:
    VBV vbv;

};

TEST_F(VBV_Test, ALTITUDE_SUITE)
{
    /* Altitude success test. [SHOULD RETURN 0] */
    double sensor_data = 10000;

    uint8_t sensor_check = vbv.alt_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Altitude Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Altitude Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Altitude failure test. [SHOULD RETURN 1] */
    sensor_data = 15000;

    sensor_check = vbv.alt_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Altitude Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Altitude Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, LATITUDE_SUITE)
{
    /* Latitude success test. [SHOULD RETURN 0] */
    double sensor_data = 0;

    uint8_t sensor_check = vbv.lat_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Latitude Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Latitude Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Latitude failure test. [SHOULD RETURN 1] */
    sensor_data = 150;

    sensor_check = vbv.lat_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Latitude Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Latitude Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, LONGITUDE_SUITE)
{
    /* Longitude success test. [SHOULD RETURN 0] */
    double sensor_data = 0;

    uint8_t sensor_check = vbv.lon_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Longitude Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Longitude Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Longitude failure test. [SHOULD RETURN 1] */
    sensor_data = 200;

    sensor_check = vbv.lon_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Longitude Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Longitude Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, VELOCITY_SUITE)
{
    /* Velocity success test. [SHOULD RETURN 0] */
    double sensor_data = 90;    // Velocity data is represented in meters per second (m/s).

    uint8_t sensor_check = vbv.vel_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Velocity Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Velocity Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Velocity failure test. [SHOULD RETURN 1] */
    sensor_data = -90;

    sensor_check = vbv.vel_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Velocity Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Velocity Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, PITCH_SUITE)
{
    /* Pitch success test. [SHOULD RETURN 0] */
    double sensor_data = 10;

    uint8_t sensor_check = vbv.pit_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Pitch Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Pitch Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Pitch failure test. [SHOULD RETURN 1] */
    sensor_data = 180;

    sensor_check = vbv.pit_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Pitch Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Pitch Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, ROLL_SUITE)
{
    /* Roll success test. [SHOULD RETURN 0] */
    double sensor_data = 150;

    uint8_t sensor_check = vbv.roll_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Roll Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Roll Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Roll failure test. [SHOULD RETURN 1] */
    sensor_data = 250;

    sensor_check = vbv.roll_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Roll Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Roll Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, YAW_SUITE)
{
    /* Yaw success test. [SHOULD RETURN 0] */
    double sensor_data = 100;

    uint8_t sensor_check = vbv.yaw_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Yaw Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Yaw Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Yaw failure test. [SHOULD RETURN 1] */
    sensor_data = -250;

    sensor_check = vbv.yaw_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Yaw Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Yaw Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, TEMP_SUITE)
{
    /* Temperature success test. [SHOULD RETURN 0] */
    double sensor_data = 30;

    uint8_t sensor_check = vbv.temp_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Temp Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Temp Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Temperature failure test. [SHOULD RETURN 1] */
    sensor_data = -30;

    sensor_check = vbv.temp_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Temp Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Temp Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}

TEST_F(VBV_Test, PRES_SUITE)
{
    /* Pressure success test. [SHOULD RETURN 0] */
    double sensor_data = 98000;

    uint8_t sensor_check = vbv.pres_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Pressure Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Pressure Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 0);

    /* Pressure failure test. [SHOULD RETURN 1] */
    sensor_data = 96000;

    sensor_check = vbv.pres_sensor_check(sensor_data);

    std::cout << "\n\n---------------------------------------------------------------\n\n";
    std::cout << "Pressure Sensor Data: " << sensor_data << "\n\n";
    std::cout << "Pressure Sensor Check: " << sensor_check;
    std::cout << "\n\n---------------------------------------------------------------\n\n";

    EXPECT_TRUE(sensor_check == 1);
}