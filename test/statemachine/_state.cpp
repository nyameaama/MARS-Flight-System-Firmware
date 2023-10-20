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

    //CHange state to prep
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
        //std::cout << "SWITCHTOPREP RETURNING";
        //std::string strChange = std::to_string(change);
        //std::cout << strChange << std::endl;
        return change;
    }

    //CHange state to armed
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
        //std::cout << "SWITCHTOARMED RETURNING ";
        //std::string strChange = std::to_string(change);
        //std::cout << strChange << std::endl;
        return change;
    }

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
        //std::cout << "SWITCHTOBYPASS RETURNING";
        //std::string strChange = std::to_string(change);
        //std::cout << strChange << std::endl;
        return change;
    }

    void STATE::ASSIGN_PREP_TASKS(){
        
    }

    void STATE::UNDEF_FLAGS(std::string state){
        if(state == "IDLE"){
            
        }
        if(state == "PREP"){
            //Reset drone server setup PTAM Register
            //std::string reg_name = "setupSFlag";
            //Remove previous value
            //obj -> clearData(reg_name);
            //Push Update
            //obj -> storeData(reg_name,1);
        }
        if(state == "ARMED"){
        
        }
        if(state == "BYPASS"){
        
        }
    }

    std::string STATE::getLastStateRequest(){
        SharedMemory& obj = SharedMemory::getInstance();
        //Get STATE data from PTAM
        auto dta = obj.getLastString("stateDescript");
        return dta;
    }

    //If output = 1, strings match
    uint8_t STATE::compareX(std::string x, std::string y){
        if (x != y){
            return 0;
        }
        else{
            return 1;
        }
    }