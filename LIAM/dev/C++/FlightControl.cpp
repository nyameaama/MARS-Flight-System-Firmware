#include "FlightControl.h"
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