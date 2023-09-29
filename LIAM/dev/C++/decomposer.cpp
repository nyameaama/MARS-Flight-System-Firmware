#include "decomposer.h"

#include <vector>
#include <algorithm>
#include <string>

double DECOMPOSER::mapToRange(double input, double input_start, double input_end, double output_start, double output_end) {
    // Map input range to output range
    double slope = (output_end - output_start) / (input_end - input_start);
    double output = output_start + slope * (input - input_start);
    return output;
}

std::vector<double> DECOMPOSER::decomposeFL(std::string angleType, double angleValue) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (FL) -> 180 - 270
        finalPos = mapToRange(angleValue, 0, 90, 270, 180);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (FL) -> 180 - 270
        finalPos = mapToRange(angleValue, 0, 180, 270, 180);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::decomposeFR(std::string angleType, double angleValue) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (FR) -> 90 - 180
        finalPos = mapToRange(angleValue, 0, 90, 90, 180);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (FR) -> 90 - 180
        finalPos = mapToRange(angleValue, 0, 180, 90, 180);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::decomposeRL(std::string angleType, double angleValue) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (RL) -> 180 - 270
        finalPos = mapToRange(angleValue, 0, 90, 270, 180);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (RL) -> 180 - 270
        finalPos = mapToRange(angleValue, 0, 180, 270, 180);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::decomposeRR(std::string angleType, double angleValue) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (RR) -> 90 - 180
        finalPos = mapToRange(angleValue, 0, 90, 90, 180);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (RR) -> 90 - 180
        finalPos = mapToRange(angleValue, 0, 180, 90, 180);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::pitchAxisToSweep(double pitch_deg) {
    std::vector<double> pos;
    
    if (pitch_deg >= 0) {
        // Positive moment requested, so rear wings will move
        std::vector<double> tp1 = decomposeRL("Pitch", pitch_deg);
        std::vector<double> tp2 = decomposeRR("Pitch", pitch_deg);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    if (pitch_deg < 0) {
        // Negative moment requested, so rear wings will move
        // Multiply by -1 to get the positive value
        std::vector<double> tp1 = decomposeFL("Pitch", -pitch_deg);
        std::vector<double> tp2 = decomposeFR("Pitch", -pitch_deg);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    return pos;
}

std::vector<double> DECOMPOSER::rollAxisToSweep(double roll_deg) {
    std::vector<double> pos;
    
    if (roll_deg >= 0) {
        // Positive moment requested, so right side wings will move
        std::vector<double> tp1 = decomposeFR("Roll", roll_deg);
        std::vector<double> tp2 = decomposeRR("Roll", roll_deg);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    if (roll_deg < 0) {
        // Negative moment requested, so left side wings will move
        // Multiply by -1 to get the positive value
        std::vector<double> tp1 = decomposeFL("Roll", -roll_deg);
        std::vector<double> tp2 = decomposeRL("Roll", -roll_deg);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    return pos;
}