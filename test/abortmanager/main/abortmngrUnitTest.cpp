#include "gtest/gtest.h"  // Include the Google Test framework
#include "../abort.h"        // Include the header file of the code to be tested

// Define a test fixture class for common setup/teardown
class VAMSTest : public ::testing::Test {
protected:
    VAMS vams;

    // Optional: Setup code to be executed before each test
    void SetUp() override {
        // Initialize any necessary resources or variables
    }

    // Optional: Teardown code to be executed after each test
    void TearDown() override {
        // Clean up resources if needed
    }
};

// Test case for VERIFY_PITCH function
TEST_F(VAMSTest, VerifyPitchWithinThreshold) {
    // Test with values within the threshold
    weighted_t result = vams.VERIFY_PITCH(0.0, 0.0, 9.81);
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
    std::cout<< "\n\nResults: " << result.name << " " << result.data << result.vstatus << NO_LOSS_OF_CONTROL << "\n\n\n";
}

TEST_F(VAMSTest, VerifyPitchOutsideThreshold) {
    // Test with values outside the threshold
    weighted_t result = vams.VERIFY_PITCH(0.0, 0.0, 20.0);
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL);
}

// Test case for VERIFY_YAW function
TEST_F(VAMSTest, VerifyYawWithinThreshold) {
    // Test with values within the threshold
    weighted_t result = vams.VERIFY_YAW(1.0, 0.0);
    EXPECT_EQ(result.vstatus, NO_LOSS_OF_CONTROL);
}

TEST_F(VAMSTest, VerifyYawOutsideThreshold) {
    // Test with values outside the threshold
    weighted_t result = vams.VERIFY_YAW(2.0, 0.0);
    EXPECT_EQ(result.vstatus, LOSS_OF_CONTROL);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
