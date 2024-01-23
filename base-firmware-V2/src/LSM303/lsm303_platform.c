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

#include"lsm303_platform.h"

int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len){
    uint8_t dt[256];
	uint8_t i;
	dt[0] = reg;
	for(i = 0; i < len; i++){
		dt[i+1] = data[i];
	}
	uint8_t ret;
	ret = i2c_write_dt(&dev_i2c, dt, sizeof(dt));
	if(ret != 0){
		printk("Failed to write to I2C device address");
	}
}
                              
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len){
    for (size_t i = 0; i < len; i++) {
        ret = i2c_write_read_dt(&dev_i2c_acc, reg_addr, 1, data, len);
        if(ret != 0){
            printk("Failed to write/read I2C device address");
        }
    }
}

void platform_init(void){
    if (!device_is_ready(dev_i2c_acc.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c_acc.bus->name);
		return;
	}
}