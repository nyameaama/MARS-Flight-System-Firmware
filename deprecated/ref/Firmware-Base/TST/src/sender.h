#ifndef ESP32_SENDER_H
#define ESP32_SENDER_H

#include <SoftwareSerial.h>
#include <Arduino.h>

class Sender {
private:
  SoftwareSerial mySerial;
public:
  Sender(int txPin, int rxPin);
  void setup();
  void sendData(String data);
  String receiveData();
};

#endif