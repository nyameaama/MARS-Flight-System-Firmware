#include<iostream>

uint8_t verifyFlightConfiguration();
std::string generateRandomAlphanumericToken(uint32_t seed1, uint32_t seed2, int length = 6);

int main(){
    // Provide two random seeds
    uint32_t seed1 = 12345;
    uint32_t seed2 = 67890;

    // Generate and print a random alphanumeric token
    std::string token = generateRandomAlphanumericToken(seed1, seed2);
    std::cout << "Random Token: " << token << std::endl;

    return 0;
}

std::string generateRandomAlphanumericToken(uint32_t seed1, uint32_t seed2, int length = 6) {
    const std::string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;

    for (int i = 0; i < length; i++) {
        seed1 = (seed1 * 1664525 + 1013904223) % characters.size();
        seed2 = (seed2 * 1664525 + 1013904223) % characters.size();
        token += characters[seed1 ^ seed2];
    }

    return token;
}

uint8_t verifyFlightConfiguration(){
    //To verify flight config, we just check to make sure all flight critical PTAM 
    //registers have valid data (non-zero) and we return 1 or 0
    /*Flight Critical Registers
        SWP:
        Target Latitude
        Target Longitude
        Target Altitude
        Final Altitude
        Target Velocity
    */
    //SharedMemory& sharedMemory = SharedMemory::getInstance();
    uint8_t verified = 0;
    //auto _lat = sharedMemory.getLastDouble("TLat");
    //auto _long = sharedMemory.getLastDouble("TLong");
    //auto _Talt = sharedMemory.getLastDouble("TAlt");
    //auto _Calt = sharedMemory.getLastDouble("CAlt");
    //auto _vel = sharedMemory.getLastDouble("TVel");

    auto _lat = 1.0;
    auto _long = 2.0;
    auto _Talt = 3.0;
    auto _Calt = 4.0;
    auto _vel = 5.0;

    // Check if all variables contain non-zero values
    if (_lat != 0.0 && 
        _long != 0.0 && 
        _Talt != 0.0 && 
        _Calt != 0.0 && 
        _vel != 0.0) {
        // All variables contain non-zero values
        // We can provide authorization
        verified = 1;
    } else {
        // At least one variable contains a zero value
        // Configuration not finished
        verified = 0;
    }
    return verified;
}

