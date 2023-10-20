#ifndef BROADCASTED_SERVER_H
#define BROADCASTED_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include "page.h"

class BroadcastedServer {
    public:
        BroadcastedServer();

        void begin();

        void handleClient();

        void sendWebpage();

        void performTask();

        void handleNotFound();

    private:
        void set_ALT_REGISTER();

        void set_LAT_REGISTER();

        void set_LNG_REGISTER();

    private:
        WebServer server;
};

#endif