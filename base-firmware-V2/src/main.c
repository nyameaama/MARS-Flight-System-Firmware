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

#include <zephyr/kernel.h>
#include "Display/ssd1306.h"
#include "System/_state.h"

uint8_t DRONE_STATE = 1;

void INIT_CORE0();

int main(void){
    INIT_CORE0();
}

void INIT_CORE0(){
    SSD1306_Init();
    displayBOOT();

    //FAN_COOLING *cool = new FAN_COOLING();
    //cool -> init_relay();
    //delete cool;

    while(1){

        if(DRONE_STATE == 1){ // STANDBY
            //Display Controller
            displayStandByClientSuccess();
            //Fan Controller
            //cool -> coolSierra_task(baro -> pushTemperature());
            //FROM STANDBY PREP WE CAN EITHER SWITCH TO ARMED OR BYPASS
            if(SWITCH2ARMED() == 1){
                DRONE_STATE = 2;
                continue;
            }
            if(SWITCH2BYPASS() == 1){
                DRONE_STATE = 3;
                continue;
            }
        }

        if(DRONE_STATE == 2){ // ARMED
            //Display Controller
            displayARMED();
            //Fan Controller
            //cool -> coolSierra_task(baro -> pushTemperature());
            //FROM ARMED WE CAN EITHER SWITCH TO STANDY PREP OR BYPASS
            if(SWITCH2PREP() == 1){
                DRONE_STATE = 1;
                continue;
            }
            if(SWITCH2BYPASS() == 1){
                DRONE_STATE = 3;
                continue;
            }
        }
            
        if(DRONE_STATE == 3){ // BYPASS
            //Display Controller
            displayBYPASS();
            //Fan Controller
            //cool -> coolSierra_task(baro -> pushTemperature());
            //FROM BYPASS WE CAN EITHER SWITCH TO STANDY PREP OR ARMED
            if(SWITCH2PREP() == 1){
                DRONE_STATE = 1;
                continue;
            }
            if(SWITCH2ARMED() == 1){
                DRONE_STATE = 2;
                continue;
            }
        }
        }
}


/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>

#define TEST_BUF_SIZE 128

void main(void)
{
    printk("The I2C scanner started\n");
    const struct device *i2c_dev;
    int error;

    i2c_dev = device_get_binding("I2C_1");
    if (!i2c_dev) {
        printk("Binding failed.");
        return;
    }

    // Demonstration of runtime configuration
    i2c_configure(i2c_dev, I2C_SPEED_SET(I2C_SPEED_STANDARD));
    printk("Value of NRF_TWIM2->PSEL.SCL : %d \n",NRF_TWIM1->PSEL.SCL);
    printk("Value of NRF_TWIM2->PSEL.SDA : %d \n",NRF_TWIM1->PSEL.SDA);
    printk("Value of NRF_TWIM2->FREQUENCY: %d \n",NRF_TWIM1->FREQUENCY);
    printk("26738688 -> 100k\n");

    for (uint8_t i = 4; i <= 0x7F; i++) {
        struct i2c_msg msgs[1];
        uint8_t dst = 1;

        msgs[0].buf = &dst;
        msgs[0].len = 1U;
        msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

        error = i2c_transfer(i2c_dev, &msgs[0], 1, i);
        if (error == 0) {
            printk("0x%2x FOUND\n", i);
        }
        else {
            //printk("error %d \n", error);
        }

    }
}
*/