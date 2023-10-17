#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Transponder {
public:
    std::string id;
    double latitude;
    double longitude;

    UAV(const std::string& _id, double _latitude, double _longitude)
        : id(_id), latitude(_latitude), longitude(_longitude) {}

    double CalculateDistanceToUAV(const UAV& other) {
        
        const double EarthRadius = 6371;  

        double lat1Rad = latitude * M_PI / 180;
        double lon1Rad = longitude * M_PI / 180;
        double lat2Rad = other.latitude * M_PI / 180;
        double lon2Rad = other.longitude * M_PI / 180;

        double dlat = lat2Rad - lat1Rad;
        double dlon = lon2Rad - lon1Rad;

        double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(dlon / 2) * sin(dlon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = EarthRadius * c;  

        return distance * 1000;  
    }

    void CommunicateWithNearbyUAVs(const std::vector<UAV>& allUAVs) {
        for (const UAV& uav : allUAVs) {
            if (uav.id != id) {
                double distance = CalculateDistanceToUAV(uav);

                if (distance <= 100.0) {  
                    std::cout << "UAV " << id << " is communicating with UAV " << uav.id << " within " << distance << " meters." << std::endl;
                }
            }
        }
    }
};

int main() {
    
    UAV uav1("UAV1", 29.1848, -81.0607);  
    UAV uav2("UAV2", 29.2278, -81.0094);  
    UAV uav3("UAV3", 29.1197, -80.9795);   

    std::vector<UAV> uavs = {uav1, uav2, uav3};

    
    for (UAV& uav : uavs) {
        uav.CommunicateWithNearbyUAVs(uavs);
    }

    return 0;
}
