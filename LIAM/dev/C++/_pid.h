#ifndef _PID_
#define _PID_

#include <cstddef>  // Include for size_t
#include <iostream>
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