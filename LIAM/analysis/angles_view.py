import open3d as o3d
import numpy as np

# Load the STL model
mesh = o3d.io.read_triangle_mesh("models/Unity_Exterior_Render_v2.stl")

# Define a custom transformation matrix (e.g., identity matrix for no transformation)
# Adjust this matrix based on your model's initial orientation if needed
custom_transform = np.eye(4)

# Apply the custom transformation to the mesh
mesh.transform(custom_transform)

# Extract the rotation matrix from the transformation matrix
rotation_matrix = custom_transform[:3, :3]

# Calculate the pitch, roll, and yaw angles
pitch = np.arctan2(rotation_matrix[2, 1], rotation_matrix[2, 2])
roll = -np.arcsin(rotation_matrix[2, 0])
yaw = np.arctan2(rotation_matrix[1, 0], rotation_matrix[0, 0])

# Convert angles to degrees
pitch_deg = np.degrees(pitch)
roll_deg = np.degrees(roll)
yaw_deg = np.degrees(yaw)

# Print the angles
print(f"Pitch: {round(pitch_deg, 2)} deg")
print(f"Roll: {round(roll_deg, 2)} deg")
print(f"Yaw: {round(yaw_deg, 2)} deg")
#models/Unity_Exterior_Render_v2.stl