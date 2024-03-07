/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <stdio.h>
#include "multiplexer.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

static const char *TAG = "PCA9548A";


/**
 * @brief initialize PCA9548A
 * 
 * @param pca struct with PCA9548A parameters
*/
void PCA9548A_init(PCA9548A_t pca) {
    const struct device *gpio_dev;
    int ret;

    gpio_dev = device_get_binding(DT_LABEL(DT_NODELABEL(gpio0))); // Adjust gpio0 based on your board configuration
    if (gpio_dev == NULL) {
        printf("Failed to bind to GPIO device.\n");
        return;
    }

    // Configure the reset pin as an output
    ret = gpio_pin_configure(gpio_dev, pca.reset, GPIO_OUTPUT_ACTIVE | GPIO_OUTPUT_INIT_LOW);
    if (ret < 0) {
        printf("Failed to configure GPIO pin %d.\n", pca.reset);
        return;
    }

    // Set the reset pin to high
    ret = gpio_pin_set(gpio_dev, pca.reset, 1);
    if (ret < 0) {
        printf("Failed to set GPIO pin %d.\n", pca.reset);
    }
}


/**
 * @brief select channel on PCA9548A
 * 
 * @param pca struct with PCA9548A parameters
 * @param channel channel to select (0 -7)
*/
void PCA9548A_select_channel(PCA9548A_t pca, uint8_t channel) {
    if (channel > 7) {
        printf("Channel out of range!\n");
        return;
    }

    uint8_t buffer[1];
    buffer[0] = 1 << channel;

    const struct device *i2c_dev = device_get_binding(DT_LABEL(DT_NODELABEL(i2c0))); // Adjust i2c0 based on your board configuration
    if (!i2c_dev) {
        printf("I2C: Device driver not found.\n");
        return;
    }

    int ret = i2c_write(i2c_dev, buffer, 1, pca.i2c_address);
    if (ret) {
        printf("I2C write failed\n");
    }
}


/**
 * @brief reset PCA9548A
 * 
 * @param pca struct with PCA9548A parameters
*/
void PCA9548A_reset(PCA9548A_t pca)
{
    const struct device *gpio_dev = device_get_binding(DT_LABEL(DT_NODELABEL(gpio0)));
    gpio_pin_set(gpio_dev, pca.reset, 0);
    k_msleep(10);
    gpio_pin_set(gpio_dev, pca.reset, 1);
}