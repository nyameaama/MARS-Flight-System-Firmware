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

#include<cmath> // For math related functions
#include"include/aborttypes.h" // For abort_t

#define ALPHA                                 0.98

#define PITCH_THRESHOLD_DEGREES             (int16_t)       90.00
#define PITCH_THRESHOLD_RADIANS             (int16_t)       (PITCH_THRESHOLD_DEGREES * M_PI / 180)

#define YAW_THRESHOLD_DEGREES               (int16_t)       180.00
#define YAW_THRESHOLD_RADIANS               (int16_t)       (YAW_THRESHOLD_DEGREES * M_PI / 180)

#define ROLL_THRESHOLD_DEGREES              (int16_t)       180.00
#define ROLL_THRESHOLD_RADIANS              (int16_t)       (ROLL_THRESHOLD_DEGREES * M_PI / 180)

#define FLIGHT_PATH_THRESHOLD_LATITUDE      (int16_t)       90.00
#define FLIGHT_PATH_THRESHOLD_LONGITUDE     (int16_t)       180.00

#define EARTH_RADIUS                        (int16_t)       6371.00
#define TO_RADIANS                          (degrees)       ((degrees) * M_PI / 180.0)

#define WEIGHTED_THRESHOLD 2

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
    weighted_t VERIFY_PITCH(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z)noexcept(true);

    /**
     * @brief Verifies the range of vehicle YAW
     *
     * @param magn_x    Magnetic field component on the X axis
     * @param magn_y    Magnetic field component on the Y axis
     *
     * @return uint8_t | 0 if within -90 and 90 degrees OR 1 if out of those bounds.
     */
    weighted_t VERIFY_YAW(double magn_x, double magn_y)noexcept(true);

    /**
     * @brief Verifies the range of vehicle ROLL
     *
     * @param accel_x   Acceleration of the aircraft on the X axis.
     * @param accel_y   Acceleration of the aircraft on the Y axis.
     * @param accel_z   Acceleration of the aircraft on the Z axis.
     *
     * @return uint8_t | 0 if within -90 and 90 degrees OR 1 if out of those bounds.
     */
    weighted_t VERIFY_ROLL(double accel_x, double accel_y, double accel_z)noexcept(true);

    /**
     * @brief The Haversine formula
     *
     * @param lat1      Starting latitude
     * @param lon1      Starting Longitude
     * @param lat2      Ending Latitude
     * @param lon2      Ending Longitude
     * @return double | The distance calculated with parameters. (in KM)
     */
    double haversine(double lat1, double lon1, double lat2, double lon2)noexcept(true);

    /**
     * @brief Verifies the vehicle PATH
     *
     * @param initloc           Initial Location
     * @param targetloc         Targeted Location
     * @param boundaryRadius    Boundary radius set by the user
     * @return weighted_t | 0 or 2
     */
    weighted_t VERIFY_PATH(const Vector3D& initloc, const Vector3D& targetloc, double boundaryRadius)noexcept(true);

    /**
     * @brief Verifies the battery percentage.
     *
     * @param voltage       Voltage to calulcate remainder of battery
     *
     * @return double   | Battery percentage
     */
    double VERIFY_BATTERY(double voltage)noexcept(true);

    /**
     * @brief VAMS decision matrix
     *
     * @param weighted_PI   PITCH weighted total
     * @param weighted_YA   YAW weighted total
     * @param weighted_RO   ROLL weighted total
     * @param weightedPA    PATH weighted total
     * @return abort_t | If it shall abort or not
     */
    abort_t VAMS_MATRIX(weighted_t weighted_PI, weighted_t weighted_YA, weighted_t weighted_RO, weighted_t weightedPA);

private:
    static weighted_t weighted_pitch;
    static weighted_t weighted_yaw;
    static weighted_t weighted_roll;

    static weighted_t weighted_path;
};
#endif /* ABORT_H */