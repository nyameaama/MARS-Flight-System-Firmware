import PID
import utility

# Define PID gains
kp = 0.5
ki = 0.1
kd = 0.7

# Set initial and target values for vx, vy, and vz
initial_values = [76, 8, 0]
target_values = [78, 88, 0]

# Simulation parameters
dt = 0.1
duration = 5.0

# Initialize variables
integral = [0.0, 0.0, 0.0]
previous_errors = [0.0, 0.0, 0.0]

# Simulation loop
num_steps = int(duration / dt)

for step in range(num_steps):
    # Calculate control signals using PID controller
    control_signals = PID.pid_controller(
        target_values, initial_values, kp, ki, kd, integral, previous_errors, dt,-90,90
    )

    # Update variables for the next iteration
    integral = [PID.calculate_integral(integral[i], control_signals[i], dt) for i in range(3)]
    previous_errors = PID.calculate_error(target_values, initial_values)
    initial_values = [initial_values[i] + control_signals[i] * dt for i in range(3)]

    # Print the current values for debugging
    print("Step:", step+1)
    print("Control signals:", control_signals)
    print("Current values:", initial_values)
    print()
