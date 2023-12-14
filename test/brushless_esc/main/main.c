#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define motor_pin 15    // PWM pin gpio 5 
static const char *Tag = "ESC 30A Motor Driver";
/* motor configuration */
mcpwm_config_t pwm_motor_config = {
    .frequency = 50,
    .cmpr_a = 0,
    .counter_mode = MCPWM_UP_COUNTER,
    .duty_mode = MCPWM_DUTY_MODE_0,
};

/* Here 1000us = 1ms and duty cycle of 1ms to  2ms mean motor to control 0 to max. speed*/
void throttle_control(){
    for(int i = 1000; i < 2000; i++){
        ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, i));
        ESP_LOGI(Tag, "Duty Cycle is %d in us", i);
        vTaskDelay(10/portTICK_PERIOD_MS); // Add a small delay between duty cycle changes
    }
    for(int j = 2000; j < 1000; j--){
        ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, j));
        ESP_LOGI(Tag, "Duty Cycle is %d in us", j);
        vTaskDelay(10/portTICK_PERIOD_MS); // Add a small delay between duty cycle changes
    }
}

void app_main(void)
{
    /*Driver initalization */
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, motor_pin);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_motor_config);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    ESP_LOGI(Tag, "Initialization done");

    /*Calibration for ESC 30A to control max and min throttle*/
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 2000));
    ESP_LOGI(Tag, "Maximum calibrated duty cycle");
    
    vTaskDelay(2000/portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 1000));
    ESP_LOGI(Tag, "Minimum calibrated duty cycle");

    vTaskDelay(3000/portTICK_PERIOD_MS);

    /*After Calibration motor start from minimum to maximum speed*/
    throttle_control();    
}
