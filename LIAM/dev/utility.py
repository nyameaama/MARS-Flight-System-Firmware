'''
MIT License

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
SOFTWARE.
'''

import matplotlib.pyplot as plt
import math

def plot_path(path):
    #Plots the given path of coordinates.
    latitudes = [point[0] for point in path]
    longitudes = [point[1] for point in path]

    plt.plot(longitudes, latitudes, 'bo-')
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.title('Generated Path')
    plt.grid(True)
    plt.show()

def extractXY(points):
    extrctX = [point[0] for point in points]
    extrctY = [point[1] for point in points]
    extrctZ = [point[2] for point in points]
    return extrctX,extrctY,extrctZ

def get_last_value(points,variable):
    if len(points) == 0:
        return None
    if variable == 'x':
        last_point = points[-1]
        x, _, _ = last_point
        return x
    if variable == 'y':
        last_point = points[-1]
        _, y, _ = last_point
        return y
    if variable == 'z':
        last_point = points[-1]
        _, _, z = last_point
        return z
    return ValueError
    
def calculate_distance(point1, point2):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)

def calculate_nearest_forward_point(trajectory_points, current_location):
    nearest_distance = float('inf')
    nearest_point = None

    for point in trajectory_points:
        distance = calculate_distance(current_location, point)
        if distance < nearest_distance:
            nearest_distance = distance
            nearest_point = point

    return nearest_point

def calculate_velocity(current_point, target_point):
    dx = target_point[0] - current_point[0]
    dy = target_point[1] - current_point[1]
    dz = target_point[2] - current_point[2]
    
    vx = dx
    vy = dy
    vz = dz
    
    return vx, vy, vz

def calculate_angle_of_attack(vx, vy, vz):
    # Calculate the magnitude of the horizontal velocity
    v_horizontal = math.sqrt(vx**2 + vy**2)
    
    # Calculate the angle of attack using the arctan2 function
    angle_of_attack = math.degrees(math.atan2(vz, v_horizontal))
    
    return angle_of_attack

def calculate_pitch_roll_yaw(vx, vy, vz):
    # Calculate pitch (rotation around x-axis)
    pitch = math.atan2(-vz, math.sqrt(vx**2 + vy**2))
    
    # Calculate roll (rotation around y-axis)
    roll = math.atan2(vy, vx)
    
    # Calculate yaw (rotation around z-axis)
    yaw = 0  # Yaw is not determined by velocity components alone, additional information is needed
    
    return pitch, roll, yaw

def append_array_to_tuples(first_array, second_array):
    if len(first_array) != len(second_array):
        print(f"Error: The arrays have different lengths. First array length: {len(first_array)}, Second array length: {len(second_array)}")
        return None

    result_array = [(x, y, z) for (x, y), z in zip(first_array, second_array)]
    return result_array

def has_passed_target(current_point, target_point):
    current_x, current_y, current_z = current_point
    target_x, target_y, target_z = target_point

    # Calculate the distance between the current point and the target point
    distance = math.sqrt((target_x - current_x)**2 + (target_y - current_y)**2 + (target_z - current_z)**2)

    # Check if the distance is less than or equal to a small threshold value
    # indicating that the current point has moved past the target point
    threshold = 0.1  # Adjust this threshold as needed
    if distance <= threshold:
        return False
    else:
        return True