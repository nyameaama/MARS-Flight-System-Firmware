#include <iostream>
#include "../abort.h"
#include <cassert>
#include <gtest/gtest.h>

// Define a test fixture for your tests if needed
class VAMSTest : public ::testing::Test {
protected:
    VAMS vams;
};

TEST_F(VAMSTest, VERIFY_PITCH) {
    // Test cases for VERIFY_PITCH
    weighted_t result = vams.VERIFY_PITCH(5.0, 0.0, 9); // Assuming no loss of control
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);

    result = vams.VERIFY_PITCH(0.0, 0.0, 50.0); // Assuming loss of control
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VERIFY_YAW) {
    // Test cases for VERIFY_YAW
    weighted_t result = vams.VERIFY_YAW(1.0, 0.0); // Assuming no loss of control
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    
    result = vams.VERIFY_YAW(1.0, 2.0); // Assuming loss of control
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VERIFY_ROLL) {
    // Test cases for VERIFY_ROLL
    weighted_t result = vams.VERIFY_ROLL(0.0, 9.81, 0.0); // Assuming no loss of control
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);

    result = vams.VERIFY_ROLL(0.0, 11.0, 0.0); // Assuming loss of control
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VERIFY_PATH) {
    // Test cases for VERIFY_PATH
    Vector3D initloc{0.0, 0.0};
    Vector3D targetloc{0.1, 0.1};
    double boundaryRadius = 0.2;

    // Assuming distance within boundary
    weighted_t result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);
    EXPECT_EQ(result.vstatus, NOT_OFF_COURSE);

    // Assuming distance far off course
    initloc = {0.0, 0.0};
    targetloc = {10.0, 10.0};
    result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);
    EXPECT_EQ(result.vstatus, FAR_OFF_COURSE);
}

TEST_F(VAMSTest, VAMS_MATRIX) {
    // Test cases for VAMS_MATRIX
    weighted_t weighted_PI{"Pitch_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_YA{"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_RO{"Roll_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_PA{"Path_verif", 0.0, NOT_OFF_COURSE};

    // Assuming totalWeightedStatus <= WEIGHTED_THRESHOLD
    abort_t result = vams.VAMS_MATRIX(weighted_PI, weighted_YA, weighted_RO, weighted_PA);
    EXPECT_EQ(result, NO_LOSS_OF_CONTROL);

    // Assuming totalWeightedStatus > WEIGHTED_THRESHOLD
    weighted_PA.vstatus = FAR_OFF_COURSE;
    result = vams.VAMS_MATRIX(weighted_PI, weighted_YA, weighted_RO, weighted_PA);
    EXPECT_EQ(result, LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VERIFY_PITCH_EdgeCases) {
    // Test cases for VERIFY_PITCH edge cases
    weighted_t result = vams.VERIFY_PITCH(0.0, 0.0, 0.0); // No acceleration, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    
    result = vams.VERIFY_PITCH(0.0, 0.0, 9.81); // Vertical acceleration, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    
    result = vams.VERIFY_PITCH(9.81, 0.0, 0.0); // Horizontal acceleration, pitch should be close to 90 degrees
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL); // As pitch is close to 90 degrees, it should be considered LOSS_OF_CONTROL
}

TEST_F(VAMSTest, VERIFY_YAW_EdgeCases) {
    // Test cases for VERIFY_YAW edge cases
    weighted_t result = vams.VERIFY_YAW(0.0, 0.0); // No magnetic field, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    
    result = vams.VERIFY_YAW(1.0, 0.0); // Magnetic field in the X-axis, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    
    result = vams.VERIFY_YAW(0.0, 1.0); // Magnetic field in the Y-axis, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VERIFY_ROLL_EdgeCases) {
    // Test cases for VERIFY_ROLL edge cases
    weighted_t result = vams.VERIFY_ROLL(0.0, 0.0, 0.0); // No acceleration, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    
    result = vams.VERIFY_ROLL(0.0, 0.0, 9.81); // Vertical acceleration, should be considered NO_LOSS_OF_CONTROL
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);

    result = vams.VERIFY_ROLL(9.81, 0.0, 0.0); // Horizontal acceleration, roll should be close to 90 degrees
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL); // As roll is close to 90 degrees, it should be considered LOSS_OF_CONTROL
}

TEST_F(VAMSTest, VERIFY_PATH_EdgeCases) {
    // Test cases for VERIFY_PATH edge cases
    Vector3D initloc{0.0, 0.0};
    Vector3D targetloc{0.0, 0.0};
    double boundaryRadius = 1.0; // Assuming boundary radius is 1 unit

    // Assuming the same location, should be considered NOT_OFF_COURSE
    weighted_t result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);
    EXPECT_EQ(result.vstatus, NOT_OFF_COURSE);

    // Assuming a very large boundary radius, should be considered NOT_OFF_COURSE
    boundaryRadius = 1000.0; // A large boundary radius
    result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);
    EXPECT_EQ(result.vstatus, NOT_OFF_COURSE);

    // Assuming a target location far from the initial location, should be considered FAR_OFF_COURSE
    targetloc = {10.0, 10.0};
    result = vams.VERIFY_PATH(initloc, targetloc, boundaryRadius);
    EXPECT_EQ(result.vstatus, FAR_OFF_COURSE);
}

TEST_F(VAMSTest, VAMS_MATRIX_EdgeCases) {
    // Test cases for VAMS_MATRIX edge cases
    weighted_t weighted_PI{"Pitch_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_YA{"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_RO{"Roll_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_PA{"Path_verif", 0.0, NOT_OFF_COURSE};

    // Assuming totalWeightedStatus exactly equal to WEIGHTED_THRESHOLD
    abort_t result = vams.VAMS_MATRIX(weighted_PI, weighted_YA, weighted_RO, weighted_PA);
    EXPECT_EQ(result, NO_LOSS_OF_CONTROL);

    // Assuming totalWeightedStatus slightly greater than WEIGHTED_THRESHOLD
    weighted_PA.vstatus = FAR_OFF_COURSE;
    result = vams.VAMS_MATRIX(weighted_PI, weighted_YA, weighted_RO, weighted_PA);
    EXPECT_EQ(result, LOSS_OF_CONTROL);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
