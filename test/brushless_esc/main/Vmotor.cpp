#include"Vmotor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define MOTOR_GPIO 15
#define THROTTLE_MAX 2000
#define THROTTLE_MIN 1000

void V_MOTOR::motor_initialize()
{
    /* motor configuration */
    mcpwm_config_t pwm_motor_config;
    pwm_motor_config.frequency = 50;
    pwm_motor_config.cmpr_a = 0;
    pwm_motor_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_motor_config.duty_mode = MCPWM_DUTY_MODE_0;
    
    /*Driver initalization */
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, MOTOR_GPIO);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_motor_config);
    vTaskDelay(2000/portTICK_PERIOD_MS);
}

uint8_t V_MOTOR::mcpwm_motor_control(uint8_t throttleValue){
    uint16_t motorDuty = map(throttleValue, 0, 100, 1000, 2000);
    if(throttleValue == 0){
        ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, THROTTLE_MIN));
        return throttleValue;
    }
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, motorDuty));
    vTaskDelay(10/portTICK_PERIOD_MS); // Add a small delay between duty cycle changes
    return throttleValue;
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
    /*Calibration for ESC 30A to control max and min throttle*/
    //Maximum calibrated duty cycle
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 2000));
    
    vTaskDelay(2000/portTICK_PERIOD_MS);
    //Minimum calibrated duty cycle
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 1000));

    vTaskDelay(3000/portTICK_PERIOD_MS);
}

void V_MOTOR::esc_disarm(){
    // Send minimum duty cycle for a moment
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 1000));
    vTaskDelay(pdMS_TO_TICKS(2000));
}