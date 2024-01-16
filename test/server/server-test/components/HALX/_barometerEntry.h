#ifndef BAROMETER_
#define BAROMETER_

#include <math.h>
#include "esp_log.h"

#define DEFAULT_SEA_LEVEL 1013.25

class VEHICLE_BARO
{
  public:
    static void init_barometer(void);

    static void startMeasurement();

    static float pushTemperature();

    static float pushPressure();

    static float pushHumidity();

    static double pushAltitude(double seaLevelhPa);
};

#endif  // BAROMETER_