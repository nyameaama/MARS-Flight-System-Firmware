import math

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

trajectory = [(1, 2, 3), (4, 5, 6), (7, 8, 9), (10, 11, 12)]
current_location = (7.6, 8.8, 3.6)

nearest_forward_point = calculate_nearest_forward_point(trajectory, current_location)
print(current_location)
print(nearest_forward_point)  # Output: (7, 8, 9)
print(calculate_velocity(current_location, nearest_forward_point))