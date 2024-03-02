#ifndef ICM42688
#define ICM42688

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <zephyr/drivers/i2c.h>

/**
* @brief Read a sequence of bytes from sensor registers
*/
void icm42688p_register_read(uint8_t reg_addr, uint8_t *data, size_t len);

/**
 * 
 * @brief Write a byte to a icm42688p sensor register
 */
void icm42688p_register_write_byte(uint8_t reg_addr, uint8_t data);

/**
* @brief i2c master initialization
*/
void i2c_master_init(void);

void ICM_INIT();

//void setBank();

void reset();

/*!
* @brief This function converts lsb to meter per second squared for 16 bit accelerometer at
* range 2G, 4G, 8G or 16G.
*/
float lsb_to_mps2(int16_t val, int8_t g_range, uint8_t bit_width);

/*!
* @brief This function converts lsb to degree per second for 16 bit gyro at
* range 125, 250, 500, 1000 or 2000dps.
*/
float lsb_to_dps(int16_t val, float dps, uint8_t bit_width);

/*!
* @brief This function reads raw accel_x LSB data and converts to degree per second
*/double accel_read_rawX();

/*!
* @brief This function reads raw accel_y LSB data and converts to degree per second
*/
double accel_read_rawY();

/*!
* @brief This function reads raw accel_z LSB data and converts to degree per second
*/
double accel_read_rawZ();

/*!
* @brief This function reads raw gyro_x LSB data and converts to degree per second
*/
double gyro_read_rawX();

/*!
* @brief This function reads raw gyro_y LSB data and converts to degree per second
*/
double gyro_read_rawY();

/*!
* @brief This function reads raw gyro_z LSB data and converts to degree per second
*/

double gyro_read_rawZ();

#endif //ICM42688