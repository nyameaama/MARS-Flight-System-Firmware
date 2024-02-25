/**
 * @file abortmngrUnitTest.cpp
 * @brief Abort manager flashable unit test
 *
 *
 * @date October 16th 2023
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

#include <stdio.h>
#include <string.h>
#include "../abort.h"

void
PITCH_TEST(void)
{
    double accel_x = 0.1;
    double accel_y = 0.2;
    double accel_z = 9.8;
    double gyro_x = 0.02;
    double gyro_y = 0.03;
    double gyro_z = 0.04;

    weighted_t result = VERIFY_PITCH(accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);

    printf("\n\n---------------------------------------------------------------");
    printf("\n\nresult ID: %s%s", result.name, "\n\n");
    printf("result data: %f%s", result.data, "\n\n");
    printf("result vstatus: %f%s", result.vstatus, "\n\n");
    printf("\n\n---------------------------------------------------------------");

    if (result.vstatus == NO_LOSS_OF_CONTROL)
    {
        printf("PITCH_TEST: %d\n", PASSED);
    }
    else
    {
        printf("PITCH_TEST: %d\n", FAILED);
    }
}

void
YAW_TEST(void)
{
    double magn_x = 1.0;
    double magn_y = 0.1;

    weighted_t result = VERIFY_YAW(magn_x, magn_y);

    printf("\n\n---------------------------------------------------------------");
    printf("\n\nresult ID: %s%s", result.name, "\n\n");
    printf("result data: %f%s", result.data, "\n\n");
    printf("result vstatus: %f%s", result.vstatus, "\n\n");
    printf("\n\n---------------------------------------------------------------");

    if (result.vstatus == NO_LOSS_OF_CONTROL)
    {
        printf("YAW_TEST: %d\n", PASSED);
    }
    else
    {
        printf("YAW_TEST: %d\n", FAILED);
    }
}

void
ROLL_TEST(void)
{
    double validRoll = 0.0;  // Replace with a valid roll value.

    weighted_t result = VERIFY_ROLL(0.0, 0.0, 9.8);  // Replace with valid accelerometer values.

    // Print the value of Vector data
    printf("\n\n---------------------------------------------------------------");
    printf("\n\nresult ID: %s%s", result.name, "\n\n");
    printf("result data: %f%s", result.data, "\n\n");
    printf("result vstatus: %f%s", result.vstatus, "\n\n");
    printf("\n\n---------------------------------------------------------------");

    if (strcmp(result.name, "Roll_Verif") == 0 && result.data == validRoll &&
        result.vstatus == NO_LOSS_OF_CONTROL)
    {
        printf("ROLL_TEST: %d\n", PASSED);
    }
    else
    {
        printf("ROLL_TEST: %d\n", FAILED);
    }
}

void
VerifyPathWithinBoundary(void)
{
    vector3d_t initloc = {0.0, 0.0, 0.0};    // Replace with a valid initial location.
    vector3d_t targetloc = {1.0, 1.0, 0.0};  // Replace with a valid target location.
    double boundaryRadius = 0.1;             // Replace with a valid boundary radius.

    const vector3d_t* initlocation = &initloc;
    const vector3d_t* targetlocation = &targetloc;

    // Call the VERIFY_PATH function with the distance within the boundary radius.
    weighted_t result = VERIFY_PATH(initlocation, targetlocation, boundaryRadius);

    printf("\n\n---------------------------------------------------------------");
    printf("\n\nresult ID: %s%s", result.name, "\n\n");
    printf("result data: %f%s", result.data, "\n\n");
    printf("result vstatus: %f%s", result.vstatus, "\n\n");
    printf("\n\n---------------------------------------------------------------");

    if (result.name == "Path_verif" && result.vstatus == NOT_OFF_COURSE)
    {
        printf("VerifyPathWithinBoundary: %d\n", PASSED);
    }
    else
    {
        printf("VerifyPathWithinBoundary: %d\n", FAILED);
    }
}

void
VAMS_MATRIX_WithNoLossOfControl(void)
{
    // Create weighted_t instances with no loss of control for pitch, yaw, roll, and path.
    weighted_t weighted_pitch = {"Pitch_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_yaw = {"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_roll = {"Roll_Verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_path = {"Path_verif", 0.0, NOT_OFF_COURSE};

    // Call VAMS_MATRIX function with the above weighted status.
    abort_t decision = VAMS_MATRIX(weighted_pitch, weighted_yaw, weighted_roll, weighted_path);

    if (decision == NO_LOSS_OF_CONTROL)
    {
        printf("VAMS_MATRIX_WithNoLossOfControl: %d\n", PASSED);
    }
    else
    {
        printf("VAMS_MATRIX_WithNoLossOfControl: %d\n", FAILED);
    }
}

#ifdef ESP_TARGET
void
app_main(void)
{
    PITCH_TEST();
    YAW_TEST();
    ROLL_TEST();
    VerifyPathWithinBoundary();
    VAMS_MATRIX_WithNoLossOfControl();
}
#else
int
main(void)
{
    PITCH_TEST();
    YAW_TEST();
    ROLL_TEST();
    VerifyPathWithinBoundary();
    VAMS_MATRIX_WithNoLossOfControl();

    return 0;
}
#endif