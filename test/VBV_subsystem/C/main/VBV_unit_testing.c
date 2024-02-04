/**
 * @file VBV_unit_testing.c
 * @brief Vehicle-boot up sensor subsystem(VBV) Unit test suites
 *
 *
 * @date Febuary 3rd, 2024
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
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

#include <stdio.h>
#include "../VBV.h"

void
test_altitude_suite(void)
{
    // Altitude success test. [SHOULD RETURN 0]
    double sensor_data1 = 10000;
    uint8_t sensor_check1 = alt_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Altitude Sensor Data: %lf\n\n", sensor_data1);
    printf("Altitude Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Altitude failure test. [SHOULD RETURN 1]
    double sensor_data2 = 15000;
    uint8_t sensor_check2 = alt_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Altitude Sensor Data: %lf\n\n", sensor_data2);
    printf("Altitude Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_latitude_suite(void)
{
    // Latitude success test. [SHOULD RETURN 0]
    double sensor_data1 = 0;
    uint8_t sensor_check1 = lat_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Latitude Sensor Data: %lf\n\n", sensor_data1);
    printf("Latitude Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Latitude failure test. [SHOULD RETURN 1]
    double sensor_data2 = 150;
    uint8_t sensor_check2 = lat_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Latitude Sensor Data: %lf\n\n", sensor_data2);
    printf("Latitude Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_longitude_suite()
{
    // Longitude success test. [SHOULD RETURN 0]
    double sensor_data1 = 0;
    uint8_t sensor_check1 = lon_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Longitude Sensor Data: %lf\n\n", sensor_data1);
    printf("Longitude Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Longitude failure test. [SHOULD RETURN 1]
    double sensor_data2 = 200;
    uint8_t sensor_check2 = lon_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Longitude Sensor Data: %lf\n\n", sensor_data2);
    printf("Longitude Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_velocity_suite()
{
    // Velocity success test. [SHOULD RETURN 0]
    double sensor_data1 = 90;
    uint8_t sensor_check1 = vel_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Velocity Sensor Data: %lf\n\n", sensor_data1);
    printf("Velocity Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Velocity failure test. [SHOULD RETURN 1]
    double sensor_data2 = -90;
    uint8_t sensor_check2 = vel_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Velocity Sensor Data: %lf\n\n", sensor_data2);
    printf("Velocity Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_pitch_suite()
{
    // Pitch success test. [SHOULD RETURN 0]
    double sensor_data1 = 10;
    uint8_t sensor_check1 = pit_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Pitch Sensor Data: %lf\n\n", sensor_data1);
    printf("Pitch Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Pitch failure test. [SHOULD RETURN 1]
    double sensor_data2 = 180;
    uint8_t sensor_check2 = pit_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Pitch Sensor Data: %lf\n\n", sensor_data2);
    printf("Pitch Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_roll_suite()
{
    // Roll success test. [SHOULD RETURN 0]
    double sensor_data1 = 150;
    uint8_t sensor_check1 = roll_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Roll Sensor Data: %lf\n\n", sensor_data1);
    printf("Roll Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Roll failure test. [SHOULD RETURN 1]
    double sensor_data2 = 250;
    uint8_t sensor_check2 = roll_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Roll Sensor Data: %lf\n\n", sensor_data2);
    printf("Roll Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_yaw_suite()
{
    // Yaw success test. [SHOULD RETURN 0]
    double sensor_data1 = 100;
    uint8_t sensor_check1 = yaw_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Yaw Sensor Data: %lf\n\n", sensor_data1);
    printf("Yaw Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Yaw failure test. [SHOULD RETURN 1]
    double sensor_data2 = -250;
    uint8_t sensor_check2 = yaw_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Yaw Sensor Data: %lf\n\n", sensor_data2);
    printf("Yaw Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_temperature_suite()
{
    // Temperature success test. [SHOULD RETURN 0]
    double sensor_data1 = 30;
    uint8_t sensor_check1 = temp_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Temp Sensor Data: %lf\n\n", sensor_data1);
    printf("Temp Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Temperature failure test. [SHOULD RETURN 1]
    double sensor_data2 = -30;
    uint8_t sensor_check2 = temp_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Temp Sensor Data: %lf\n\n", sensor_data2);
    printf("Temp Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

void
test_pressure_suite()
{
    // Pressure success test. [SHOULD RETURN 0]
    double sensor_data1 = 98000;
    uint8_t sensor_check1 = pres_sensor_check(sensor_data1);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Pressure Sensor Data: %lf\n\n", sensor_data1);
    printf("Pressure Sensor Check: %d\n", sensor_check1);
    printf("\n\n---------------------------------------------------------------\n\n");

    // Pressure failure test. [SHOULD RETURN 1]
    double sensor_data2 = 96000;
    uint8_t sensor_check2 = pres_sensor_check(sensor_data2);

    printf("\n\n---------------------------------------------------------------\n\n");
    printf("Pressure Sensor Data: %lf\n\n", sensor_data2);
    printf("Pressure Sensor Check: %d\n", sensor_check2);
    printf("\n\n---------------------------------------------------------------\n\n");
}

#ifdef ESP_TARGET

void
app_main(void)
{
    // Call the test functions
    test_altitude_suite();
    test_latitude_suite();
    test_longitude_suite();
    test_velocity_suite();
    test_pitch_suite();
    test_roll_suite();
    test_yaw_suite();
    test_temperature_suite();
    test_pressure_suite();
}
#else

int
main(void)
{
    // Call the test functions
    test_altitude_suite();
    test_latitude_suite();
    test_longitude_suite();
    test_velocity_suite();
    test_pitch_suite();
    test_roll_suite();
    test_yaw_suite();
    test_temperature_suite();
    test_pressure_suite();

    return 0;
}

#endif