#include <WiFi.h>
#include "_broadcast.h"

BroadcastedServer server;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  //WiFi.begin("MyWiFiNetwork", "password");
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(1000);
  //  Serial.println("Connecting to WiFi...");
  //}

  // Initialize and start the server
  server.begin();
  server.sendWebpage();
  server.handleNotFound();
}

void loop() {
  server.handleClient();
}