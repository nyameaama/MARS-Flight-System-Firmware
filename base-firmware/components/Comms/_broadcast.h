/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef BROADCASTED_SERVER_H
#define BROADCASTED_SERVER_H

#include <esp_http_server.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include <iomanip>
#include<vector>
#include"page.h"
#include"esp_log.h"
#include"esp_random.h"
#include"../PTAM/_ptam.h"
#include"../system/sys_controller.h"
#include "os_config.h"

class BroadcastedServer {
    public:
        static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);
        void wifi_init_softap(void);

    private:
        static std::string packData(const std::string& id1, float value1,
                     const std::string& id2, float value2,
                     const std::string& id3, float value3,
                     const std::string& id4, float value4);
        
        static void extractValuesAndIds(const std::string& data, std::vector<std::string>& ids, std::vector<double>& values);

    private:
        static esp_err_t root_handler(httpd_req_t *req);

        static esp_err_t handle_GPS_request(httpd_req_t *req);

        static esp_err_t handle_IMU1_request(httpd_req_t *req);

        static esp_err_t handle_IMU2_request(httpd_req_t *req);

        static esp_err_t handle_W1_request(httpd_req_t *req);

        static esp_err_t handle_AMB_request(httpd_req_t *req);

        static esp_err_t handle_arm_token_request(httpd_req_t *req);

        static esp_err_t handle_SWP_incoming(httpd_req_t *req);

        static esp_err_t handle_SYS_incoming(httpd_req_t *req);

        static esp_err_t handle_STATE_incoming(httpd_req_t *req);

        static esp_err_t handle_AUTH_incoming(httpd_req_t *req);

    private:
        const char *html_content = responseXX;
};

#endif