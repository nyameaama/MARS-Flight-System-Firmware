#ifndef FAN_RELAY
#define FAN_RELAY

class FAN_COOLING{
    public:
        static void init_relay();

        static void fan_relay_on();

        static void fan_relay_off();

        static void coolSierra_task(double sierraTemp);
};

#endif