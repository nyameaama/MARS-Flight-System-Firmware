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

#include"_state.h"

//CHange state to idle
uint8_t STATE::SWITCH2IDLE(){
    //Change variable
    uint8_t change = 0;
    if(compareX(getLastStateRequest(),"IDLE")){
        change = 1;
    }
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),0);
    delete ptObject;
    return change;
}

//CHange state to prep
uint8_t STATE::SWITCH2PREP(){
    //Change variable
    uint8_t change = 0;
    if(compareX(getLastStateRequest(),"PREP")){
        change = 1;
    }
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),1);
    delete ptObject;
    return change;
}

//CHange state to armed
uint8_t STATE::SWITCH2ARMED(){
    //Change variable
    uint8_t change = 0;
    if(compareX(getLastStateRequest(),"ARMED")){
        change = 1;
    }
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),2);
    delete ptObject;
    return change;
}

//Change state to bypass
uint8_t STATE::SWITCH2BYPASS(){
    //Change variable
    uint8_t change = 0;
    if(compareX(getLastStateRequest(),"BYPASS")){
        change = 1;
    }
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),3);
    delete ptObject;
    return change;
}

void STATE::ASSIGN_PREP_TASKS(){
    DataStore *tsK = new DataStore();
    auto setupFL = tsK -> getIntData("TARGET-LAT").back();
    if(setupFL == 0){
        //
    }
}

void STATE::UNDEF_FLAGS(std::string state){
    DataStore* obj = new DataStore();
    if(state == "IDLE"){
        
    }
    if(state == "PREP"){
        //Reset drone server setup PTAM Register
        std::string reg_name = "setupSFlag";
        //Remove previous value
        obj -> clearData(reg_name);
        //Push Update
        obj -> storeData(reg_name,1);
    }
    if(state == "ARMED"){
    
    }
    if(state == "BYPASS"){
    
    }
    delete obj;
}

char* STATE::getLastStateRequest(){
    //Get STATE data from PTAM
    DataStore* obj = new DataStore();
    std::vector<std::string> stringData = obj->getStringData("stateDescript");
    for (const std::string& element : stringData) {
        std::cout << element << std::endl;
    }
    delete obj;
}

//Reset all drone tags
void STATE::reset_(){
    //Reset prep tag
    //prep = 0;

    //Reset drone started tag
    //droneStarted = 0;
}

//If output = 1, strings match
uint8_t STATE::compareX(char* x, char* y){
    if (x != y){
        return 0;
    }
    else{
        return 1;
    }
}