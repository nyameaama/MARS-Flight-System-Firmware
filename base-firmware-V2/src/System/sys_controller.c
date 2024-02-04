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

void _init_(){
    PTAM_REGISTER_SET();
}

void PTAM_REGISTER_SET(){
    storeData("state", 1, DOUBLE);
    storeData("stateDescript", "PREP", STRING);

    storeData("arm_token", "", STRING);

    //GPS functionality flag
    storeData("GPScheck", 0, DOUBLE);
    //IMU functionality flag
    storeData("IMUcheck", 0, DOUBLE);
    //BMP functionality flag
    storeData("BMPcheck", 0, DOUBLE);
    //Latitude functionality flag
    storeData("LATITUDE_CHECK", 0, DOUBLE);
    //Longitude functionality flag
    storeData("LONGITUDE_CHECK", 0, DOUBLE);
    //Altitude functionality flag
    storeData("ALTITUDE_CHECK", 0, DOUBLE);
    //Velocity functionality flag
    storeData("VELOCITY_CHECK", 0, DOUBLE);
    //Pitch functionality flag
    storeData("PITCH_CHECK", 0, DOUBLE);
    //Roll functionality flag
    storeData("ROLL_CHECK", 0, DOUBLE);
    //Yaw functionality flag
    storeData("YAW_CHECK", 0, DOUBLE);
    //Temperature functionality flag
    storeData("TEMPERATURE_CHECK", 0, DOUBLE);
    //Pressure functionality flag
    storeData("PRESSURE_CHECK", 0, DOUBLE);

    //ServerSetupFlag
    storeData("setupSFlag", 0, DOUBLE);
    //Target Latitude 
    storeData("TLat", 0, DOUBLE);
    //Target Longitude
    storeData("TLong", 0, DOUBLE);
    //Target Altitude
    storeData("TAlt", 0, DOUBLE);
    //Cruise Altitude
    storeData("CAlt", 0, DOUBLE);
    //Target Velocity
    storeData("TVel", 0, DOUBLE);
    //Wing FL
    storeData("WingFL", 0, DOUBLE);
    storeData("FL-ref-byp", 0, DOUBLE);
    //Wing FR
    storeData("WingFR", 0, DOUBLE);
    storeData("FR-ref-byp", 0, DOUBLE);
    //Wing RL
    storeData("WingRL", 0, DOUBLE);
    storeData("RL-ref-byp", 0, DOUBLE);
    //Wing RR
    storeData("WingRR", 0, DOUBLE);
    storeData("RR-ref-byp", 0, DOUBLE);
    //Throttle
    storeData("THR", 0, DOUBLE);
    storeData("THR-ref-byp", 0, DOUBLE);
}