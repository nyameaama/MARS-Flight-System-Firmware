#include <iostream>
#include <vector>
#include <cstddef>
#include"_pid.h"

// Define the PID controller functions here (as provided in the previous response)

int main() {
    // Sample target and current values
    std::vector<double> target = {78.0, 0.0, 0.0};
    std::vector<double> current = {34.0, 0.0, 0.0};

    // PID control parameters
    double kp = 0.5;
    double ki = 0.1;
    double kd = 0.7;
    double dt = 0.6;  // Time step
    double min_output = -90.0;
    double max_output = 90.0;

    // Initialize integral and previous_errors vectors
    std::vector<double> integral = {0.0, 0.0, 0.0};
    std::vector<double> previous_errors = {0.0, 0.0, 0.0};

    PID *pobj = new PID();
    // Call the PID controller
    std::vector<double> control_signals = pobj -> pid_controller(target, current, kp, ki, kd,
                                                         integral, previous_errors, dt,
                                                         min_output, max_output);

    // Print the control signals
    std::cout << "Control Signals:";
    for (std::size_t i = 0; i < control_signals.size(); ++i) {
        std::cout << " " << control_signals[i];
    }
    std::cout << std::endl;

    return 0;
}