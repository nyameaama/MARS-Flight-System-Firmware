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
        Logger log;
        int master_port = 0;
        // creating master bus
        shared_ptr<I2CMaster> master(new I2CMaster(I2C_MASTER_NUM,
                                                   I2C_MASTER_SCL_IO,
                                                   I2C_MASTER_SDA_IO,
                                                   Frequency(400000)));

        ESP_LOGI(TAG, "I2C initialized successfully");

        while (1)
        {
            auto result = log.EVENT_LOG_SDD();
            std::vector<uint8_t> resultVec(result.begin(), result.end());
            uint8_t *res = &resultVec[0];

            master->i2c_master_send(res, resultVec.size(), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(2000 / portTICK_PERIOD_MS);

            auto result2 = log.EVENT_LOG_SEL("UAV-SEL-TEST-HARD-FAIL", mars_exception_t::ROUTINE_HARD_FAIL, "Submodule Down");
            std::vector<uint8_t> resultVec2(result2.begin(), result2.end());
            uint8_t *res2 = &resultVec2[0];

            master->i2c_master_send(res2, resultVec2.size(), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(2000 / portTICK_PERIOD_MS);

            auto result3 = log.EVENT_LOG_SSL();
            std::vector<uint8_t> resultVec3(result3.begin(), result3.end());
            uint8_t *res3 = &resultVec3[0];

            master->i2c_master_send(res3, resultVec3.size(), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(2000 / portTICK_PERIOD_MS);

            result2 = log.EVENT_LOG_SEL("UAV-SEL-TEST-SOFT-FAIL", mars_exception_t::ROUTINE_SOFT_FAIL, "Submodule Unresponsive");
            std::vector<uint8_t> resultVec2_soft(result2.begin(), result2.end());
            uint8_t *res2_soft = &resultVec2_soft[0];

            master->i2c_master_send(res2_soft, resultVec2_soft.size(), static_cast<int>(SLAVE_ADDRESS), static_cast<int>(ACK_CHECK_EN), static_cast<i2c_port_t>(master_port));
            vTaskDelay(2000 / portTICK_PERIOD_MS);
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
