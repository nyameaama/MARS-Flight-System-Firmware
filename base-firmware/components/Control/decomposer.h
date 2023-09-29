/*MIT License
Copyright (c) 2023 limitless Aeronautics
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

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