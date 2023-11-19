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

#ifndef IMU
#define IMU

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"

class BMI088_IMU {
    public:
        static void IMU_INIT();
        /**
         * @brief Read a sequence of bytes from a BM1088 accel sensor registers
         */
        static esp_err_t bm1088_accel_read(uint8_t reg_addr, uint8_t *data, size_t len);

        /**
         * @brief Read a sequence of bytes from a BM1088 gyro sensor registers
         */
        static esp_err_t bm1088_gyro_read(uint8_t reg_addr, uint8_t *data, size_t len);

        /**
         * @brief Write a byte to a BM1088 accel sensor register
         */
        static esp_err_t bm1088_accel_write_byte(uint8_t reg_addr, uint8_t data);

        /**
         * @brief Write a byte to a BM1088 gyro sensor register
        */
        static esp_err_t bm1088_gyro_write_byte(uint8_t reg_addr, uint8_t data);

        /**
         * @brief i2c master initialization
         */
        static esp_err_t i2c_master_init(void);

        /*!
        * @brief This function converts lsb to meter per second squared for 16 bit accelerometer at
        * range 2G, 4G, 8G or 16G.
        */
        static float lsb_to_mps2(int16_t val, int8_t g_range, uint8_t bit_width);

        /*!
        * @brief This function converts lsb to degree per second for 16 bit gyro at
        * range 125, 250, 500, 1000 or 2000dps.
        */
        static float lsb_to_dps(int16_t val, float dps, uint8_t bit_width);

        /*!
        * @brief This function reads raw accel_x LSB data and converts to degree per second
        */
        static double accel_read_rawX();

        /*!
        * @brief This function reads raw accel_y LSB data and converts to degree per second
        */
        static double accel_read_rawY();

        /*!
        * @brief This function reads raw accel_z LSB data and converts to degree per second
        */
        static double accel_read_rawZ();

        /*!
        * @brief This function reads raw gyro_x LSB data and converts to degree per second
        */
        static double gyro_read_rawX();

        /*!
        * @brief This function reads raw gyro_y LSB data and converts to degree per second
        */
        static double gyro_read_rawY();

        /*!
        * @brief This function reads raw gyro_z LSB data and converts to degree per second
        */
        static double gyro_read_rawZ();

        static double angle_read_pitch();

        static double angle_read_roll();

        static double angle_read_yaw();

};

#endif //IMU