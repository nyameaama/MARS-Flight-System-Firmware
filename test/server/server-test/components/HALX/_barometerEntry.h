#include"esp_log.h"

class VEHICLE_BARO {
    public:
        static void init_barometer(void);

        static void startMeasurement();

        static float pushTemperature();

        static float pushPressure();

        static float pushHumidity();
};