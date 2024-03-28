#include "driver_bmp280_interface.h"

/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t bmp280_interface_iic_init(void)
{
    //Only check the acc bus because both acc and gyro are on the same bus
    if (!device_is_ready(dev_i2c_270.bus)) {
		printf("I2C bus %s is not ready!\n\r",dev_i2c_270.bus->name);
		return;
	}
    return 0;
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t bmp280_interface_iic_deinit(void)
{   
    return 0;
}

/**
 * @brief      interface iic bus read
 * @param[in]  addr is the iic device write address
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bmp280_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t write_buf[1] = {reg_addr};
    int ret = i2c_write_read_dt(&sensor, write_buf, sizeof(write_buf), buf, len);
    if (ret != 0) {
        printf("Failed to write/read I2C device address");
    }
    return 0;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr is the iic device write address
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t bmp280_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t dt[256];
    dt[0] = reg;
    for(int i = 0; i < len; i++) {
        dt[i+1] = buf[i];
    }
    int ret = i2c_write_dt(&sensor, dt, len + 1);
    if(ret != 0) {
        printf("Failed to write to I2C device address");
    }
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void bmp280_interface_delay_ms(uint32_t ms)
{
    k_msleep(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void bmp280_interface_debug_print(const char *const fmt, ...)
{
    
}