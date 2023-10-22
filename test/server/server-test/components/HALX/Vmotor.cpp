#include"Vmotor.h"
#include "mg90s_servo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define MOTOR_GPIO 15
#define THROTTLE_MAX 2000
#define THROTTLE_MIN 1000
#define THROTTLE_IDLE 1500

#define ESC_PWM_DUTY_MAX 2000
#define ESC_PWM_DUTY_MIN 1000
#define ESC_PWM_DUTY_NEUTRAL 1500

void V_MOTOR::mcpwm_gpio_initialize()
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, MOTOR_GPIO); //Set MOTOR as PWM0A, to which servo is connected

    //Initial mcpwm configuration
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 500; //frequency = 50Hz, i.e. for every motor time period should be 20ms
    pwm_config.cmpr_a = 50;     //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 50;     //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config); //Configure PWM0A & PWM0B with above settings
}

uint8_t V_MOTOR::mcpwm_motor_control(uint8_t throttleValue){
    if(throttleValue == 0){
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, THROTTLE_IDLE);
        return throttleValue;
    }
    uint16_t pulseWidth = map(throttleValue, 0, 180, THROTTLE_MIN, THROTTLE_MAX);  // Map throttle value to pulse width range
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pulseWidth);
    return throttleValue;
}

uint16_t V_MOTOR::mcpwm_motor_control(uint16_t duty){
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty);
    return duty;
}

uint16_t V_MOTOR::map(uint8_t value, uint8_t fromLow, uint8_t fromHigh, uint16_t toLow, uint16_t toHigh){
  // Check if the value is within the input range
  if (value <= fromLow) {
    return toLow;
  }
  else if (value >= fromHigh) {
    return toHigh;
  }
  
  // Calculate the scaled value
  long mappedValue = (long)(value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
  
  // Return the mapped value as an integer
  return (int)mappedValue;
}

void V_MOTOR::esc_arm_sequence(){
    // Send maximum duty cycle for a few seconds
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, ESC_PWM_DUTY_MAX);
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Send minimum duty cycle for a moment
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, ESC_PWM_DUTY_MIN);
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Send middle duty cycle (neutral position)
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, ESC_PWM_DUTY_NEUTRAL);
}

void V_MOTOR::esc_disarm(){
    // Send minimum duty cycle for a moment
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, ESC_PWM_DUTY_MIN);
    vTaskDelay(pdMS_TO_TICKS(500));
}

void V_MOTOR::motor_control_task() {
    // Control the motor speed by adjusting the duty cycle
    while (1) {
        // Increase duty cycle to speed up the motor
        for (int duty = 1500; duty <= 2000; duty += 100) {
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, duty);
            vTaskDelay(pdMS_TO_TICKS(100)); // Delay for motor to respond
        }

        // Decrease duty cycle to slow down the motor
        for (int duty = 2000; duty >= 1500; duty -= 100) {
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, duty);
            vTaskDelay(pdMS_TO_TICKS(100)); // Delay for motor to respond
        }
    }
}