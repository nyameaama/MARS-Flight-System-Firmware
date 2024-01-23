#ifndef ESP32_SENDER_H
#define ESP32_SENDER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Sender
{
  private:
    SoftwareSerial mySerial;

  public:
    Sender(int txPin, int rxPin);
    void setup();
    void sendData(String data);
    String receiveData();
};

#endif