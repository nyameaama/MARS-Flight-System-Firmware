def calculate_error(target, current):
    return [target[i] - current[i] for i in range(len(target))]

def calculate_integral(integral, errors, dt):
    if isinstance(integral, list):
        return [integral[i] + errors[i] * dt for i in range(len(integral))]
    else:
        return integral + errors * dt
    
def calculate_derivative(previous_error, error, dt):
    return (error - previous_error) / dt

def calculate_control_signal(kp, ki, kd, error, integral, derivative, min_output, max_output):
    control_signal = kp * error + ki * integral + kd * derivative
    # Clamp the control signal within the specified range
    return max(min_output, min(max_output, control_signal))

def pid_controller(target, current, kp, ki, kd, integral, previous_errors, dt, min_output, max_output):
    errors = calculate_error(target, current)
    integrals = [calculate_integral(integral[i], errors[i], dt) for i in range(3)]
    derivatives = [calculate_derivative(previous_errors[i], errors[i], dt) for i in range(3)]

    control_signals = [
        calculate_control_signal(kp, ki, kd, errors[i], integrals[i], derivatives[i], min_output, max_output)
        for i in range(3)
    ]

    return control_signals