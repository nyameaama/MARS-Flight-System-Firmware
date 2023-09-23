#include "_pid.h"

// Calculate error between target and current values
std::vector<double> PID::calculate_error(const std::vector<double>& target, const std::vector<double>& current) {
    std::vector<double> errors(target.size());
    for (std::size_t i = 0; i < target.size(); ++i) {
        errors[i] = target[i] - current[i];
    }
    return errors;
}

// Calculate integral term for PID control
std::vector<double> PID::calculate_integral(const std::vector<double>& integral, const std::vector<double>& errors, double dt) {
    std::vector<double> new_integral(integral.size());
    for (std::size_t i = 0; i < integral.size(); ++i) {
        new_integral[i] = integral[i] + errors[i] * dt;
    }
    return new_integral;
}

// Calculate derivative term for PID control
double PID::calculate_derivative(double previous_error, double error, double dt) {
    return (error - previous_error) / dt;
}

// Calculate control signal with output clamping
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

// PID controller
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