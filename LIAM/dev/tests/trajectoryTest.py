import sys
sys.path.insert(0,'/Users/nyameaama/Documents/MARS-Firmware/LIAM/dev')
import utility
import matplotlib.pyplot as plt

import time
sys.path.insert(0,'/Users/nyameaama/Documents/MARS-Firmware/LIAM/dev/simulator')
import physics
import visualization
import PID

'''
start_lat = 40.7128  # Latitude of start point
start_lon = -74.0060  # Longitude of start point
end_lat = 34.0522  # Latitude of end point
end_lon = -118.2437  # Longitude of end point
num_points = 10  # Number of points in the generated path

path = generate_path(start_lat, start_lon, end_lat, end_lon, num_points)

print("Generated Path:")
for point in path:
    print(point)

plot_path(path)
'''


# Initial state
mass = 1  # kg
initial_position = (0, 0, 5)  # (x, y, z) coordinates
initial_velocity = (5, 0, 15)  # (vx, vy, vz) velocities

# Time step and duration
dt = 0.1  # time step in seconds
duration = 10  # duration in seconds

# Simulation loop
num_steps = int(duration / dt)
position = initial_position
velocity = initial_velocity

posVector = []
AOA = 15
throttle = 0

for step in range(num_steps):
    # Update the plane's state
    position, velocity = physics.update_plane(mass, position, velocity, AOA, throttle, dt)

    # Get the new position from the updated state
    new_position = position
    # Print the new position
    print(f"Step {step+1}: New Position = {new_position}")

    posVector.append(new_position)
    if(utility.get_last_value(posVector,'z') <= 0):
        break

    # Wait for the time step before proceeding to the next iteration
    # (useful  to simulate the time progression realistically)
    #time.sleep(dt)

posX, posY, posZ = utility.extractXY(posVector)
# Visualize the trajectory animation
visualization.visualize_trajectory(posX,posY,posZ)

