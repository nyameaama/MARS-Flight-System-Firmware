#include "sender.h"

Sender::Sender(int txPin, int rxPin) : mySerial(txPin, rxPin) {}

void Sender::setup() {
  Serial.begin(115200);
  mySerial.begin(9600);    // Set the baud rate to match the Arduino Uno
}

void Sender::sendData(String data) {
  mySerial.println(data);
}

String Sender::receiveData() {
  if (mySerial.available()) {
    String receivedData = mySerial.readString();
    return receivedData;
  }
  return "";
}