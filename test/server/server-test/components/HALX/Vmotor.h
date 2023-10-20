#ifndef V_MOTOR_DEF
#define V_MOTOR_DEF

#include <cstdint>

class V_MOTOR {
    public:
        static void mcpwm_gpio_initialize(void);
        
        //+1 Overload
        static uint8_t mcpwm_motor_control(uint8_t throttleValue);
        static uint16_t mcpwm_motor_control(uint16_t duty);

        static uint16_t map(uint8_t value, uint8_t fromLow, uint8_t fromHigh, uint16_t toLow, uint16_t toHigh);

        static void esc_arm_sequence();

        static void esc_disarm();

        static void motor_control_task();
};

#endif // MG90S_SERVO_H