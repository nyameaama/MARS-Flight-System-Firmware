#include"icm42688.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define ICM_IMU DT_NODELABEL(icm42688)
static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(ICM_IMU);

#define icm42688p_address                   0x68        /*!< Slave address of the icm42688p sensor */
#define icm42688p_WHO_AM_I_REG_ADDR         0x75        /*!< Register addresses of the "who am I" register */

#define icm42688p_PWR_MGMT_REG_ADDR         0x6E        /*!< Register addresses of the power managment register */
int ret = 0;
uint8_t _bank = 0; ///< current user bank

/*! Earth's gravity in m/s^2 */
#define GRAVITY_EARTH  (9.80665f)

/**
 * @brief Memory locations to store icm42688p accel and gyro Sensors data
 */
uint8_t accel_x_LSB[2] = {0};
uint8_t accel_x_MSB[2] = {0};
uint8_t accel_y_LSB[2] = {0};
uint8_t accel_y_MSB[2] = {0};
uint8_t accel_z_LSB[2] = {0};
uint8_t accel_z_MSB[2] = {0};

uint8_t gyro_x_LSB[2] = {0};
uint8_t gyro_x_MSB[2] = {0};
uint8_t gyro_y_LSB[2] = {0};
uint8_t gyro_y_MSB[2] = {0};
uint8_t gyro_z_LSB[2] = {0};
uint8_t gyro_z_MSB[2] = {0};

/**
 * @brief Convertion of icm42688p accel and gyro Sensors data into signed integer
 */
float accel_x_int16 = 0;
float accel_y_int16 = 0;
float accel_z_int16 = 0;


float gyro_x_int16 = 0;
float gyro_y_int16 = 0;
float gyro_z_int16 = 0;

/**
 * @brief icm42688p IMU Register Addresses
 */
typedef enum
{
    ACC_X_LSB      = 0x20,
    ACC_X_MSB      = 0x1F,
    ACC_Y_LSB      = 0x22,
    ACC_Y_MSB      = 0x21,
    ACC_Z_LSB      = 0x24,
    ACC_Z_MSB      = 0x23,
    GYRO_X_LSB     = 0x26,
    GYRO_X_MSB     = 0x25,
    GYRO_Y_LSB     = 0x28,
    GYRO_Y_MSB     = 0x27,
    GYRO_Z_LSB     = 0x2A,
    GYRO_Z_MSB     = 0x29,
    UB0_REG_DEVICE_CONFIG = 0x11,
    REG_BANK_SEL   = 0x76,

}icm42688p_register_address;

/**
* @brief Read a sequence of bytes from sensor registers
*/
void icm42688p_register_read(uint8_t reg_addr, uint8_t *data, size_t len){
    uint8_t write_buf[1] = {reg_addr};
    int ret = i2c_write_read_dt(&dev_i2c, write_buf, sizeof(write_buf), data, len);
    if (ret != 0) {
        printk("Failed to write/read I2C device address");
    }
}

/**
* @brief Write a byte to sensor register
*/

void icm42688p_register_write_byte(uint8_t reg_addr, uint8_t data){
    uint8_t msg[2] = {reg_addr, data};
	ret = i2c_write_dt(&dev_i2c, msg, sizeof(data));
	if(ret != 0){
		printk("Failed to write to I2C device address");
	}
}

/**
* @brief i2c master initialization
*/
void i2c_master_init(void){
    //Only check the acc bus because both acc and gyro are on the same bus
    if (!device_is_ready(dev_i2c.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
		return;
	}
}

void ICM_INIT(){
    uint8_t data[1];
    i2c_master_init();
    printf("I2C initialized successfully");

    reset();

    /* Read the icm42688p WHO_AM_I register, on power up the register should have the value 0x47 */
    icm42688p_register_read(icm42688p_WHO_AM_I_REG_ADDR, data, 1);
    printf("WHO_AM_I = %X", data[0]);

    /* Accel mode to low noise and gyro to standby mode to on both sensors */
	uint8_t read_sensor_mode;
	icm42688p_register_read(icm42688p_PWR_MGMT_REG_ADDR, &read_sensor_mode, 1);
    read_sensor_mode |= 0x03 << 0;

    icm42688p_register_write_byte(icm42688p_PWR_MGMT_REG_ADDR, read_sensor_mode);
	k_msleep(50);
}

//void setBank(uint8_t bank){
     // if we are already on this bank, bail
    //if (_bank == bank) return 1;

    //_bank = bank;

    //icm42688p_register_write_byte(REG_BANK_SEL, bank);
//}

void reset(){
    //setBank(0);

    icm42688p_register_write_byte(UB0_REG_DEVICE_CONFIG, 0x01);

    // wait for ICM42688 to come back up
    k_msleep(1);
}

/*!
 * @brief This function converts lsb to meter per second squared for 16 bit accelerometer at
 * range 2G, 4G, 8G or 16G.
 */
float lsb_to_mps2(int16_t val, int8_t g_range, uint8_t bit_width)
{
    double power = 2;

    float half_scale = (float)((pow((double)power, (double)bit_width) / 2.0f));

    return (GRAVITY_EARTH * val * g_range) / half_scale;
}

/*!
 * @brief This function converts lsb to degree per second for 16 bit gyro at
 * range 125, 250, 500, 1000 or 2000dps.
 */
float lsb_to_dps(int16_t val, float dps, uint8_t bit_width)
{
    double power = 2;

    float half_scale = (float)((pow((double)power, (double)bit_width) / 2.0f));

    return (dps / (half_scale)) * (val);
}

/*!
 * @brief This function reads raw accel_x LSB data and converts to degree per second
 */
double accel_read_rawX(){
    uint8_t lsb, msb;
    uint16_t msblsb;
    icm42688p_register_read(ACC_X_LSB, accel_x_LSB, 2);
    icm42688p_register_read(ACC_X_MSB, accel_x_MSB, 2);
    lsb = accel_x_LSB[0];
    msb = accel_x_MSB[0];
    msblsb = (msb << 8) | lsb;
    float x_original_int = ((int16_t) msblsb); /* Data in X axis */
    float x = lsb_to_mps2(x_original_int, 24, 16);
    return x;
}

/*!
 * @brief This function reads raw accel_y LSB data and converts to degree per second
 */
double accel_read_rawY(){
    uint8_t lsb, msb;
    uint16_t msblsb;
    icm42688p_register_read(ACC_Y_LSB, accel_y_LSB, 2);
    icm42688p_register_read(ACC_Y_MSB, accel_y_MSB, 2);
    lsb = accel_y_LSB[0];
    msb = accel_y_MSB[0];
    msblsb = (msb << 8) | lsb;
    float y_original_int = ((int16_t) msblsb); /* Data in Y axis */
    float y = lsb_to_mps2(y_original_int, 24, 16);
    return y;
}

/*!
 * @brief This function reads raw accel_z LSB data and converts to degree per second
 */
double accel_read_rawZ(){
    uint8_t lsb, msb;
    uint16_t msblsb;
    icm42688p_register_read(ACC_Z_LSB, accel_z_LSB, 2);
    icm42688p_register_read(ACC_Z_MSB, accel_z_MSB, 2);
    lsb = accel_z_LSB[0];
    msb = accel_z_MSB[0];
    msblsb = (msb << 8) | lsb;
    float z_original_int = ((int16_t) msblsb); /* Data in Z axis */
    float z = lsb_to_mps2(z_original_int, 24, 16);
    return z;
}

/*!
 * @brief This function reads raw gyro_x LSB data and converts to degree per second
 */
double gyro_read_rawX(){
    uint8_t lsb, msb;
    uint16_t msblsb;
    icm42688p_register_read(GYRO_X_LSB, gyro_x_LSB, 2);
    icm42688p_register_read(GYRO_X_MSB, gyro_x_MSB, 2);
    lsb = gyro_x_LSB[0];
    msb = gyro_x_MSB[0];
    msblsb = (msb << 8) | lsb;
    float x_original_int = ((int16_t) msblsb); /* Data in X axis */
    float x = lsb_to_dps(x_original_int, (float)250, 16);
    return x;
}

/*!
 * @brief This function reads raw gyro_y LSB data and converts to degree per second
 */
double gyro_read_rawY(){
    uint8_t lsb, msb;
    uint16_t msblsb;
    icm42688p_register_read(GYRO_Y_LSB, gyro_y_LSB, 2);
    icm42688p_register_read(GYRO_Y_MSB, gyro_y_MSB, 2);
    lsb = gyro_y_LSB[0];
    msb = gyro_y_MSB[0];
    msblsb = (msb << 8) | lsb;
    float y_original_int = ((int16_t) msblsb); /* Data in Y axis */
    float y = lsb_to_dps(y_original_int, (float)250, 16);
    return y;
}

/*!
 * @brief This function reads raw gyro_z LSB data and converts to degree per second
 */
double gyro_read_rawZ(){
    uint8_t lsb, msb;
    uint16_t msblsb;
    icm42688p_register_read(GYRO_Z_LSB, gyro_z_LSB, 2);
    icm42688p_register_read(GYRO_Z_MSB, gyro_z_MSB, 2);
    lsb = gyro_z_LSB[0];
    msb = gyro_z_MSB[0];
    msblsb = (msb << 8) | lsb;
    float z_original_int = ((int16_t) msblsb); /* Data in Z axis */
    float z = lsb_to_dps(z_original_int, (float)250, 16);
    return z;
}