#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "BM1088 Module";

#define I2C_MASTER_SCL_IO           22                         /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21                         /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define BM1088_ACCEL_ADDRESS                 0x18        /*!< Slave address of the BM1088_acceleromter sensor SD01 pull to GND */
#define BM1088_GYRO_ADDRESS                  0x68        /*!< Slave address of the BM1088 gyroscope sensor SD02 pull to GND*/
int ret = 0;

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
int accel_x_int16 = 0;
int accel_y_int16 = 0;
int accel_z_int16 = 0;


 int gyro_x_int16 = 0;
 int gyro_y_int16 = 0;
 int gyro_z_int16 = 0;


/**
 * @brief Convertion of BM1088 accel and gyro Sensors  signed integer into acceleration
 */
int accel_x_in_mg = 0;
int accel_y_in_mg = 0;
int accel_z_in_mg = 0;

/**
 * @brief calculate BM1088 data in signed form  from LSB into Degree per second
 */
 int gyro_x_in_degree = 0;
 int gyro_y_in_degree = 0;
 int gyro_z_in_degree = 0;

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
static esp_err_t bm1088_accel_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        ret = i2c_master_write_read_device(I2C_MASTER_NUM, BM1088_ACCEL_ADDRESS, (&reg_addr + i), 1,
                                     (data + i), 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS );
    }    
    return ret;
}

/**
 * @brief Read a sequence of bytes from a BM1088 gyro sensor registers
 */
static esp_err_t bm1088_gyro_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        ret = i2c_master_write_read_device(I2C_MASTER_NUM, BM1088_GYRO_ADDRESS, (&reg_addr + i), 1,
                                     (data + i), 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS );
    }
    return ret;

}

/**
 * @brief Write a byte to a BM1088 accel sensor register
 */
static esp_err_t bm1088_accel_write_byte(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM, BM1088_ACCEL_ADDRESS, write_buf, sizeof(write_buf),
                                      I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}

/**
 * @brief Write a byte to a BM1088 gyro sensor register
 
static esp_err_t bm1088_gyro_write_byte(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM, BM1088_GYRO_ADDRESS, write_buf, sizeof(write_buf),
                                      I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}
**/

/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

/**
 * @brief BM1088 initialization
 */
void bm1088_init(void *pvParameters)
{

    while(1)
    {
        /* Obtain the current timestamp */
        int64_t current_timestamp = esp_timer_get_time();
        /* Calculate dt (time elapsed since the last measurement) */
        int64_t dt = current_timestamp - previous_timestamp;

        /* Read the BM1088 accelerometer registers data sequencially */
        ESP_ERROR_CHECK(bm1088_accel_read(ACC_X_LSB, accel_x, 2));
        ESP_ERROR_CHECK(bm1088_accel_read(ACC_Y_LSB, accel_y, 2));
        ESP_ERROR_CHECK(bm1088_accel_read(ACC_Z_LSB, accel_z, 2));

        /* Read the BM1088 gyroscope registers data sequencially */
        ESP_ERROR_CHECK(bm1088_gyro_read(GYRO_X_LSB, gyro_x, 2));
        ESP_ERROR_CHECK(bm1088_gyro_read(GYRO_Y_LSB, gyro_y, 2));
        ESP_ERROR_CHECK(bm1088_gyro_read(GYRO_Z_LSB, gyro_z, 2));

        /* calculate BM1088 accel data in signed form  */
        accel_x_int16 =((((int)accel_x[1]) * 256) + ((int)accel_x[0]));
        accel_y_int16 =((((int)accel_y[1]) * 256) + ((int)accel_y[0]));
        accel_z_int16 =((((int)accel_z[1]) * 256) + ((int)accel_z[0]));

        /* calculate BM1088 gyro data in signed form  */
        gyro_x_int16 =((((int)gyro_x[1]) * 256) + ((int)gyro_x[0]));
        gyro_y_int16 =((((int)gyro_x[1]) * 256) + ((int)gyro_x[0]));
        gyro_z_int16 =((((int)gyro_x[1]) * 256) + ((int)gyro_x[0]));

        /* calculate BM1088 data in signed form  from LSB into acceleration (mg) */
        accel_x_in_mg = ((accel_x_int16)/(32768 * 1000 * pow(2, 0x01 + 1)*1.5));
        accel_y_in_mg = ((accel_y_int16)/(32768 * 1000 * pow(2, 0x01 + 1)*1.5));
        accel_y_in_mg = ((accel_z_int16)/(32768 * 1000 * pow(2, 0x01 + 1)*1.5));
        ESP_LOGI(TAG, "accel_x_in_mg  %d", accel_x_in_mg);
        ESP_LOGI(TAG, "accel_y_in_mg  %d", accel_y_in_mg);
        ESP_LOGI(TAG, "accel_z_in_mg  %d", accel_z_in_mg);

        ESP_LOGI(TAG, "accel_x_int16  %d", accel_x_int16);
        ESP_LOGI(TAG, "accel_y_int16  %d", accel_y_int16);
        ESP_LOGI(TAG, "accel_z_int16  %d", accel_z_int16);

        ESP_LOGI(TAG, "gyro_x_int16  %d", gyro_x_int16);
        ESP_LOGI(TAG, "gyro_y_int16  %d", gyro_y_int16);
        ESP_LOGI(TAG, "gyro_z_int16  %d", gyro_z_int16);
        
        /* calculate BM1088 data in signed form  from LSB into Degree per second */
        gyro_x_in_degree = ((gyro_x_int16)*((2000)/(32767)));
        gyro_y_in_degree = ((gyro_y_int16)*((2000)/(32767)));
        gyro_z_in_degree = ((gyro_z_int16)*((2000)/(32767)));

        pitch_acc = atan2(accel_y_in_mg, accel_z_in_mg);
        roll_acc = atan2(-accel_x_in_mg, sqrt(accel_y_in_mg * accel_y_in_mg + accel_z_in_mg * accel_z_in_mg));

        ESP_LOGI(TAG, "gyro_x_in_degree  %d", gyro_x_in_degree);
        ESP_LOGI(TAG, "gyro_y_in_degree  %d", gyro_y_in_degree);
        ESP_LOGI(TAG, "gyro_z_in_degree  %d", gyro_z_in_degree);
        ESP_LOGI(TAG, "pitch_acc  %lf", pitch_acc);
        ESP_LOGI(TAG, "roll_acc  %lf", roll_acc);

        gyro_x_rad = gyro_x_in_degree * (M_PI / 180.0);
        gyro_y_rad = gyro_y_in_degree * (M_PI / 180.0);
        gyro_z_rad = gyro_z_in_degree * (M_PI / 180.0);


        ESP_LOGI(TAG, "gyro_x_rad  %lf", gyro_x_rad);
        ESP_LOGI(TAG, "gyro_y_rad  %lf", gyro_y_rad);
        ESP_LOGI(TAG, "gyro_z_rad  %lf", gyro_z_rad);

        /* Complementary filter equations */ 
        pitch = 0.98 * (pitch + gyro_x_rad * dt) + 0.02 * pitch_acc;
        roll = 0.98 * (roll + gyro_y_rad * dt) + 0.02 * roll_acc;
        yaw += gyro_z_rad * dt;

        ESP_LOGI(TAG, "pitch  %lf", pitch);
        ESP_LOGI(TAG, "yaw  %lf", yaw);
        ESP_LOGI(TAG, "roll  %lf", roll);

        /* Update previous angles */ 
        prev_yaw = yaw;
        prev_pitch = pitch;
        prev_roll = roll;

        /* Update the previous timestamp for the next iteration  */
        previous_timestamp = current_timestamp;

        vTaskDelay(80000/ portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    uint8_t data[2];
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    /* Read the BM1088 GYRO_CHIP_ID REGISTER, on power up the register should have the value 0x0F */
    ESP_ERROR_CHECK(bm1088_gyro_read(GYRO_CHIP_ID, data, 1));
    ESP_LOGI(TAG, "GYRO_CHIP_ID_REGISTER_VALUE = %X", data[0]);

    /* Read the BM1088 ACC_PWR_CTRL REGISTER to check power on reset */
    uint8_t check_por[2];
    ESP_ERROR_CHECK(bm1088_accel_read(ACC_PWR_CTRL, check_por, 1));
    vTaskDelay(1/ portTICK_PERIOD_MS);

    /* Enable accel module by writing 0x04 to power control register */
    uint8_t acc_pwr_ctr = 0x04;
    acc_pwr_ctr |= check_por[0];

    ESP_ERROR_CHECK(bm1088_accel_write_byte(ACC_PWR_CTRL, acc_pwr_ctr));
    vTaskDelay(50/ portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(bm1088_accel_read(ACC_PWR_CTRL, check_por, 1));
    
    if (check_por[0] == acc_pwr_ctr)
    {
        ESP_LOGI(TAG, "Accelerometer configured successfully");
    }
    else ESP_LOGI(TAG, "Accelerometer not configured ");

    xTaskCreate(bm1088_init, "BM1088 MODULE", 4*1024, NULL, 5, NULL);
}
