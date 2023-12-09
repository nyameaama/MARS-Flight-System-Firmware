/**
 * @file I2C_Slave_testing.cpp
 * @brief Inter-Integrated Circuit(I2C) SLAVE API testing
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

#include "../i2c_slave.h"

int slave_port = 0;

void app_main(void)
{
    uint8_t received_data[I2C_SLAVE_RX_BUF_LEN] = {0};

    i2c_r_gpio_select_gpio(LED_PIN);
    set_gpio_dir(LED_PIN, GPIO_MODE_OUTPUT);

    ESP_ERROR_CHECK(i2c_slave_conf(slave_port));
    ESP_LOGI(TAG, "I2C Slave initialized successfully");
    const uint8_t i2c_size[] = "I2C Connection Successful!";

    while (1)
    {
        slave_read_buffer(slave_port, received_data, I2C_SLAVE_RX_BUF_LEN, 100 / portTICK_PERIOD_MS);
        reset_rx_fifo(slave_port);

        if (strncmp((const char *)received_data, "LED_ON", 6) == 0)
        {
            ESP_LOGI(TAG, "Data Recived = %s", received_data);
            set_gpio_level(LED_PIN, 1);
        }
        else if (strncmp((const char *)received_data, "LED_OFF", 7) == 0)
        {
            ESP_LOGI(TAG, "Data Recived = %s", received_data);
            set_gpio_level(LED_PIN, 0);
        }
        else if (strncmp((const char *)received_data, (const char *)i2c_size, sizeof(i2c_size)) == 0)
        {
            ESP_LOGI(TAG, "Data Recived = %s", received_data);
        }

        memset(received_data, 0, I2C_SLAVE_RX_BUF_LEN);
    }
}
