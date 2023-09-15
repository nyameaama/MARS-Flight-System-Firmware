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

#include"abort.h"

uint8_t VAMS::VERIFY_PITCH(double accel_x, double accel_y, double accel_z)noexcept
{
    double pitch = atan2(-accel_x, sqrt(accel_y * accel_y + accel_z * accel_z));
    if (pitch >= -PITCH_THRESHOLD_DEGREES && pitch <= PITCH_THRESHOLD_DEGREES)
    {
        return 0;
    }
    return 1;
}

uint8_t VAMS::VERIFY_YAW(double magn_x, double magn_y)noexcept
{
    double yaw = atan2(magn_y, magn_x);
    if (yaw >= -YAW_THRESHOLD_DEGREES && yaw <= YAW_THRESHOLD_DEGREES)
    {
        return 0;
    }
    return 1;
}

uint8_t VAMS::VERIFY_ROLL(double accel_x, double accel_y, double accel_z)noexcept
{
    double roll = atan2(accel_y, sqrt(accel_x * accel_x + accel_z * accel_z));
    if (roll >= -ROLL_THRESHOLD_DEGREES && roll <= ROLL_THRESHOLD_DEGREES)
    {
        return 0;
    }
    return 1;
}