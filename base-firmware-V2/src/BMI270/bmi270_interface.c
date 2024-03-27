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

#include "bmi270_interface.h"
#include <zephyr/sys/printk.h>

#define NUM_DATA 14                     // Number of int values to send
struct bmi270 sensor_upper = {.i2c_addr = I2C_PRIM_ADDR};

static void bmi270_init(){
    if (bmi270_init(&sensor_upper) == -1){
        printf("Failed to initialize sensor_upper");
    }

    // -------------------------------------------------
    // HARDWARE CONFIGURATION
    // -------------------------------------------------

    set_mode(&sensor_upper, PERFORMANCE_MODE);
    set_acc_range(&sensor_upper, ACC_RANGE_2G);
    set_gyr_range(&sensor_upper, GYR_RANGE_1000);
    set_acc_odr(&sensor_upper, ACC_ODR_200);
    set_gyr_odr(&sensor_upper, GYR_ODR_200);
    set_acc_bwp(&sensor_upper, ACC_BWP_OSR4);
    set_gyr_bwp(&sensor_upper, GYR_BWP_OSR4);
    disable_fifo_header(&sensor_upper);
    enable_data_streaming(&sensor_upper);
    enable_acc_filter_perf(&sensor_upper);
    enable_gyr_noise_perf(&sensor_upper);
    enable_gyr_filter_perf(&sensor_upper);

    set_mode(&sensor_lower, PERFORMANCE_MODE);
    set_acc_range(&sensor_lower, ACC_RANGE_2G);
    set_gyr_range(&sensor_lower, GYR_RANGE_1000);
    set_acc_odr(&sensor_lower, ACC_ODR_200);
    set_gyr_odr(&sensor_lower, GYR_ODR_200);
    set_acc_bwp(&sensor_lower, ACC_BWP_OSR4);
    set_gyr_bwp(&sensor_lower, GYR_BWP_OSR4);
    disable_fifo_header(&sensor_lower);
    enable_data_streaming(&sensor_lower);
    enable_acc_filter_perf(&sensor_lower);
    enable_gyr_noise_perf(&sensor_lower);
    enable_gyr_filter_perf(&sensor_lower);  
}

static double bmi270_read_accel_rawX(){
    int16_t temp_acc[3];
    int32_t data_array[NUM_DATA];
    get_acc_raw(&sensor_upper, &temp_acc[0], &temp_acc[1], &temp_acc[2]);
    return (int32_t)temp_acc[0]; //accX
}

static double bmi270_read_accel_rawY(){
    int16_t temp_acc[3];
    int32_t data_array[NUM_DATA];
    get_acc_raw(&sensor_upper, &temp_acc[0], &temp_acc[1], &temp_acc[2]);
    return (int32_t)temp_acc[1]; //accY
}

static double bmi270_read_accel_rawZ(){
    int16_t temp_acc[3];
    int32_t data_array[NUM_DATA];
    get_acc_raw(&sensor_upper, &temp_acc[0], &temp_acc[1], &temp_acc[2]);
    return (int32_t)temp_acc[2]; //accZ
}

static double bmi270_read_gyro_rawX(){
    int16_t temp_gyr[3];
    int32_t data_array[NUM_DATA];
    get_gyr_raw(&sensor_upper, &temp_gyr[0], &temp_gyr[1], &temp_gyr[2]);
    return (int32_t)temp_gyr[0]; //gyroX
}

static double bmi270_read_gyro_rawY(){
    int16_t temp_gyr[3];
    int32_t data_array[NUM_DATA];
    get_gyr_raw(&sensor_upper, &temp_gyr[0], &temp_gyr[1], &temp_gyr[2]);
    return (int32_t)temp_gyr[1]; //gyroY
}

static double bmi270_read_gyro_rawZ(){
    int16_t temp_gyr[3];
    int32_t data_array[NUM_DATA];
    get_gyr_raw(&sensor_upper, &temp_gyr[0], &temp_gyr[1], &temp_gyr[2]);
    return (int32_t)temp_gyr[2]; //gyroZ
}


