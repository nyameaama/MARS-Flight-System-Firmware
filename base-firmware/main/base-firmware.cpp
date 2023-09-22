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

#include <stdio.h>
#include"../components/Comms/_broadcast.h"
#include"../components/HALX/mg90s_servo.h"
#include"../components/HALX/ssd1306.h"
#include"../components/HALX/fan_relay.h"
#include"../components/HALX/_barometerEntry.h"
#include"../components/PTAM/_ptam.h"
#include"../components/system/validateSensors.h"
#include"../components/system/_state.h"
#include"../components/system/sys_controller.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include<string>

uint8_t DRONE_STATE = 1;

extern "C"{
    void app_main(void){
        // Wait for Wi-Fi to initialize
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
        //Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        BroadcastedServer server;
        server.wifi_init_softap();

        SSD1306_Init();
        displayBOOT();
        vTaskDelay(pdMS_TO_TICKS(4000)); // Boot delay

        FAN_COOLING *cool = new FAN_COOLING();
        cool -> init_relay();

        VEHICLE_BARO *baro = new VEHICLE_BARO();
        baro -> init_barometer();
        double tp;

        CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
        //Boot 
        CTobj -> _init_();

        STATE *change = new STATE();   
        while(1){
            if(DRONE_STATE == 1){ // STANDBY
                //Display Controller
                displayStandByClientFail();
                //Fan Controller
                cool -> coolSierra_task(baro -> pushTemperature());
                //FROM STANDBY PREP WE CAN EITHER SWITCH TO ARMED OR BYPASS
                CTobj -> _PREP_();
                if(change -> SWITCH2ARMED() == 1){
                    DRONE_STATE = 2;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
                if(change -> SWITCH2BYPASS() == 1){
                    DRONE_STATE = 3;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
            }

            if(DRONE_STATE == 2){ // ARMED
                //Display Controller
                displayARMED();
                //Fan Controller
                cool -> coolSierra_task(baro -> pushTemperature());
                //FROM ARMED WE CAN EITHER SWITCH TO STANDY PREP OR BYPASS
                CTobj -> _ARMED_();
                if(change -> SWITCH2PREP() == 1){
                    DRONE_STATE = 1;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
                if(change -> SWITCH2BYPASS() == 1){
                    DRONE_STATE = 3;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
            }
            
            if(DRONE_STATE == 3){ // BYPASS
                //Display Controller
                displayBYPASS();
                //Fan Controller
                cool -> coolSierra_task(baro -> pushTemperature());
                //FROM BYPASS WE CAN EITHER SWITCH TO STANDY PREP OR ARMED
                CTobj -> _bypass_(std::string("ID"));
                if(change -> SWITCH2PREP() == 1){
                    DRONE_STATE = 1;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
                if(change -> SWITCH2ARMED() == 1){
                    DRONE_STATE = 2;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
            }

        }
        delete cool;
        delete change;
        delete CTobj;
        delete baro;
    }
}