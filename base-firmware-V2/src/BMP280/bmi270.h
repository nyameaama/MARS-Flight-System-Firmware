#pragma once

#ifndef BMI270_H
#define BMI270_H

#include "bmi270_defs.h"

/* ----------------------------------------------------
                     FUNCTIONS
-----------------------------------------------------*/

/* Print 8 bit value as binary */
void print_binary(uint8_t num);

/* Read 8 bit out of 8 bit register */
uint8_t read_register(struct bmi270 *sensor, uint8_t reg);

/* Read block of 8 bit values out of 8 bit register */
int read_register_block(struct bmi270 *sensor, uint8_t reg_addr, uint8_t *data, uint8_t len);

/* Write 8 bit value into 8 bit register */
int write_register(struct bmi270 *sensor, uint8_t reg, uint8_t val);

/* Write block of 8 bit values into 8 bit register */
int write_register_block(struct bmi270 *sensor, uint8_t reg_addr, uint8_t len, const uint8_t *data);

/* Load config file from bmi270_config_file.h into sensor */
int load_config_file(struct bmi270 *sensor);

/* Initialize sensor - Includes I2C setup and the config file load */
int bmi270_init(struct bmi270 *sensor);

/* Set sensor mode: Low power, Normal, Performance */
void set_mode(struct bmi270 *sensor, uint8_t mode);

/* Enable auxiliary sensor interface */
void enable_aux(struct bmi270 *sensor);

/* Disable auxiliary sensor interface */
void disable_aux(struct bmi270 *sensor);

/* Enable accelerometer */
void enable_acc(struct bmi270 *sensor);

/* Disable accelerometer */
void disable_acc(struct bmi270 *sensor);

/* Enable gyroscope */
void enable_gyr(struct bmi270 *sensor);

/* Disable gyroscope */
void disable_gyr(struct bmi270 *sensor);

/* Enable temperatur sensor */
void enable_temp(struct bmi270 *sensor);

/* Disable temperatur sensor */
void disable_temp(struct bmi270 *sensor);

/* Set accelerometer range */
void set_acc_range(struct bmi270 *sensor, uint8_t range);

/* Set gyroscope range */
void set_gyr_range(struct bmi270 *sensor, uint8_t range);

/* Set accelerometer output data rate */
void set_acc_odr(struct bmi270 *sensor, uint8_t odr);

/* Set gyroscope output data rate */
void set_gyr_odr(struct bmi270 *sensor, uint8_t odr);

/* Set accelerometer bandwidth parameter */
void set_acc_bwp(struct bmi270 *sensor, uint8_t bwp);

/* Set gyroscope bandwidth */
void set_gyr_bwp(struct bmi270 *sensor, uint8_t bwp);

/* Enable FIFO header */
void enable_fifo_header(struct bmi270 *sensor);

/* Disable FIFO header */
void disable_fifo_header(struct bmi270 *sensor);

/* Enable data streaming */
void enable_data_streaming(struct bmi270 *sensor);

/* Disable data streaming */
void disable_data_streaming(struct bmi270 *sensor);

/* Enable accelerometer filter performance */
void enable_acc_filter_perf(struct bmi270 *sensor);

/* Disable accelerometer filter performance */
void disable_acc_filter_perf(struct bmi270 *sensor);

/* Enable gyroscope noise performance */
void enable_gyr_noise_perf(struct bmi270 *sensor);

/* Disable gyroscope noise performance */
void disable_gyr_noise_perf(struct bmi270 *sensor);

/* Enable gyroscope filter performance */
void enable_gyr_filter_perf(struct bmi270 *sensor);

/* Disable gyroscope filter performance */
void disable_gyr_filter_perf(struct bmi270 *sensor);

/* Get raw accelerometer data */
void get_acc_raw(struct bmi270 *sensor, int16_t *acc_x_raw, int16_t *acc_y_raw, int16_t *acc_z_raw);

/* Get raw gyroscope data */
void get_gyr_raw(struct bmi270 *sensor, int16_t *gyr_x_raw, int16_t *gyr_y_raw, int16_t *gyr_z_raw);

/* Get raw temperature data */
void get_temp_raw(struct bmi270 *sensor, int16_t *temp);

/* Get accelerometer data in m/s^2 */
void get_acc(struct bmi270 *sensor, double *acc_x, double *acc_y, double *acc_z);

/* Get gyroscope data in °/s */
void get_gyr(struct bmi270 *sensor, double *gyr_x, double *gyr_y, double *gyr_z);

/* Get temperature data in °C */
void get_temp(struct bmi270 *sensor, double *temp);

#endif // BMI270_H