/**
 * @file I2C_Master_testing.cpp
 * @brief Inter-Integrated Circuit(I2C) SLAVE API prototypes
 *
 *
 * @date December 13th, 2023
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
#include "../I2C_master.hpp"

using namespace std;
using namespace idf;

constexpr I2CNumber I2C_MASTER_NUM(I2CNumber::I2C0()); /*!< I2C master i2c port number, the number of i2c peripheral
                                                            interfaces available will depend on the chip */
#define I2C_MASTER_SCL_IO SCL_GPIO(22)                 /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO SDA_GPIO(21)                 /*!< GPIO number used for I2C master data  */

#define ESP_SLAVE_ADDRESS I2CAddress(SLAVE_ADDRESS)

extern "C" void app_main(void)
{
    try
    {
        int master_port = 0;
        // creating master bus
        shared_ptr<I2CMaster> master(new I2CMaster(I2C_MASTER_NUM,
                                                   I2C_MASTER_SCL_IO,
                                                   I2C_MASTER_SDA_IO,
                                                   Frequency(400000)));

        uint8_t on_command[] = "LED_ON";
        uint8_t off_command[] = "LED_OFF";

        uint8_t custom_command[] = "I2C Connection Successful!";

        ESP_LOGI(TAG, "I2C initialized successfully");

        while (1)
        {
            master->i2c_master_send(on_command, sizeof(on_command), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            master->i2c_master_send(off_command, sizeof(on_command), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            master->i2c_master_send(custom_command, sizeof(on_command), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
    catch (const I2CException &e)
    {
        ESP_LOGI(TAG, "I2C Exception with error: %s (0x%X)", e.what(), e.error);
        ESP_LOGI(TAG, "Couldn't read sensor!");
    }

    // The I2CMaster object is de-initialized in its destructor when going out of scope.
    ESP_LOGI(TAG, "I2C de-initialized successfully");
}
