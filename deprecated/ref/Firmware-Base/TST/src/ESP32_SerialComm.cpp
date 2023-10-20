#include "ESP32_SerialComm.h"

ESP32_SerialComm::ESP32_SerialComm(uint8_t pin) : pin_(pin) {}

void ESP32_SerialComm::begin() {
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, HIGH);
}

void ESP32_SerialComm::sendString(const String& data) {
  // Start bit
  digitalWrite(pin_, LOW);
  delayMicroseconds(200);

  // Send each character
  for (char c : data) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(pin_, c & (1 << i));
      delayMicroseconds(200);
    }
  }

  // Stop bit
  digitalWrite(pin_, HIGH);
  delayMicroseconds(200);
}
