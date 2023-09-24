#include"_battery.h"
//https://en.ovcharov.me/2020/02/29/how-to-measure-battery-level-with-esp32-microcontroller/

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"

#define DEFAULT_VREF    1100        // Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   16          // Multisampling

#define TAG "Meter"

static esp_adc_cal_characteristics_t *adc_chars;

static const adc_channel_t channel = ADC_CHANNEL_7;     //GPIO35 if ADC1, GPIO14 if ADC2
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;

static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

#define ACS724LLCTR_OUTPUT_PIN ADC_CHANNEL_6 //GPIO34
#define SENSITIVITY 40.0  // Sensitivity of ACS724LLCTR in mV/A

#define R2 300
#define R3 100

#define VOLTAGE_OUT(Vin) (((Vin) * R3) / (R2 + R3))

#define VOLTAGE_MAX 12.6
#define VOLTAGE_MIN 10

#define VOLTAGE_TO_ADC(in) ((DEFAULT_VREF * (in)) / 4096)

#define BATTERY_MAX_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MAX))
#define BATTERY_MIN_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MIN))



void  BATTERY::check_efuse(void)
{
    // Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        ESP_LOGI(TAG, "eFuse Two Point: Supported");
    } else {
        ESP_LOGI(TAG, "eFuse Two Point: NOT supported");
    }
    // Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        ESP_LOGI(TAG, "eFuse Vref: Supported");
    } else {
        ESP_LOGI(TAG, "eFuse Vref: NOT supported");
    }
}

void BATTERY::print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        ESP_LOGI(TAG, "Characterized using Two Point Value");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        ESP_LOGI(TAG, "Characterized using eFuse Vref");
    } else {
        ESP_LOGI(TAG, "Characterized using Default Vref");
    }
}

double BATTERY::batteryInterfaceInit()
{
    // Check if Two Point or Vref are burned into eFuse
    //check_efuse();

    // Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(width);
        adc1_config_channel_atten((adc1_channel_t)channel, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
    }

    // Characterize ADC
    adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);
    //print_char_val_type(val_type);

    // Sample ADC1
    int adc_reading = 0;
    // Multisampling
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
    // Convert adc_reading to voltage in mV
    int voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    ESP_LOGI(TAG, "Raw: %d\tVoltage: %dmV", adc_reading, voltage);
    double percent = returnBatteryPercent(voltage);
    return percent;
}

double BATTERY::returnBatteryPercent(int adc){
    // Calculate the ratio of the value within the source range
    //Attenuation Low = 150 mv
    //Attenuation High = 2450 mv
    ESP_LOGI("TAG","VX: %d",adc);
    // Battery voltage scale (10V to 12.6V)
    double vrs = mapValue(adc, 150, 2450, VOLTAGE_MIN, VOLTAGE_MAX);

    ESP_LOGI("TAG","VA: %f",vrs);
    //Now we do the same to get a percent value
    // Percent Value Scale (0% to 100%)
    double brp = mapValue(vrs, VOLTAGE_MIN, VOLTAGE_MAX, 0, 100);

    return brp;
}

//Returns current in ma
double BATTERY::returnBatteryCurrentDraw(){
    initCurrentADC();
    // Sample ADC1
    int adc_reading = 0;
    // Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        if (unit == ADC_UNIT_1) {
            adc_reading += adc1_get_raw((adc1_channel_t)ACS724LLCTR_OUTPUT_PIN);
        } else {
            int raw;
            adc2_get_raw((adc2_channel_t)ACS724LLCTR_OUTPUT_PIN, width, &raw);
            adc_reading += raw;
        }
    }
    adc_reading /= NO_OF_SAMPLES;
    // Convert adc_reading to voltage in mV
    int voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    // Convert voltage to current using the sensor's sensitivity
    //Convert mv to V and use datasheet to calculate current
    double current = ((voltage / 1000) - 2.5) / SENSITIVITY;
    //Convert to milliamps
    return current * 1000;
}

void BATTERY::initCurrentADC(){
    // Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(width);
        adc1_config_channel_atten((adc1_channel_t)ACS724LLCTR_OUTPUT_PIN, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)ACS724LLCTR_OUTPUT_PIN, atten);
    }

    // Characterize ADC
    adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);
}

double BATTERY::mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh) {
    // Check if the value is within the source range
    if (value < fromLow) {
        value = fromLow;
    } else if (value > fromHigh) {
        value = fromHigh;
    }

    // Calculate the ratio of the value within the source range
    double ratio = (value - fromLow) / (fromHigh - fromLow);

    // Map the ratio to the target range
    double result = toLow + ratio * (toHigh - toLow);

    return result;
}