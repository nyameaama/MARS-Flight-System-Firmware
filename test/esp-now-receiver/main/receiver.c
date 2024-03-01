

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../receiver.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

uint8_t*
convertChar(const char* charptr, uint8_t* uint8ptr, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        uint8ptr[i] = (uint8_t)charptr[i];
    }
    return uint8ptr;
}

const char*
convertUint(const uint8_t* uint8data, size_t length)
{
    return (const char*)uint8data;
}