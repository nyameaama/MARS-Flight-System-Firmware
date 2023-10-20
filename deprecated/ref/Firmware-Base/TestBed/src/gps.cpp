#include "gps.h"

GPSModule::GPSModule(int rxPin, int txPin) : gpsSerial(rxPin, txPin) {}

void GPSModule::begin() {
  gpsSerial.begin(9600);
}

bool GPSModule::update() {
  while (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) {
      return true;
    }
  }
  return false;
}

double GPSModule::getLatitude() {
  return gps.location.lat();
}

double GPSModule::getLongitude() {
  return gps.location.lng();
}

double GPSModule::getAltitude() {
  return gps.altitude.meters();
}

double GPSModule::getVelocity() {
  return gps.speed.kmph();
}

unsigned long GPSModule::getTime() {
  return gps.time.value();
}