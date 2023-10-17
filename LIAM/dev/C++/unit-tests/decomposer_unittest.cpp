#include <iostream>
#include <vector>
#include"decomposer.h"

int main() {

    DECOMPOSER *dObj = new DECOMPOSER();
    // Test pitch axis conversion
    double pitch_deg = 45.0;  // Example pitch angle in degrees

    std::vector<double> pitch_positions = dObj -> pitchAxisToSweep(pitch_deg);

    std::cout << "Pitch Axis Positions:" << std::endl;
    for (size_t i = 0; i < pitch_positions.size(); ++i) {
        std::cout << "Servo " << i + 1 << ": " << pitch_positions[i] << " degrees" << std::endl;
    }

    // Test roll axis conversion
    double roll_deg = -30.0;  // Example roll angle in degrees

    std::vector<double> roll_positions = dObj -> rollAxisToSweep(roll_deg);

    std::cout << "Roll Axis Positions:" << std::endl;
    for (size_t i = 0; i < roll_positions.size(); ++i) {
        std::cout << "Servo " << i + 1 << ": " << roll_positions[i] << " degrees" << std::endl;
    }

    delete dObj;

    return 0;
}