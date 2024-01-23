#ifndef IMU
#define IMU

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PITCH (uint8_t)0
#define ROLL (uint8_t)1
#define YAW (uint8_t)2

class BMI088_IMU
{
  public:
    static void IMU_INIT();
    /**
     * @brief Read a sequence of bytes from a BM1088 accel sensor registers
     */
    static esp_err_t bm1088_accel_read(uint8_t reg_addr, uint8_t* data, size_t len);

    /**
     * @brief Read a sequence of bytes from a BM1088 gyro sensor registers
     */
    static esp_err_t bm1088_gyro_read(uint8_t reg_addr, uint8_t* data, size_t len);

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

    static double linearInterpolate(double input, double input_start, double input_end,
                                    double output_start, double output_end);

    static double readAugmentedIMUData(uint8_t angle_type);
};

#endif  // IMU
