/**
 * @brief Individual six pwm outputs to drive bldc motor using drv8302 driver ic.
 * 
 */

#include "pwm_driver.h"




int main(void)
{
	//configure pwm driver
	pwm_driver_config();

    //Start pwm driver
	pwm_driver_start();

	return 0;
}
