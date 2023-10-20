/*
#include "route.h"

double MODULE_ROUTER::motors(uint8_t type, uint8_t value) {
  sendCommandWithValue("MOTORS:", type);
  sendCommandWithValue("", value);
  return 0;
}

void MODULE_ROUTER::readIMU(uint8_t variable) {
  Sender *obj = new Sender(RX,TX);
  sendCommandWithValue("IMU:", variable);
}

double MODULE_ROUTER::readGPS(uint8_t variable) {
  Sender *obj = new Sender(RX,TX);
  sendCommandWithValue("GPS:", variable);

  return 0;
}

uint8_t MODULE_ROUTER::initiateThrottle(uint8_t value) {
  sendCommandWithValue("THROTTLE:", value);
  return 0;
}

void MODULE_ROUTER::sendCommandWithValue(const char* command, uint8_t value) {
  EncoderDecoder *ecode = new EncoderDecoder();
  Sender *obj = new Sender(RX,TX);
  //Encode
  std::string formatted = ecode -> encode(command, value);
  //Send
  //obj -> sendData(formatted);
  delete ecode;
  delete obj;
}
*/