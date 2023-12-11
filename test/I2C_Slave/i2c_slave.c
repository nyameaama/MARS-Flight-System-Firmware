/**
 * @file i2c_slave.c
 * @brief Inter-Integrated Circuit(I2C) SLAVE API definitions
 *
 *
 * @date December 7th, 2023
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

#include "i2c_slave.h"

/**
 * @brief Default I2C slave configuration
 *
 * @return esp_err_t
 */
esp_err_t i2c_slave_conf(int i2c_slave_port)
{

    i2c_config_t conf = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = I2C_SLAVE_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SLAVE_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = ESP_SLAVE_ADDR,
        .clk_flags = 0,
    };

    esp_err_t err = i2c_param_config(i2c_slave_port, &conf);
    if (err != ESP_OK)
    {
        return err;
    }
    return i2c_driver_install(i2c_slave_port, conf.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

/*
/// @brief Configure the slave for use in I2C communications
/// @param i2c_sl_sda_io    I2C slave SDA GPIO num
/// @param sda_pullup_en    SDA pullup internal pull-up resistor enable
/// @param i2c_sl_scl_io    I2C slave SCL GPIO num
/// @param scl_pullup_en    SCL pullup internal pull-up resistor enable
/// @param mode             I2C mode type | SLAVE or MASTER
/// @param i2c_slave_addr   I2C slave memory address
/// @param clk_speed        Clock frequency for slave mode
/// @return  esp_err_t
esp_err_t i2c_slave_conf(uint8_t i2c_sl_sda_io, bool sda_pullup_en, uint8_t i2c_sl_scl_io, bool scl_pullup_en, i2c_mode_t mode, uint8_t i2c_slave_addr, int i2c_slave_port, uint32_t clk_speed)
{
    i2c_config_t conf = {
        .mode = mode,
        .sda_io_num = i2c_sl_sda_io,
        .sda_pullup_en = sda_pullup_en,
        .scl_io_num = i2c_sl_scl_io,
        .scl_pullup_en = scl_pullup_en,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = i2c_slave_addr,
        .clk_speed = clk_speed,
    };

    esp_err_t err = i2c_param_config(i2c_slave_port, &conf);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure I2C slave: %d", err);
        return err;
    }

    return i2c_driver_install(i2c_port_t(i2c_slave_port), conf.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}
**/

/**
/// @brief Configure the slave for use in I2C communications
/// @param i2c_sl_sda_io    I2C slave SDA GPIO num
/// @param sda_pullup_en    SDA pullup internal pull-up resistor enable
/// @param i2c_sl_scl_io    I2C slave SCL GPIO num
/// @param scl_pullup_en    SCL pullup internal pull-up resistor enable
/// @param mode             I2C mode type | SLAVE or MASTER
/// @param i2c_slave_addr   I2C slave memory address
/// @return  esp_err_t
esp_err_t i2c_slave_conf(uint8_t i2c_sl_sda_io, bool sda_pullup_en, uint8_t i2c_sl_scl_io, bool scl_pullup_en, i2c_mode_t mode, uint8_t i2c_slave_addr, int i2c_slave_port)
{
    i2c_config_t conf = {
        .mode = mode,
        .sda_io_num = i2c_sl_sda_io,
        .sda_pullup_en = sda_pullup_en,
        .scl_io_num = i2c_sl_scl_io,
        .scl_pullup_en = scl_pullup_en,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = i2c_slave_addr,
        .clk_speed = 0,  // You might want to set the clock speed here or adjust as needed
    };

    esp_err_t err = i2c_param_config(i2c_slave_port, &conf);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure I2C slave: %d", err);
        return err;
    }

    return i2c_driver_install(i2c_port_t(i2c_slave_port), conf.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}
**/

/**
 * @brief Configure an I2C bus with the given configuration.
 *
 * @param i2c_slave_port    I2C port to configure
 * @param i2c_config        Pointer to the I2C configuration
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t slave_param_config(int i2c_slave_port, const i2c_config_t *i2c_config)
{
    esp_err_t err = i2c_param_config(i2c_slave_port, i2c_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "\nERROR: %s %d", "Failed to initialize slave device", err);
        return err;
    }
    return err;
}

/**
 * @brief Install an I2C driver
 * @note  Not all Espressif chips can support slave mode (e.g. ESP32C2)
 *
 * @param i2c_port_num I2C port number
 * @param mode I2C mode (either master or slave).
 * @param slv_rx_buf_len Receiving buffer size. Only slave mode will use this value, it is ignored in master mode.
 * @param slv_tx_buf_len Sending buffer size. Only slave mode will use this value, it is ignored in master mode.
 * @param intr_alloc_flags Flags used to allocate the interrupt. One or multiple (ORred) ESP_INTR_FLAG_* values.
 *                         See esp_intr_alloc.h for more info.
 *        @note
 *        In master mode, if the cache is likely to be disabled(such as write flash) and the slave is time-sensitive,
 *        `ESP_INTR_FLAG_IRAM` is suggested to be used. In this case, please use the memory allocated from internal RAM in i2c read and write function,
 *        because we can not access the psram(if psram is enabled) in interrupt handle function when cache is disabled.
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_FAIL Driver installation error
 */
esp_err_t slave_driver_install(i2c_port_t i2c_port_num, const i2c_config_t *config, size_t slv_rx_buf_len, size_t slv_tx_buf_len, int intr_alloc_flags)
{
    esp_err_t err = i2c_driver_install(i2c_port_num, config->mode, slv_rx_buf_len, slv_tx_buf_len, intr_alloc_flags);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "\nERROR: %s %d", "Failed to install slave driver", err);
        return err;
    }
    return err;
}

/**
 * @brief Configure IO Pad as General Purpose IO,
 *        so that it can be connected to internal Matrix,
 *        then combined with one or more peripheral signals.
 *
 * @param iopad_num
 */
void i2c_r_gpio_select_gpio(uint32_t iopad_num)
{
    esp_rom_gpio_pad_select_gpio(iopad_num);
}

/**
 * @brief Configure GPIO direction,such as output_only,input_only,output_and_input
 *
 * @param gpio_num  Configure GPIO pins number, it should be GPIO number.
 *                  If you want to set direction of e.g. GPIO16, gpio_num should be GPIO_NUM_16 (16);
 *
 * @param mode      GPIO direction
 * @return esp_err_t
 */
esp_err_t set_gpio_dir(int gpio_num, gpio_mode_t mode)
{
    esp_err_t err = gpio_set_direction(gpio_num, mode);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "\nERROR: %s %d", "Failed to set General Purpose Input/Output(GPIO) Direction.", err);
        return err;
    }
    return err;
}

/**
 * @brief Set the gpio level object
 *
 * @param gpio_num      -- GPIO number. If you want to set the output level of e.g. GPIO16, gpio_num should be GPIO_NUM_16 (16);
 * @param level         -- Output level. 0: low ; 1: high
 * @return esp_err_t
 */
esp_err_t set_gpio_level(int gpio_num, uint32_t level)
{
    esp_err_t err = gpio_set_level(gpio_num, level);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "\nERROR: %s %d", "Failed to set gpio level.", err);
        return err;
    }
    return err;
}

/**
 * @brief Read bytes from I2C internal buffer. When the I2C bus receives data, the ISR will copy them
 *        from the hardware RX FIFO to the internal ringbuffer.
 *        Calling this function will then copy bytes from the internal ringbuffer to the `data` user buffer.
 *        @note This function shall only be called in I2C slave mode.
 *
 * @param i2c_num       I2C port number
 * @param data          Buffer to fill with ringbuffer's bytes
 * @param max_size      Maximum bytes to read
 * @param ticks_to_wait Maximum waiting ticks (M/S)
 *
 * @return
 *     - ESP_FAIL(-1) Parameter error
 *     - Others(>=0) The number of data bytes read from I2C slave buffer.
 */
esp_err_t slave_read_buffer(int i2c_slave_port, uint8_t *data, size_t max_size, TickType_t ticks_to_wait)
{
    esp_err_t err = i2c_slave_read_buffer(i2c_slave_port, data, max_size, 100 / ticks_to_wait);
    return err;
}

/**
 * @brief reset I2C tx hardware fifo
 *
 * @param i2c_num        I2C port number
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t reset_rx_fifo(i2c_port_t i2c_num)
{
    esp_err_t err = i2c_reset_rx_fifo(i2c_num);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "\nERROR: %s %d", "Failed to reset rx fifo.", err);
        return err;
    }
    return err;
}