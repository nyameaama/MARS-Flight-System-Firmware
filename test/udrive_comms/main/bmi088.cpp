#include "bmi088.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"

#define I2C_MASTER_SCL_IO           22                         /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21                         /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define BM1088_ACCEL_ADDRESS                 0x18        /*!< Slave address of the BM1088_acceleromter sensor SD01 pull to GND */
#define BM1088_GYRO_ADDRESS                  0x68        /*!< Slave address of the BM1088 gyroscope sensor SD02 pull to GND*/
int16_t ret = 0;

/*! Earth's gravity in m/s^2 */
#define GRAVITY_EARTH  (9.80665f)

static const char *TAG = "BM1088 Module";

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


/**
* @brief Read a sequence of bytes from a BM1088 accel sensor registers
*/
esp_err_t BMI088_IMU::bm1088_accel_read(uint8_t reg_addr, uint8_t *data, size_t len){
    for (size_t i = 0; i < len; i++) {
        ret = i2c_master_write_read_device(i2c_port_t(I2C_MASTER_NUM), BM1088_ACCEL_ADDRESS, &reg_addr, 1,
            data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS );
    }    
    return ret;
}

/**
* @brief Read a sequence of bytes from a BM1088 gyro sensor registers
*/
esp_err_t BMI088_IMU::bm1088_gyro_read(uint8_t reg_addr, uint8_t *data, size_t len){
    for (size_t i = 0; i < len; i++) {
        ret = i2c_master_write_read_device(i2c_port_t(I2C_MASTER_NUM), BM1088_GYRO_ADDRESS, &reg_addr, 1,
            data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS );
    }
    return ret;
}

/**
* @brief Write a byte to a BM1088 accel sensor register
*/
esp_err_t BMI088_IMU::bm1088_accel_write_byte(uint8_t reg_addr, uint8_t data){
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(i2c_port_t(I2C_MASTER_NUM), BM1088_ACCEL_ADDRESS, write_buf, sizeof(write_buf),
                                      I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}

/**
* @brief Write a byte to a BM1088 gyro sensor register
*/
esp_err_t BMI088_IMU::bm1088_gyro_write_byte(uint8_t reg_addr, uint8_t data){
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(i2c_port_t(I2C_MASTER_NUM), BM1088_GYRO_ADDRESS, write_buf, sizeof(write_buf),
                                      I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}

/**
* @brief i2c master initialization
*/
esp_err_t BMI088_IMU::i2c_master_init(void){
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = 0;


    i2c_param_config(i2c_port_t(i2c_master_port), &conf);

    return i2c_driver_install(i2c_port_t(i2c_master_port), conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}