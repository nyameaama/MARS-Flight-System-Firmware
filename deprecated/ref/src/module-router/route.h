/*
#ifndef MOD_ROUTER
#define MOD_ROUTER

#include"util/defi.h"

#define OPEN 1
#define CLOSE 0

#define READ 2
#define RX 22
#define TX 23

class MODULE_ROUTER {
  public:
    double motors(uint8_t type, uint8_t value);

    void readIMU(uint8_t variable);

    double readGPS(uint8_t variable);

    uint8_t initiateThrottle(uint8_t value);

  private:
    void sendCommandWithValue(const char* command, uint8_t value);
};

#endif // MOD_ROUTER
*/