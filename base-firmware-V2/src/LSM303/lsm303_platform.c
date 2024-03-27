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

#include"lsm303_platform.h"

#define BOOT_TIME              5 //ms
#define TX_BUF_DIM          1000

#define LSM303 DT_NODELABEL(lsm303)

const struct i2c_dt_spec dev_i2c_lsm303 = I2C_DT_SPEC_GET(LSM303);

/**
 * @brief Writes data to a specific register on the platform.
 * 
 * This function writes a sequence of bytes to a specified register
 * address using i2c.
 * 
 * @param handle Pointer to the platform-specific handle.
 * @param reg Register address to write to.
 * @param bufp Pointer to the data buffer that will be written.
 * @param len Number of bytes to write.
 * @return int32_t Returns 0 for a successful operation, non-zero for failure.
 */
int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len){
    uint8_t dt[256];
	uint8_t i;
	dt[0] = reg;
	for(i = 0; i < len; i++){
		dt[i+1] = data[i];
	}
	uint8_t ret;
	ret = i2c_write_dt(&dev_i2c_lsm303, dt, sizeof(dt));
	if(ret != 0){
		printk("Failed to write to I2C device address");
	}
}

/**
 * @brief Reads data from a specific register on the platform.
 * 
 * This function reads a sequence of bytes from a specified register
 * address using i2c.
 * 
 * @param handle Pointer to the platform-specific handle.
 * @param reg Register address to read from.
 * @param bufp Pointer to the data buffer where read data will be stored.
 * @param len Number of bytes to read.
 * @return int32_t Returns 0 for a successful operation, non-zero for failure.
 */	                          
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len){
    for (size_t i = 0; i < len; i++) {
        ret = i2c_write_read_dt(&dev_i2c_lsm303, reg_addr, 1, data, len);
        if(ret != 0){
            printk("Failed to write/read I2C device address");
        }
    }
}

/**
 * @brief Delays execution for a given number of milliseconds.
 * 
 * @param ms Number of milliseconds to delay.
 */
 void platform_delay(uint32_t ms){
	k_msleep(ms);
}

/**
 * @brief Initializes the platform.
 * 
 * This function performs any necessary initializations on the platform,
 * such as setting up communication interfaces or configuring hardware.
 */
void platform_init(void){
    if (!device_is_ready(dev_i2c_lsm303.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c_lsm303.bus->name);
		return;
	}
}

/**
 * @brief Initializes the LSM303 sensor.
 * 
 * Sets up the LSM303 sensor for reading accelerometer and magnetometer
 * data, including configuring registers and setting default states.
 */
 void lsm303_init(){
	/* Initialize mems driver interface */
	stmdev_ctx_t dev_ctx_xl;
	dev_ctx_xl.write_reg = platform_write;
	dev_ctx_xl.read_reg = platform_read;
	dev_ctx_xl.handle = (void *)&xl_bus;
	stmdev_ctx_t dev_ctx_mg;
	dev_ctx_mg.write_reg = platform_write;
	dev_ctx_mg.read_reg = platform_read;
	dev_ctx_mg.handle = (void *)&mag_bus;
	/* Wait boot time and initialize platform specific hardware */
	platform_init();
	/* Wait sensor boot time */
	platform_delay(BOOT_TIME);
	/* Check device ID */
	whoamI = 0;
	lsm303agr_xl_device_id_get(&dev_ctx_xl, &whoamI);

	if ( whoamI != LSM303AGR_ID_XL )
		while (1); /*manage device not found */

	whoamI = 0;
	lsm303agr_mag_device_id_get(&dev_ctx_mg, &whoamI);

	if ( whoamI != LSM303AGR_ID_MG )
		while (1); /*manage device not found */

	/* Restore default configuration for magnetometer */
	lsm303agr_mag_reset_set(&dev_ctx_mg, PROPERTY_ENABLE);

	do {
		lsm303agr_mag_reset_get(&dev_ctx_mg, &rst);
	} while (rst);

	/* Enable Block Data Update */
	lsm303agr_xl_block_data_update_set(&dev_ctx_xl, PROPERTY_ENABLE);
	lsm303agr_mag_block_data_update_set(&dev_ctx_mg, PROPERTY_ENABLE);
	/* Set Output Data Rate */
	lsm303agr_xl_data_rate_set(&dev_ctx_xl, LSM303AGR_XL_ODR_1Hz);
	lsm303agr_mag_data_rate_set(&dev_ctx_mg, LSM303AGR_MG_ODR_10Hz);
	/* Set accelerometer full scale */
	lsm303agr_xl_full_scale_set(&dev_ctx_xl, LSM303AGR_2g);
	/* Set / Reset magnetic sensor mode */
	lsm303agr_mag_set_rst_mode_set(&dev_ctx_mg,
									LSM303AGR_SENS_OFF_CANC_EVERY_ODR);
	/* Enable temperature compensation on mag sensor */
	lsm303agr_mag_offset_temp_comp_set(&dev_ctx_mg, PROPERTY_ENABLE);
	/* Enable temperature sensor */
	lsm303agr_temperature_meas_set(&dev_ctx_xl, LSM303AGR_TEMP_ENABLE);
	/* Set device in continuous mode */
	lsm303agr_xl_operating_mode_set(&dev_ctx_xl, LSM303AGR_HR_12bit);
	/* Set magnetometer in continuous mode */
	lsm303agr_mag_operating_mode_set(&dev_ctx_mg, LSM303AGR_CONTINUOUS_MODE);
}

/**
 * @brief Reads raw X-axis acceleration data from LSM303.
 * 
 * @return double Returns the raw X-axis acceleration value.
 */
 double lsm303_read_accel_rawX(){
	int16_t data_raw_acceleration[3];
	float acceleration_mg[3];
	/* Read accelerometer data */
    memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
    lsm303agr_acceleration_raw_get(&dev_ctx_xl, data_raw_acceleration);
    acceleration_mg[0] = lsm303agr_from_fs_2g_hr_to_mg(data_raw_acceleration[0]);
	return (double) acceleration_mg[0]; // <- Casting int16_t to double. Lets hope it works
}

/**
 * @brief Reads raw Y-axis acceleration data from LSM303.
 * 
 * @return double Returns the raw Y-axis acceleration value.
 */
 double lsm303_read_accel_rawY(){
	int16_t data_raw_acceleration[3];
	float acceleration_mg[3];
	/* Read accelerometer data */
    memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
    lsm303agr_acceleration_raw_get(&dev_ctx_xl, data_raw_acceleration);
    acceleration_mg[1] = lsm303agr_from_fs_2g_hr_to_mg(data_raw_acceleration[1]);
	return (double) acceleration_mg[1];
}

/**
 * @brief Reads raw Z-axis acceleration data from LSM303.
 * 
 * @return double Returns the raw Z-axis acceleration value.
 */
 double lsm303_read_accel_rawZ(){
	int16_t data_raw_acceleration[3];
	float acceleration_mg[3];
	/* Read accelerometer data */
    memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
    lsm303agr_acceleration_raw_get(&dev_ctx_xl, data_raw_acceleration);
    acceleration_mg[2] = lsm303agr_from_fs_2g_hr_to_mg(data_raw_acceleration[2]);
	return (double) acceleration_mg[2];
}

/**
 * @brief Reads raw X-axis magnetic data from LSM303.
 * 
 * @return double Returns the raw X-axis magnetic value.
 */
 double lsm303_read_mag_rawX(){
	int16_t data_raw_magnetic[3];
	float magnetic_mG[3];
	/* Read magnetic field data */
    memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
    lsm303agr_magnetic_raw_get(&dev_ctx_mg, data_raw_magnetic);
    magnetic_mG[0] = lsm303agr_from_lsb_to_mgauss(data_raw_magnetic[0]);
	return (double) data_raw_magnetic[0];
}

/**
 * @brief Reads raw Y-axis magnetic data from LSM303.
 * 
 * @return double Returns the raw Y-axis magnetic value.
 */
 double lsm303_read_mag_rawY(){
	 int16_t data_raw_magnetic[3];
	 float magnetic_mG[3];
	/* Read magnetic field data */
    memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
    lsm303agr_magnetic_raw_get(&dev_ctx_mg, data_raw_magnetic);
    magnetic_mG[1] = lsm303agr_from_lsb_to_mgauss(data_raw_magnetic[1]);
	return (double) data_raw_magnetic[1];
}

/**
 * @brief Reads raw Z-axis magnetic data from LSM303.
 * 
 * @return double Returns the raw Z-axis magnetic value.
 */
double lsm303_read_mag_rawZ(){
	int16_t data_raw_magnetic[3];
	float magnetic_mG[3];
	/* Read magnetic field data */
    memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
    lsm303agr_magnetic_raw_get(&dev_ctx_mg, data_raw_magnetic);
    magnetic_mG[2] = lsm303agr_from_lsb_to_mgauss(data_raw_magnetic[2]);
	return (double) data_raw_magnetic[2];
}

/**
 * @brief Reads raw temperature data from LSM303.
 * 
 * @return double Returns the raw temperature data value.
 */
double lsm303_read_temp(){
	float temperature_degC;
	/* Read temperature data */
    memset(&data_raw_temperature, 0x00, sizeof(int16_t));
    lsm303agr_temperature_raw_get(&dev_ctx_xl, &data_raw_temperature);
    temperature_degC = lsm303agr_from_lsb_hr_to_celsius(data_raw_temperature);
	return (double) temperature_degC;
}