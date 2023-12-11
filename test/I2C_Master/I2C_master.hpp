/**
 * @file i2c.hpp
 *
 * @brief Inter-Integrated Circuit(I2C) API declarations
 *
 *
 * @date November 7th, 2023
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas Jackson (LukasJacksonEG@gmail.com)
 *
 * @license MIT License
 *          Copyright (c) 2023 limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */

#ifndef i2c_master_hpp
#define i2c_master_hpp

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "../Logging/logger.hpp"

/* Master Config Macros */

static const char *TAG = "i2c-master";

#define I2C_MASTER_SCL_IO 22        /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 21        /*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ 100000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define SLAVE_ADDRESS 0x0A

#define WRITE_BIT I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ   /*!< I2C master read */
#define ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0          /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                /*!< I2C ack value */
#define NACK_VAL 0x1               /*!< I2C nack value */


class I2C
{
public:
    /**
     * @brief Configure the master for use in I2C communications
     *
     * @param i2c_master_port   Port the master will be assigned
     * @param mode              I2C mode
     * @param sda_io_num        GPIO number for I2C SDA signal
     * @param sda_pullup_en     Enable pull mode for I2C SDA signal
     * @param scl_io_num        GPIO number for I2c SCL signal
     * @param scl_pullup_en     Enable pull mode for I2C SCL signal
     * @param clk_speed         Clock frequency for master mode
     * @return esp_err_t
     */
    esp_err_t i2c_master_conf(int i2c_master_port, i2c_mode_t mode, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en, uint32_t clk_speed);

    /**
     * @brief Configure the master for use in I2C communications
     *
     * @param i2c_master_port   Port the master will be assigned
     * @param mode              I2C mode
     * @param sda_io_num        GPIO number for I2C SDA signal
     * @param sda_pullup_en     Enable pull mode for I2C SDA signal
     * @param scl_io_num        GPIO number for I2c SCL signal
     * @param scl_pullup_en     Enable pull mode for I2C SCL signal
     * @return esp_err_t
     */
    esp_err_t i2c_master_conf(int i2c_master_port, i2c_mode_t mode, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en);

    /**
     * @brief Sends a message over i2c master
     *
     * @param message   The message to be sent
     * @param len       The exact size of the message sent
     * @return esp_err_t
     */
    esp_err_t i2c_master_send_dta(uint8_t message[], int len);

public:
    int i2c_slave_port = 0;
}

#endif /* i2c_master_hpp */