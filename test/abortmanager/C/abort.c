/**
 * @file abort.c
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

#include "abort.h"
#include <math.h>                 // For math related functions

// weighted_t weighted_pitch;
// weighted_t weighted_yaw;
// weighted_t weighted_roll;
// weighted_t weighted_path;

/**
 * Calculate and verify the pitch angle using accelerometer and gyroscope data.
 *
 * @param accel_x Acceleration along the X-axis.
 * @param accel_y Acceleration along the Y-axis.
 * @param accel_z Acceleration along the Z-axis.
 * @param gyro_x Angular velocity around the X-axis.
 * @param gyro_y Angular velocity around the Y-axis.
 * @param gyro_z Angular velocity around the Z-axis.
 * @return A weighted_t structure containing pitch angle information and a status flag.
 */
weighted_t
VERIFY_PITCH(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y,
             double gyro_z)
{
    double pitch = atan2(accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * 180.0 / M_PI;

    // Calculate pitch from gyroscope data
    double dt = 1.0;  // Time interval
    double pitchGyro = pitch + gyro_x * dt;

    // Combine accelerometer and gyroscope data using a complementary filter
    pitch = ALPHA * pitchGyro + (1.0 - ALPHA) * pitch;

    weighted_t result;
    if ((pitch >= -PITCH_THRESHOLD_DEGREES && pitch <= PITCH_THRESHOLD_DEGREES) || pitch == 0)
    {
        result = (weighted_t){"Pitch_verif", pitch, NO_LOSS_OF_CONTROL};
    }
    else
    {
        result = (weighted_t){"Pitch_Verif", pitch, LOSS_OF_CONTROL};
    }

    weighted_pitch = result;
    return result;
}

/**
 * Calculate and verify the yaw angle using magnetometer data.
 *
 * @param magn_x Magnetic field strength along the X-axis.
 * @param magn_y Magnetic field strength along the Y-axis.
 * @return A weighted_t structure containing yaw angle information and a status flag.
 */
weighted_t
VERIFY_YAW(double magn_x, double magn_y)
{
    double yaw = atan2(magn_y, magn_x);

    weighted_t result;
    if (yaw >= -YAW_THRESHOLD_DEGREES && yaw <= YAW_THRESHOLD_DEGREES)
    {
        result = (weighted_t){"Yaw_verif", yaw, NO_LOSS_OF_CONTROL};
    }
    else
    {
        result = (weighted_t){"Yaw_verif", yaw, LOSS_OF_CONTROL};
    }

    weighted_yaw = result;
    return result;
}

/**
 * Calculate and verify the roll angle using accelerometer data.
 *
 * @param accel_x Acceleration along the X-axis.
 * @param accel_y Acceleration along the Y-axis.
 * @param accel_z Acceleration along the Z-axis.
 * @return A weighted_t structure containing roll angle information and a status flag.
 */
weighted_t
VERIFY_ROLL(double accel_x, double accel_y, double accel_z)
{
    double roll = atan2(accel_y, sqrt(accel_x * accel_x + accel_z * accel_z));

    weighted_t result;
    if (roll >= -ROLL_THRESHOLD_DEGREES && roll <= ROLL_THRESHOLD_DEGREES)
    {
        result = (weighted_t){"Roll_Verif", roll, NO_LOSS_OF_CONTROL};
    }
    else
    {
        result = (weighted_t){"Roll_Verif", roll, LOSS_OF_CONTROL};
    }

    weighted_roll = result;
    return result;
}

/**
 * Calculate the Haversine distance between two points on the Earth's surface.
 *
 * @param startLat Latitude of the starting location.
 * @param startLong Longitude of the starting location.
 * @param endLat Latitude of the ending location.
 * @param endLong Longitude of the ending location.
 * @return The Haversine distance between the two points.
 */
double
haversine(double startLat, double startLong, double endLat, double endLong)
{
    startLat = startLat * M_PI / 180.0;
    startLong = startLong * M_PI / 180.0;
    endLat = endLat * M_PI / 180.0;
    endLong = endLong * M_PI / 180.0;

    double dLat = endLat - startLat;
    double dLon = endLong - startLong;
    double a =
        sin(dLat / 2) * sin(dLat / 2) + cos(startLat) * cos(endLat) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

/**
 * Verify the flight path based on the Haversine distance between initial and target locations.
 *
 * @param initloc The initial location (latitude, longitude, altitude).
 * @param targetloc The target location (latitude, longitude, altitude).
 * @param boundaryRadius The boundary radius within which the flight path is considered on course.
 * @return A weighted_t structure containing the Haversine distance and a status flag.
 */
weighted_t
VERIFY_PATH(const vector3d_t* initloc, const vector3d_t* targetloc, double boundaryRadius)
{
    double distance = haversine(initloc->lat, initloc->lon, targetloc->lat, targetloc->lon);

    weighted_t result;
    if (distance <= boundaryRadius || distance >= boundaryRadius)
    {
        result = (weighted_t){"Path_verif", distance, NOT_OFF_COURSE};
    }
    else
    {
        result = (weighted_t){"Path_verif", distance, FAR_OFF_COURSE};
    }

    weighted_path = result;
    return result;
}

/**
 * Make an abort decision based on weighted status of pitch, yaw, roll, and flight path.
 *
 * @param weighted_PI Weighted status result of pitch verification.
 * @param weighted_YA Weighted status result of yaw verification.
 * @param weighted_RO Weighted status result of roll verification.
 * @param weighted_PA Weighted status result of flight path verification.
 * @return An abort decision based on the weighted status and a threshold.
 */
abort_t
VAMS_MATRIX(weighted_t weighted_PI, weighted_t weighted_YA, weighted_t weighted_RO,
            weighted_t weighted_PA)
{
    // Calculate the total weighted status
    int totalWeightedStatus =
        weighted_PI.vstatus + weighted_YA.vstatus + weighted_RO.vstatus + weighted_PA.vstatus;

    // Make a decision based on the total weighted status and the threshold
    abort_t decision;
    if (totalWeightedStatus > WEIGHTED_THRESHOLD)
    {
        decision = LOSS_OF_CONTROL;  // Abort
    }
    else
    {
        decision = NO_LOSS_OF_CONTROL;  // Continue
    }

    return decision;
}