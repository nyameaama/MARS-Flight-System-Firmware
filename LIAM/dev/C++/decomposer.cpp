#include "decomposer.h"

#include <vector>
#include <algorithm>
#include <string>

//PITCH
std::vector<double> integralPitch = {0.0, 0.0, 0.0};
std::vector<double> previous_errorsPitch = {0.0, 0.0, 0.0};
// Pitch PID control parameters
double kp_pitch = 1.01;
double ki_pitch = 0.12;
double kd_pitch = 0.68;
double dt_pitch = 0.1;  // Time step
double min_outputPitch = 0;
double max_outputPitch = 90;

//ROLL
// PID control parameters
double kp_roll = 1.01;
double ki_roll = 0.12;
double kd_roll = 0.68;
double dt_roll = 0.1;  // Time step
double min_output_roll = 0;
double max_output_roll = 90;

// Initialize integral and previous_errors vectors
std::vector<double> integralRoll = {0.0, 0.0, 0.0};
std::vector<double> previous_errorsRoll = {0.0, 0.0, 0.0};


double DECOMPOSER::linearInterpolate(double input, double input_start, double input_end, 
                                        double output_start, double output_end) {
    // Map input range to output range
    double slope = (output_end - output_start) / (input_end - input_start);
    double output = output_start + slope * (input - input_start);
    return output;
}

double DECOMPOSER::mapToRangePitch(double currentInput, double targetInput, double output_start, double output_end) {
    //Run PID through to output
    // Sample target and current values
    //PITCH PID CONTROLLER
    std::vector<double> target = {targetInput, 0.0, 0.0};
    std::vector<double> current = {currentInput, 0.0, 0.0};

    PID *pobj = new PID();
    // Call the PID controller
    std::vector<double> control_signals = pobj -> pid_controller(target, current, kp_pitch, ki_pitch, kd_pitch,
                                                         integralPitch, previous_errorsPitch, dt_pitch,
                                                         min_outputPitch, max_outputPitch);
    //linear interpolate to range specified
    double elem = control_signals.front();
    double interpolatedValue = linearInterpolate(elem, 0, 90, output_start, output_end);
    return interpolatedValue;
}

double DECOMPOSER::mapToRangeRoll(double currentInput, double targetInput, double output_start, double output_end) {
    //Run PID through to output
    // Sample target and current values
    // ROLL PID CONTROLLER
    std::vector<double> target = {targetInput, 0.0, 0.0};
    std::vector<double> current = {currentInput, 0.0, 0.0};

    PID *pobj = new PID();
    // Call the PID controller
    std::vector<double> control_signals = pobj -> pid_controller(target, current, kp_roll, ki_roll, kd_roll,
                                                         integralRoll, previous_errorsRoll, dt_roll,
                                                         min_output_roll, max_output_roll);
    //linear interpolate to range specified
    double elem = control_signals.front();
    double interpolatedValue = linearInterpolate(elem, 0, 90, output_start, output_end);
    return interpolatedValue;
}

std::vector<double> DECOMPOSER::decomposeFL(std::string angleType, double angleValueCurrent, double angleValueTarget) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (FL) -> 180 - 270
        //Limit to 40 deg movement from deployed pos
        //ServoPos (FL) -> 230 - 270 (with limit)
        finalPos = mapToRangePitch(angleValueCurrent, angleValueTarget, 270, 230);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (FL) -> 180 - 270 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (FL) -> 230 - 270 (with limit)
        finalPos = mapToRangeRoll(angleValueCurrent, angleValueTarget, 270, 230);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::decomposeFR(std::string angleType, double angleValueCurrent, double angleValueTarget) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (FR) -> 90 - 180 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (FR) -> 90 - 130 (with limit)
        finalPos = mapToRangePitch(angleValueCurrent, angleValueTarget, 90, 130);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (FR) -> 90 - 180 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (FR) -> 90 - 130 (with limit)
        finalPos = mapToRangeRoll(angleValueCurrent, angleValueTarget, 90, 130);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::decomposeRL(std::string angleType, double angleValueCurrent, double angleValueTarget) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (RL) -> 180 - 270 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (RL) -> 230 - 270 (with limit)
        finalPos = mapToRangePitch(angleValueCurrent, angleValueTarget, 270, 230);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (RL) -> 180 - 270 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (RL) -> 230 - 270 (with limit)
        finalPos = mapToRangeRoll(angleValueCurrent, angleValueTarget, 270, 230);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::decomposeRR(std::string angleType, double angleValueCurrent, double angleValueTarget) {
    double finalPos = 0;
    std::vector<double> pos;
    
    if (angleType == "Pitch") {
        // Angle type is pitch:
        // Pitch -> 0 - 90
        // ServoPos (RR) -> 90 - 180 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (RR) -> 90 - 130 (with limit)
        finalPos = mapToRangePitch(angleValueCurrent, angleValueTarget, 90, 130);
        pos.push_back(finalPos);
    }

    if (angleType == "Roll") {
        // Angle type is Roll:
        // Roll -> 0 - 180
        // ServoPos (RR) -> 90 - 180 (actual)
        //Limit to 40 deg movement from deployed pos
        //ServoPos (RR) -> 90 - 130 (with limit)
        finalPos = mapToRangeRoll(angleValueCurrent, angleValueTarget, 90, 130);
        pos.push_back(finalPos);
    }

    return pos;
}

std::vector<double> DECOMPOSER::pitchAxisToSweep(double pitch_degCurrent, double pitch_degTarget) {
    std::vector<double> pos;
    
    if (pitch_degTarget >= pitch_degCurrent) {
        // Positive moment required, so rear wings will move
        std::vector<double> tp1 = decomposeRL("Pitch", pitch_degCurrent, pitch_degTarget);
        std::vector<double> tp2 = decomposeRR("Pitch", pitch_degCurrent, pitch_degTarget);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    if (pitch_degTarget < pitch_degCurrent) {
        // Negative moment required, so front wings will move
        std::vector<double> tp1 = decomposeFL("Pitch", pitch_degCurrent, pitch_degTarget);
        std::vector<double> tp2 = decomposeFR("Pitch", pitch_degCurrent, pitch_degTarget);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    return pos;
}

std::vector<double> DECOMPOSER::rollAxisToSweep(double roll_degCurrent, double roll_degTarget) {
    std::vector<double> pos;
    
    if (roll_degTarget >= roll_degCurrent) {
        // Positive moment requested, so right side wings will move
        std::vector<double> tp1 = decomposeFR("Roll", roll_degCurrent, roll_degTarget);
        std::vector<double> tp2 = decomposeRR("Roll", roll_degCurrent, roll_degTarget);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    if (roll_degTarget < roll_degCurrent) {
        // Negative moment requested, so left side wings will move
        std::vector<double> tp1 = decomposeFL("Roll", roll_degCurrent, roll_degTarget);
        std::vector<double> tp2 = decomposeRL("Roll", roll_degCurrent, roll_degTarget);
        pos.insert(pos.end(), tp1.begin(), tp1.end());
        pos.insert(pos.end(), tp2.begin(), tp2.end());
    }

    return pos;
}