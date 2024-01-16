#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class GPSModule
{
  private:
    SoftwareSerial gpsSerial;
    TinyGPSPlus gps;

  public:
    GPSModule(int rxPin, int txPin);
    void begin();
    bool update();
    double getLatitude();
    double getLongitude();
    double getAltitude();
    double getVelocity();
    unsigned long getTime();
};

#endif