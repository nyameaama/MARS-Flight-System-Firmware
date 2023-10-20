#include<iostream>
#include<string>
#include"_ptam.h"
#include"_state.h"
#include"sys_controller.h"

#define DRONE_STATE 1 

int main(){
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
        //Boot 
        CTobj -> _init_();
        STATE *change = new STATE();
        while(1){
            #if DRONE_STATE == 1 // STANDBY
            //FROM STANDBY PREP WE CAN EITHER SWITCH TO ARMED OR BYPASS
            CTobj -> _PREP_();
            if(change -> SWITCH2ARMED() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 2
                
                continue;
            }
            if(change -> SWITCH2BYPASS() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 3
                continue;
            }
            #endif

            #if DRONE_STATE == 2 // ARMED
            //FROM ARMED WE CAN EITHER SWITCH TO STANDY PREP OR BYPASS
            CTobj -> _ARMED_();
            if(change -> SWITCH2PREP() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 1
                continue;
            }
            if(change -> SWITCH2BYPASS() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 3
                continue;
            }
            #endif
            
            #if DRONE_STATE == 3 // BYPASS
            //FROM BYPASS WE CAN EITHER SWITCH TO STANDY PREP OR ARMED
            CTobj -> _bypass_(std::string("ID"));
            if(change -> SWITCH2PREP() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 1
                continue;
            }
            if(change -> SWITCH2ARMED() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 2
                continue;
            }
            #endif

        }
        delete change;
        delete CTobj;
}