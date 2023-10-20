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

#include"sys_controller.h"

BroadcastedServer server;

//Setup pins based on config
void CONTROLLER_TASKS::pin_setup(){
   
}

//Setup comms to GSE over ESP32 Wifi
void CONTROLLER_TASKS::GSE_COMMS_SETUP(){
    // Initialize and start the server
    server.begin();
    server.sendWebpage();
    server.handleNotFound();

}
//Start comms and attach RF interrupt 
//ATTACH PIN NUMBERS
void CONTROLLER_TASKS::_init_(){
    PTAM_REGISTER_SET();
    //Start Serial Communication
    Serial.begin(9600);
    //Setup pins - SPI,sensors
    //pin_setup();
    //SPI.begin();
    //SENSORS
    DataStore *ptObject = new DataStore();

    SensorValidator *valD = new SensorValidator();
    bool GPScheck = valD -> validateGPSData();
    if(GPScheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "GPScheck";
        //Remove previous value
        ptObject -> clearData(reg_name);
        //Push Update
        ptObject -> storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "GPScheck";
        //Remove previous value
        ptObject -> clearData(reg_name);
        //Push Update
        ptObject -> storeData(reg_name,0);
    }

    bool IMUcheck = valD -> validateIMUData();
    if(IMUcheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "IMUcheck";
        //Remove previous value
        ptObject -> clearData(reg_name);
        //Push Update
        ptObject -> storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "IMUcheck";
        //Remove previous value
        ptObject -> clearData(reg_name);
        //Push Update
        ptObject -> storeData(reg_name,0);
    }

    bool BMPcheck = valD -> validateBMP280Data();
    if(BMPcheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "BMPcheck";
        //Remove previous value
        ptObject -> clearData(reg_name);
        //Push Update
        ptObject -> storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "BMPcheck";
        //Remove previous value
        ptObject -> clearData(reg_name);
        //Push Update
        ptObject -> storeData(reg_name,0);
    }
    //SETUP ONBOARD DISPLAY
    _ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
    dispInit -> _init_();
    dispInit -> _showBoot();
    delete dispInit;
    //Rotate wing servos to default
    /*uint8_t defaultP = 0;
    _motors *_mObj = new _motors();
    _mObj -> adjustServoFWLEFT(defaultP);
    _mObj -> adjustServoFWRIGHT(defaultP);
    _mObj -> adjustServoRWLEFT(defaultP);
    _mObj -> adjustServoRWRIGHT(defaultP);
    delete _mObj;*/
}

void CONTROLLER_TASKS::_IDLE_(){
    //Controller does nothing
}

//Telemetry checks, peripheral checks
void CONTROLLER_TASKS::_PREP_(){
    DataStore* obj = new DataStore();
    auto setupFL = obj -> getIntData("setupSFlag").back();
    if(setupFL == 0){
        GSE_COMMS_SETUP();
        //Set server setup PTAM register to 1
        obj -> clearData("setupSFlag");
        obj -> storeData(std::string("setupSFlag"),1);
    }
    //Controller runs ground server
    server.handleClient();
    delete obj;
}

void CONTROLLER_TASKS::_ARMED_(){
    _ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
    dispInit -> stateARMED();
    delete dispInit;
    //Check if takeoff conditions met

    // If takeoff = true , Set cruise - follow waypoint

    //
}

//For manual testing, implement bypass to respond to sensor and motor
//comms without additional processes.
//+1 Overload

//Bypass
//No function overloading possible so search SBC table to 
//determine if return or non-return peripheral !! needs attention !!
void CONTROLLER_TASKS::_bypass_(char* sbc_id){
    _ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
    dispInit -> stateBYPASS();
    delete dispInit;
    if(sbc_id){
        //bypass
        
    }else{
        //Sensor bypass
        //Request sensor data
        //
    }
}
 //Sensor bypass

void CONTROLLER_TASKS::PTAM_REGISTER_SET(){
    //On startup init PTAM registers so no module calls an undefined register
    DataStore *init = new DataStore();
    //StateMachine main status
    init -> storeData("state"," ");
    //GPS functionality flag
    init -> storeData("GPScheck",0);
    //IMU functionality flag
    init -> storeData("IMUcheck",0);
    //BMP functionality flag
    init -> storeData("BMPcheck",0);
    //ServerSetupFlag
    init -> storeData("setupSFlag",0);
    delete init;
}