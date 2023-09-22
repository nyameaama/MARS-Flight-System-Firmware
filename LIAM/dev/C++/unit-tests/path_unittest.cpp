#include "path_gen.h"
#include <iostream>

//COMPILE WITH C++17 
//g++ -std=c++17 -o main path_unittest.cpp path_gen.cpp

int main() {
    // Test calculateCoordinate function
    std::pair<double, double> coordinate = PathGenerator::calculateCoordinate(52.5200, 13.4050, 48.8566, 2.3522, 500);
    std::cout << "Calculated Coordinate: (" << coordinate.first << ", " << coordinate.second << ")\n";

    // Test generatePathLatLong function
    std::vector<std::pair<double, double>> path = PathGenerator::generatePathLatLong(52.5200, 13.4050, 48.8566, 2.3522, 5);
    std::cout << "Generated Path LatLong:\n";
    for (const auto& point : path) {
        std::cout << "(" << point.first << ", " << point.second << ")\n";
    }

    // Test generatePath function
    std::pair<double, double> startPoint(1.0, 2.0);
    std::pair<double, double> endPoint(3.0, 4.0);
    std::vector<std::pair<double, double>> path2 = PathGenerator::generatePath(startPoint, endPoint, 5);
    std::cout << "Generated Path:\n";
    for (const auto& point : path2) {
        std::cout << "(" << point.first << ", " << point.second << ")\n";
    }

    // Test generateAltitudeTrajectory function
    std::vector<double> altitudes = PathGenerator::generateAltitudeTrajectory(100, 200, 300, 5);
    std::cout << "Generated Altitude Trajectory:\n";
    for (const auto& altitude : altitudes) {
        std::cout << altitude << " ";
    }
    std::cout << "\n";

    // Test generateCompletePath function
    std::vector<std::tuple<double, double, double>> completePath = PathGenerator::generateCompletePath(52.5200, 13.4050, 48.8566, 2.3522, 100, 200, 300, 5);
    std::cout << "Generated Complete Path:\n";
    for (const auto& point : completePath) {
        std::cout << "(" << std::get<0>(point) << ", " << std::get<1>(point) << ", " << std::get<2>(point) << ")\n";
    }

    // Test generateCompletePath2 function
    std::vector<std::tuple<double, double, double>> completePath2 = PathGenerator::generateCompletePath2(startPoint, endPoint, 100, 200, 300, 5);
    std::cout << "Generated Complete Path 2:\n";
    for (const auto& point : completePath2) {
        std::cout << "(" << std::get<0>(point) << ", " << std::get<1>(point) << ", " << std::get<2>(point) << ")\n";
    }

    return 0;
}