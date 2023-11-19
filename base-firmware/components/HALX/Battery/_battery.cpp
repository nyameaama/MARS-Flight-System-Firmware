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


//________________________________________________________________________
    /* Check the eFuse settings
    ===========================================================================
    | void
    ===========================================================================
    */
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

//________________________________________________________________________
    /* Print the character value type for ADC calibration
    ===========================================================================
    | void
    ===========================================================================
    */
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

//________________________________________________________________________
    /* Initialize the battery interface
    ===========================================================================
    | Returns: double - The initialized battery voltage.
    ===========================================================================
    */
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
    double adc_reading = 0;
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

    return adc_reading;
}

//________________________________________________________________________
    /* Get the battery percentage
    ===========================================================================
    | Returns: double - The battery percentage.
    ===========================================================================
    */
double BATTERY::returnBatteryPercent(){
    double adc = returnBatteryVoltage();
    // Calculate the ratio of the value within the source range
    //Attenuation Low = 150 mv
    //Attenuation High = 2450 mv
    // Battery voltage scale (10V to 12.6V)
    double vrs = mapValue(adc, 150, 2450, VOLTAGE_MIN, VOLTAGE_MAX);

    //ESP_LOGI("TAG","VA: %f",vrs);
    //Now we do the same to get a percent value
    // Percent Value Scale (0% to 100%)
    double brp = mapValue(vrs, VOLTAGE_MIN, VOLTAGE_MAX, 0, 100);

    return brp;
}

//________________________________________________________________________
    /* Get the current battery voltage
    ===========================================================================
    | Returns: double - The current battery voltage.
    ===========================================================================
    */
double BATTERY::returnBatteryVoltage(){
    double b_II = batteryInterfaceInit();
    //Convert adc_reading to voltage in mV
    double voltage = esp_adc_cal_raw_to_voltage(b_II, adc_chars);
    return voltage;
}

//________________________________________________________________________
    /* Get the current battery current draw
    ===========================================================================
    | Returns: double - The current battery current draw.
    ===========================================================================
    */
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

//________________________________________________________________________
    /* Initialize the ADC for measuring current
    ===========================================================================
    | void
    ===========================================================================
    */
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

//________________________________________________________________________
    /* Map a value from one range to another
    ===========================================================================
    | Parameters:
    |    - value: The value to map.
    |    - fromLow: The low end of the input range.
    |    - fromHigh: The high end of the input range.
    |    - toLow: The low end of the output range.
    |    - toHigh: The high end of the output range.
    | Returns: double - The mapped value.
    ===========================================================================
    */
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