/**
 * @file i2c.cpp
 * @brief Inter-Integrated Circuit(I2C) API definitions
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

#include "i2c_conf.hpp"

esp_err_t i2c::i2c_master_conf(int i2c_master_port, i2c_mode_t mode, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en, uint32_t clk_speed)
{
    int i2c_master_p = i2c_master_port;

    i2c_config_t conf = {
        .mode = mode,
        .sda_io_num = sda_io_num,
        .sda_pullup_en = sda_pullup_en,
        .scl_io_num = scl_pullup_en,
        .master.clk_speed = clk_speed,
    };

    esp_err_t err = i2c_param_config(i2c_master_port, &conf);
    if(err != ESP_OK){
        return err;
    }
    return i2c_driver_install(i2c_master_p, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t i2c::i2c_slave_conf(int i2c_slave_port, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en, i2c_mode_t mode, uint8_t addr_10bit_en, uint16_t slave_addr, uint32_t clk_speed)
{
    int i2c_slave_p = i2c_slave_port;

    i2c_config_t conf_slave = {
        .sda_io_num = sda_io_num,
        .sda_pullup_en = sda_pullup_en,
        .scl_io_num = scl_io_num,
        .scl_pullup_en = scl_pullup_en
        .mode = mode,
        .slave.addr_10bit_en = addr_10bit_en,
        .slave.slave_addr = slave_addr,
    };

    esp_err_t err = i2c_param_config(i2c_slave_p, &conf_slave);
    if (err != ESP_OK) {
        return err;
    }
    return i2c_driver_install(i2c_slave_p, conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

