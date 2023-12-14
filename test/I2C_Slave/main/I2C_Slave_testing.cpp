/**
 * @file I2C_Slave_testing.cpp
 * @brief Inter-Integrated Circuit(I2C) SLAVE API testing
 *
 * @date December 7th, 2023
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
 *
 * @license MIT License
 *          Copyright (c) 2023 Limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */

#include "../i2c_slave.hpp"

using namespace std;
using namespace idf;

constexpr I2CNumber I2C_SLAVE_NUM(I2CNumber::I2C0());

#define I2C_SLAVE_SCL_IO SCL_GPIO(22) /*!< GPIO number used for I2C slave clock */
#define I2C_SLAVE_SDA_IO SDA_GPIO(21) /*!< GPIO number used for I2C slave data  */

#define ESP_SLAVE_ADDRESS I2CAddress(0x0A)

extern "C" void app_main(void)
{
    try
    {
        int i2c_slave_port = 0;
        shared_ptr<I2CSlave> slave(new I2CSlave(I2C_SLAVE_NUM,
                                                I2C_SLAVE_SCL_IO,
                                                I2C_SLAVE_SDA_IO,
                                                ESP_SLAVE_ADDRESS,
                                                static_cast<size_t>(I2C_SLAVE_RX_BUF_LEN),
                                                static_cast<size_t>(I2C_SLAVE_TX_BUF_LEN),
                                                GPIO_PULLUP_ENABLE,
                                                GPIO_PULLUP_ENABLE));
        ESP_LOGI(TAG, "I2C initialized successfully");

        uint8_t received_data[I2C_SLAVE_RX_BUF_LEN] = {0};

        i2c_r_gpio_select_gpio(static_cast<uint8_t>(LED_PIN));
        set_gpio_dir(static_cast<gpio_num_t>(LED_PIN), GPIO_MODE_OUTPUT);

        ESP_LOGI(TAG, "I2C Slave initialized successfully");

        // ... (your existing code)

        constexpr uint32_t DELAY_TIME_MS = 1000; // Increase delay time

        std::string accumulatedData; // Variable to accumulate received data

        while (1)
        {
            size_t bytesRead = slave_read_buffer(static_cast<i2c_port_t>(i2c_slave_port), received_data, I2C_SLAVE_RX_BUF_LEN, DELAY_TIME_MS / portTICK_PERIOD_MS);
            reset_rx_fifo(static_cast<i2c_port_t>(i2c_slave_port));

            if (bytesRead > 0)
            {
                // Instead of reinterpret_cast, directly copy the received_data to a string
                std::string receivedString(reinterpret_cast<char *>(received_data), bytesRead);

                // Append the received string to accumulatedData
                accumulatedData += receivedString;
            }

            // Check if a complete message is received (assuming messages are terminated with '}')
            size_t messageEndPos = accumulatedData.find('}');
            if (messageEndPos != std::string::npos)
            {
                // Process the complete message
                std::string completeMessage = accumulatedData.substr(0, messageEndPos + 1); // Include the '}'
                ESP_LOGI(TAG, "%s", completeMessage.c_str());

                // Remove the processed message from accumulatedData
                accumulatedData.erase(0, messageEndPos + 2);
            }
            else
            {
                // Log incomplete or corrupted messages
                // ESP_LOGE(TAG, "Incomplete or Corrupted Message Received: %s", accumulatedData.c_str());
                accumulatedData.clear(); // Clear accumulated data to avoid processing incomplete messages repeatedly
            }

            vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);
        }

        // ... (the rest of your code)
    }
    catch (const I2CException &e)
    {
        ESP_LOGI(TAG, "I2C Exception with error: %s (0x%X)", e.what(), e.error);
        ESP_LOGI(TAG, "Couldn't read sensor!");
    }
}
