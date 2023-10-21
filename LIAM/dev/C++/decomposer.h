#ifndef DECOMPOSER_
#define DECOMPOSER_

#include <vector>
#include <algorithm>
#include <string>
#include "_pid.h"

class DECOMPOSER {
    public:
        static double linearInterpolate(double input, double input_start, double input_end,
                                            double output_start, double output_end);

        static double mapToRangePitch(double currentInput, double targetInput, double output_start, double output_end);

        static double mapToRangeRoll(double currentInput, double targetInput, double output_start, double output_end);
        
        static std::vector<double> decomposeFL(std::string angleType, double angleValueCurrent, double angleValueTarget);

        static std::vector<double> decomposeFR(std::string angleType, double angleValueCurrent, double angleValueTarget);

        static std::vector<double> decomposeRL(std::string angleType, double angleValueCurrent, double angleValueTarget);

        static std::vector<double> decomposeRR(std::string angleType, double angleValueCurrent, double angleValueTarget);

        static std::vector<double> pitchAxisToSweep(double pitch_degCurrent, double pitch_degTarget);

        static std::vector<double> rollAxisToSweep(double roll_degCurrent, double roll_degTarget);
};

#endif