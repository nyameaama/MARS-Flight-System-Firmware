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

#ifndef BAROMETER_
#define BAROMETER_

#include <math.h>
//#include "../PTAM/_ptam.h"


#define DEFAULT_SEA_LEVEL 1013.25

class VEHICLE_BARO
{
  public:
    //________________________________________________________________________
    /* Initialize the barometer sensor
    ===========================================================================
    | void
    ===========================================================================
    */
    static void init_barometer(void);

    //________________________________________________________________________
    /* Start a measurement with the barometer sensor
    ===========================================================================
    | void
    ===========================================================================
    */
    static void startMeasurement();

    //________________________________________________________________________
    /* Push the temperature data from the barometer sensor
    ===========================================================================
    | Returns: float - The temperature data.
    ===========================================================================
    */
    static float pushTemperature();

    //________________________________________________________________________
    /* Push the pressure data from the barometer sensor
    ===========================================================================
    | Returns: float - The pressure data.
    ===========================================================================
    */
    static float pushPressure();

    //________________________________________________________________________
    /* Push the humidity data from the barometer sensor
    ===========================================================================
    | Returns: float - The humidity data.
    ===========================================================================
    */
    static float pushHumidity();

    //________________________________________________________________________
    /* Push the altitude data calculated based on sea level pressure
    ===========================================================================
    | Parameters:
    |    - seaLevelhPa: Sea level pressure in hectopascals.
    | Returns: double - The calculated altitude.
    ===========================================================================
    */
    static double pushAltitude(double seaLevelhPa);
};

#endif  // BAROMETER_