#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include <esp_ota_ops.h>
#include"../components/system/_state.h"

uint8_t COMP_STATE = 2;

void INIT_DEFAULT_TSK(void *pvParameters);

extern "C"{
    void app_main(void)
    {
        xTaskCreate(&INIT_DEFAULT_TSK, "INIT_DEFAULT_TSK", 4096, NULL, 5, NULL);
    }
}

void INIT_DEFAULT_TSK(void *pvParameters){
    /* Mark current app as valid */
        const esp_partition_t *partition = esp_ota_get_running_partition();

        esp_ota_img_states_t ota_state;
        if (esp_ota_get_state_partition(partition, &ota_state) == ESP_OK) {
            if (ota_state == ESP_OTA_IMG_PENDING_VERIFY) {
                esp_ota_mark_app_valid_cancel_rollback();
            }
        }
        while(1){
            STATE *change = new STATE(); 

            if(COMP_STATE == 1){ // LOW POWER
                //FROM LOW POWER WE CAN SWITCH TO STANDARD
                if(change -> SWITCH2STANDARD() == 1){
                    COMP_STATE = 2;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
            }

            if(COMP_STATE == 2){ // STANDARD
                //FROM STANDARD WE CAN EITHER SWITCH TO LOW POWER
                if(change -> SWITCH2LOWPOWER() == 1){
                    COMP_STATE = 1;
                    //Set a stategic delay so we dont trigger CPU1 watchdog timer
                    vTaskDelay(1);
                    continue;
                }
            }
            delete change;
        }
}