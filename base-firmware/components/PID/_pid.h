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

#ifndef _PID_
#define _PID_

#include <cstddef>  // Include for size_t
#include <vector>

class PID
{
  public:
    std::vector<double> calculate_error(const std::vector<double>& target,
                                        const std::vector<double>& current);

    std::vector<double> calculate_integral(const std::vector<double>& integral,
                                           const std::vector<double>& errors, double dt);

    double calculate_derivative(double previous_error, double error, double dt);

    double calculate_control_signal(double kp, double ki, double kd, double error, double integral,
                                    double derivative, double min_output, double max_output);

    std::vector<double> pid_controller(const std::vector<double>& target,
                                       const std::vector<double>& current, double kp, double ki,
                                       double kd, std::vector<double>& integral,
                                       std::vector<double>& previous_errors, double dt,
                                       double min_output, double max_output);
};

#endif  //_PID_