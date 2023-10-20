#include "cruise.h"
#include <cmath>

EulerAngles FlightControl::calculatePitchAndRoll(const Vector3& currentPos, const Vector3& nextWaypoint) {
    Vector3 directionVector(
        nextWaypoint.x - currentPos.x,
        nextWaypoint.y - currentPos.y,
        nextWaypoint.z - currentPos.z
    );

    double pitchRadians = atan2(directionVector.z, sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y));
    double pitchDegrees = pitchRadians * 180.0 / M_PI;
    double rollRadians = atan2(directionVector.y, directionVector.x);
    double rollDegrees = rollRadians * 180.0 / M_PI;

    return EulerAngles(pitchDegrees, rollDegrees);
}

double cruise_app(){
    //Get A* Path
    // Define the starting and goal points as vectors (latitude and longitude)
    std::vector<double> start = {0, 0};
    std::vector<double> goal = {90, 180};

    // Define a vector of obstacles as vectors (latitude and longitude)
    std::vector<std::vector<double>> obstacles = {
        {30, 30},
        {40, 60},
        {60, 100},
        {70, 150}
    };

    // Find the path using A*
    std::vector<std::vector<double>> path = AStarPathfinding::findPathAStar(start, goal, obstacles);

    // Print the path
    if (!path.empty()) {
        std::cout << "Path found:" << std::endl;
        for (const std::vector<double>& point : path) {
            std::cout << "Latitude: " << point[0] << ", Longitude: " << point[1] << std::endl;
        }
    } else {
        std::cout << "No path found." << std::endl;
    }
    //Get Pitch and Roll from next point in path
    
    //Decompose angles to servo positions

}