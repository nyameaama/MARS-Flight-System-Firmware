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

#include "mg90s_servo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

//You can get these value from the datasheet of servo you use, in general pulse width varies between 1000 to 2000 microsecond
#define SERVO_MIN_PULSEWIDTH 1000 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2000 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 90       //Maximum angle in degree upto which servo can rotate
#define servo_pin 16              //gpio pin of servo
#define servo_pin2 17              //gpio pin of servo
#define servo_pin3 18              //gpio pin of servo
#define servo_pin4 19              //gpio pin of servo

uint8_t SERVO_POS_1 = 0;

uint8_t SERVO_POS_2 = 0;

uint8_t SERVO_POS_3 = 0;

uint8_t SERVO_POS_4 = 0;

//____________________________________________________________
/* Initializes MG90S Servo using MCPWM
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
void WingTranslate::mcpwm_gpio_initialize(uint8_t motor)
{
    switch(motor) {
        case 0:
            mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, servo_pin); //Set servo_pin as PWM0A, to which servo is connected
        break;
        case 1:
            mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, servo_pin2); //Set servo_pin2 as PWM0A, to which servo is connected
        break;
        case 2:
            mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, servo_pin3); //Set servo_pin3 as PWM0A, to which servo is connected
        break;
        case 3:
            mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, servo_pin4); //Set servo_pin4 as PWM0A, to which servo is connected
        break;
    }
}


//____________________________________________________________
/* Utillity subroutine -> angle to pulsewidth converter
===========================================================================
|    motor rotation degree   The motor rotation bounded between 0 deg to 90 deg
===========================================================================
*/
uint32_t WingTranslate::servo_per_degree_init(uint32_t degree_of_rotation)
{
    uint32_t cal_pulsewidth = 0;
    cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
    return cal_pulsewidth;
}

//____________________________________________________________
/* Main API routine
===========================================================================
|    motor target angle   The motor rotation angle bounded between 0 deg to 90 deg
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
uint8_t WingTranslate::mcpwm_servo_control(uint32_t target,uint8_t pin)
{
    uint32_t angle, count;
    uint32_t SERVO_TARGET_ANGLE = target;
    //1. mcpwm gpio initialization
    mcpwm_gpio_initialize(pin);

    //2. initial mcpwm configuration
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50; //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwm_config.cmpr_a = 0;     //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;     //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config); //Configure PWM0A & PWM0B with above settings
    
    //Hardware Check
    if(target > 90){
        //MARS LOGGER SOFT FAIL 
        return 0;
    }
    uint8_t SP = GET_SERVO_POS(pin);

    if(SP != target){
        if(target > SP){
            for (count = SP; count < SERVO_TARGET_ANGLE; count += (SERVO_TARGET_ANGLE - SP)){
                angle = servo_per_degree_init(count);
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
                vTaskDelay(10 * (SERVO_TARGET_ANGLE - SP)); //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation at 5V
            }
            UPDATE_SERVO_POS(pin,target);
        }
        if(target < SP){
            for (count = SP; count > SERVO_TARGET_ANGLE; count -= (SERVO_TARGET_ANGLE - SP)){
                angle = servo_per_degree_init(count);
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
                vTaskDelay(10 * (SERVO_TARGET_ANGLE - SP)); //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation at 5V
            }
            UPDATE_SERVO_POS(pin,target);
        }
    }
    return 1;
}


//____________________________________________________________
/* Utillity subroutine -> retrieve current motor position 
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
===========================================================================
*/
uint8_t WingTranslate::GET_SERVO_POS(uint8_t pin)
{
     switch(pin) {
        case 0:
            return SERVO_POS_1;
        break;
        case 1:
            return SERVO_POS_2;
        break;
        case 2:
            return SERVO_POS_3;
        break;
        case 3:
            return SERVO_POS_4;
        break;
    }
    return 0;
}


//____________________________________________________________
/* Utillity subroutine -> update current motor position after movement change
===========================================================================
|    motor selection   The identification of the motor intended to be interfaced
|    updated servo position      New motor position to be updated
===========================================================================
*/
void WingTranslate::UPDATE_SERVO_POS(uint8_t pin, uint8_t updatedValue){
    switch(pin) {
        case 0:
            SERVO_POS_1 = updatedValue;
        break;
        case 1:
            SERVO_POS_2 = updatedValue;
        break;
        case 2:
            SERVO_POS_3 = updatedValue;
        break;
        case 3:
            SERVO_POS_4 = updatedValue;
        break;
    }
}