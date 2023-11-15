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

#include"../components/Comms/_broadcast.h"
#include"../components/HALX/mg90s_servo.h"
#include"../components/HALX/ssd1306.h"
#include"../components/HALX/fan_relay.h"
#include"../components/HALX/_barometerEntry.h"
#include"../components/PTAM/_ptam.h"
#include"../components/system/validateSensors.h"
#include"../components/system/_state.h"
#include"../components/system/sys_controller.h"
#include"../components/Logging/logger.hpp"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include<string>
#include <esp_ota_ops.h>
#include"os_config.h"

uint8_t DRONE_STATE = 1;

void monitor_memory_task(void *pvParameters) {
    while (1) {
        // Get the free heap memory size in bytes
        size_t free_heap_size = esp_get_free_heap_size();
        
        // Print the free heap memory size
        ESP_LOGI("Memory", "Free Heap Size: %u bytes", free_heap_size);
        if(free_heap_size < 10000){
            esp_restart();
        }
        // Delay for some time before checking again
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
    }
}

void INIT_CORE0(void *pvParameters){
    /* Mark current app as valid */
        const esp_partition_t *partition = esp_ota_get_running_partition();

        esp_ota_img_states_t ota_state;
        if (esp_ota_get_state_partition(partition, &ota_state) == ESP_OK) {
            if (ota_state == ESP_OTA_IMG_PENDING_VERIFY) {
                esp_ota_mark_app_valid_cancel_rollback();
            }
        }

        SSD1306_Init();
        displayBOOT();
        vTaskDelay(pdMS_TO_TICKS(4000)); // Boot delay

        //VEHICLE_BARO *baro = new VEHICLE_BARO();
        //baro -> init_barometer();
        //delete baro;

        //FAN_COOLING *cool = new FAN_COOLING();
        //cool -> init_relay();
        //delete cool;

        CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
        //Boot 
        CTobj -> _init_();
        delete CTobj;

        
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

        while(1){
            CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
            STATE *change = new STATE(); 
            //VEHICLE_BARO *baro = new VEHICLE_BARO();
            //FAN_COOLING *cool = new FAN_COOLING();

            if(DRONE_STATE == 1){ // STANDBY
                //Idle Restart Task
                CTobj -> restart_after_idle_task();
                //Display Controller
                displayStandByClientSuccess();
                //Fan Controller
                //cool -> coolSierra_task(baro -> pushTemperature());
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
                //cool -> coolSierra_task(baro -> pushTemperature());
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
                //Idle Restart Task
                CTobj -> restart_after_idle_task();
                //Display Controller
                displayBYPASS();
                //Fan Controller
                //cool -> coolSierra_task(baro -> pushTemperature());
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

            //delete cool;
            delete change;
            //delete baro;
            delete CTobj;
        }
}

extern "C"{
    void app_main(void){
        xTaskCreate(&monitor_memory_task, "memory_task", 2048, NULL, 5, NULL);
        xTaskCreate(&INIT_CORE0, "INIT_CORE0", 4096, NULL, 5, NULL);
    }
}