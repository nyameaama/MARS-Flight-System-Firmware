/**
 * @file Abort-Gtest.cpp
 * @brief Optional Gtest suite for abort manager
 *
 *
 * @date Created September 7th 2023 | modified Octoober 16th 2023
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

#include "gtest/gtest.h" // Include the Google Test framework
#include "abort.h"       // Include the header file of the code to be tested
#include <iostream>

// Define a test fixture class for common setup/teardown
class VAMSTest : public ::testing::Test
{
protected:
    VAMS vams;

    // Optional: Setup code to be executed before each test
    void SetUp() override
    {
        // Initialize any necessary resources or variables
    }

    // Optional: Teardown code to be executed after each test
    void TearDown() override
    {
        // Clean up resources if needed
    }
};

TEST_F(VAMSTest, PITCH_TEST)
{
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

    ASSERT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
}


TEST_F(VAMSTest, YAW_TEST)
{
    double magn_x = 1.0;
    double magn_y = 0.1;

    weighted_t result = vams.VERIFY_YAW(magn_x, magn_y);

    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";
    ASSERT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, ROLL_TEST)
{
    double validRoll = 0.0; // Replace with a valid roll value.

    // Call the VERIFY_ROLL function with the roll within threshold.
    weighted_t result = vams.VERIFY_ROLL(0.0, 0.0, 9.8);  // Replace with valid accelerometer values.

    // Print the value of Vector data
    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";

    // Check if the result is as expected.
    ASSERT_EQ(result.name, "Roll_Verif");
    ASSERT_DOUBLE_EQ(result.data, validRoll);
    ASSERT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VerifyPathWithinBoundary) {
    Vector3D initloc{0.0, 0.0, 0.0}; // Replace with a valid initial location.
    Vector3D targetloc{1.0, 1.0, 0.0}; // Replace with a valid target location.
    double boundaryRadius = 0.1; // Replace with a valid boundary radius.

    // Call the VERIFY_PATH function with the distance within the boundary radius.
    weighted_t result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);

    std::cout << "\n\n---------------------------------------------------------------";
    std::cout << "\n\nresult ID: " << result.name << "\n\n";
    std::cout << "result data: " << result.data << "\n\n";
    std::cout << "result vstatus: " << result.vstatus << "\n\n";
    std::cout << "---------------------------------------------------------------\n\n";
    
    // Check if the result is as expected.
    EXPECT_EQ(result.name, "Path_verif");
    if(result.data <= FLIGHT_PATH_THRESHOLD_LATITUDE && result.data >= FLIGHT_PATH_THRESHOLD_LONGITUDE)
    {
        std::cout << "Path within threshold ";
    }
    EXPECT_EQ(result.vstatus, NOT_OFF_COURSE);
}


TEST_F(VAMSTest, VAMS_MATRIX_WithNoLossOfControl)
{
    // Create weighted_t instances with no loss of control for pitch, yaw, roll, and path.
    weighted_t weighted_pitch{"Pitch_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_yaw{"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_roll{"Roll_Verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_path{"Path_verif", 0.0, NOT_OFF_COURSE};

    // Call VAMS_MATRIX function with the above weighted status.
    abort_t decision = vams.VAMS_MATRIX(weighted_pitch, weighted_yaw, weighted_roll, weighted_path);

    // Check if the decision is NO_LOSS_OF_CONTROL.
    if(decision <=2)
    {
        SUCCEED();
    }
    else{
        FAIL();
    }
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}