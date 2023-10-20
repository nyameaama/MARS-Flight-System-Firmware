import math

def calculate_acceleration(mass, total_force):
    acceleration = (
        total_force[0] / mass,
        total_force[1] / mass,
        total_force[2] / mass
    )
    return acceleration

def calculate_inertia(mass, velocity):
    inertia = (
        mass * velocity[0],
        mass * velocity[1],
        mass * velocity[2]
    )
    return inertia

def calculate_total_force(thrust, drag, lift, gravity, inertia):
    total_force = (
        thrust[0] + drag[0],
        thrust[1] + drag[1],
        thrust[2] + drag[2] + lift[2] - gravity[2]
    )
    total_force = (
        total_force[0] - inertia[0],
        total_force[1] - inertia[1],
        total_force[2] - inertia[2]
    )
    return total_force


def calculate_thrust(throttle, airspeed):
    # Constants
    THRUST_CONSTANT = 0.01  # Adjust this value based on motor and propeller characteristics

    # Constant air density
    air_density = 1.225  # kg/m^3 (typical air density at sea level)

    # Calculate thrust force
    thrust = THRUST_CONSTANT * throttle * air_density * airspeed**2

    # Return thrust force vector
    return (thrust, 0, 0)

def calculate_drag(velocity):
    drag = (
        -0.1 * velocity[0],
        -0.1 * velocity[1],
        -0.1 * velocity[2]
    )
    return drag

def calculate_lift(velocity, angle_of_attack):
    # Implement the lift calculation based on the given parameters
    # You can use lift coefficients, air density, wing area, etc.

    # Example calculation: lift proportional to velocity and angle of attack
    lift_coefficient = 1  # Adjust this value based on your aircraft model
    wing_area = 1  # Adjust this value based on your aircraft model
    air_density = 1.225  # Adjust this value based on your simulation environment

    scaling_factor = 0.001  # Adjust this value as needed to prevent overflow

    lift = (
        lift_coefficient * wing_area * air_density * velocity[0]**2 * angle_of_attack * scaling_factor,
        lift_coefficient * wing_area * air_density * velocity[1]**2 * angle_of_attack * scaling_factor,
        lift_coefficient * wing_area * air_density * velocity[2]**2 * angle_of_attack * scaling_factor
    )
    return lift

def calculate_gravity(mass):
    gravity = (0, 0, 9.81 * mass)
    return gravity

def update_velocity(velocity, acceleration, dt):
    new_velocity = (
        velocity[0] + acceleration[0] * dt,
        velocity[1] + acceleration[1] * dt,
        velocity[2] + acceleration[2] * dt
    )
    return new_velocity

def update_position(position, velocity, dt):
    new_position = (
        position[0] + velocity[0] * dt,
        position[1] + velocity[1] * dt,
        position[2] + velocity[2] * dt
    )
    return new_position

def update_plane(mass, position, velocity, AOA, throttle, dt):
    thrust = calculate_thrust(throttle, velocity[0])
    drag = calculate_drag(velocity)
    lift = calculate_lift(velocity,AOA)
    gravity = calculate_gravity(mass)
    inertia = calculate_inertia(mass, velocity)

    total_force = calculate_total_force(thrust, drag, lift, gravity, inertia)
    acceleration = calculate_acceleration(mass, total_force)
    new_velocity = update_velocity(velocity, acceleration, dt)
    new_position = update_position(position, new_velocity, dt)

    return new_position, new_velocity