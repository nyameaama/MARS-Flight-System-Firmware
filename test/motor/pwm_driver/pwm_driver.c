#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>
#include "pwm_driver.h"

/**
 * @brief drv8302 logic table
 * 
 * INL_X INH_X GL_X GH_X
 * 0      0     L    L
 * 0      1     L    H
 * 1      0     H    L
 * 1      1     L    L
 * 
*/

/**
 * @brief drv8302 pwm mosfet drive --> { {GHA_PIN,  }, {GLA_PIN}}
 * @brief drv8302 pwm mosfet drive --> { {GHB_PIN,  }, {GLB_PIN}}
 * @brief drv8302 pwm mosfet drive --> { {GHC_PIN,  }, {GLC_PIN}}
 * 
 * @brief 50% duty cycle
 **/

LOG_MODULE_REGISTER(PWM_DRIVER, LOG_LEVEL_INF);

#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U)/ 4U
#define sleep_time_ms 1000


/*After configuration min and max period */
static uint32_t max_period = 0U;

/* minimim duty cycle */
static uint32_t min_duty_cycle = 0U;
static uint32_t max_duty_cycle = 0U;
int ret;



uint8_t states_without_feedback =0;

/* pwm pins specification */
static const struct pwm_dt_spec GHA_PIN = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
static const struct pwm_dt_spec GLA_PIN = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
static const struct pwm_dt_spec GHB_PIN = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led2));
static const struct pwm_dt_spec GLB_PIN = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led3));
static const struct pwm_dt_spec GHC_PIN = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led4));
static const struct pwm_dt_spec GLC_PIN = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led5));

/**
 * 
 * @brief pwm driver configuration
 * 
*/
void pwm_driver_config(void)
{
	LOG_INF("PWM-based blinky\n");

    /* Modeule pwm0 --> 4 channels individually configuration */
	if (!device_is_ready(GHA_PIN.dev)) {
		LOG_ERR("Error: PWM device %s is not ready\n",
		       GHA_PIN.dev->name);
		return;
	}

    /* Modeule pwm1 --> 2 channels individually configuration */
	if(!device_is_ready(GHC_PIN.dev)){
		LOG_ERR("Error: PWM device %s is not ready\n",
		        GHC_PIN.dev->name);
		return;
	}

	/*
	 * In case the default MAX_PERIOD value cannot be set for
	 * some PWM hardware, decrease its value until it can.
	 *
	 * Keep its value at least MIN_PERIOD * 4 to make sure
	 * the sample changes frequency at least once.
	 */
	LOG_INF("Calibrating for channel %d...\n", GHA_PIN.channel);
	max_period = MAX_PERIOD;
	while (pwm_set_dt(&GHA_PIN, max_period, max_period / 2U)) {
		max_period /= 2U;
		if (max_period < (4U * MIN_PERIOD)) {
			LOG_ERR("Error: PWM device "
			       "does not support a period at least %lu\n",
			       4U * MIN_PERIOD); 
			return;
		}
	}

    /* First all pins output should zero after initialization of driver */

	while (pwm_set_dt(&GHA_PIN, max_period, min_duty_cycle)) {
	}

	while (pwm_set_dt(&GLA_PIN, max_period, min_duty_cycle)) {
	}

	while (pwm_set_dt(&GHB_PIN, max_period, min_duty_cycle)) {
	}

	while (pwm_set_dt(&GLB_PIN, max_period, min_duty_cycle)) {
	}

	while (pwm_set_dt(&GHC_PIN, max_period, min_duty_cycle)) {
	}

	while (pwm_set_dt(&GLC_PIN, max_period, min_duty_cycle)) {
	}

	LOG_INF("Done calibrating; maximum/minimum periods %u/%lu nsec\n",
	       max_period, MIN_PERIOD);

	/*50% duty cycle --> max_period / 2U (user can vary this parameter)*/
    max_duty_cycle = max_period / 2U;
}

/**
 * 
 * @brief pwm driver start
 * 
*/
void pwm_driver_start(void)
{
    while(1)
    {
        /* Here we follow six window technique to make trapizoidal control over BLDC motor */
        switch(states_without_feedback)
        {
            /*Window 1 --> GHA  high, GLB high  GHC low*/
            case 0:
			    while (pwm_set_dt(&GHC_PIN, max_period, min_duty_cycle)){

				}
                while (pwm_set_dt(&GHA_PIN, max_period, max_duty_cycle)){

				}
                while (pwm_set_dt(&GLB_PIN, max_period, max_duty_cycle)){
					
				}
                states_without_feedback = 1;
                k_msleep(sleep_time_ms);
            break;

            /*Window 2 --> GHA  high, GLC high, GLB low*/
            case 1:
			    while (pwm_set_dt(&GLB_PIN, max_period, min_duty_cycle)){

				}
                while (pwm_set_dt(&GLC_PIN, max_period, max_duty_cycle)){

				}
                states_without_feedback = 2;
                k_msleep(sleep_time_ms);               
            break;

            /*Window 3 --> GHA  low, GLC high, GHB high*/
            case 2:
			    while (pwm_set_dt(&GHA_PIN, max_period, min_duty_cycle)){

				}
				while (pwm_set_dt(&GHB_PIN, max_period, max_duty_cycle)){

				}
                states_without_feedback = 3;
                k_msleep(sleep_time_ms); 
            break;

            /*Window 4 --> GLA  high, GLC low, GHB high*/
            case 3:
			    while (pwm_set_dt(&GLC_PIN, max_period, min_duty_cycle)){

				}
				while (pwm_set_dt(&GLA_PIN, max_period, max_duty_cycle)){

				}
                states_without_feedback = 4;             
                k_msleep(sleep_time_ms);
            break;

            /*Window 5 --> GLA  high, GHC high, GHB low*/
            case 4:
			    while (pwm_set_dt(&GHB_PIN, max_period, min_duty_cycle)){

				}
				while (pwm_set_dt(&GHC_PIN, max_period, max_duty_cycle)){

				}
                states_without_feedback = 5;
                k_msleep(sleep_time_ms);                
            break;

            /*Window 6 --> GLA  low, GHC high, GLB high*/
            case 5:
			    while (pwm_set_dt(&GLA_PIN, max_period, min_duty_cycle)){

				}
				while (pwm_set_dt(&GLB_PIN, max_period, max_duty_cycle)){

				}
                states_without_feedback = 0;
                k_msleep(sleep_time_ms);
			break;
            default:

            break;
        }
    }
}