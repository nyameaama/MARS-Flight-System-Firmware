#include"icm42688.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "icm-42688_p";

#define I2C_MASTER_SCL_IO           22                         /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21                         /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define icm42688p_address                   0x68        /*!< Slave address of the icm42688p sensor */
#define icm42688p_WHO_AM_I_REG_ADDR         0x75        /*!< Register addresses of the "who am I" register */

#define icm42688p_PWR_MGMT_REG_ADDR         0x6E        /*!< Register addresses of the power managment register */
int ret = 0;

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
    ACC_X_LSB      = 0X20,
    ACC_X_MSB      = 0X1F,
    ACC_Y_LSB      = 0X22,
    ACC_Y_MSB      = 0X21,
    ACC_Z_LSB      = 0X24,
    ACC_Z_MSB      = 0X23,
    GYRO_X_LSB     = 0X26,
    GYRO_X_MSB     = 0X25,
    GYRO_Y_LSB     = 0X28,
    GYRO_Y_MSB     = 0X27,
    GYRO_Z_LSB     = 0X2A,
    GYRO_Z_MSB     = 0X29,

}icm42688p_register_address;

/**
* @brief Read a sequence of bytes from a BM1088 accel sensor registers
*/
esp_err_t icm42688p_register_read(uint8_t reg_addr, uint8_t *data, size_t len){
    for (size_t i = 0; i < len; i++) {
        ret = i2c_master_write_read_device(i2c_port_t(I2C_MASTER_NUM), icm42688p_address, &reg_addr, 1,
            data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS );
    }    
    return ret;
}

esp_err_t icm42688p_register_write_byte(uint8_t reg_addr, uint8_t data){
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(i2c_port_t(I2C_MASTER_NUM), icm42688p_address, write_buf, sizeof(write_buf),
                                      I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}

esp_err_t i2c_master_init(void){
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

void ICM_INIT(){
    uint8_t data[1];
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    /* Read the icm42688p WHO_AM_I register, on power up the register should have the value 0x47 */
    ESP_ERROR_CHECK(icm42688p_register_read(icm42688p_WHO_AM_I_REG_ADDR, data, 1));
    ESP_LOGI(TAG, "WHO_AM_I = %X", data[0]);

    /* Accel mode to low noise and gyro to standby mode to on both sensors */
	uint8_t read_sensor_mode;
	ESP_ERROR_CHECK(icm42688p_register_read(icm42688p_PWR_MGMT_REG_ADDR, &read_sensor_mode, 1));
    read_sensor_mode |= 0x03 << 0;

    ESP_ERROR_CHECK(icm42688p_register_write_byte(icm42688p_PWR_MGMT_REG_ADDR, read_sensor_mode));
	vTaskDelay(50 / portTICK_PERIOD_MS);
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
    ESP_ERROR_CHECK(icm42688p_register_read(ACC_X_LSB, accel_x_LSB, 2));
    ESP_ERROR_CHECK(icm42688p_register_read(ACC_X_MSB, accel_x_MSB, 2));
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
    ESP_ERROR_CHECK(icm42688p_register_read(ACC_Y_LSB, accel_y_LSB, 2));
    ESP_ERROR_CHECK(icm42688p_register_read(ACC_Y_MSB, accel_y_MSB, 2));
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
    ESP_ERROR_CHECK(icm42688p_register_read(ACC_Z_LSB, accel_z_LSB, 2));
    ESP_ERROR_CHECK(icm42688p_register_read(ACC_Z_MSB, accel_z_MSB, 2));
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
    ESP_ERROR_CHECK(icm42688p_register_read(GYRO_X_LSB, gyro_x_LSB, 2));
    ESP_ERROR_CHECK(icm42688p_register_read(GYRO_X_MSB, gyro_x_MSB, 2));
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
    ESP_ERROR_CHECK(icm42688p_register_read(GYRO_Y_LSB, gyro_y_LSB, 2));
    ESP_ERROR_CHECK(icm42688p_register_read(GYRO_Y_MSB, gyro_y_MSB, 2));
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
    ESP_ERROR_CHECK(icm42688p_register_read(GYRO_Z_LSB, gyro_z_LSB, 2));
    ESP_ERROR_CHECK(icm42688p_register_read(GYRO_Z_MSB, gyro_z_MSB, 2));
    lsb = gyro_z_LSB[0];
    msb = gyro_z_MSB[0];
    msblsb = (msb << 8) | lsb;
    float z_original_int = ((int16_t) msblsb); /* Data in Z axis */
    float z = lsb_to_dps(z_original_int, (float)250, 16);
    return z;
}