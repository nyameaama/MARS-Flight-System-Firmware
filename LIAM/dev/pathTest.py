import trajectoryTrace as trJ
import matplotlib.pyplot as plt
import utility

start_lat = 40.7128  # Latitude of start point
start_lon = -74.0060  # Longitude of start point
end_lat = 34.0522  # Latitude of end point
end_lon = -118.2437  # Longitude of end point
num_points = 10  # Number of points in the generated path
initial_altitude = 20
mid_altitude = 120
final_altitude = 60
num_points = 20

path = trJ.generateCompletePath(start_lat, start_lon, end_lat, end_lon,initial_altitude, mid_altitude, final_altitude, num_points)
print(path)

extX, extY, extZ = utility.extractXY(path)
# Creating a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plotting the data
ax.plot(extX, extY, extZ)

# Adding labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Trajectory')

plt.show()