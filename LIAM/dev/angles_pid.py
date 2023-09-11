import PID
import utility

def define_target(initial_values,target_values, min, max):
    # Define PID gains
    kp = 0.5
    ki = 0.1
    kd = 0.7

    dt = 0.1

    # Initialize variables
    integral = [0.0, 0.0, 0.0]
    previous_errors = [0.0, 0.0, 0.0]

    # Calculate control signals using PID controller
    control_signals = PID.pid_controller(
        target_values, initial_values, kp, ki, kd, integral, previous_errors, dt,min,max
    )

    # Update variables for the next iteration
    integral = [PID.calculate_integral(integral[i], control_signals[i], dt) for i in range(3)]
    previous_errors = PID.calculate_error(target_values, initial_values)
    initial_values = [initial_values[i] + control_signals[i] * dt for i in range(3)]

    # Print the current values for debugging
    print("Control signals:", control_signals)
    print("Current values:", initial_values)
    print()

#Pitch
define_target([34,0,0],[78,0,0],-90,90)

#Roll
define_target([56,0,0],[108,0,0],-180,180)
