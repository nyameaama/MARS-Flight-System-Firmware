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
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

#define PCA9548A_ADDRESS0 0x70
#define PCA9548A_ADDRESS1 0x71
#define PCA9548A_ADDRESS2 0x72
#define PCA9548A_ADDRESS3 0x73
#define PCA9548A_ADDRESS4 0x74
#define PCA9548A_ADDRESS5 0x75
#define PCA9548A_ADDRESS6 0x76
#define PCA9548A_ADDRESS7 0x77

#define ACK_EN            true
#define PCA9548A_TIMEOUT  k_msleep(100);

typedef struct PCA9548A_t
{
    uint8_t i2c_address;
    uint8_t reset;
} PCA9548A_t;


void PCA9548A_init(PCA9548A_t pca);

void PCA9548A_select_channel(PCA9548A_t pca, uint8_t channel);

void PCA9548A_reset(PCA9548A_t pca);