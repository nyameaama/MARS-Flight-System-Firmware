#ifndef _BATTERY_
#define _BATTERY_

class BATTERY{
    public:
        static void batteryInterfaceInit();
        
        static uint16_t returnBatteryVoltage();

        static double returnBatteryCurrentDraw();

        static double returnBatteryPercent();

        static void adcInit(void);

        static float analogReadVoltage();

        static void print_char_val_type(esp_adc_cal_value_t val_type);

        static bool adcTest(void);
};

#endif //BATTERY