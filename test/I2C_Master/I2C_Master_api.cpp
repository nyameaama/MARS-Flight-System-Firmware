/**
 * @file I2C_Master_api.c
 * @brief Inter-Integrated Circuit(I2C) API definitions
 *
 *
 * @date December 5th, 2023
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
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

#include "I2C_master.hpp"

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
esp_err_t I2C::i2c_master_conf(int i2c_master_port, i2c_mode_t mode, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en, uint32_t clk_speed)
{
    i2c_config_t conf;
    conf.mode = mode;
    conf.sda_io_num = sda_io_num;
    conf.scl_io_num = scl_io_num;
    conf.sda_pullup_en = sda_pullup_en;
    conf.scl_pullup_en = scl_pullup_en;
    conf.master.clk_speed = clk_speed;
    conf.clk_flags = 0;

    esp_err_t err = i2c_param_config(i2c_port_t(i2c_master_port), &conf);
    if (err != ESP_OK)
    {
        printf("\nERROR: %s %d", "Failed to initialize master device", err);
        return err;
    }
    return i2c_driver_install(i2c_port_t(i2c_master_port), conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

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
esp_err_t I2C::i2c_master_conf(int i2c_master_port, i2c_mode_t mode, int sda_io_num, bool sda_pullup_en, int scl_io_num, bool scl_pullup_en)
{
    i2c_config_t conf;
    conf.mode = mode;
    conf.sda_io_num = sda_io_num;
    conf.scl_io_num = scl_io_num;
    conf.sda_pullup_en = sda_pullup_en;
    conf.scl_pullup_en = scl_pullup_en;
    conf.clk_flags = 0;

    esp_err_t err = i2c_param_config(i2c_port_t(i2c_master_port), &conf);
    if (err != ESP_OK)
    {
        printf("\nERROR: %s %d", "Failed to initialize master device", err);
        return err;
    }
    return i2c_driver_install(i2c_port_t(i2c_master_port), conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

/**
 * @brief Sends a message over i2c master
 *
 * @param message   The message to be sent
 * @param len       The exact size of the message sent
 * @return esp_err_t
 */
esp_err_t I2C::i2c_master_send_dta(uint8_t message[], int length)
{
    ESP_LOGI(TAG, "Sending Message = %s", message);

    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SLAVE_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(cmd, message, len, ACK_CHECK_EN);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(i2c_master_port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}