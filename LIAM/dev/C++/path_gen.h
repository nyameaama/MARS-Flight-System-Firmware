#ifndef PATHGENERATOR_H
#define PATHGENERATOR_H

#include <vector>
#include <utility>

class PathGenerator {
public:
    static std::pair<double, double> calculateCoordinate(double lat1, double lon1, double lat2, double lon2, double distance);
    static std::vector<std::pair<double, double>> generatePathLatLong(double startLat, double startLon, double endLat, double endLon, int numPoints);
    static std::vector<std::pair<double, double>> generatePath(const std::pair<double, double>& startPoint, const std::pair<double, double>& endPoint, int numPoints);
    static std::vector<double> generateAltitudeTrajectory(double initialAltitude, double midAltitude, double finalAltitude, int numPoints);
    static std::vector<std::tuple<double, double, double>> generateCompletePath(double startLat, double startLon, double endLat, double endLon, double initialAltitude, double midAltitude, double finalAltitude, int numPoints);
    static std::vector<std::tuple<double, double, double>> generateCompletePath2(const std::pair<double, double>& point1, const std::pair<double, double>& point2, double initialAltitude, double midAltitude, double finalAltitude, int numPoints);
};

#endif // PATHGENERATOR_H