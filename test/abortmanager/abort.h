/**
 * @file abort.h
 * @brief UAV Abort Manager Subsystem (VAMS) Interface Prototypes
 *
 *
 * @date September 7th 2023
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

#ifndef ABORT_H
#define ABORT_H

#include<inttypes.h>
#include<cmath>
#include"include/aborttypes.h" // For abort_t

#define PITCH_THRESHOLD_DEGREES (int64_t) 90.00
#define PITCH_THRESHOLD_RADIANS (int64_t) (PITCH_THRESHOLD_DEGREES * M_PI / 180)

#define YAW_THRESHOLD_DEGREES (int64_t) 180.00
#define YAW_THRESHOLD_RADIANS (int64_t) (YAW_THRESHOLD_DEGREES * M_PI / 180)

#define ROLL_THRESHOLD_DEGREES (int64_t) 180.00
#define ROLL_THRESHOLD_RADIANS (int64_t) (ROLL_THRESHOLD_DEGREES * M_PI / 180)

class VAMS
{
public:
    /**
     * @brief Verifies the range of vehicle PITCH
     *
     * @param accel_x   Acceleration of the aircraft on the X axis.
     * @param accel_y   Acceleration of the aircraft on the Y axis.
     * @param accel_z   Acceleration of the aircraft on the Z axis.
     *
     * @return uint8_t | 0 if within -90 and 90 degrees OR 1 if out of those bounds.
     */
    inline double VERIFY_PITCH(double accel_x, double accel_y, double accel_z)noexcept(true);

    /**
     * @brief Verifies the range of vehicle YAW
     *
     * @param magn_x    Magnetic field component on the X axis
     * @param magn_y    Magnetic field component on the Y axis
     *
     * @return uint8_t | 0 if within -90 and 90 degrees OR 1 if out of those bounds.
     */
    inline double VERIFY_YAW(double magn_x, double magn_y)noexcept(true);

    /**
     * @brief Verifies the range of vehicle ROLL
     *
     * @param accel_x   Acceleration of the aircraft on the X axis.
     * @param accel_y   Acceleration of the aircraft on the Y axis.
     * @param accel_z   Acceleration of the aircraft on the Z axis.
     *
     * @return uint8_t | 0 if within -90 and 90 degrees OR 1 if out of those bounds.
     */
    inline double VERIFY_ROLL(double accel_x, double accel_y, double accel_z)noexcept(true);

    /**
     * @brief Verifies if drone within computed path threshold
     *
     * @param latitudeY     Latitude of the computed path
     * @param longitudeX    Longitude of the computed path
     * @param altitudeY     Altitude of computed path
     * @param timeX         Time it took the drone to travel in computed path
     * @param threshold     Allowed drone threshold
     * @param currentP      Drone current position to be computed
     * @return uint8_t | 0 if within -90 and 90 degrees OR 1 if out of those bounds.
     */
    inline double VERIFY_PATH(double latitudeY, double longitudeX, double altitudeY, double timeX, double threshold, double currentP)noexcept(true);

    /**
     * @brief performs a decision based on the results yielded by PITCH, YAW, & ROLL
     *
     * 
     * @return uint64_t
     */
    inline abort_t VAMS_MATRIX();

private:
    static abort_t pitch_flag;      /* EITHER TRUE(1) OR FALSE(2) */
    static abort_t yaw_flag;        /* EITHER TRUE(1) OR FALSE(2) */
    static abort_t roll_flag;       /* EITHER TRUE(1) OR FALSE(2) */
    static abort_t ABORT_SIGNAL;    /* EITHER ABORT(3) OR NO_ABORT(4) */
};
#endif /* ABORT_H */