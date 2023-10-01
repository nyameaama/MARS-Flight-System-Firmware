#include <iostream>
#include "../abort.h"
#include <cassert>

void runTests() {
    VAMS vams;

    // Test VERIFY_PITCH
    weighted_t result1 = vams.VERIFY_PITCH(0.0, 9.8, 0.0);
    assert(result1.vstatus == NO_LOSS_OF_CONTROL);

    // Test VERIFY_YAW
    weighted_t result2 = vams.VERIFY_YAW(1.0, 1.0);
    assert(result2.vstatus == NO_LOSS_OF_CONTROL);

    // Test VERIFY_ROLL
    weighted_t result3 = vams.VERIFY_ROLL(9.8, 0.0, 0.0);
    assert(result3.vstatus == NO_LOSS_OF_CONTROL);

    // Test haversine distance calculation
    double distance = vams.haversine(0.0, 0.0, 0.0, 1.0);
    assert(distance == 111.195);

    // Test VERIFY_PATH
    Vector3D initloc = {0.0, 0.0, 0.0};
    Vector3D targetloc = {0.01, 0.01, 0.0};
    weighted_t result4 = vams.VERIFY_PATH(initloc, targetloc, 0.1);
    assert(result4.vstatus == NOT_OFF_COURSE);

    // Test VAMS_MATRIX - No loss of control
    weighted_t weighted_PI = {"Pitch_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_YA = {"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_RO = {"Roll_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_PA = {"Path_verif", 0.0, NOT_OFF_COURSE};
    abort_t result5 = vams.VAMS_MATRIX(weighted_PI, weighted_YA, weighted_RO, weighted_PA);
    assert(result5 == NO_LOSS_OF_CONTROL);

    // Test VAMS_MATRIX - Loss of control
    weighted_t weighted_PI2 = {"Pitch_verif", 1.5, LOSS_OF_CONTROL};
    weighted_t weighted_YA2 = {"Yaw_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_RO2 = {"Roll_verif", 0.0, NO_LOSS_OF_CONTROL};
    weighted_t weighted_PA2 = {"Path_verif", 0.0, NOT_OFF_COURSE};
    abort_t result6 = vams.VAMS_MATRIX(weighted_PI2, weighted_YA2, weighted_RO2, weighted_PA2);
    assert(result6 == LOSS_OF_CONTROL);

    std::cout << "All tests passed." << std::endl;
}

extern "C" {
    void app_main(void) {
        runTests();
    }
}
