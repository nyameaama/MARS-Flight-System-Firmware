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

#ifndef LSM303
#define LSM303

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include "lsm303agr_reg.h"

/**
 * @brief Writes data to a specific register on the platform.
 * 
 * This function writes a sequence of bytes to a specified register
 * address using i2c.
 * 
 * @param handle Pointer to the platform-specific handle.
 * @param reg Register address to write to.
 * @param bufp Pointer to the data buffer that will be written.
 * @param len Number of bytes to write.
 * @return int32_t Returns 0 for a successful operation, non-zero for failure.
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);

/**
 * @brief Reads data from a specific register on the platform.
 * 
 * This function reads a sequence of bytes from a specified register
 * address using i2c.
 * 
 * @param handle Pointer to the platform-specific handle.
 * @param reg Register address to read from.
 * @param bufp Pointer to the data buffer where read data will be stored.
 * @param len Number of bytes to read.
 * @return int32_t Returns 0 for a successful operation, non-zero for failure.
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

/**
 * @brief Delays execution for a given number of milliseconds.
 * 
 * @param ms Number of milliseconds to delay.
 */
static void platform_delay(uint32_t ms);

/**
 * @brief Initializes the platform.
 * 
 * This function performs any necessary initializations on the platform,
 * such as setting up communication interfaces or configuring hardware.
 */
static void platform_init(void);

/**
 * @brief Initializes the LSM303 sensor.
 * 
 * Sets up the LSM303 sensor for reading accelerometer and magnetometer
 * data, including configuring registers and setting default states.
 */
static void lsm303_init();

/**
 * @brief Reads raw X-axis acceleration data from LSM303.
 * 
 * @return double Returns the raw X-axis acceleration value.
 */
static double lsm303_read_accel_rawX();

/**
 * @brief Reads raw Y-axis acceleration data from LSM303.
 * 
 * @return double Returns the raw Y-axis acceleration value.
 */
static double lsm303_read_accel_rawY();

/**
 * @brief Reads raw Z-axis acceleration data from LSM303.
 * 
 * @return double Returns the raw Z-axis acceleration value.
 */
static double lsm303_read_accel_rawZ();

/**
 * @brief Reads raw X-axis magnetic data from LSM303.
 * 
 * @return double Returns the raw X-axis magnetic value.
 */
static double lsm303_read_mag_rawX();

/**
 * @brief Reads raw Y-axis magnetic data from LSM303.
 * 
 * @return double Returns the raw Y-axis magnetic value.
 */
static double lsm303_read_mag_rawY();

/**
 * @brief Reads raw Z-axis magnetic data from LSM303.
 * 
 * @return double Returns the raw Z-axis magnetic value.
 */
static double lsm303_read_mag_rawZ();

/**
 * @brief Reads raw temperature data from LSM303.
 * 
 * @return double Returns the raw temperature data value.
 */
static double lsm303_read_temp();

#endif //LSM303