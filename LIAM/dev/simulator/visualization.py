import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

def visualize_trajectory(x, y, z):
    fig = plt.figure("LIAM Simulator")
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Altitude')

    # Set the aspect ratio and limits
    ax.set_box_aspect([1, 1, 0.5])
    ax.set_xlim(min(x), max(x))
    ax.set_ylim(min(y), max(y))
    ax.set_zlim(min(z), max(z))

    # Create initial empty lines for the animation
    line, = ax.plot([], [], [], marker='o', label='Trajectory')
    current_point, = ax.plot([], [], [], 'ro', label='Current Position')

    # Function called for each frame of the animation
    def update(frame):
        # Update the trajectory line
        line.set_data(x[:frame+1], y[:frame+1])
        line.set_3d_properties(z[:frame+1])

        # Update the current position
        current_position = [x[frame], y[frame], z[frame]]
        current_point.set_data([current_position[0]], [current_position[1]])
        current_point.set_3d_properties([current_position[2]])

        return line, current_point

    # Create the animation
    anim = FuncAnimation(fig, update, frames=len(x), interval=200, blit=True)

    # Display the animation
    plt.legend()
    plt.show()
