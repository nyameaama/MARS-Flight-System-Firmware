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
        //________________________________________________________________________
        /* Initialize the battery interface
        ===========================================================================
        | Returns: double - The initialized battery voltage.
        ===========================================================================
        */
        static double batteryInterfaceInit();
        
        //________________________________________________________________________
        /* Get the current battery voltage
        ===========================================================================
        | Returns: double - The current battery voltage.
        ===========================================================================
        */
        static double returnBatteryVoltage();

        //________________________________________________________________________
        /* Get the current battery current draw
        ===========================================================================
        | Returns: double - The current battery current draw.
        ===========================================================================
        */
        static double returnBatteryCurrentDraw();

        //________________________________________________________________________
        /* Initialize the ADC for measuring current
        ===========================================================================
        | void
        ===========================================================================
        */
        static void initCurrentADC();

        //________________________________________________________________________
        /* Get the battery percentage
        ===========================================================================
        | Returns: double - The battery percentage.
        ===========================================================================
        */
        static double returnBatteryPercent();

        //________________________________________________________________________
        /* Print the character value type for ADC calibration
        ===========================================================================
        | void
        ===========================================================================
        */
        static void print_char_val_type(esp_adc_cal_value_t val_type);

        //________________________________________________________________________
        /* Check the eFuse settings
        ===========================================================================
        | void
        ===========================================================================
        */
        static void check_efuse(void);

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
        static double mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh);
};

#endif //BATTERY