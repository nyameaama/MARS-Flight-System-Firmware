#pragma once

#ifndef BMI270_DEFS_H_
#define BMI270_DEFS_H_

#include <stdint.h>

/* ----------------------------------------------------
                    REGISTERS
-----------------------------------------------------*/

// I2C
#define I2C_DEVICE          "/dev/i2c-1"
#define I2C_BUS             (1)
#define I2C_SLAVE	        0x0703
#define I2C_PRIM_ADDR       (0x68)
#define I2C_SEC_ADDR        (0x69)

// General
#define CHIP_ID_ADDRESS     (0x00)
#define SENSORTIME_0        (0x18)
#define SENSORTIME_1        (0x19)
#define SENSORTIME_2        (0x1A)
#define INTERNAL_STATUS     (0x21)
#define DATA_REG            (0x0C)
#define FIFO_CONFIG_0       (0x48)
#define FIFO_CONFIG_1       (0x49)
#define INIT_CTRL           (0x59)
#define INIT_ADDR_0         (0x5B)
#define INIT_ADDR_1         (0x5C)
#define INIT_DATA           (0x5E)
#define CMD                 (0x7E)
#define PWR_CONF            (0x7C)
#define PWR_CTRL            (0x7D)

// Accelerometer
#define ACC_CONF            (0x40)
#define ACC_RANGE           (0x41)
#define ACC_X_7_0           (0x0C)
#define ACC_X_15_8          (0x0D)
#define ACC_Y_7_0           (0x0E)
#define ACC_Y_15_8          (0x0F)
#define ACC_Z_7_0           (0x10)
#define ACC_Z_15_8          (0x11)

// Gyroscope
#define GYR_CONF            (0x42)
#define GYR_RANGE           (0x43)
#define GYR_X_7_0           (0x12)
#define GYR_X_15_8          (0x13)
#define GYR_Y_7_0           (0x14)
#define GYR_Y_15_8          (0x15)
#define GYR_Z_7_0           (0x16)
#define GYR_Z_15_8          (0x17)

// Temperature
#define TEMP_7_0            (0x22)
#define TEMP_15_8           (0x23)

/* ----------------------------------------------------
                    DEFINITIONS
-----------------------------------------------------*/

// General
#define GRAVITY             9.80665
#define DEG2RAD             (3.141592653589793 / 180.0)
#define HERTZ_100           0.01
#define HERTZ_200           0.005
#define BINARY              (2)
#define HEXADECIMAL         (16)
#define BIT_0               0b00000001
#define BIT_1               0b00000010
#define BIT_2               0b00000100
#define BIT_3               0b00001000
#define BIT_4               0b00010000
#define BIT_5               0b00100000
#define BIT_6               0b01000000
#define BIT_7               0b10000000
#define LSB_MASK_8BIT       (0x0F)      // 00001111
#define MSB_MASK_8BIT       (0xF0)      // 11110000
#define FULL_MASK_8BIT      (0xFF)      // 11111111
#define LSB_MASK_8BIT_5     (0x1F)      // 00011111
#define LSB_MASK_8BIT_8     (0x8F)      // 10001111
#define LAST_2_BITS         (0xC0)      // 11000000
#define LAST_3_BITS         (0xE0)      // 11100000


// BMI270
#define BMI270_CHIP_ID      (0x24)

// Device Modes
#define LOW_POWER_MODE      (0)
#define NORMAL_MODE         (1)
#define PERFORMANCE_MODE    (2)

// Accelerometer
#define ACC_RANGE_2G        (0x00)      // +/- 2g
#define ACC_RANGE_4G        (0x01)      // +/- 4g
#define ACC_RANGE_8G        (0x02)      // +/- 8g
#define ACC_RANGE_16G       (0x03)      // +/- 16g
#define ACC_ODR_1600        (0x0C)      // 1600Hz
#define ACC_ODR_800         (0x0B)      // 800Hz
#define ACC_ODR_400         (0x0A)      // 400Hz
#define ACC_ODR_200         (0x09)      // 200Hz
#define ACC_ODR_100         (0x08)      // 100Hz
#define ACC_ODR_50          (0x07)      // 50Hz
#define ACC_ODR_25          (0x06)      // 25Hz
#define ACC_BWP_OSR4        (0x00)      // OSR4
#define ACC_BWP_OSR2        (0x01)      // OSR2
#define ACC_BWP_NORMAL      (0x02)      // Normal
#define ACC_BWP_CIC         (0x03)      // CIC
#define ACC_BWP_RES16       (0x04)      // Reserved
#define ACC_BWP_RES32       (0x05)      // Reserved
#define ACC_BWP_RES64       (0x06)      // Reserved
#define ACC_BWP_RES128      (0x07)      // Reserved

// Gyroscope
#define GYR_RANGE_2000      (0x00)      // +/- 2000dps,  16.4 LSB/dps
#define GYR_RANGE_1000      (0x01)      // +/- 1000dps,  32.8 LSB/dps
#define GYR_RANGE_500       (0x02)      // +/- 500dps,   65.6 LSB/dps
#define GYR_RANGE_250       (0x03)      // +/- 250dps,  131.2 LSB/dps
#define GYR_RANGE_125       (0x04)      // +/- 125dps,  262.4 LSB/dps
#define GYR_ODR_3200        (0x0D)      // 3200Hz
#define GYR_ODR_1600        (0x0C)      // 1600Hz
#define GYR_ODR_800         (0x0B)      // 800Hz
#define GYR_ODR_400         (0x0A)      // 400Hz
#define GYR_ODR_200         (0x09)      // 200Hz
#define GYR_ODR_100         (0x08)      // 100Hz
#define GYR_ODR_50          (0x07)      // 50Hz
#define GYR_ODR_25          (0x06)      // 25Hz
#define GYR_BWP_OSR4        (0x00)      // OSR4
#define GYR_BWP_OSR2        (0x01)      // OSR2
#define GYR_BWP_NORMAL      (0x02)      // Normal


struct bmi270
{
    /* I2C File Descriptor */
    int i2c_fd;

    /* I2C Address */
    uint8_t i2c_addr;

    /* Chip ID */
    uint8_t chip_id;

    /* Internal Status */
    uint8_t internal_status;

    /* Accelerator Range */
    double acc_range;

    /* Accelerator ODR */
    int acc_odr;

    /* Gyroscope Range */
    double gyr_range;

    /* Gyroscope ODR */
    int gyr_odr;
};

#endif /* BMI270_DEFS_H */