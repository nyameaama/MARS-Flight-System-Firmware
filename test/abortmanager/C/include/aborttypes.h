/**
 * @file aborttypes.h
 * @brief UAV Vehicle Abort Manager (VAMS) Definitions
 *
 *
 * @date Feburary 4th, 2024
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
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

#ifndef ABORT_TYPES_H
#define ABORT_TYPES_H

#include <inttypes.h>
//#include <string>

#define ALPHA 0.98

#define PITCH_THRESHOLD_DEGREES (int16_t)90.00
#define PITCH_THRESHOLD_RADIANS (int16_t)(PITCH_THRESHOLD_DEGREES * M_PI / 180)

#define YAW_THRESHOLD_DEGREES (int16_t)180.00
#define YAW_THRESHOLD_RADIANS (int16_t)(YAW_THRESHOLD_DEGREES * M_PI / 180)

#define ROLL_THRESHOLD_DEGREES (int16_t)180.00
#define ROLL_THRESHOLD_RADIANS (int16_t)(ROLL_THRESHOLD_DEGREES * M_PI / 180)

#define FLIGHT_PATH_THRESHOLD_LATITUDE (int16_t)90.00
#define FLIGHT_PATH_THRESHOLD_LONGITUDE (int16_t)180.00

#define EARTH_RADIUS (int16_t)6371.00
#define TO_RADIANS (degrees)((degrees) * M_PI / 180.0)

#define WEIGHTED_THRESHOLD 2

# define M_PI           3.14159265358979323846  /* pi */

// Define macros for abort_t values
#define LOSS_OF_CONTROL 0
#define BAD_SENSOR_DATA 0
#define UNEXPECTED_LOW_BATTERY 0
#define FAR_OFF_COURSE 0

#define NO_LOSS_OF_CONTROL 1
#define NO_BAD_SENSOR_DATA 1
#define NO_UNEXPECTED_LOW_BATTERY 1
#define NOT_OFF_COURSE 1

#define PASSED 0
#define FAILED 1

typedef double abort_t;

typedef struct weighted_type
{
    const char* name;
    double data;
    abort_t vstatus;
} weighted_t;

typedef struct Vector3D
{
    double lat;
    double lon;
    double alt;
}vector3d_t;

struct accelero
{
    double accel_x;
    double accel_y;
    double accel_z;
    double gyro_x;
    double gyro_y;
    double gyro_z;
};

#endif /* ABORT_TYPES_H */
