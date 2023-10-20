"""
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
"""
import math
import utility

def calculate_coordinate(lat1, lon1, lat2, lon2, distance):
    """
    Calculates a new coordinate given a starting coordinate, distance, and bearing.
    """
    radius = 6371  # Radius of the Earth in kilometers
    brng = math.radians(distance / radius)  # Convert distance to radians

    lat1 = math.radians(lat1)
    lon1 = math.radians(lon1)

    lat2 = math.asin(math.sin(lat1) * math.cos(brng) +
                     math.cos(lat1) * math.sin(brng) * math.cos(lat2))
    lon2 = lon1 + math.atan2(math.sin(brng) * math.sin(lat2) * math.cos(lat1),
                             math.cos(brng) - math.sin(lat1) * math.sin(lat2))

    return math.degrees(lat2), math.degrees(lon2)

def generate_pathLatLong(start_lat, start_lon, end_lat, end_lon, num_points):
    delta_lat = (end_lat - start_lat) / num_points
    delta_lon = (end_lon - start_lon) / num_points

    path = [(start_lat + i * delta_lat, start_lon + i * delta_lon) for i in range(num_points)]

    return path

def generate_path(start_point, end_point, num_points):
    delta_x = (end_point[0] - start_point[0]) / num_points
    delta_y = (end_point[1] - start_point[1]) / num_points

    path = [(start_point[0] + i * delta_x, start_point[1] + i * delta_y) for i in range(num_points)]

    return path

def generate_altitude_trajectory(initial_altitude, mid_altitude, final_altitude, num_points):
    delta_altitude1 = mid_altitude - initial_altitude
    delta_altitude2 = final_altitude - mid_altitude

    num_points1 = num_points // 2
    num_points2 = num_points - num_points1

    altitude_increment1 = delta_altitude1 / (num_points1 - 1)
    altitude_increment2 = delta_altitude2 / (num_points2 - 1)

    trajectory = [initial_altitude + i * altitude_increment1 for i in range(num_points1)]
    trajectory += [mid_altitude + i * altitude_increment2 for i in range(num_points2)]

    return trajectory

def generateCompletePath(start_lat, start_lon, end_lat, end_lon,initial_altitude, mid_altitude, final_altitude, num_points):
    xy = generate_pathLatLong(start_lat, start_lon, end_lat, end_lon, num_points)
    zAlt = generate_altitude_trajectory(initial_altitude, mid_altitude, final_altitude, num_points)
    complete = utility.append_array_to_tuples(xy,zAlt)
    return complete

def generateCompletePath2(point1,point2,initial_altitude, mid_altitude, final_altitude, num_points):
    xy = generate_path(point1,point2, num_points)
    zAlt = generate_altitude_trajectory(initial_altitude, mid_altitude, final_altitude, num_points)
    complete = utility.append_array_to_tuples(xy,zAlt)
    return complete
