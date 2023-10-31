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

//Start comms and attach RF interrupt 
//ATTACH PIN NUMBERS
void CONTROLLER_TASKS::_init_(){
    PTAM_REGISTER_SET();
    //Setup pins - SPI,sensors
    //pin_setup();

    //SENSORS
    /*DataStore *ptObject = new DataStore();

    SensorValidator *valD = new SensorValidator();
    bool GPScheck = valD.validateGPSData();
    if(GPScheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "GPScheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "GPScheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,0);
    }

    bool IMUcheck = valD.validateIMUData();
    if(IMUcheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "IMUcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "IMUcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,0);
    }

    bool BMPcheck = valD.validateBMP280Data();
    if(BMPcheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "BMPcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "BMPcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,0);
    }*/
    //SETUP ONBOARD DISPLAY
   // _ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
    //dispInit._init_();
    //dispInit._showBoot();
    //delete dispInit;
}

void CONTROLLER_TASKS::_IDLE_(){
    //Controller does nothing
}

//Telemetry checks, peripheral checks
void CONTROLLER_TASKS::_PREP_(){
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    auto lat = sharedMemory.getLastDouble("TLat");
    //ESP_LOGI("LAT", "%f",lat);
    //Check for full configuraton completion

}

uint8_t CONTROLLER_TASKS::verifyFlightConfiguration(){
    //To verify flight config, we just check to make sure all flight critical PTAM 
    //registers have valid data (non-zero) and we return 1 or 0
    /*Flight Critical Registers
        SWP:
        Target Latitude
        Target Longitude
        Target Altitude
        Final Altitude
        Target Velocity
    */
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    uint8_t verified = 0;
    auto _lat = sharedMemory.getLastDouble("TLat");
    auto _long = sharedMemory.getLastDouble("TLong");
    auto _Talt = sharedMemory.getLastDouble("TAlt");
    auto _Calt = sharedMemory.getLastDouble("CAlt");
    auto _vel = sharedMemory.getLastDouble("TVel");

    // Check if all variables contain non-zero values
    if (_lat != 0.0 && 
        _long != 0.0 && 
        _Talt != 0.0 && 
        _Calt != 0.0 && 
        _vel != 0.0) {
        // All variables contain non-zero values
        // We can provide authorization
        verified = 1;
    } else {
        // At least one variable contains a zero value
        // Configuration not finished
        verified = 0;
    }
    return verified;
}

std::string CONTROLLER_TASKS::generateRandomAlphanumericToken(uint32_t seed1, uint32_t seed2, int length) {

    const std::string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;

    for (int i = 0; i < length; i++) {
        seed1 = (seed1 * 1664525 + 1013904223) % characters.size();
        seed2 = (seed2 * 1664525 + 1013904223) % characters.size();
        token += characters[seed1 ^ seed2];
    }

    return token;
}

void CONTROLLER_TASKS::restart_after_idle_task() {
    const uint32_t restart_interval = 12 * 60 * 60;  // 12 hours in seconds

    // Get the time elapsed since boot in seconds
    uint32_t uptime = esp_timer_get_time() / 1000000;  // Convert microseconds to seconds

    // Check if it's time to restart after every 12-hour period
    if (uptime % restart_interval == 0) {
        ESP_LOGI("Restart", "Restarting after %d hours of idle time.", int(restart_interval / 3600));
        esp_restart();
    }

}

void CONTROLLER_TASKS::_ARMED_(){
    //Start App
}

//For manual testing, implement bypass to respond to sensor and motor
//comms without additional processes.
//+1 Overload

//Bypass
//No function overloading possible so search SBC table to 
//determine if return or non-return peripheral !! needs attention !!
void CONTROLLER_TASKS::_bypass_(std::string sbc_id){
    //Check if there is any update to the ptam registers
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    //If there is a difference between Wing Register and referenceupdate register there has been an update
    auto dtaWFL = sharedMemory.getLastDouble("WingFL");
    auto dtaWFR = sharedMemory.getLastDouble("WingFR");
    auto dtaWRL = sharedMemory.getLastDouble("WingRL");
    auto dtaWRR = sharedMemory.getLastDouble("WingRR");

    auto dtaWFL_ref = sharedMemory.getLastDouble("FL-ref-byp");
    auto dtaWFR_ref = sharedMemory.getLastDouble("FR-ref-byp");
    auto dtaWRL_ref = sharedMemory.getLastDouble("RL-ref-byp");
    auto dtaWRR_ref = sharedMemory.getLastDouble("RR-ref-byp");

    ESP_LOGI("SEN", "FL %f",dtaWFL);
    ESP_LOGI("SEN", "FL-ref %f",dtaWFL_ref);

    WingTranslate *obj = new WingTranslate();
    if(dtaWFL != dtaWFL_ref){
        //There has been an update, wings can be commanded
        obj -> servo_control(dtaWFL,SERVO_FL);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("FL-ref-byp");
        sharedMemory.storeDouble("FL-ref-byp", dtaWFL);
    }
    if(dtaWFR != dtaWFR_ref){
        //There has been an update, wings can be commanded
        obj -> servo_control(dtaWFR,SERVO_FR);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("FR-ref-byp");
        sharedMemory.storeDouble("FR-ref-byp", dtaWFR);
    }
    if(dtaWRL != dtaWRL_ref){
        //There has been an update, wings can be commanded
        obj -> servo_control(dtaWRL,SERVO_RL);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("RL-ref-byp");
        sharedMemory.storeDouble("RL-ref-byp", dtaWRL);
    }
    if(dtaWRR != dtaWRR_ref){
        //There has been an update, wings can be commanded
        obj -> servo_control(dtaWRR,SERVO_RR);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("RR-ref-byp");
        sharedMemory.storeDouble("RR-ref-byp", dtaWRR);
    }
    delete obj;
}
 //Sensor bypass

void CONTROLLER_TASKS::PTAM_REGISTER_SET(){
    //On startup init PTAM registers so no module calls an undefined register
    //StateMachine main status | Init to STANDBY PREP ON INIT
    // Store data in shared memory
    SharedMemory& sharedMemory = SharedMemory::getInstance();

    sharedMemory.storeInt("state", 1);
    sharedMemory.storeString("stateDescript", "PREP");

    sharedMemory.storeString("arm_token", "");

    //GPS functionality flag
    sharedMemory.storeInt("GPScheck", 0);
    //IMU functionality flag
    sharedMemory.storeInt("IMUcheck", 0);
    //BMP functionality flag
    sharedMemory.storeInt("BMPcheck", 0);
    //Latitude functionality flag
    sharedMemory.storeInt("LATITUDE_CHECK", 0);
    //Longitude functionality flag
    sharedMemory.storeInt("LONGITUDE_CHECK", 0);
    //Altitude functionality flag
    sharedMemory.storeInt("ALTITUDE_CHECK", 0);
    //Velocity functionality flag
    sharedMemory.storeInt("VELOCITY_CHECK", 0);
    //Pitch functionality flag
    sharedMemory.storeInt("PITCH_CHECK", 0);
    //Roll functionality flag
    sharedMemory.storeInt("ROLL_CHECK", 0);
    //Yaw functionality flag
    sharedMemory.storeInt("YAW_CHECK", 0);
    //Temperature functionality flag
    sharedMemory.storeInt("TEMPERATURE_CHECK", 0);
    //Pressure functionality flag
    sharedMemory.storeInt("PRESSURE_CHECK", 0);

    //ServerSetupFlag
    sharedMemory.storeInt("setupSFlag", 0);
    //Target Latitude 
    sharedMemory.storeDouble("TLat", 0);
    //Target Longitude
    sharedMemory.storeDouble("TLong", 0);
    //Target Altitude
    sharedMemory.storeDouble("TAlt", 0);
    //Cruise Altitude
    sharedMemory.storeDouble("CAlt", 0);
    //Target Velocity
    sharedMemory.storeDouble("TVel", 0);
    //Wing FL
    sharedMemory.storeDouble("WingFL", 0);
    sharedMemory.storeDouble("FL-ref-byp", 0);
    //Wing FR
    sharedMemory.storeDouble("WingFR", 0);
    sharedMemory.storeDouble("FR-ref-byp", 0);
    //Wing RL
    sharedMemory.storeDouble("WingRL", 0);
    sharedMemory.storeDouble("RL-ref-byp", 0);
    //Wing RR
    sharedMemory.storeDouble("WingRR", 0);
    sharedMemory.storeDouble("RR-ref-byp", 0);
    //Throttle
    sharedMemory.storeDouble("THR", 0);
    sharedMemory.storeDouble("THR-ref-byp", 0);

    //auto po = init.getStringData(std::string("stateDescript")).back();
    //std::cout << po << std::endl;
}

