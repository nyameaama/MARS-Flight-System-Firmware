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

#include "battery.h"

const struct device *adc_dev;

#define ADC_DEVICE_NAME DT_ADC_0_NAME
#define ADC_RESOLUTION 10
#define ADC_GAIN ADC_GAIN_1_6
#define ADC_REFERENCE ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10)
#define ADC_1ST_CHANNEL_ID 0
#define ADC_1ST_CHANNEL_INPUT NRF_SAADC_INPUT_AIN0
#define ADC_2ND_CHANNEL_ID 2
#define ADC_2ND_CHANNEL_INPUT NRF_SAADC_INPUT_AIN2

static const struct adc_channel_cfg m_1st_channel_cfg = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_1ST_CHANNEL_ID,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive = ADC_1ST_CHANNEL_INPUT,
#endif
};

#define BUFFER_SIZE 8
static int16_t m_sample_buffer[BUFFER_SIZE];

const struct adc_sequence_options sequence_opts = {
	.interval_us = 0,
	.callback = NULL,
	.user_data = NULL,
	.extra_samplings = 7,
};

double batteryInterfaceInit(){
    int err;

	adc_dev = device_get_binding("ADC_0");
	if (!adc_dev) {
		//printk("device_get_binding ADC_0 failed\n");
	}
	err = adc_channel_setup(adc_dev, &m_1st_channel_cfg);
	if (err) {
		//printk("Error in adc setup: %d\n", err);
	}
    NRF_SAADC_S->TASKS_CALIBRATEOFFSET = 1;
    return 0;
}

double returnBatteryVoltage(){
    double voltageArray[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) {
		float adc_voltage = 0;
		adc_voltage = (float)(((float)m_sample_buffer[i] / 1023.0f) *
				      3600.0f);
        voltageArray[i] = adc_voltage;
	}
    return calculateAverage(voltageArray, BUFFER_SIZE);
}

int adc_sample(void){
	int ret;

	const struct adc_sequence sequence = {
		.options = &sequence_opts,
		.channels = BIT(ADC_1ST_CHANNEL_ID),
		.buffer = m_sample_buffer,
		.buffer_size = sizeof(m_sample_buffer),
		.resolution = ADC_RESOLUTION,
	};

	if (!adc_dev) {
		return -1;
	}

	ret = adc_read(adc_dev, &sequence);

    double ADCArray[BUFFER_SIZE];
	for (int i = 0; i < BUFFER_SIZE; i++) {
        ADCArray[i] = m_sample_buffer[i];
	}
	return calculateAverage(ADCArray, BUFFER_SIZE);
}

// Function to calculate the average of an array
double calculateAverage(const int array[], int size) {
    if (size <= 0) {
        // Handle empty array or invalid size
        //printf("Error: Invalid array size\n");
        return 0.0;
    }

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }

    // Calculate and return the average
    return (double)sum / size;
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