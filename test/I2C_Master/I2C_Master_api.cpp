/**
 * @file i2c_slave.cpp
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

#ifdef __cpp_exceptions

#include "driver/i2c.h"
#include "I2C_master.hpp"

using namespace std;

namespace idf
{

#define I2C_CHECK_THROW(err) CHECK_THROW_SPECIFIC((err), I2CException)

/**
 * I2C bus are defined in the header files, let's check that the values are correct
 */
#if SOC_I2C_NUM >= 2
    static_assert(I2C_NUM_1 == 1, "I2C_NUM_1 must be equal to 1");
#endif // SOC_I2C_NUM >= 2

    esp_err_t check_i2c_num(uint32_t i2c_num) noexcept
    {
        if (i2c_num >= I2C_NUM_MAX)
        {
            return ESP_ERR_INVALID_ARG;
        }

        return ESP_OK;
    }

    esp_err_t check_i2c_addr(uint32_t addr) noexcept
    {
        // maximum I2C address currently supported in the C++ classes is 127
        if (addr > 0x7f)
        {
            return ESP_ERR_INVALID_ARG;
        }

        return ESP_OK;
    }

    I2CException::I2CException(esp_err_t error) : ESPException(error) {}

    I2CTransferException::I2CTransferException(esp_err_t error) : I2CException(error) {}

    I2CAddress::I2CAddress(uint8_t addr) : StrongValueComparable<uint8_t>(addr)
    {
        esp_err_t error = check_i2c_addr(addr);
        if (error != ESP_OK)
        {
            throw I2CException(error);
        }
    }

    I2CCommandLink::I2CCommandLink()
    {
        handle = i2c_cmd_link_create();
        if (!handle)
        {
            throw I2CException(ESP_ERR_NO_MEM);
        }
    }

    I2CCommandLink::~I2CCommandLink()
    {
        i2c_cmd_link_delete(handle);
    }

    void I2CCommandLink::start()
    {
        I2C_CHECK_THROW(i2c_master_start(handle));
    }

    void I2CCommandLink::write(const std::vector<uint8_t> &bytes, bool expect_ack)
    {
        I2C_CHECK_THROW(i2c_master_write(handle, bytes.data(), bytes.size(), expect_ack));
    }

    void I2CCommandLink::write_byte(uint8_t byte, bool expect_ack)
    {
        I2C_CHECK_THROW(i2c_master_write_byte(handle, byte, expect_ack));
    }

    void I2CCommandLink::read(std::vector<uint8_t> &bytes)
    {
        I2C_CHECK_THROW(i2c_master_read(handle, bytes.data(), bytes.size(), I2C_MASTER_LAST_NACK));
    }

    void I2CCommandLink::stop()
    {
        I2C_CHECK_THROW(i2c_master_stop(handle));
    }

    void I2CCommandLink::execute_transfer(I2CNumber i2c_num, chrono::milliseconds driver_timeout)
    {
        esp_err_t err = i2c_master_cmd_begin(i2c_num.get_value<i2c_port_t>(), handle, driver_timeout.count() / portTICK_PERIOD_MS);
        if (err != ESP_OK)
        {
            throw I2CTransferException(err);
        }
    }

    I2CBus::I2CBus(I2CNumber i2c_number) : i2c_num(std::move(i2c_number)) {}

    I2CBus::~I2CBus() {}

    I2CMaster::I2CMaster(I2CNumber i2c_number,
                         SCL_GPIO scl_gpio,
                         SDA_GPIO sda_gpio,
                         Frequency clock_speed,
                         bool scl_pullup,
                         bool sda_pullup)
        : I2CBus(std::move(i2c_number))
    {
        i2c_config_t conf = {};
        conf.mode = I2C_MODE_MASTER;
        conf.scl_io_num = scl_gpio.get_value();
        conf.scl_pullup_en = scl_pullup;
        conf.sda_io_num = sda_gpio.get_value();
        conf.sda_pullup_en = sda_pullup;
        conf.master.clk_speed = clock_speed.get_value();
        I2C_CHECK_THROW(i2c_param_config(i2c_num.get_value<i2c_port_t>(), &conf));
        I2C_CHECK_THROW(i2c_driver_install(i2c_num.get_value<i2c_port_t>(), conf.mode, 0, 0, 0));
    }

    I2CMaster::~I2CMaster()
    {
        i2c_driver_delete(i2c_num.get_value<i2c_port_t>());
    }

    void I2CMaster::sync_write(I2CAddress i2c_addr, const vector<uint8_t> &data)
    {
        I2CWrite writer(data);

        writer.do_transfer(i2c_num, i2c_addr);
    }

    /**
     * @brief Sends message over I2C communication to given slave address
     *
     * @param message The message sent to the I2C device
     * @param len       The length of said message
     * @param slave_addr The address of the slave device
     * @param ack_check_en ack check enable
     * @param i2c_master_port The master port
     */
    esp_err_t I2CMaster::i2c_master_send(uint8_t message[], int len, int slave_addr, int ack_check_en, i2c_port_t i2c_master_port)
    {
        ESP_LOGI(TAG, "Sending Message = %s", message);

        esp_err_t ret;
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, slave_addr << 1 | WRITE_BIT, ACK_CHECK_EN);
        i2c_master_write(cmd, message, len, ACK_CHECK_EN);
        i2c_master_stop(cmd);

        ret = i2c_master_cmd_begin(i2c_master_port, cmd, 1000 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);
        return ret;
    }

    std::vector<uint8_t> I2CMaster::sync_read(I2CAddress i2c_addr, size_t n_bytes)
    {
        I2CRead reader(n_bytes);

        return reader.do_transfer(i2c_num, i2c_addr);
    }

    vector<uint8_t> I2CMaster::sync_transfer(I2CAddress i2c_addr,
                                             const std::vector<uint8_t> &write_data,
                                             size_t read_n_bytes)
    {
        I2CComposed composed_transfer;
        composed_transfer.add_write(write_data);
        composed_transfer.add_read(read_n_bytes);

        return composed_transfer.do_transfer(i2c_num, i2c_addr)[0];
    }

#if CONFIG_SOC_I2C_SUPPORT_SLAVE
    I2CSlave::I2CSlave(I2CNumber i2c_number,
                       SCL_GPIO scl_gpio,
                       SDA_GPIO sda_gpio,
                       I2CAddress slave_addr,
                       size_t rx_buf_len,
                       size_t tx_buf_len,
                       bool scl_pullup,
                       bool sda_pullup)
        : I2CBus(std::move(i2c_number))
    {
        i2c_config_t conf = {};
        conf.mode = I2C_MODE_SLAVE;
        conf.scl_io_num = scl_gpio.get_value();
        conf.scl_pullup_en = scl_pullup;
        conf.sda_io_num = sda_gpio.get_value();
        conf.sda_pullup_en = sda_pullup;
        conf.slave.addr_10bit_en = 0;
        conf.slave.slave_addr = slave_addr.get_value();
        I2C_CHECK_THROW(i2c_param_config(i2c_num.get_value<i2c_port_t>(), &conf));
        I2C_CHECK_THROW(i2c_driver_install(i2c_num.get_value<i2c_port_t>(), conf.mode, rx_buf_len, tx_buf_len, 0));
    }

    I2CSlave::~I2CSlave()
    {
        i2c_driver_delete(i2c_num.get_value<i2c_port_t>());
    }

    int I2CSlave::write_raw(const uint8_t *data, size_t data_len, chrono::milliseconds timeout)
    {
        return i2c_slave_write_buffer(i2c_num.get_value<i2c_port_t>(), data, data_len, (TickType_t)timeout.count() / portTICK_PERIOD_MS);
    }

    int I2CSlave::read_raw(uint8_t *buffer, size_t buffer_len, chrono::milliseconds timeout)
    {
        return i2c_slave_read_buffer(i2c_num.get_value<i2c_port_t>(), buffer, buffer_len, (TickType_t)timeout.count() / portTICK_PERIOD_MS);
    }
#endif // CONFIG_SOC_I2C_SUPPORT_SLAVE

    I2CWrite::I2CWrite(const vector<uint8_t> &bytes, chrono::milliseconds driver_timeout)
        : I2CTransfer<void>(driver_timeout), bytes(bytes)
    {
        if (bytes.empty())
        {
            throw I2CException(ESP_ERR_INVALID_ARG);
        }
    }

    void I2CWrite::queue_cmd(I2CCommandLink &handle, I2CAddress i2c_addr)
    {
        handle.start();
        handle.write_byte(i2c_addr.get_value() << 1 | I2C_MASTER_WRITE);
        handle.write(bytes);
    }

    void I2CWrite::process_result() {}

    I2CRead::I2CRead(size_t size, chrono::milliseconds driver_timeout)
        : I2CTransfer<vector<uint8_t>>(driver_timeout), bytes(size)
    {
        if (size == 0)
        {
            throw I2CException(ESP_ERR_INVALID_ARG);
        }
    }

    void I2CRead::queue_cmd(I2CCommandLink &handle, I2CAddress i2c_addr)
    {
        handle.start();
        handle.write_byte(i2c_addr.get_value() << 1 | I2C_MASTER_READ);
        handle.read(bytes);
    }

    vector<uint8_t> I2CRead::process_result()
    {
        return bytes;
    }

    I2CComposed::I2CComposed(chrono::milliseconds driver_timeout)
        : I2CTransfer<vector<vector<uint8_t>>>(driver_timeout), transfer_list() {}

    void I2CComposed::CompTransferNodeRead::queue_cmd(I2CCommandLink &handle, I2CAddress i2c_addr)
    {
        handle.write_byte(i2c_addr.get_value() << 1 | I2C_MASTER_READ);
        handle.read(bytes);
    }

    void I2CComposed::CompTransferNodeRead::process_result(std::vector<std::vector<uint8_t>> &read_results)
    {
        read_results.push_back(bytes);
    }

    void I2CComposed::CompTransferNodeWrite::queue_cmd(I2CCommandLink &handle, I2CAddress i2c_addr)
    {
        handle.write_byte(i2c_addr.get_value() << 1 | I2C_MASTER_WRITE);
        handle.write(bytes);
    }

    void I2CComposed::add_read(size_t size)
    {
        if (!size)
        {
            throw I2CException(ESP_ERR_INVALID_ARG);
        }

        transfer_list.push_back(make_shared<CompTransferNodeRead>(size));
    }

    void I2CComposed::add_write(std::vector<uint8_t> bytes)
    {
        if (bytes.empty())
        {
            throw I2CException(ESP_ERR_INVALID_ARG);
        }

        transfer_list.push_back(make_shared<CompTransferNodeWrite>(bytes));
    }

    void I2CComposed::queue_cmd(I2CCommandLink &handle, I2CAddress i2c_addr)
    {
        for (auto it = transfer_list.begin(); it != transfer_list.end(); it++)
        {
            handle.start();
            (*it)->queue_cmd(handle, i2c_addr);
        }
    }

    std::vector<std::vector<uint8_t>> I2CComposed::process_result()
    {
        std::vector<std::vector<uint8_t>> results;
        for (auto it = transfer_list.begin(); it != transfer_list.end(); it++)
        {
            (*it)->process_result(results);
        }
        return results;
    }

} // idf
#endif // __cpp_exceptions

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
esp_err_t set_gpio_dir(gpio_num_t gpio_num, gpio_mode_t mode)
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
esp_err_t set_gpio_level(gpio_num_t gpio_num, uint32_t level)
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
esp_err_t slave_read_buffer(i2c_port_t i2c_slave_port, uint8_t *data, size_t max_size, TickType_t ticks_to_wait)
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