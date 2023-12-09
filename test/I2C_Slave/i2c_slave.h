/**
 * @file i2c_slave.h
 * @brief Inter-Integrated Circuit(I2C) SLAVE API prototypes
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
#ifndef i2c_slave_h
#define i2c_slave_h

/**
 * @brief I2C Communication Overview
 *
 * @date December 7th, 2023
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
 *
 * @section I2C Communication Overview
 *
 * I2C (Inter-Integrated Circuit) is a widely used serial communication protocol that allows multiple devices
 * to communicate with each other using only two wires: SDA (Serial Data) and SCL (Serial Clock).
 *
 *
 * @par Visual Representation:
 *
 * @code{.unparsed}
 * +-------------------------+
 * |      Master Device      |
 * |         +---------+      |
 * |         |         |      |
 * | SDA o---|         |      |
 * |         |         |      |
 * | SCL o---|         |      |
 * |         |         |      |
 * |         +---------+      |
 * |                         |
 * |      Slave Device 1     |
 * |         +---------+      |
 * |         |         |      |
 * | SDA o---|         |      |
 * |         |         |      |
 * | SCL o---|         |      |
 * |         |         |      |
 * |         +---------+      |
 * |                         |
 * |      Slave Device 2     |
 * |         +---------+      |
 * |         |         |      |
 * | SDA o---|         |      |
 * |         |         |      |
 * | SCL o---|         |      |
 * |         |         |      |
 * |         +---------+      |
 * +-------------------------+
 * @endcode
 *
 * @par Explanation:
 *
 * - The Master device initiates communication and generates the clock signal (SCL).
 * - The Master sends the Start condition to begin communication.
 * - Each Slave device on the bus has a unique address.
 * - The Master sends the address of the intended Slave along with the Read/Write bit.
 * - The addressed Slave acknowledges its presence.
 * - Data transfer occurs in 8-bit chunks.
 * - Acknowledgments or NACKs are sent by the receiver.
 * - The Master generates the Stop condition to end communication.
 *
 * I2C is known for its simplicity and is widely used in various applications, such as connecting sensors,
 * EEPROMs, and other integrated circuits in embedded systems.
 */

/**
 * @brief I2C Connection between Two ESP32 Boards
 *
 * @date December 7th, 2023
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
 *
 * @section i2c_connection_sec I2C Connection Diagram
 *
 * @code{.unparsed}
 * +-----------------------------------------------+
 * |                ESP32 Board 1                  |
 * |                                               |
 * |                 +------------+                |
 * |                 |            |                |
 * |           +-----| SDA (21)   |                |
 * |           |     |            |                |
 * |           |     +------------+                |
 * |           |                                   |
 * |           |                                   |
 * |           |     +------------+                |
 * |           |     |            |                |
 * |           +-----| SCL (22)   |                |
 * |                 |            |                |
 * |                 +------------+                |
 * |                                               |
 * |                 +------------+                |
 * |                 |            |                |
 * |           +-----| GND        |                |
 * |           |     |            |                |
 * |           |     +------------+                |
 * |           |                                   |
 * +-----------------------------------------------+
 * +-----------------------------------------------+
 * |                 ESP32 Board 2                 |
 * |                                               |
 * |                 +------------+                |
 * |                 |            |                |
 * |           +-----| SDA (21)   |                |
 * |           |     |            |                |
 * |           |     +------------+                |
 * |           |                                   |
 * |           |                                   |
 * |           |     +------------+                |
 * |           |     |            |                |
 * |           +-----| SCL (22)   |                |
 * |                 |            |                |
 * |                 +------------+                |
 * |                                               |
 * |                 +------------+                |
 * |                 |            |                |
 * |           +-----| GND        |                |
 * |           |     |            |                |
 * |           |     +------------+                |
 * +-----------------------------------------------+
 * @endcode
 *
 * @par Connection Details:
 *
 * - Connect the SDA pin (21) of Board 1 to the SDA pin (21) of Board 2.
 * - Connect the SCL pin (22) of Board 1 to the SCL pin (22) of Board 2.
 * - Connect the GND (Ground) of Board 1 to the GND (Ground) of Board 2.
 *
 * This establishes a basic I2C connection between the two ESP32 boards, allowing them to communicate
 * using the I2C protocol.
 */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"

/* Predefined I2C Slave Macros */
static const char *TAG = "i2c-slave";

#define LED_PIN 2

#define I2C_SLAVE_SCL_IO 22      /*!< gpio number for I2C master clock */
#define I2C_SLAVE_SDA_IO 21      /*!< gpio number for I2C master data  */
#define I2C_SLAVE_FREQ_HZ 100000 /*!< I2C master clock frequency */
#define I2C_SLAVE_TX_BUF_LEN 255 /*!< I2C master doesn't need buffer */
#define I2C_SLAVE_RX_BUF_LEN 255 /*!< I2C master doesn't need buffer */
#define ESP_SLAVE_ADDR 0x0A

#define WRITE_BIT I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ   /*!< I2C master read */
#define ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0          /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                /*!< I2C ack value */
#define NACK_VAL 0x1               /*!< I2C nack value */

/**
 * @brief Default I2C slave configuration
 *
 * @return esp_err_t
 */
esp_err_t i2c_slave_conf(int slave_port_num);

/**
    /// @brief Configure the slave for use in I2C communications

    /// @param i2c_sl_sda_io    I2C slave SDA GPIO num
    /// @param sda_pullup_en    SDA pullup internal pull-up resistor enable
    /// @param i2c_sl_scl_io    I2C slave SCL GPIO num
    /// @param scl_pullup_en    SCL pullup internal pull-up resistor enable
    /// @param mode             I2C mode type | SLAVE or MASTER
    /// @param i2c_slave_addr   I2C slave memory address
    /// @param clk_speed        Clock frequency for slave mode
    /// @return  esp_err_t
    esp_err_t i2c_slave_conf(uint8_t i2c_sl_sda_io, bool sda_pullup_en, uint8_t i2c_sl_scl_io, bool scl_pullup_en, i2c_mode_t mode, uint8_t i2c_slave_addr, int i2c_slave_port, uint32_t clk_speed);

    /// @brief Configure the slave for use in I2C communications

    /// @param i2c_sl_sda_io    I2C slave SDA GPIO num
    /// @param sda_pullup_en    SDA pullup internal pull-up resistor enable
    /// @param i2c_sl_scl_io    I2C slave SCL GPIO num
    /// @param scl_pullup_en    SCL pullup internal pull-up resistor enable
    /// @param mode             I2C mode type | SLAVE or MASTER
    /// @param i2c_slave_addr   I2C slave memory address
    /// @return  esp_err_t
    esp_err_t i2c_slave_conf(uint8_t i2c_sl_sda_io, bool sda_pullup_en, uint8_t i2c_sl_scl_io, bool scl_pullup_en, i2c_mode_t mode, uint8_t i2c_slave_addr, int i2c_slave_port);
**/

/**
 * @brief Configure an I2C bus with the given configuration.
 *
 * @param i2c_num I2C port to configure
 * @param i2c_conf Pointer to the I2C configuration
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t slave_param_config(int i2c_slave_port, const i2c_config_t *i2c_config);

/**
 * @brief Install an I2C driver
 * @note  Not all Espressif chips can support slave mode (e.g. ESP32C2)
 *
 * @param i2c_num I2C port number
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
esp_err_t slave_driver_install(i2c_port_t i2c_num, const i2c_config_t *config, size_t slv_rx_buf_len, size_t slv_tx_buf_len, int intr_alloc_flags);

/**
 * @brief Configure IO Pad as General Purpose IO,
 *        so that it can be connected to internal Matrix,
 *        then combined with one or more peripheral signals.
 *
 * @param iopad_num
 */
void i2c_r_gpio_select_gpio(uint32_t iopad_num);

/**
 * @brief Configure GPIO direction,such as output_only,input_only,output_and_input
 *
 * @param gpio_num  Configure GPIO pins number, it should be GPIO number.
 *                  If you want to set direction of e.g. GPIO16, gpio_num should be GPIO_NUM_16 (16);
 * @param mode      GPIO direction
 * @return esp_err_t
 */
esp_err_t set_gpio_dir(int gpio_num, gpio_mode_t mode);

/**
 * @brief Set the gpio level object
 *
 * @param gpio_num      -- GPIO number. If you want to set the output level of e.g. GPIO16, gpio_num should be GPIO_NUM_16 (16);
 * @param level         -- Output level. 0: low ; 1: high
 * @return esp_err_t
 */
esp_err_t set_gpio_level(int gpio_num, uint32_t level);

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
int slave_read_buffer(int i2c_num, uint8_t *data, size_t max_size, TickType_t ticks_to_wait);

/**
 * @brief reset I2C tx hardware fifo
 *
 * @param i2c_num        I2C port number
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t reset_rx_fifo(i2c_port_t i2c_num);

#endif /* i2c_slave_h */