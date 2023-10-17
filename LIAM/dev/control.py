from angles_pid import *
import sys
import trajectoryTrace as tr
import math

def calculate_pitch_and_roll(current_pos, next_waypoint):
    # Calculate the direction vector from current position to the next waypoint
    direction_vector = (next_waypoint[0] - current_pos[0], 
                        next_waypoint[1] - current_pos[1], 
                        next_waypoint[2] - current_pos[2])

    # Calculate the pitch angle (in degrees)
    pitch_radians = math.atan2(direction_vector[2], math.sqrt(direction_vector[0]**2 + direction_vector[1]**2))
    pitch_degrees = math.degrees(pitch_radians)

    # Calculate the roll angle (in degrees)
    roll_radians = math.atan2(direction_vector[1], direction_vector[0])
    roll_degrees = math.degrees(roll_radians)

    return pitch_degrees, roll_degrees

# Example usage:
current_pos = (10, 39, 20)
next_waypoint = (50, 67, 38)
pitch, roll = calculate_pitch_and_roll(current_pos, next_waypoint)
print(f"Pitch Angle: {pitch} degrees")
print(f"Roll Angle: {roll} degrees")