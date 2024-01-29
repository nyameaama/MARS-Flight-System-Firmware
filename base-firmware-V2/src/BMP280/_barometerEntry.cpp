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

#include"_barometerEntry.h"
#include"bmx280.h"


static gpio_num_t i2c_gpio_sda = GPIO_NUM_21;
static gpio_num_t i2c_gpio_scl = GPIO_NUM_22;
#define I2C_NUM I2C_NUM_1
#define I2C_MASTER_FREQ_HZ 100000 /*!< I2C master clock frequency. no higher than 1MHz for now */

double GroundRef = 0;
bmx280_t* bmx280;

//________________________________________________________________________
/* Initialize the barometer sensor
===========================================================================
| void
===========================================================================
*/
void VEHICLE_BARO::init_barometer(void){
    

    //Driver installed so we can zero out for altitude readings
    double zero_ref = pushPressure();
    GroundRef = zero_ref;
}

//________________________________________________________________________
/* Start a measurement with the barometer sensor
===========================================================================
| void
===========================================================================
*/
void VEHICLE_BARO::startMeasurement(){
    
}

//________________________________________________________________________
/* Push the temperature data from the barometer sensor
===========================================================================
| Returns: float - The temperature data.
===========================================================================
*/
float VEHICLE_BARO::pushTemperature(){
    
}

//________________________________________________________________________
/* Push the pressure data from the barometer sensor
===========================================================================
| Returns: float - The pressure data.
===========================================================================
*/
float VEHICLE_BARO::pushPressure(){
    
}

//________________________________________________________________________
/* Push the humidity data from the barometer sensor
===========================================================================
| Returns: float - The humidity data.
===========================================================================
*/
float VEHICLE_BARO::pushHumidity(){
    
}

//________________________________________________________________________
/* Push the altitude data calculated based on sea level pressure
===========================================================================
| Parameters:
|    - seaLevelhPa: Sea level pressure in hectopascals.
| Returns: double - The calculated altitude.
===========================================================================
*/
double VEHICLE_BARO::pushAltitude(double seaLevelhPa){
    //Get reference altitude from zeroed point
    double zer_pressure = GroundRef;
    // Calculate altitude using the barometric formula
    double zer_altitude = (1.0 - pow((zer_pressure / seaLevelhPa), 0.190284)) * 44330.8;
    //We can now use this to get a computed altitude
    double curr_altitude;
    double curr_pressure = pushPressure();
    curr_altitude = (1.0 - pow((curr_pressure / seaLevelhPa), 0.190284)) * 44330.8;
    //Subtract current altitude and reference altitude to get relative altitude
    double relative_altitude = curr_altitude - zer_altitude;
    return relative_altitude;
}