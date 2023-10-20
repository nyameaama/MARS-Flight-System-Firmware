#include "_broadcast.h"

BroadcastedServer::BroadcastedServer() {}

void BroadcastedServer::begin() {
  // Set up ESP32 as an access point
  WiFi.softAP("HIVE", "password");

  IPAddress ipAddress(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(ipAddress, ipAddress, subnet);
  // Start the server
  server.begin();

  // Handle page not found and /perform-task request
  handleNotFound();
}

void BroadcastedServer::handleClient() {
  server.handleClient();
}

void BroadcastedServer::sendWebpage() {
  // Serve the HTML webpage
  server.on("/", HTTP_GET, [this]() {
    server.send(200, "text/html", responseXX);
  });
}

void BroadcastedServer::performTask() {
  // Perform the task
  // ...
  Serial.println("PRESSED");
  // Send a response back to the client
  //server.send(200, "text/plain", "Task completed");
}

void BroadcastedServer::handleNotFound() {
  // Handle page not found and requests
  server.onNotFound([this]() {
    if (server.uri() == "/perform-task") {
      performTask();
    }else if(server.uri() == "/LAT-set"){
      set_LAT_REGISTER();
    }else if(server.uri() == "/LNG-set"){
      set_LNG_REGISTER();
    }else if(server.uri() == "/Alt-set"){
      set_ALT_REGISTER();
    }else {
      server.send(404, "text/plain", "Page not found");
    }
  });
}

void BroadcastedServer::set_ALT_REGISTER(){
  Serial.println("ALT");
}

void BroadcastedServer::set_LAT_REGISTER(){
  Serial.println("LAT");
}

void BroadcastedServer::set_LNG_REGISTER(){
  Serial.println("LNG");
}