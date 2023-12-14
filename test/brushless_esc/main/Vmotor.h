#ifndef V_MOTOR_DEF
#define V_MOTOR_DEF

#include <cstdint>

class V_MOTOR {
    public:
        static void motor_initialize(void);
        
        static uint8_t mcpwm_motor_control(uint8_t throttleValue);

        static uint16_t map(uint8_t value, uint8_t fromLow, uint8_t fromHigh, uint16_t toLow, uint16_t toHigh);

        static void esc_arm_sequence();

        static void esc_disarm();

};

#endif // V_MOTOR_DEF