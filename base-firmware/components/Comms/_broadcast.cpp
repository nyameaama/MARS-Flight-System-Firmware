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

#include "_broadcast.h"
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_ota_ops.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <sys/param.h>

#define _ESP_WIFI_SSID      "HIVE2"
#define _ESP_WIFI_PASS      "HIVE_PASS"
#define _ESP_WIFI_CHANNEL   6
#define _MAX_STA_CONN       1
#define MAX_DATA_LEN        100

static const char *TAG = "wifi softAP";

void BroadcastedServer::wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        //ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                // MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        //ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 //MAC2STR(event->mac), event->aid);
    }
}

void BroadcastedServer::wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
        .ssid = _ESP_WIFI_SSID,
        .password = _ESP_WIFI_PASS,
        .channel = _ESP_WIFI_CHANNEL,
        .max_connection = _MAX_STA_CONN,
        },
    };

    wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             _ESP_WIFI_SSID, _ESP_WIFI_PASS, _ESP_WIFI_CHANNEL);

    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;

    /* HTTP server configuration */

    httpd_uri_t root_uri = {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = root_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t LAT1_uri = {
        .uri       = "/GET_GPS",
        .method    = HTTP_POST,
        .handler   = handle_GPS_request,
        .user_ctx  = NULL
    };

    httpd_uri_t IMU1_uri = {
        .uri       = "/GET_IMU1",
        .method    = HTTP_POST,
        .handler   = handle_IMU1_request,
        .user_ctx  = NULL
    };

    httpd_uri_t IMU2_uri = {
        .uri       = "/GET_IMU2",
        .method    = HTTP_POST,
        .handler   = handle_IMU2_request,
        .user_ctx  = NULL
    };

    httpd_uri_t W1_uri = {
        .uri       = "/GET_W1",
        .method    = HTTP_POST,
        .handler   = handle_W1_request,
        .user_ctx  = NULL
    };

    httpd_uri_t AMB1_uri = {
        .uri       = "/GET_AMB",
        .method    = HTTP_POST,
        .handler   = handle_AMB_request,
        .user_ctx  = NULL
    };

    httpd_uri_t TOKEN_uri = {
        .uri       = "/GET_TOKEN",
        .method    = HTTP_POST,
        .handler   = handle_arm_token_request,
        .user_ctx  = NULL
    };

    httpd_uri_t BATT_uri = {
        .uri       = "/GET_BATT",
        .method    = HTTP_POST,
        .handler   = handle_battery_request,
        .user_ctx  = NULL
    };

    httpd_uri_t SWP_uri = {
        .uri       = "/INC_SWP",
        .method    = HTTP_POST,
        .handler   = handle_SWP_incoming,
        .user_ctx  = NULL
    };

    httpd_uri_t SYS_uri = {
        .uri       = "/INC_SYS",
        .method    = HTTP_POST,
        .handler   = handle_SYS_incoming,
        .user_ctx  = NULL
    };

    httpd_uri_t STATE_uri = {
        .uri       = "/INC_STATE",
        .method    = HTTP_POST,
        .handler   = handle_STATE_incoming,
        .user_ctx  = NULL
    };

    httpd_uri_t AUTH_uri = {
        .uri       = "/INC_AUTH",
        .method    = HTTP_POST,
        .handler   = handle_AUTH_incoming,
        .user_ctx  = NULL
    };

    httpd_uri_t OTA_uri = {
        .uri       = "/INC_OTA",
        .method    = HTTP_POST,
        .handler   = handle_OTA_incoming,
        .user_ctx  = NULL
    };

    // Start the HTTP server
    if (httpd_start(&server, &config) == ESP_OK) {
        //Register root
        httpd_register_uri_handler(server, &root_uri);
        httpd_register_uri_handler(server, &LAT1_uri);
        httpd_register_uri_handler(server, &IMU1_uri);
        httpd_register_uri_handler(server, &IMU2_uri);
        httpd_register_uri_handler(server, &W1_uri);
        httpd_register_uri_handler(server, &AMB1_uri);
        httpd_register_uri_handler(server, &SWP_uri);
        httpd_register_uri_handler(server, &SYS_uri);
        httpd_register_uri_handler(server, &STATE_uri);
        httpd_register_uri_handler(server, &TOKEN_uri);
        httpd_register_uri_handler(server, &AUTH_uri);
        httpd_register_uri_handler(server, &OTA_uri);
        httpd_register_uri_handler(server, &BATT_uri);
    }

}

std::string BroadcastedServer::packData(const std::string& id1, float value1,
                     const std::string& id2, float value2,
                     const std::string& id3, float value3,
                     const std::string& id4, float value4) {
    std::ostringstream packed;
    packed << id1 << value1 << "_" << id2 << value2 << "_" << id3 << value3 << "_" << id4 << value4;
    return packed.str();
}

void BroadcastedServer::extractValuesAndIds(const std::string& data, std::vector<std::string>& ids, std::vector<double>& values) {
    std::stringstream ss(data);
    std::string item;

    while (getline(ss, item, '_')) {
        // Extract the ID and value from each item
        std::string id = item.substr(0, item.find_first_of("0123456789.-"));
        double value = std::stod(item.substr(item.find_first_of("0123456789.-")));

        // Add the ID and value to the respective vectors
        ids.push_back(id);
        values.push_back(value);
    }
}

/* Handler for the root ("/") endpoint */
esp_err_t BroadcastedServer::root_handler(httpd_req_t *req) {
    // Open the "index.html" file
    // Set the HTTP response content type as "text/html"
    httpd_resp_set_type(req, "text/html");

    // Send the "index.html" content as the HTTP response
    httpd_resp_send(req, responseXX, strlen(responseXX));

    return ESP_OK;
}

/* Handler for the "/GET_GPS" endpoint */
esp_err_t BroadcastedServer::handle_GPS_request(httpd_req_t *req) {
    VEHICLE_BARO *baro = new VEHICLE_BARO();
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

        std::string id1 = "LAT";
        double value1 = 56;
        std::string id2 = "LONG";
        double value2 = 78.50;
        std::string id3 = "SAT";
        double value3 = 72.34;
        std::string id4 = "ALT";
        double value4 = 48.2; //baro -> pushAltitude(DEFAULT_SEA_LEVEL);

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");

    delete baro;
    return ESP_OK;
}


/* Handler for the "/IMU1" endpoint */
esp_err_t BroadcastedServer::handle_IMU1_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

        std::string id1 = "PITCH";
        double value1 = 98;
        std::string id2 = "ROLL";
        double value2 = 42;
        std::string id3 = "YAW";
        double value3 = 87;
        std::string id4 = "GYROY";
        double value4 =22;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);
        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/IMU1" endpoint */
esp_err_t BroadcastedServer::handle_IMU2_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

        std::string id1 = "ACCX";
        double value1 = 98;
        std::string id2 = "ACCY";
        double value2 = 42;
        std::string id3 = "ACCZ";
        double value3 = 87;
        std::string id4 = "GYROX";
        double value4 =22;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);
        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/W1" endpoint */
esp_err_t BroadcastedServer::handle_W1_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

       std::string id1 = "WFL";
        double value1 = 165;
        std::string id2 = "WFR";
        double value2 = 148;
        std::string id3 = "WRL";
        double value3 = 109;
        std::string id4 = "WRR";
        double value4 = 112;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}


esp_err_t BroadcastedServer::handle_AMB_request(httpd_req_t *req) {
    BATTERY *power = new BATTERY();
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

       std::string id1 = "OAT";
        double value1 = 165;
        std::string id2 = "PRESS";
        double value2 = 148;
        std::string id3 = "GYROZ";
        double value3 = 109;
        std::string id4 = "THROT";
        double value4 = power -> returnBatteryPercent();

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    delete power;
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_arm_token_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        uint32_t seed1 = esp_random();
        uint32_t seed2 = esp_random();
        CONTROLLER_TASKS *cobj = new CONTROLLER_TASKS();
        SharedMemory& sharedMemory = SharedMemory::getInstance();
        std::string packed_data = "";
        if(cobj -> verifyFlightConfiguration() != 0){
            packed_data = cobj -> generateRandomAlphanumericToken(seed1, seed2, 6);
            //UPDATE PTAM REGISTERS
            sharedMemory.clearData("arm_token");
            sharedMemory.storeString("arm_token", packed_data);
            // Send a response to the client
            httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        }else{
            //We do not send anything so the request will fail
        }
        delete cobj;
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_battery_request(httpd_req_t *req) {
    BATTERY *power = new BATTERY();
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

       std::string id1 = "VOLTAGE";
        double value1 = power -> returnBatteryVoltage();
        std::string id2 = "CURRENT";
        double value2 = power -> returnBatteryCurrentDraw();
        std::string id3 = "PERCENT";
        double value3 = power -> returnBatteryPercent();
        std::string id4 = "XXX";
        double value4 = 112;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");

    delete power;
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_SWP_incoming(httpd_req_t *req){
    char received_data[MAX_DATA_LEN] = "";
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        int total_len = req->content_len;
    int cur_len = 0;
    int received = 0;
    
    if (total_len >= MAX_DATA_LEN) {
        return ESP_FAIL;
    }

    while (received < total_len) {
        // Receive the data in chunks
        cur_len = httpd_req_recv(req, received_data + received, MAX_DATA_LEN);
        if (cur_len <= 0) {
            if (cur_len == HTTPD_SOCK_ERR_TIMEOUT) {
                continue;
            }
            return ESP_FAIL;
        }
        received += cur_len;
    }

    // Null-terminate the received_data string
    received_data[received] = '\0';
        // Send a response to the client
        //httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        std::string data = received_data;
        std::vector<std::string> ids;
        std::vector<double> values;

        extractValuesAndIds(data, ids, values);
        ESP_LOGI("TAG", "%f",values[0]);
        
        //UPDATE PTAM REGISTERS
        SharedMemory& sharedMemory = SharedMemory::getInstance();
        //If value from frontend is not 0, update PTAM register for respective variable
        if(values[0] != 0){
            //Latitude
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("TLat");
            sharedMemory.storeDouble("TLat", values[0]);
        }
        if(values[1] != 0){
            //Longitude
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("TLong");
            sharedMemory.storeDouble("TLong", values[1]);
        }
        if(values[2] != 0){
            //Altitude - target
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("TAlt");
            sharedMemory.storeDouble("TAlt", values[2]);
        }
        if(values[3] != 0){
            //Altitude - cruise
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("CAlt");
            sharedMemory.storeDouble("CAlt", values[3]);
        }
        if(values[4] != 0){
            //Velocity
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("TVel");
            sharedMemory.storeDouble("TVel", values[4]);
        }
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_SYS_incoming(httpd_req_t *req){
    char received_data[MAX_DATA_LEN] = "";
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        int total_len = req->content_len;
    int cur_len = 0;
    int received = 0;
    
    if (total_len >= MAX_DATA_LEN) {
        return ESP_FAIL;
    }

    while (received < total_len) {
        // Receive the data in chunks
        cur_len = httpd_req_recv(req, received_data + received, MAX_DATA_LEN);
        if (cur_len <= 0) {
            if (cur_len == HTTPD_SOCK_ERR_TIMEOUT) {
                continue;
            }
            return ESP_FAIL;
        }
        received += cur_len;
    }

    // Null-terminate the received_data string
    received_data[received] = '\0';
        // Send a response to the client
        //httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        std::string data = received_data;
        std::vector<std::string> ids;
        std::vector<double> values;

        extractValuesAndIds(data, ids, values);
        ESP_LOGI("TAG", "%f",values[0]);
        
        //UPDATE PTAM REGISTERS
        SharedMemory& sharedMemory = SharedMemory::getInstance();
        //If value from frontend is not 0, update PTAM register for respective variable
        if(values[0] != 0){
            //Latitude
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("WingFL");
            sharedMemory.storeDouble("WingFL", values[0]);
        }
        if(values[1] != 0){
            //Longitude
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("WingFR");
            sharedMemory.storeDouble("WingFR", values[1]);
        }
        if(values[2] != 0){
            //Altitude - target
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("WingRL");
            sharedMemory.storeDouble("WingRL", values[2]);
        }
        if(values[3] != 0){
            //Altitude - cruise
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("WingRR");
            sharedMemory.storeDouble("WingRR", values[3]);
        }
        if(values[4] != 0){
            //Velocity
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("THR");
            sharedMemory.storeDouble("THR", values[4]);
        }
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_STATE_incoming(httpd_req_t *req){
    char received_data[MAX_DATA_LEN] = "";
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        int total_len = req->content_len;
    int cur_len = 0;
    int received = 0;
    
    if (total_len >= MAX_DATA_LEN) {
        return ESP_FAIL;
    }

    while (received < total_len) {
        // Receive the data in chunks
        cur_len = httpd_req_recv(req, received_data + received, MAX_DATA_LEN);
        if (cur_len <= 0) {
            if (cur_len == HTTPD_SOCK_ERR_TIMEOUT) {
                continue;
            }
            return ESP_FAIL;
        }
        received += cur_len;
    }

    // Null-terminate the received_data string
    received_data[received] = '\0';
        // Send a response to the client
        //httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        std::string data = received_data;
        std::vector<std::string> ids;
        std::vector<double> values;

        extractValuesAndIds(data, ids, values);

        //If value from frontend is not 0, update respective variable
        if(values[0] != 0){
            STATE *switchS = new STATE();
            switch(int(values[0])){
                case 1:
                    //State switch to PREP
                    switchS -> updateState(PREP);
                    break;
                case 2:
                    //State switch to ARMED
                    switchS -> updateState(ARMED);
                    break;
                case 3:
                    //State switch to BYPASS
                    switchS -> updateState(BYPASS);
                    break;
            }
            delete switchS;
        }
        if(values[1] != 0){

        }
        if(values[2] != 0){

        }
        if(values[3] != 0){

        }
        if(values[4] != 0){
      
        }
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_AUTH_incoming(httpd_req_t *req){
    char received_data[MAX_DATA_LEN] = "";
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        int total_len = req->content_len;
    int cur_len = 0;
    int received = 0;
    
    if (total_len >= MAX_DATA_LEN) {
        return ESP_FAIL;
    }

    while (received < total_len) {
        // Receive the data in chunks
        cur_len = httpd_req_recv(req, received_data + received, MAX_DATA_LEN);
        if (cur_len <= 0) {
            if (cur_len == HTTPD_SOCK_ERR_TIMEOUT) {
                continue;
            }
            return ESP_FAIL;
        }
        received += cur_len;
    }

    // Null-terminate the received_data string
    received_data[received] = '\0';
        // Send a response to the client
        //httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        std::string data = received_data;
        //Compare token data sent with token data in PTAM register
        //If they match state can be changed to armed
        SharedMemory& sharedMemory = SharedMemory::getInstance();
        std::string token_saved = sharedMemory.getLastString("arm_token");
        if(received_data != token_saved){
            // Send a response to the client indicating no match
            std::string packed_data = "STATE-CHANGE-FAIL";
            httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        }else{
            //Change state to armed by modifying PTAM register
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("state");
            sharedMemory.storeDouble("state", 2);
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("stateDescript");
            sharedMemory.storeString("stateDescript", "ARMED");
            // Send a response to the client indicating direct match
            std::string packed_data = "STATE-CHANGE-SUCCESS";
            httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        }

        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_OTA_incoming(httpd_req_t *req){
    char buf[1000];
	esp_ota_handle_t ota_handle;
	int remaining = req->content_len;

	const esp_partition_t *ota_partition = esp_ota_get_next_update_partition(NULL);
	ESP_ERROR_CHECK(esp_ota_begin(ota_partition, OTA_SIZE_UNKNOWN, &ota_handle));

	while (remaining > 0) {
		int recv_len = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)));

		// Timeout Error: Just retry
		if (recv_len == HTTPD_SOCK_ERR_TIMEOUT) {
			continue;

		// Serious Error: Abort OTA
		} else if (recv_len <= 0) {
			httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Protocol Error");
			return ESP_FAIL;
		}

		// Successful Upload: Flash firmware chunk
		if (esp_ota_write(ota_handle, (const void *)buf, recv_len) != ESP_OK) {
			httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Flash Error");
			return ESP_FAIL;
		}

		remaining -= recv_len;
	}

	// Validate and switch to new OTA image and reboot
	if (esp_ota_end(ota_handle) != ESP_OK || esp_ota_set_boot_partition(ota_partition) != ESP_OK) {
            printf("ota_handle %d\r\n", esp_ota_end(ota_handle));
            printf("ota_partition %d\r\n", esp_ota_set_boot_partition(ota_partition));
			httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Validation / Activation Error");
			return ESP_FAIL;
	}

	httpd_resp_sendstr(req, "Firmware update complete, rebooting now!\n");

	vTaskDelay(500 / portTICK_PERIOD_MS);
	esp_restart();

	return ESP_OK;
}