#include"_battery.h"
#include "driver/gpio.h"
#include "esp_adc_cal.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"
//https://en.ovcharov.me/2020/02/29/how-to-measure-battery-level-with-esp32-microcontroller/

#define BATTERY_GPIO_PIN gpio_num_t(0)
#define R2 100
#define R3 10
#define VOLTAGE_OUT(Vin) (((Vin) * R3) / (R2 + R3))
#define VOLTAGE_MAX 4200
#define VOLTAGE_MIN 3300
#define ADC_REFERENCE 1100
#define VOLTAGE_TO_ADC(in) ((ADC_REFERENCE * (in)) / 4096)
#define BATTERY_MAX_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MAX))
#define BATTERY_MIN_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MIN))

static bool isInit;

//static esp_adc_cal_characteristics_t *adc_chars;
//static const adc_channel_t channel = ADC_CHANNEL_7; //GPIO35 if ADC1

// Define the ADC channel to read from (GPIO35)
#define ADC_CHANNEL    ADC1_CHANNEL_7
#define ADC1_EXAMPLE_CHAN0          ADC1_CHANNEL_7

static int adc_raw[2][10];
static const char *TAG = "ADC SINGLE";

static esp_adc_cal_characteristics_t adc1_chars;
//ADC Attenuation
#define ADC_EXAMPLE_ATTEN           ADC_ATTEN_DB_11

//ADC Calibration
#if CONFIG_IDF_TARGET_ESP32
#define ADC_EXAMPLE_CALI_SCHEME     ESP_ADC_CAL_VAL_EFUSE_VREF


float BATTERY::analogReadVoltage()
{
    /*uint32_t adc_reading = 0;
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        if (unit == ADC_UNIT_1) {
            adc_reading += adc1_get_raw((adc1_channel_t)channel);
        } else {
            int raw;
            adc2_get_raw((adc2_channel_t)channel, width, &raw);
            adc_reading += raw;
        }
    }
    adc_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    return voltage / 1000.0;*/
    return 0;
}

void BATTERY::adcInit(void)
{
     esp_err_t ret;
    bool cali_enable = false;

    ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else if (ret == ESP_OK) {
        cali_enable = true;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    } else {
        ESP_LOGE(TAG, "Invalid arg");
    }

    esp_err_t ret = ESP_OK;
    uint32_t voltage = 0;
    bool cali_enable = adc_calibration_init();

    //ADC1 config
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_EXAMPLE_CHAN0, ADC_EXAMPLE_ATTEN));
    

}

bool BATTERY::adcTest(void)
{
    return isInit;
}

uint16_t BATTERY::returnBatteryVoltage(){
    uint16_t voltage = 0;
    adc_raw[0][0] = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
    ESP_LOGI("BTT", "raw  data: %d", adc_raw[0][0]);

    voltage = esp_adc_cal_raw_to_voltage(adc_raw[0][0], &adc1_chars);
    ESP_LOGI("BTT", "cali data: %d mV", voltage);
    return voltage;
}

double BATTERY::returnBatteryCurrentDraw(){
    return 0;
}

double BATTERY::returnBatteryPercent(){
    int adc;
    int battery_percentage = 100 * (adc - BATTERY_MIN_ADC) / (BATTERY_MAX_ADC - BATTERY_MIN_ADC);

    if (battery_percentage < 0)
        battery_percentage = 0;
    if (battery_percentage > 100)
        battery_percentage = 100;

    return battery_percentage;
}