#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include"Vmotor.h"

extern "C"{
    void app_main(void)
    {
        /*Driver initalization */
        V_MOTOR *motor_obj = new V_MOTOR();
        motor_obj -> motor_initialize();
  
        /*Calibration for ESC 30A to control max and min throttle*/
        motor_obj -> esc_arm_sequence();

        /*After Calibration motor start from minimum to maximum speed*/
        motor_obj -> mcpwm_motor_control(100);
        /*vTaskDelay(pdMS_TO_TICKS(2000));
        motor_obj -> mcpwm_motor_control(70);
        vTaskDelay(pdMS_TO_TICKS(2000));
        motor_obj -> mcpwm_motor_control(100);*/
        //vTaskDelay(pdMS_TO_TICKS(2000));
        //motor_obj -> mcpwm_motor_control(0);
    }
}