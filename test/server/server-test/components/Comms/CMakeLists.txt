idf_component_register(SRCS "page.cpp" "_broadcast.cpp"
                        INCLUDE_DIRS "."
                        REQUIRES esp_wifi esp_netif esp_http_server nvs_flash driver)
