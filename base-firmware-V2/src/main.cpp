#include <zephyr/kernel.h>
#include "system/_state.h"
#include "system/sys_controller.h"
#include <string>

uint8_t DRONE_STATE = 1;

void INIT_CORE0(void *pvParameters);

int main(void){

}

void INIT_CORE0(void *pvParameters){
        CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
        //Boot 
        CTobj -> _init_();
        delete CTobj;

        while(1){
            CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
            STATE *change = new STATE(); 

            if(DRONE_STATE == 1){ // STANDBY
                //FROM STANDBY PREP WE CAN EITHER SWITCH TO ARMED OR BYPASS
                CTobj -> _PREP_();
                if(change -> SWITCH2ARMED() == 1){
                    DRONE_STATE = 2;
                    continue;
                }
                if(change -> SWITCH2BYPASS() == 1){
                    DRONE_STATE = 3;
                    continue;
                }
            }

            if(DRONE_STATE == 2){ // ARMED
                //FROM ARMED WE CAN EITHER SWITCH TO STANDY PREP OR BYPASS
                CTobj -> _ARMED_();
                if(change -> SWITCH2PREP() == 1){
                    DRONE_STATE = 1;
                    continue;
                }
                if(change -> SWITCH2BYPASS() == 1){
                    DRONE_STATE = 3;
                    continue;
                }
            }
            
            if(DRONE_STATE == 3){ // BYPASS
                //FROM BYPASS WE CAN EITHER SWITCH TO STANDY PREP OR ARMED
                CTobj -> _bypass_(std::string("ID"));
                if(change -> SWITCH2PREP() == 1){
                    DRONE_STATE = 1;
                    continue;
                }
                if(change -> SWITCH2ARMED() == 1){
                    DRONE_STATE = 2;
                    continue;
                }
            }

            delete change;
            delete CTobj;
        }
}

