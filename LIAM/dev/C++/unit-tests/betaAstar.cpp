#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <map>
#include <algorithm>

// Define a function to calculate the heuristic (estimated) cost from a point to the goal
double calculateHeuristic(const std::vector<double>& current, const std::vector<double>& goal) {
    // Use Euclidean distance as a simple heuristic (you can use more accurate formulas)
    double sum = 0.0;
    for (size_t i = 0; i < current.size(); ++i) {
        sum += std::pow(current[i] - goal[i], 2);
    }
    return std::sqrt(sum);
}

// Define a function to check if a point is inside a given radius of an obstacle
bool isPointInObstacle(const std::vector<double>& point, const std::vector<std::vector<double>>& obstacles, double radius) {
    for (const std::vector<double>& obstacle : obstacles) {
        double distance = calculateHeuristic(point, obstacle);
        if (distance < radius) {
            return true;  // Point is within the radius of an obstacle
        }
    }
    return false;  // Point is not within the radius of any obstacle
}

// Define a function to find the path using A*
std::vector<std::vector<double>> findPathAStar(const std::vector<double>& start, const std::vector<double>& goal, const std::vector<std::vector<double>>& obstacles) {
    // Define a priority queue to store open nodes (sorted by total cost)
    std::priority_queue<std::pair<double, std::vector<double>>> openSet;

    // Define a map to store parent nodes and their costs
    std::map<std::vector<double>, std::vector<double>> parentMap;

    // Define a map to store the cost from start to each point
    std::map<std::vector<double>, double> gScore;

    // Initialize the open set with the starting node
    openSet.push({0.0, start});

    // Initialize the cost from start to the starting node
    gScore[start] = 0.0;

    while (!openSet.empty()) {
        // Get the node with the lowest total cost from the open set
        std::vector<double> current = openSet.top().second;
        openSet.pop();

        // Check if we have reached the goal
        if (current == goal) {
            // Reconstruct the path from the goal to the start
            std::vector<std::vector<double>> path;
            while (current != start) {
                path.push_back(current);
                current = parentMap[current];
            }
            path.push_back(start);  // Add the start point
            std::reverse(path.begin(), path.end());  // Reverse the path to get it from start to goal
            return path;
        }

        // Generate neighboring nodes
        std::vector<std::vector<double>> neighbors = {
            {current[0] + 1, current[1]},
            {current[0] - 1, current[1]},
            {current[0], current[1] + 1},
            {current[0], current[1] - 1}
        };

        for (const std::vector<double>& neighbor : neighbors) {
            // Skip neighbors outside the map bounds
            if (neighbor[0] < 0 || neighbor[0] > 90 || neighbor[1] < 0 || neighbor[1] > 180) {
                continue;
            }

            // Skip neighbors in obstacles
            if (isPointInObstacle(neighbor, obstacles, 1.0)) {
                continue;
            }

            // Calculate the tentative cost from start to neighbor
            double tentativeGScore = gScore[current] + calculateHeuristic(current, neighbor);

            // If the neighbor is not in gScore or the new path is shorter
            if (!gScore.count(neighbor) || tentativeGScore < gScore[neighbor]) {
                // Update gScore and total cost
                gScore[neighbor] = tentativeGScore;
                double fScore = tentativeGScore + calculateHeuristic(neighbor, goal);

                // Add the neighbor to the open set
                openSet.push({-fScore, neighbor});

                // Update the parent of the neighbor
                parentMap[neighbor] = current;
            }
        }
    }

    // If no path is found, return an empty vector
    return std::vector<std::vector<double>>();
}

int main() {
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
    std::vector<std::vector<double>> path = findPathAStar(start, goal, obstacles);

    // Print the path
    if (!path.empty()) {
        std::cout << "Path found:" << std::endl;
        for (const std::vector<double>& point : path) {
            std::cout << "Latitude: " << point[0] << ", Longitude: " << point[1] << std::endl;
        }
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}