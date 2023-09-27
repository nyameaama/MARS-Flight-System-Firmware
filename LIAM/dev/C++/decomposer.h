#ifndef DECOMPOSER_
#define DECOMPOSER_

#include <vector>
#include <algorithm>
#include <string>

class DECOMPOSER {
    public:
        static double mapToRange(double input, double input_start, double input_end, 
                            double output_start, double output_end);
        
        static std::vector<double> decomposeFL(std::string angleType, double angleValue);

        static std::vector<double> decomposeFR(std::string angleType, double angleValue);

        static std::vector<double> decomposeRL(std::string angleType, double angleValue);

        static std::vector<double> decomposeRR(std::string angleType, double angleValue);

        static std::vector<double> pitchAxisToSweep(double pitch_deg);

        static std::vector<double> rollAxisToSweep(double roll_deg);
};

#endif