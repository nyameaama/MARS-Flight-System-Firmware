/**
 * @file i2c.hpp
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

#include "../Logging/logger.hpp"
#include "i2c.h"


class i2c: protected Logger
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
     * @brief Configure the slave for use in I2C communications
     *
     * @param i2c_slave_port   Port the slave will be assigned
     * @param mode              I2C mode
     * @param sda_io_num        GPIO number for I2C SDA signal
     * @param sda_pullup_en     Enable pull mode for I2C SDA signal
     * @param scl_io_num        GPIO number for I2c SCL signal
     * @param scl_pullup_en     Enable pull mode for I2C SCL signal
     * @param clk_speed         Clock frequency for master mode
     * @return esp_err_t
     */
    esp_err_t i2c_slave_conf(int i2c_slave_port, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en, i2c_mode_t mode, uint8_t addr_10bit_en, uint16_t slave_addr, uint32_t clk_speed);

}