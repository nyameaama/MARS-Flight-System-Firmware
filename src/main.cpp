/*MIT License

Copyright (c) 2020 Nyameaama Gambrah

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

#ifndef MAIN_
#define MAIN_

#include"system/sys_controller.h"
//#include"PTAM/temp_access_mem.h"
#include"util/defi.h"

//Through spi interface, ECU recieves instructions from main computer

#define DRONE_STATE 0

void setup(){
    CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
    //CTobj -> pin_setup();
    //CTobj -> GSE_comms_setup();
    CTobj -> _init_();
    delete CTobj;
}

void loop(){
    CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
    while(1){
        #if DRONE_STATE == 0 // IDLE
        CTobj -> _IDLE_();
        if(CTobj -> SWITCH2PREP() == 1){
            #undef DRONE_STATE
            #define DRONE_STATE 1
        }
        #endif

        #if DRONE_STATE == 1 // PREP
        CTobj -> _PREP_();
        if(CTobj -> SWITCH2ARMED() == 1){
            #undef DRONE_STATE
            #define DRONE_STATE 2
        }
        #endif

        #if DRONE_STATE == 2 // ARMED
        CTobj -> _ARMED_();
        if(CTobj -> SWITCH2IDLE() == 1){
            #undef DRONE_STATE
            #define DRONE_STATE 0
        }
        #endif
        
        #if DRONE_STATE == 3 // BYPASS
        CTobj -> _bypass_();
        #endif

    }
    delete CTobj;
}

#endif // MAIN_