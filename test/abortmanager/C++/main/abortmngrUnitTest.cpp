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

#include "../abort.h"
#include <iostream>

void PITCH_TEST(void)
{
    VAMS vams;
    double accel_x = 0.1;
    double accel_y = 0.2;
    double accel_z = 9.8;
    double gyro_x = 0.02;
    double gyro_y = 0.03;
    double gyro_z = 0.04;

    weighted_t result = vams.VERIFY_PITCH(accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);

    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";

    if (result.vstatus == NO_LOSS_OF_CONTROL)
    {
        std::cout << "PITCH_TEST: Passed\n";
    }
    else
    {
        std::cout << "PITCH_TEST: Failed\n";
    }
}

void YAW_TEST(void)
{
    VAMS vams;
    double magn_x = 1.0;
    double magn_y = 0.1;

    weighted_t result = vams.VERIFY_YAW(magn_x, magn_y);

    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";

    if (result.vstatus == NO_LOSS_OF_CONTROL)
    {
        std::cout << "YAW_TEST: Passed\n";
    }
    else
    {
        std::cout << "YAW_TEST: Failed\n";
    }
}

void ROLL_TEST(void)
{
    VAMS vams;
    double validRoll = 0.0; // Replace with a valid roll value.

    weighted_t result = vams.VERIFY_ROLL(0.0, 0.0, 9.8); // Replace with valid accelerometer values.

    // Print the value of Vector data
    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";

    if (result.name == "Roll_Verif" && result.data == validRoll && result.vstatus == NO_LOSS_OF_CONTROL)
    {
        std::cout << "ROLL_TEST: Passed\n";
    }
    else
    {
        std::cout << "ROLL_TEST: Failed\n";
    }
}

void VerifyPathWithinBoundary(void)
{
    VAMS vams;
    Vector3D initloc{0.0, 0.0, 0.0};   // Replace with a valid initial location.
    Vector3D targetloc{1.0, 1.0, 0.0}; // Replace with a valid target location.
    double boundaryRadius = 0.1;       // Replace with a valid boundary radius.

    // Call the VERIFY_PATH function with the distance within the boundary radius.
    weighted_t result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);

    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";

    if (result.name == "Path_verif" && result.vstatus == NOT_OFF_COURSE)
    {
        std::cout << "VerifyPathWithinBoundary: Passed\n";
    }
    else
    {
        std::cout << "VerifyPathWithinBoundary: Failed\n";
    }
}

void VAMS_MATRIX_WithNoLossOfControl(void)
{
    VAMS vams;

    // Create weighted_t instances with no loss of control for pitch, yaw, roll, and path.
    weighted_t weighted_pitch{"Pitch_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_yaw{"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_roll{"Roll_Verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_path{"Path_verif", 0.0, NOT_OFF_COURSE};

    // Call VAMS_MATRIX function with the above weighted status.
    abort_t decision = vams.VAMS_MATRIX(weighted_pitch, weighted_yaw, weighted_roll, weighted_path);

    if (decision == NO_LOSS_OF_CONTROL)
    {
        std::cout << "VAMS_MATRIX_WithNoLossOfControl: Passed\n";
    }
    else
    {
        std::cout << "VAMS_MATRIX_WithNoLossOfControl: Failed\n";
    }
}

extern "C"
{
    void app_main(void)
    {
        PITCH_TEST();
        YAW_TEST();
        ROLL_TEST();
        VerifyPathWithinBoundary();
        VAMS_MATRIX_WithNoLossOfControl();
    }
}
