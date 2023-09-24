#ifndef _BATTERY_
#define _BATTERY_

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"

class BATTERY{
    public:
        static double batteryInterfaceInit();
        
        static uint16_t returnBatteryVoltage();

        static double returnBatteryCurrentDraw();

        static void initCurrentADC();

        static double returnBatteryPercent(int adc);

        static void print_char_val_type(esp_adc_cal_value_t val_type);

        static void check_efuse(void);

        static double mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh);
};

#endif //BATTERY