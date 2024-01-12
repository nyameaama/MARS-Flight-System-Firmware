#ifndef ESP32_SERIAL_COMM_H
#define ESP32_SERIAL_COMM_H

#include <Arduino.h>

class ESP32_SerialComm
{
  public:
    ESP32_SerialComm(uint8_t pin);

    void begin();

    void sendString(const String& data);

  private:
    uint8_t pin_;
};

#endif  // ESP32_SERIAL_COMM_H