idf_component_register(SRCS "OTA_test.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES web/index.html
                    REQUIRES esp_wifi esp_netif esp_http_server nvs_flash app_update)
