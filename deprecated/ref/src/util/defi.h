/*Copyright (c) 2023 Limitless Aeronautics

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
SOFTWARE.
*/
#ifndef DEFINITION
#define DEFINITION

#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include<Arduino.h>
//#include <SoftwareSerial.h>
#include<SPI.h>
#include<WiFi.h>
#include<esp_now.h>
#include<Wire.h>
#include"PTAM/_ptam.h"
#include"system/sys_controller.h"
#include"system/flight_tasks.h"
#include"Control/_pid.h"
#include"system/Comms/_broadcast.h"
#include"_encode.h"
#include"WingControl/_wingDynamics.h"
#include"module-router/route.h"
#include"system/_state.h"
#include"system/display/onboardDisplay.h"
#include"HALX/drivers/_motors.h"
#include"HALX/drivers/MotorController.h"
#include"HALX/drivers/mpu6050.h"
#include"HALX/drivers/_neo6M.h"
#include"system/checks/validateSensors.h"


//PTAM REGISTER INFO
//"state" -> StateMachine main status
//"GPScheck" -> GPS functionality flag
//"IMUcheck" -> IMU functionality flag
//"BMPcheck" -> BMP functionality flag
//setupSFlag -> ServerSetupFlag
//TARGET-LAT -> destination latitude
//TARGET-LONG -> destination longitude
//TARGET-ALT -> destination altitude

#endif //DEFINITION