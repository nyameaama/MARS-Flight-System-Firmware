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

#include "_pid.h"

//____________________________________________________________
/* Calculate error between target and current values

===========================================================================
*/
std::vector<double> PID::calculate_error(const std::vector<double>& target, const std::vector<double>& current) {
    std::vector<double> errors(target.size());
    for (std::size_t i = 0; i < target.size(); ++i) {
        errors[i] = target[i] - current[i];
    }
    return errors;
}

//____________________________________________________________
/* // Calculate integral term for PID control

===========================================================================
*/
std::vector<double> PID::calculate_integral(const std::vector<double>& integral, const std::vector<double>& errors, double dt) {
    std::vector<double> new_integral(integral.size());
    for (std::size_t i = 0; i < integral.size(); ++i) {
        new_integral[i] = integral[i] + errors[i] * dt;
    }
    return new_integral;
}

//____________________________________________________________
/* // Calculate derivative term for PID control

===========================================================================
*/
double PID::calculate_derivative(double previous_error, double error, double dt) {
    return (error - previous_error) / dt;
}

//____________________________________________________________
/* // Calculate control signal with output clamping

===========================================================================
*/
double PID::calculate_control_signal(double kp, double ki, double kd, double error, double integral, double derivative,
                                double min_output, double max_output) {
    double control_signal = kp * error + ki * integral + kd * derivative;
    // Clamp the control signal within the specified range
    if (control_signal < min_output) {
        return min_output;
    } else if (control_signal > max_output) {
        return max_output;
    }
    return control_signal;
}

//____________________________________________________________
/* Main subroutine -> PID controller
===========================================================================

===========================================================================
*/
std::vector<double> PID::pid_controller(const std::vector<double>& target, const std::vector<double>& current,
                                   double kp, double ki, double kd, std::vector<double>& integral,
                                   std::vector<double>& previous_errors, double dt,
                                   double min_output, double max_output) {
    std::vector<double> errors = calculate_error(target, current);
    std::vector<double> integrals = calculate_integral(integral, errors, dt);
    std::vector<double> derivatives(previous_errors.size());

    std::vector<double> control_signals(target.size());
    for (std::size_t i = 0; i < target.size(); ++i) {
        derivatives[i] = calculate_derivative(previous_errors[i], errors[i], dt);
        control_signals[i] = calculate_control_signal(kp, ki, kd, errors[i], integrals[i], derivatives[i],
                                                      min_output, max_output);
    }

    integral = integrals;
    previous_errors = errors;

    return control_signals;
}