#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>

class UAVData {
public:
    UAVObject* uavObject;
    Text* headingText;
    Text* locationText;
    Text* altitudeText;
    Text* detectedUAVsText;
    std::string uniqueID;
    std::vector<std::string> detectedUAVs;
    bool isUavMissing = false;

    void GenerateUniqueID() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(100000, 999999);
        uniqueID = std::to_string(dist(gen));
    }

    std::string GetUniqueID() {
        return uniqueID;
    }

    void AddDetectedUAV(std::string uavID) {
        if (std::find(detectedUAVs.begin(), detectedUAVs.end(), uavID) == detectedUAVs.end()) {
            detectedUAVs.push_back(uavID);
        }
    }

    std::vector<std::string> GetDetectedUAVs() {
        return detectedUAVs;
    }

    void SetMissing(bool missing) {
        isUavMissing = missing;
    }

    bool IsUavMissing() {
        return isUavMissing;
    }
};

class UAVDisplay {
public:
    UAVData uavDataArray[9];

    void Start() {
        for (UAVData& uavData : uavDataArray) {
            if (uavData.uavObject != nullptr) {
                uavData.GenerateUniqueID();
            }
        }
    }

    void Update() {
        for (int i = 0; i < 9; i++) {
            UAVData& uavData = uavDataArray[i];

            if (uavData.uavObject != nullptr) {
                bool isUavMissing = uavData.uavObject == nullptr;

                std::string idText = "UAV " + uavData.GetUniqueID();
                if (isUavMissing) {
                    idText += " (Offline)";
                }

                if (!isUavMissing && uavData.headingText != nullptr &&
                    uavData.locationText != nullptr && uavData.altitudeText != nullptr && uavData.detectedUAVsText != nullptr) {

                    Quaternion uavRotation = uavData.uavObject->GetRotation();
                    Vector3 uavPosition = uavData.uavObject->GetPosition();
                    float altitude = uavPosition.y;

                    float heading = Quaternion(0, uavRotation.GetEulerAngles().y, 0).GetEulerAngles().y;

                    uavData.headingText->SetText(idText + ": Heading: " + std::to_string(heading) + "°");
                    uavData.headingText->SetColor(Color::Green);

                    float latitude = asin(uavPosition.y / 6371.0f) * Rad2Deg;
                    float longitude = atan2(uavPosition.x, uavPosition.z) * Rad2Deg;

                    uavData.locationText->SetText(idText + ": " +
                        "Lat: " + std::to_string(latitude) +
                        " Lon: " + std::to_string(longitude));
                    uavData.locationText->SetColor(Color::Green);

                    uavData.altitudeText->SetText(idText + ": " +
                        "Altitude: " + std::to_string(altitude) + " meters");
                    uavData.altitudeText->SetColor(Color::Green);

                    DetectNearbyUAVs(uavData);

                    uavData.detectedUAVsText->SetText("Detected UAVs: " + String::Join(", ", uavData.GetDetectedUAVs()));
                    uavData.detectedUAVsText->SetColor(Color::Green);

                    uavData.SetMissing(false);
                }
                else {
                    if (!uavData.IsUavMissing()) {
                        uavData.headingText->SetText(idText + " (Offline)");
                        uavData.headingText->SetColor(Color::Red);

                        uavData.locationText->SetText(idText + " (Offline)");
                        uavData.locationText->SetColor(Color::Red);

                        uavData.altitudeText->SetText(idText + " (Offline)");
                        uavData.altitudeText->SetColor(Color::Red);

                        uavData.detectedUAVsText->SetText("Detected UAVs: None");
                        uavData.detectedUAVsText->SetColor(Color::Red);

                        uavData.SetMissing(true);
                    }
                }
            }
        }
    }

    void DetectNearbyUAVs(UAVData& uavData) {
        uavData.GetDetectedUAVs().clear();
        for (UAVData& otherUAVData : uavDataArray) {
            if (otherUAVData.uavObject != nullptr && &otherUAVData != &uavData) {
                float distance = Vector3::Distance(uavData.uavObject->GetPosition(), otherUAVData.uavObject->GetPosition());
                if (distance <= 100.0f) {
                    uavData.AddDetectedUAV(otherUAVData.GetUniqueID());
                }
            }
        }
    }
};

int main() {
    
    UAVDisplay uavDisplay;

    
    while (true) {
        
        uavDisplay.Update();

       
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
