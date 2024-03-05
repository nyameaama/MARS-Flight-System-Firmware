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

#include "bmi088.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define ACCEL DT_NODELABEL(bmi088_acc)
#define GYRO DT_NODELABEL(bmi088_gyro)

static const struct i2c_dt_spec dev_i2c_acc = I2C_DT_SPEC_GET(ACCEL);
static const struct i2c_dt_spec dev_i2c_gyro = I2C_DT_SPEC_GET(GYRO);

#define BM1088_ACCEL_ADDRESS                 0x18        /*!< Slave address of the BM1088_acceleromter sensor SD01 pull to GND */
#define BM1088_GYRO_ADDRESS                  0x68        /*!< Slave address of the BM1088 gyroscope sensor SD02 pull to GND*/
int16_t ret = 0;

/*! Earth's gravity in m/s^2 */
#define GRAVITY_EARTH  (9.80665f)

/**
 * @brief Memory locations to store BM1088 accel and gyro Sensors data
 */
uint8_t accel_x[2] = {0};
uint8_t accel_y[2] = {0};
uint8_t accel_z[2] = {0};

uint8_t gyro_x[2] = {0};
uint8_t gyro_y[2] = {0};
uint8_t gyro_z[2] = {0};

/**
 * @brief Convertion of BM1088 accel and gyro Sensors data into signed integer
 */
float accel_x_int16 = 0;
float accel_y_int16 = 0;
float accel_z_int16 = 0;


 float gyro_x_int16 = 0;
 float gyro_y_int16 = 0;
 float gyro_z_int16 = 0;


/**
 * @brief Convertion of BM1088 accel and gyro Sensors  signed integer into acceleration
 */
float accel_x_in_mg = 0;
float accel_y_in_mg = 0;
float accel_z_in_mg = 0;

/**
 * @brief calculate BM1088 data in signed form  from LSB into Degree per second
 */
 float gyro_x_in_degree = 0;
 float gyro_y_in_degree = 0;
 float gyro_z_in_degree = 0;

/**
 * @brief Initialize angles
 */  
double yaw = 0.0;
double pitch = 0.0;
double roll = 0.0;

/**
 * @brief Initialize previous angles
 */
double prev_yaw = 0.0;
double prev_pitch = 0.0;
double prev_roll = 0.0;  

/**
 * @brief Initialize the previous timestamp
 */
int64_t previous_timestamp = 0;

/* Initialize other variables */
double pitch_acc = 0.0;
double roll_acc = 0.0;
double gyro_x_rad = 0.0; 
double gyro_y_rad = 0.0;  
double gyro_z_rad = 0.0; 

/**
 * @brief BM1088 IMU Register Addresses
 */
typedef enum
{
    ACC_CHIP_ID    = 0X00,
    ACC_ERR_REG    = 0X02,
    ACC_STATUS     = 0X03,
    ACC_X_LSB      = 0X12,
    ACC_X_MSB      = 0X13,
    ACC_Y_LSB      = 0X14,
    ACC_Y_MSB      = 0X15,
    ACC_Z_LSB      = 0X16,
    ACC_Z_MSB      = 0X17,
    ACC_CONF       = 0X40,
    ACC_RANGE      = 0X41,
    ACC_SELF_TEST  = 0X6D,
    ACC_PWR_CONF   = 0X7C,
    ACC_PWR_CTRL   = 0X7D,
    ACC_SOFT_REST  = 0X7E,
    GYRO_CHIP_ID   = 0X00,
    GYRO_X_LSB     = 0X02,
    GYRO_X_MSB     = 0X03,
    GYRO_Y_LSB     = 0X04,
    GYRO_Y_MSB     = 0X05,
    GYRO_Z_LSB     = 0X06,
    GYRO_Z_MSB     = 0X07,
    GYRO_RANGE     = 0X0F,
    GYRO_BANDWIDTH = 0X10,
    GYRO_LPM1      = 0X11,
    GYRO_SOFT_REST = 0X14,
    GYRO_SELF_TEST = 0X3C,

}mpu_register_address;

void IMU_INIT(){
    uint8_t data[2];
    i2c_master_init();
    printk("I2C initialized successfully");

    /* Read the BM1088 GYRO_CHIP_ID REGISTER, on power up the register should have the value 0x0F */
    bm1088_gyro_read(GYRO_CHIP_ID, data, 1);
    printk("GYRO_CHIP_ID_REGISTER_VALUE = %X", data[0]);

    /* Read the BM1088 ACC_PWR_CTRL REGISTER to check power on reset */
    uint8_t check_por[2];
    bm1088_accel_read(ACC_PWR_CTRL, check_por, 1);
    k_msleep(5);

    /* Enable accel module by writing 0x04 to power control register */
    uint8_t acc_pwr_ctr = 0x04;
    acc_pwr_ctr |= check_por[0];

    bm1088_accel_write_byte(ACC_PWR_CTRL, acc_pwr_ctr);
    k_msleep(5);
    bm1088_accel_read(ACC_PWR_CTRL, check_por, 1);
    
    if (check_por[0] == acc_pwr_ctr)
    {
        printk("Accelerometer configured successfully");
    }
    else printk("Accelerometer not configured ");
}

/**
* @brief Read a sequence of bytes from a BM1088 accel sensor registers
*/
void bm1088_accel_read(uint8_t reg_addr, uint8_t *data, size_t len){
    uint8_t write_buf[1] = {reg_addr};
    int ret = i2c_write_read_dt(&dev_i2c_acc, write_buf, sizeof(write_buf), data, len);
    if (ret != 0) {
        printk("Failed to write/read I2C device address");
    }
}

/**
* @brief Read a sequence of bytes from a BM1088 gyro sensor registers
*/
void bm1088_gyro_read(uint8_t reg_addr, uint8_t *data, size_t len){
    uint8_t write_buf[1] = {reg_addr};
    int ret = i2c_write_read_dt(&dev_i2c_gyro, write_buf, sizeof(write_buf), data, len);
    if (ret != 0) {
        printk("Failed to write/read I2C device address");
    }
}

/**
* @brief Write a byte to a BM1088 accel sensor register
*/
void bm1088_accel_write_byte(uint8_t reg_addr, uint8_t data){
    uint8_t msg[2] = {reg_addr, data};
	ret = i2c_write_dt(&dev_i2c_acc, msg, sizeof(data));
	if(ret != 0){
		printk("Failed to write to I2C device address");
	}
}

/**
* @brief Write a byte to a BM1088 gyro sensor register
*/
void bm1088_gyro_write_byte(uint8_t reg_addr, uint8_t data){
    uint8_t msg[2] = {reg_addr, data};
	ret = i2c_write_dt(&dev_i2c_acc, msg, sizeof(data));
	if(ret != 0){
		printk("Failed to write to I2C device address");
	}
}

/**
* @brief i2c master initialization
*/
void i2c_master_init(void){
    //Only check the acc bus because both acc and gyro are on the same bus
    if (!device_is_ready(dev_i2c_acc.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c_acc.bus->name);
		return;
	}
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
    bm1088_accel_read(ACC_X_LSB, accel_x, 2);
    lsb = accel_x[0];
    msb = accel_x[1];
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
    bm1088_accel_read(ACC_Y_LSB, accel_y, 2);
    lsb = accel_y[0];
    msb = accel_y[1];
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
    bm1088_accel_read(ACC_Z_LSB, accel_z, 2);
    lsb = accel_z[0];
    msb = accel_z[1];
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
    bm1088_gyro_read(GYRO_X_LSB, gyro_x, 2);
    lsb = gyro_x[0];
    msb = gyro_x[1];
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
    bm1088_gyro_read(GYRO_Y_LSB, gyro_y, 2);
    lsb = gyro_y[0];
    msb = gyro_y[1];
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
    bm1088_gyro_read(GYRO_Z_LSB, gyro_z, 2);
    lsb = gyro_z[0];
    msb = gyro_z[1];
    msblsb = (msb << 8) | lsb;
    float z_original_int = ((int16_t) msblsb); /* Data in Z axis */
    float z = lsb_to_dps(z_original_int, (float)250, 16);
    return z;
}

double angle_read_pitch(){
    double x_Buff = accel_read_rawX();
    double y_Buff = accel_read_rawY();
    double z_Buff = accel_read_rawZ();
    double pitch = atan2((- x_Buff) , sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;
    return pitch;
}

double angle_read_roll(){
    double y_Buff = accel_read_rawY();
    double z_Buff = accel_read_rawZ();
    double roll = atan2(y_Buff , z_Buff) * 57.3;
    return roll;
}

double angle_read_yaw(){
    /*double previousTime, currentTime, elapsedTime;
    previousTime = esp_timer_get_time();        // Previous time is stored before the actual time read
    currentTime = esp_timer_get_time();           // Current time actual time read
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds

    double GyroZ = gyro_read_rawZ();
    
    double yaw = GyroZ * elapsedTime;
    return yaw;*/
}

double linearInterpolate(double input, double input_start, double input_end, 
                                        double output_start, double output_end) {
    // Map input range to output range
    double slope = (output_end - output_start) / (input_end - input_start);
    double output = output_start + slope * (input - input_start);
    return output;
}

double readAugmentedIMUData(uint8_t angle_type){
    //Roll -> -90 to 90 Augmented to Pitch -90 to 90
    //Pitch -> Augmented to Roll; Left = positive; Right = negative

    //The BMI088 IMU is not oriented in the same direction as the vehicle's
    //intended direction for accurate values so the data has to be augmented for
    //accurate angle results
    switch(angle_type){
        case PITCH:
            return -(angle_read_roll());
            break;
        case ROLL:
            return -(linearInterpolate(angle_read_pitch(), -90, 90, -180, 180));
            break;
        case YAW:
            return angle_read_yaw();
            break;
    }
    return 0;
}
