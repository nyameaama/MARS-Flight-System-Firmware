#include "path_gen.h"
#include <cmath>

std::pair<double, double> PathGenerator::calculateCoordinate(double lat1, double lon1, double lat2, double lon2, double distance) {
    double radius = 6371;  // Radius of the Earth in kilometers
        double brng = (distance / radius) * (180.0 / M_PI);  // Convert distance to degrees

        lat1 = (lat1 * M_PI) / 180.0;
        lon1 = (lon1 * M_PI) / 180.0;

        double lat2_rad = asin(sin(lat1) * cos(brng) + cos(lat1) * sin(brng) * cos(lat2));
        double lon2_rad = lon1 + atan2(sin(brng) * sin(lat2_rad) * cos(lat1), cos(brng) - sin(lat1) * sin(lat2_rad));

        return { (lat2_rad * 180.0) / M_PI, (lon2_rad * 180.0) / M_PI };
}

std::vector<std::pair<double, double>> PathGenerator::generatePathLatLong(double startLat, double startLon, double endLat, double endLon, int numPoints) {
    double deltaLat = (endLat - startLat) / numPoints;
        double deltaLon = (endLon - startLon) / numPoints;

        std::vector<std::pair<double, double>> path;
        for (int i = 0; i < numPoints; i++) {
            double lat = startLat + i * deltaLat;
            double lon = startLon + i * deltaLon;
            path.emplace_back(lat, lon);
        }

        return path;
}

std::vector<std::pair<double, double>> PathGenerator::generatePath(const std::pair<double, double>& startPoint, const std::pair<double, double>& endPoint, int numPoints) {
    double deltaX = (endPoint.first - startPoint.first) / numPoints;
        double deltaY = (endPoint.second - startPoint.second) / numPoints;

        std::vector<std::pair<double, double>> path;
        for (int i = 0; i < numPoints; i++) {
            double x = startPoint.first + i * deltaX;
            double y = startPoint.second + i * deltaY;
            path.emplace_back(x, y);
        }

        return path;
}

std::vector<double> PathGenerator::generateAltitudeTrajectory(double initialAltitude, double midAltitude, double finalAltitude, int numPoints) {
    double deltaAltitude1 = midAltitude - initialAltitude;
        double deltaAltitude2 = finalAltitude - midAltitude;

        int numPoints1 = numPoints / 2;
        int numPoints2 = numPoints - numPoints1;

        double altitudeIncrement1 = deltaAltitude1 / (numPoints1 - 1);
        double altitudeIncrement2 = deltaAltitude2 / (numPoints2 - 1);

        std::vector<double> trajectory;
        for (int i = 0; i < numPoints1; i++) {
            double altitude = initialAltitude + i * altitudeIncrement1;
            trajectory.push_back(altitude);
        }

        for (int i = 0; i < numPoints2; i++) {
            double altitude = midAltitude + i * altitudeIncrement2;
            trajectory.push_back(altitude);
        }

        return trajectory;
}

std::vector<std::tuple<double, double, double>> PathGenerator::generateCompletePath(double startLat, double startLon, double endLat, double endLon, double initialAltitude, double midAltitude, double finalAltitude, int numPoints) {
    std::vector<std::pair<double, double>> xy = generatePathLatLong(startLat, startLon, endLat, endLon, numPoints);
    std::vector<double> zAlt = generateAltitudeTrajectory(initialAltitude, midAltitude, finalAltitude, numPoints);
    std::vector<std::tuple<double, double, double>> complete;

    for (int i = 0; i < numPoints; i++) {
        complete.emplace_back(xy[i].first, xy[i].second, zAlt[i]);
    }

    return complete;
}

std::vector<std::tuple<double, double, double>> PathGenerator::generateCompletePath2(const std::pair<double, double>& point1, const std::pair<double, double>& point2, double initialAltitude, double midAltitude, double finalAltitude, int numPoints) {
    std::vector<std::pair<double, double>> xy = generatePath(point1, point2, numPoints);
    std::vector<double> zAlt = generateAltitudeTrajectory(initialAltitude, midAltitude, finalAltitude, numPoints);
    std::vector<std::tuple<double, double, double>> complete;

    for (int i = 0; i < numPoints; i++) {
        complete.emplace_back(xy[i].first, xy[i].second, zAlt[i]);
    }

    return complete;
}