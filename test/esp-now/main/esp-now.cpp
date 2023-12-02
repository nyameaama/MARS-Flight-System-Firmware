#include "receiver.c"

extern"C"{
void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    example_wifi_init();
    example_espnow_init();
}
}


/*#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_crc.h"

#define ESPNOW_WIFI_MODE WIFI_MODE_STA
#define ESPNOW_WIFI_IF   wifi_interface_t(ESP_IF_WIFI_STA)
#define ESPNOW_CHANNEL 1

#define delay_millis(millis) vTaskDelay(millis / portTICK_RATE_MS); 

typedef struct ESP_NOW_test_data
{
   std::string id;
   std::string test_value;
} ESP_NOW_test_data_t;

static const char *TAG = "espnow_example";

static uint8_t receiver_mac[ESP_NOW_ETH_ALEN] = { 0x58, 0xBF, 0x25, 0x35, 0xEB, 0x20 };

typedef struct ESP_NOW_send_param
{
    
    uint8_t dest_mac[ESP_NOW_ETH_ALEN];

} ESP_NOW_send_param_t;

// WiFi should start before using ESPNOW 
static void example_wifi_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(ESPNOW_WIFI_MODE) );
    ESP_ERROR_CHECK( esp_wifi_start());

    // enable esp now long range
    //ESP_ERROR_CHECK( esp_wifi_set_protocol(ESPNOW_WIFI_IF, WIFI_PROTOCOL_11B|WIFI_PROTOCOL_11G|WIFI_PROTOCOL_11N|WIFI_PROTOCOL_LR) );
}

static void example_espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    ESP_LOGI(TAG, "Start sending data");
}

static void example_espnow_task(void *pvParameter)
{
    vTaskDelay(2000);
    ESP_LOGI(TAG, "Start sending broadcast data \n");

    ESP_NOW_send_param_t *send_param = (ESP_NOW_send_param_t *)pvParameter;
    
    ESP_NOW_test_data_t ESP_NOW_data;
    ESP_NOW_data.id = "3";
    ESP_NOW_data.test_value = "Sample";
    
    while(true)
    {
        ESP_LOGI(TAG, "message sent \n");
        esp_now_send(send_param->dest_mac, (uint8_t *)&ESP_NOW_data, sizeof(ESP_NOW_data));
        vTaskDelay(1000);
    }
    
}

static esp_err_t example_espnow_init(void)
{
    ESP_NOW_send_param_t *send_param;

    //Initialize ESPNOW and register sending and receiving callback function.
    ESP_ERROR_CHECK( esp_now_init() );
    ESP_ERROR_CHECK( esp_now_register_send_cb(example_espnow_send_cb) );

    // Add broadcast peer information to peer list.
    esp_now_peer_info_t *peer = (esp_now_peer_info_t*) malloc(sizeof(esp_now_peer_info_t));
    if (peer == NULL) {
        ESP_LOGE(TAG, "Malloc peer information fail");
        esp_now_deinit();
        return ESP_FAIL;
    }
    memset(peer, 0, sizeof(esp_now_peer_info_t));
    peer->channel = ESPNOW_CHANNEL;
    peer->ifidx = ESPNOW_WIFI_IF;
    peer->encrypt = false;
    memcpy(peer->peer_addr, receiver_mac, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK( esp_now_add_peer(peer) );
    free(peer);

    // Initialize sending parameters.
    send_param = (ESP_NOW_send_param_t*)malloc(sizeof(ESP_NOW_send_param_t));
    if (send_param == NULL) {
        ESP_LOGE(TAG, "Malloc send parameter fail");
        esp_now_deinit();
        return ESP_FAIL;
    }
    memset(send_param, 0, sizeof(ESP_NOW_send_param_t));
    
    memcpy(send_param->dest_mac, receiver_mac, ESP_NOW_ETH_ALEN);
    
    xTaskCreate(example_espnow_task, "example_espnow_task", 2048, send_param, 4, NULL);

    return ESP_OK;
}

extern"C"{
void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    example_wifi_init();
    example_espnow_init();
}
}*/