#ifndef FLIGHT_CONTROL_H
#define FLIGHT_CONTROL_H

struct Vector3 {
    double x, y, z;
    Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
};

struct EulerAngles {
    double pitch, roll;
    EulerAngles(double _pitch, double _roll) : pitch(_pitch), roll(_roll) {}
};

class FlightControl {
public:
    FlightControl() {}

    EulerAngles calculatePitchAndRoll(const Vector3& currentPos, const Vector3& nextWaypoint);
};

#endif  // FLIGHT_CONTROL_H