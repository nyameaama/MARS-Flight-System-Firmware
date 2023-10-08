/**
 * @file abort.cpp
 * @brief UAV Vehicle Abort Manager (VAMS) Definitions
 *
 *
 * @date September 7th 2023
 * @copyright Copyright (c) 2023 limitless Aeronautics
 *
 * @author Lukas Jackson (LukasJacksonEG@gmail.com)
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


weighted_t VAMS::weighted_pitch;
weighted_t VAMS::weighted_yaw;
weighted_t VAMS::weighted_roll;
weighted_t VAMS::weighted_path;


weighted_t VAMS::VERIFY_PITCH(double accel_x, double accel_y, double accel_z) noexcept(true)
{
    double pitch = atan2(-accel_x, sqrt(accel_y * accel_y + accel_z * accel_z));

    weighted_pitch = (pitch >= -PITCH_THRESHOLD_DEGREES && pitch <= PITCH_THRESHOLD_DEGREES) ?
        weighted_t{"Pitch_verif", pitch, NO_LOSS_OF_CONTROL} : weighted_t{"Pitch_Verif", pitch, LOSS_OF_CONTROL};

    return weighted_pitch;
}

weighted_t VAMS::VERIFY_YAW(double magn_x, double magn_y) noexcept(true)
{
    double yaw = atan2(magn_y, magn_x);

    weighted_yaw = (yaw >= -YAW_THRESHOLD_DEGREES && yaw <= YAW_THRESHOLD_DEGREES) ?
        weighted_t{"Yaw_verif", yaw, NO_LOSS_OF_CONTROL} : weighted_t{"Yaw_verif", yaw, LOSS_OF_CONTROL};

    return weighted_yaw;
}

weighted_t VAMS::VERIFY_ROLL(double accel_x, double accel_y, double accel_z) noexcept(true)
{
    double roll = atan2(accel_y, sqrt(accel_x * accel_x + accel_z * accel_z));

    weighted_roll = (roll >= -ROLL_THRESHOLD_DEGREES && roll <= ROLL_THRESHOLD_DEGREES) ?
        weighted_t{"Roll_Verif", roll, NO_LOSS_OF_CONTROL} : weighted_t{"Roll_Verif", roll, LOSS_OF_CONTROL};

    return weighted_roll;
}

double VAMS::haversine(double startLat, double startLong, double endLat, double endLong)noexcept(true)
{
    startLat = startLat * M_PI / 180.0;
    startLong = startLong * M_PI / 180.0;
    endLat = endLat * M_PI / 180.0;
    endLong = endLong * M_PI / 180.0;

    double dLat = endLat - startLat;
    double dLon = endLong - startLong;
    double a = sin(dLat/2) * sin(dLat/2) + cos(startLat) * cos(endLat) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

weighted_t VAMS::VERIFY_PATH(const Vector3D& initloc, const Vector3D& targetloc, double boundaryRadius)noexcept(true)
{
    double distance = haversine(initloc.lat, initloc.lon, targetloc.lat, targetloc.lon);

    weighted_path = (distance <= boundaryRadius || distance >= boundaryRadius) ?
        weighted_t{"Path_verif", distance, NOT_OFF_COURSE} : weighted_t{"Path_verif", distance, FAR_OFF_COURSE};

    return weighted_path;
}

abort_t VAMS::VAMS_MATRIX(weighted_t weighted_PI, weighted_t weighted_YA, weighted_t weighted_RO, weighted_t weighted_PA)
{
    // Calculate the total weighted status
    int totalWeightedStatus = weighted_PI.vstatus + weighted_YA.vstatus + weighted_RO.vstatus + weighted_PA.vstatus;

    // Make a decision based on the total weighted status and the threshold
    abort_t decision;
    if (totalWeightedStatus > WEIGHTED_THRESHOLD)
    {
        decision = LOSS_OF_CONTROL; // Abort
    }
    else
    {
        decision = NO_LOSS_OF_CONTROL; // Continue
    }

    return decision;
}