#include <iostream>
#include <vector>
#include <cstddef>
#include"_pid.h"

double linearInterpolate(double input, double input_start, double input_end, 
                                        double output_start, double output_end);
                                        
// Define the PID controller functions here (as provided in the previous response)

int main() {
    // Sample target and current values
    std::vector<double> target = {68.0, 0.0, 0.0};
    std::vector<double> current = {75.9, 0.0, 0.0};

    // PID control parameters
    double kp = 1.01;
    double ki = 0.12;
    double kd = 0.68;
    
    double dt = 0.1;  // Time step
    double min_output = 0;
    double max_output = 90;

    // Initialize integral and previous_errors vectors
    std::vector<double> integral = {0.0, 0.0, 0.0};
    std::vector<double> previous_errors = {0.0, 0.0, 0.0};

    PID *pobj = new PID();
    // Call the PID controller
    //for(int i = 0; i < 100; i++){
    std::vector<double> control_signals = pobj -> pid_controller(target, current, kp, ki, kd,
                                                         integral, previous_errors, dt,
                                                         min_output, max_output);

    double elem = control_signals.front();
    double lI = linearInterpolate(elem, 0, 90, 270, 230);
    std::cout << " " << lI << std::endl;
    //}
    // Print the control signals
    /*std::cout << "Control Signals:";
    for (std::size_t i = 0; i < control_signals.size(); ++i) {
        std::cout << " " << control_signals[i];
    }
    std::cout << std::endl;*/

    return 0;
}

double linearInterpolate(double input, double input_start, double input_end, 
                                        double output_start, double output_end) {
    // Map input range to output range
    double slope = (output_end - output_start) / (input_end - input_start);
    double output = output_start + slope * (input - input_start);
    return output;
}