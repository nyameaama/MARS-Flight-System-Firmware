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

#include "_state.h"

//____________________________________________________________
/* Change state to prep
===========================================================================
|    void
===========================================================================
*/
    uint8_t STATE::SWITCH2PREP(){
        //Change variable
        uint8_t change = 0;
        //PREP -> 1
        if(compareX(getLastStateRequest(),std::string("PREP"))){
            change = 1;
            SharedMemory& sharedMemory = SharedMemory::getInstance();
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("state");
            sharedMemory.clearData("stateDescript");

            sharedMemory.storeInt("state", 1);
            sharedMemory.storeString(std::string("stateDescript"),std::string("PREP"));
        } 
        return change;
    }

//____________________________________________________________
/* Change state to armed
===========================================================================
|    void
===========================================================================
*/
    uint8_t STATE::SWITCH2ARMED(){
        //Change variable
        uint8_t change = 0;
        //ARMED -> 2
        if(compareX(getLastStateRequest(),std::string("ARMED"))){
            change = 1;
            SharedMemory& sharedMemory = SharedMemory::getInstance();
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("state");
            sharedMemory.clearData("stateDescript");

            sharedMemory.storeInt("state", 2);
            sharedMemory.storeString(std::string("stateDescript"),std::string("ARMED"));
        }
        return change;
    }

//____________________________________________________________
/* Change state to bypass
===========================================================================
|    void
===========================================================================
*/
    //Change state to bypass
    uint8_t STATE::SWITCH2BYPASS(){
        //Change variable
        uint8_t change = 0;
        //BYPASS -> 3
        if(compareX(getLastStateRequest(),std::string("BYPASS"))){
            change = 1;
            SharedMemory& sharedMemory = SharedMemory::getInstance();
            //Clear previous register to avoid memory overflow
            sharedMemory.clearData("state");
            sharedMemory.clearData("stateDescript");

            sharedMemory.storeInt("state", 3);
            sharedMemory.storeString(std::string("stateDescript"),std::string("BYPASS"));
        }
        return change;
    }

//____________________________________________________________
/* Get last state request from PTAM
===========================================================================
|    void
===========================================================================
*/
    std::string STATE::getLastStateRequest(){
        SharedMemory& obj = SharedMemory::getInstance();
        //Get STATE data from PTAM
        auto dta = obj.getLastString("stateDescript");
        //ESP_LOGI("STATE", "%s",dta.c_str());
        return dta;
    }

//____________________________________________________________
/* Compare two strings of type <std::string>
===========================================================================
|    void
===========================================================================
*/
    //If output = 1, strings match
    uint8_t STATE::compareX(std::string x, std::string y){
        if (x != y){
            return 0;
        }
        else{
            return 1;
        }
    }