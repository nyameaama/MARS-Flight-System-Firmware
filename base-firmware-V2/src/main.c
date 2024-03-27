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
#include "datalink/bt_data/bt_data.h"

uint8_t DRONE_STATE = 1;

void INIT_CORE0();

int main(void){
    INIT_CORE0();
}

void INIT_CORE0(){
    SSD1306_Init();
    displayBOOT();

    ble_gatt_start();

    //FAN_COOLING *cool = new FAN_COOLING();
    //cool -> init_relay();
    //delete cool;

    while(1){

        if(DRONE_STATE == 1){ // STANDBY
            printk("StandBy");
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