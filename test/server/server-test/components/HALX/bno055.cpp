
#include <stdio.h>
#include <string.h> // memset()
#include "esp_log.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BNO_SDA (gpio_num_t) 18
#define BNO_SCL (gpio_num_t) 19


#include "bno055.h"


#define I2C_MASTER_TX_BUF_DISABLE 0  // I2C master doesn't need buffer 
#define I2C_MASTER_RX_BUF_DISABLE 0  // I2C master doesn't need buffer 

#define WRITE_BIT I2C_MASTER_WRITE  // I2C master write 
#define READ_BIT I2C_MASTER_READ    // I2C master read 
#define ACK_CHECK_EN 0x1            // I2C master will check ack from slave
#define ACK_CHECK_DIS 0x0           // I2C master will not check ack from slave 
#define ACK_VAL 0x0                 // I2C ack value 
#define NACK_VAL 0x1                // I2C nack value 

   
static const char *TAG = "bno055";
   
    
typedef struct
{
    bno055_addr_t  i2c_address; // BNO055_ADDRESS_A or BNO055_ADDRESS_B
    bool  bno_is_open;
} bno055_device_t;


static bno055_device_t x_bno_dev[I2C_NUM_MAX];

static uint8_t x_buffer[200];  // we so far are using only 20 bytes max

// Internal functions

// _______________________________________________________________________
// | start | write chip_addr + wr_bit, chk_ack | write reg_addr, chk_ack |
// --------|-----------------------------------|-------------------------|
// ________________________________________________________________________
// | start | write chip_addr + rd_bit, chk_ack | read 1 byte, nack | stop |
// --------|-----------------------------------|-------------------|------|
esp_err_t bno055_read_register(i2c_port_t i2c_num, bno055_reg_t reg, uint8_t *p_reg_val){
    
    if( !x_bno_dev[i2c_num].bno_is_open) {
        ESP_LOGE(TAG, "bno055_read_register(): device is not open");
        return BNO_ERR_NOT_OPEN; //TODO: make error list
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    // making the command - begin 
    i2c_master_start(cmd);  // start condition
    // device address with write bit
    i2c_master_write_byte(cmd, (x_bno_dev[i2c_num].i2c_address << 1) | WRITE_BIT, ACK_CHECK_EN); 
    // send the register address
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);   
    i2c_master_start(cmd);  // start condition again
    // device address with read bit
    i2c_master_write_byte(cmd, (x_bno_dev[i2c_num].i2c_address << 1) | READ_BIT, ACK_CHECK_EN);   
    // read byte, issue NACK
    i2c_master_read_byte(cmd, p_reg_val, I2C_MASTER_NACK); 
    i2c_master_stop(cmd);  // stop condition
    // making the command - end 
    
    // Now execute the command
    esp_err_t err = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
    
    i2c_cmd_link_delete(cmd);
    
    switch (err) {
        case ESP_OK: 
            break;
        case  ESP_ERR_TIMEOUT:
            ESP_LOGE(TAG, "bno055_read_register(): i2c timeout");
            break;
        default: 
            ESP_LOGE(TAG, "bno055_read_register(): failed");
    }
    
    return err;   
}
  
// ______________________________________________________________________________________________________
// | start | write chip_addr + wr_bit, chk_ack | write reg_addr, chk_ack | write 1 byte, chk_ack | stop |
// --------|-----------------------------------|-------------------------|-----------------------|------|

 esp_err_t bno055_write_register(i2c_port_t i2c_num, bno055_reg_t reg, uint8_t reg_val){
    
    if( !x_bno_dev[i2c_num].bno_is_open) {
        ESP_LOGE(TAG, "bno055_write_register(): device is not open");
        return BNO_ERR_NOT_OPEN;
    }
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    // making the command - begin 
    i2c_master_start(cmd);  // start condition
    // device address with write bit
    i2c_master_write_byte(cmd, (x_bno_dev[i2c_num].i2c_address << 1) | WRITE_BIT, ACK_CHECK_EN); 
    // send the register address
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);   
    // write byte, issue NACK
    i2c_master_write_byte(cmd, reg_val, ACK_CHECK_EN); 
    i2c_master_stop(cmd);  // stop condition
    // making the command - end 
    
    // Now execute the command
    esp_err_t err = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
    
    i2c_cmd_link_delete(cmd);
    
    switch (err) {
        case ESP_OK: 
            break;
        case  ESP_ERR_TIMEOUT:
            ESP_LOGE(TAG, "bno055_write_register(): i2c timeout");
            break;
        default: 
            ESP_LOGE(TAG, "bno055_write_register(): failed");
    }
    
    return err;   
}
 
// _______________________________________________________________________
// | start | write chip_addr + wr_bit, chk_ack | write reg_addr, chk_ack |
// --------|-----------------------------------|-------------------------|
// ______________________________________________________________________________________________
// | start | write chip_addr + rd_bit, chk_ack | read n-1 bytes, ack | read 1 byte, nack | stop |
// --------|-----------------------------------|---------------------|-------------------|------|
 
esp_err_t bno055_read_data(i2c_port_t i2c_num, bno055_reg_t start_reg, uint8_t *buffer, uint8_t n_bytes){

    if( !x_bno_dev[i2c_num].bno_is_open) {
        ESP_LOGE(TAG, "bno055_read_data(): device is not open");
        return BNO_ERR_NOT_OPEN;
    }

    if( n_bytes < 2 || n_bytes > 0x7F ) {
        ESP_LOGE(TAG, "bno055_read_data(): invalid number of bytes: %d", n_bytes);
        return BNO_ERR_NOT_IN_RANGE;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    // making the command - begin 
    i2c_master_start(cmd);  // start condition
    // device address with write bit
    i2c_master_write_byte(cmd, (x_bno_dev[i2c_num].i2c_address << 1) | WRITE_BIT, ACK_CHECK_EN); 
    // send the register address
    i2c_master_write_byte(cmd, start_reg, ACK_CHECK_EN);   
    i2c_master_start(cmd);  // start condition again
    // device address with read bit
    i2c_master_write_byte(cmd, (x_bno_dev[i2c_num].i2c_address << 1) | READ_BIT, ACK_CHECK_EN);
    // read n_bytes-1, issue ACK
    i2c_master_read(cmd, buffer, n_bytes - 1, I2C_MASTER_ACK);
    // read the last byte, issue NACK
    i2c_master_read_byte(cmd, buffer+n_bytes-1, I2C_MASTER_NACK); 
    i2c_master_stop(cmd);  // stop condition
    // making the command - end 

    // Now execute the command
    esp_err_t err = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
    
    i2c_cmd_link_delete(cmd);
    
    switch (err) {
        case ESP_OK: 
        	break;
        case ESP_ERR_TIMEOUT:
            ESP_LOGE(TAG, "bno055_read_data(): i2c timeout");
            break;
        default: 
            ESP_LOGE(TAG, "bno055_read_data(): failed");
    }
    
    return err;   
}


// Public functions

esp_err_t bno055_set_default_conf(bno055_config_t * p_bno_conf){

    p_bno_conf->i2c_address = BNO055_ADDRESS_A;          // BNO055_ADDRESS_A or BNO055_ADDRESS_B 
    p_bno_conf->sda_io_num = BNO_SDA;        // GPIO number for I2C sda signal 25
    p_bno_conf->sda_pullup_en = GPIO_PULLUP_DISABLE;  // Internal GPIO pull mode for I2C sda signal
    p_bno_conf->scl_io_num = BNO_SCL;        // GPIO number for I2C scl signal 26 
    p_bno_conf->scl_pullup_en = GPIO_PULLUP_DISABLE;  // Internal GPIO pull mode for I2C scl signal
    p_bno_conf->clk_speed = 400000;     // I2C clock frequency for master mode, (no higher than 1MHz for now) 
    p_bno_conf->timeout = 10000*80;     // 10ms in 80 MHz ticks, should be < 0xFFFFF
    p_bno_conf->use_ext_oscillator = true; // Use external oscillator

    return ESP_OK;   
}



esp_err_t bno055_open(i2c_port_t i2c_num, bno055_config_t * p_bno_conf )
{
    if(i2c_num >= I2C_NUMBER_MAX) return ESP_ERR_INVALID_ARG;
    
    // Check if already in use
    if(x_bno_dev[i2c_num].bno_is_open) {
        ESP_LOGW(TAG, "bno055_open(): device is already open");
        return BNO_ERR_ALREADY_OPEN;
    }
    
    x_bno_dev[i2c_num].bno_is_open = 0;

    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = p_bno_conf->sda_io_num;        
    conf.sda_pullup_en = p_bno_conf->sda_pullup_en;  
    conf.scl_io_num = p_bno_conf->scl_io_num;        
    conf.scl_pullup_en = p_bno_conf->scl_pullup_en;  
    conf.master.clk_speed = p_bno_conf->clk_speed;
    
    esp_err_t err;
    
    err = i2c_param_config(i2c_num, &conf);
    ESP_LOGD(TAG, "i2c_param_config() returned 0x%02X", err);
    if( err != ESP_OK ) return err;
        
    err = i2c_driver_install(i2c_num, I2C_MODE_MASTER,
                              I2C_MASTER_RX_BUF_DISABLE,
                              I2C_MASTER_TX_BUF_DISABLE, 0);
    ESP_LOGD(TAG, "i2c_driver_install() returned 0x%02X", err);
    if( err != ESP_OK ) return err;
    
    err = i2c_set_timeout(i2c_num, p_bno_conf->timeout);
    ESP_LOGD(TAG, "i2c_set_timeout() returned 0x%02X", err);
    if( err != ESP_OK ) return err;
    
    x_bno_dev[i2c_num].i2c_address = (bno055_addr_t)p_bno_conf->i2c_address;
    
    // Read BNO055 Chip ID to make sure we have a connection
    x_bno_dev[i2c_num].bno_is_open = 1; // bno055_read_register() checks this flag
    uint8_t reg_val;
    err = bno055_read_register(i2c_num, BNO055_CHIP_ID_ADDR, & reg_val);
    
    if( err == ESP_OK ) {
        
        ESP_LOGD(TAG, "BNO055 ID returned 0x%02X", reg_val);
        if( reg_val == BNO055_ID ) {
            ESP_LOGI(TAG, "BNO055 detected \n");
        } 
        else {
            ESP_LOGE(TAG, "bno055_open() error: BNO055 NOT detected");
            goto errExit;
        }
    }
    
    
     // Switch to config mode
    err = bno055_write_register(i2c_num, BNO055_OPR_MODE_ADDR, OPERATION_MODE_CONFIG);
    if(err != ESP_OK) goto errExit;
    vTaskDelay(30 / portTICK_PERIOD_MS);
    ESP_LOGD(TAG, "Set config oper. mode - Ok");

    // Reset
    err=bno055_write_register(i2c_num, BNO055_SYS_TRIGGER_ADDR, 0x20 );
    if(err != ESP_OK) goto errExit;
    vTaskDelay(700 / portTICK_PERIOD_MS);
    ESP_LOGD(TAG, "BNO055 reset - Ok");

    // Set ext oscillator
    if(p_bno_conf->use_ext_oscillator) {
    	err=bno055_write_register(i2c_num, BNO055_SYS_TRIGGER_ADDR, 0x80);
        if(err != ESP_OK) goto errExit;
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    ESP_LOGD(TAG, "Set external oscillator - Ok");
    
    // TODO: turn off sleep mode
    
    // Set power mode to normal 
    err=bno055_write_register(i2c_num, BNO055_PWR_MODE_ADDR, POWER_MODE_NORMAL);
    if(err != ESP_OK) goto errExit;
    vTaskDelay(20 / portTICK_PERIOD_MS);
    ESP_LOGD(TAG, "Set normal power mode - Ok");

    return ESP_OK;   
    
errExit:
    bno055_close (i2c_num);
    return err;
}



esp_err_t bno055_close (i2c_port_t i2c_num )
{
    x_bno_dev[i2c_num].bno_is_open = 0;
    return i2c_driver_delete(i2c_num);
  
}

esp_err_t bno055_get_chip_info(i2c_port_t i2c_num, bno055_chip_info_t* chip_inf){
    
    memset(chip_inf, 0, sizeof(bno055_chip_info_t));
    
    esp_err_t err = bno055_read_data(i2c_num, BNO055_CHIP_ID_ADDR, x_buffer, 7);
    if( err != ESP_OK ) return err;
    
    chip_inf->chip_id = x_buffer[0];
    chip_inf->accel_id = x_buffer[1];
    chip_inf->mag_id = x_buffer[2];
    chip_inf->gyro_id = x_buffer[3];
    chip_inf->sw_rev = x_buffer[4] + ((uint16_t)x_buffer[5]<<8);
    chip_inf->bl_rev = x_buffer[6];
    
    return ESP_OK;
}   

void bno055_displ_chip_info(bno055_chip_info_t chip_inf){

    printf("BNO055 Chip ID (0xA0): 0x%02X \n", chip_inf.chip_id );
    printf("Accelerometer Chip ID (0xFB): 0x%02X \n", chip_inf.accel_id );
    printf("Magnetometer Chip ID (0x32): 0x%02X \n", chip_inf.mag_id );
    printf("Gyroscope Chip ID (0x0F): 0x%02X \n", chip_inf.gyro_id );
    printf("Software Revision: %d \n", chip_inf.sw_rev );
    printf("Bootloader Revision: %d \n", chip_inf.bl_rev );

}   

esp_err_t bno055_set_opmode(i2c_port_t i2c_num, bno055_opmode_t mode ){
    
    esp_err_t err=bno055_write_register(i2c_num, BNO055_OPR_MODE_ADDR, mode);
    vTaskDelay(30 / portTICK_PERIOD_MS);
    return err;
}


esp_err_t bno055_get_opmode(i2c_port_t i2c_num, bno055_opmode_t * mode ){
    
    uint8_t ui_mode;
    esp_err_t err = bno055_read_register(i2c_num, BNO055_OPR_MODE_ADDR, &ui_mode);
    ui_mode = ui_mode & 0x0F; // upper 4 bits are reserved, lower 4 represent the mode
    *mode = (bno055_opmode_t)ui_mode;
    return err;
}

// Note: should be in config mode to work!
esp_err_t bno055_set_ext_crystal_use(i2c_port_t i2c_num, bool use_ext ){
    
    bno055_opmode_t mode;
    esp_err_t err = bno055_get_opmode(i2c_num, & mode );
    if( err != ESP_OK ) return err;
    
    if( mode  != OPERATION_MODE_CONFIG ) {
        ESP_LOGE(TAG, "bno055_set_ext_crystal_use(): device should be in the config mode. Current mode: %d", mode);
        return BNO_ERR_WRONG_OPMODE;
    }

    uint8_t reg_val;
    if(use_ext) reg_val = 0x80;
    else reg_val = 0;

    // Set ext crystal on/off 
    err=bno055_write_register(i2c_num, BNO055_SYS_TRIGGER_ADDR, reg_val);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    return err;
}

esp_err_t bno055_get_system_status(i2c_port_t i2c_num,uint8_t *system_status){

	esp_err_t err;
	err = bno055_read_register(i2c_num, BNO055_SYS_STAT_ADDR, system_status);

	vTaskDelay(30 / portTICK_PERIOD_MS);
	return err;
}

esp_err_t bno055_get_self_test_result(i2c_port_t i2c_num, uint8_t *self_test_result){

	esp_err_t err;
	err = bno055_read_register(i2c_num, BNO055_SELFTEST_RESULT_ADDR, self_test_result);

	vTaskDelay(30 / portTICK_PERIOD_MS);
	return err;
}

esp_err_t bno055_get_system_error(i2c_port_t i2c_num, uint8_t *system_error){

	esp_err_t err;
	err = bno055_read_register(i2c_num, BNO055_SYS_ERR_ADDR, system_error);

	vTaskDelay(30 / portTICK_PERIOD_MS);
	return err;
}

esp_err_t bno055_get_temperature(i2c_port_t i2c_num, uint8_t* p_temperature){

  esp_err_t err = bno055_read_register(i2c_num, BNO055_TEMP_ADDR, p_temperature);
  return err;
}

esp_err_t bno055_get_calib_status_byte(i2c_port_t i2c_num, uint8_t* calib) {
	esp_err_t err;
	err = bno055_read_register(i2c_num, BNO055_CALIB_STAT_ADDR, calib);
    return err;
}

esp_err_t bno055_get_calib_status(i2c_port_t i2c_num, uint8_t* sys, uint8_t* gyro, uint8_t* accel, uint8_t* mag) {
    
    uint8_t calib_status;
	esp_err_t err;
	err = bno055_read_register(i2c_num, BNO055_CALIB_STAT_ADDR, &calib_status);
    if( err != ESP_OK ) return err;
   
    *sys = (calib_status >> 6) & 0x03;
    *gyro = (calib_status >> 4) & 0x03;
    *accel = (calib_status >> 2) & 0x03;
    *mag = calib_status & 0x03;
    
    return ESP_OK;
}

esp_err_t _bno055_buf_to_quaternion(uint8_t *buffer, bno055_quaternion_t* quat) {

    int16_t x, y, z, w;
    // combine MSB and LSB into 16-bit int
    w = (((uint16_t)buffer[1]) << 8) | ((uint16_t)buffer[0]);
    x = (((uint16_t)buffer[3]) << 8) | ((uint16_t)buffer[2]);
    y = (((uint16_t)buffer[5]) << 8) | ((uint16_t)buffer[4]);
    z = (((uint16_t)buffer[7]) << 8) | ((uint16_t)buffer[6]);

    const double conv_coeff = (1.0 / (1<<14));
    quat->w = conv_coeff * w;
    quat->x = conv_coeff * x;
    quat->y = conv_coeff * y;
    quat->z = conv_coeff * z;

    return ESP_OK;
}

esp_err_t bno055_get_quaternion(i2c_port_t i2c_num, bno055_quaternion_t* quat) {

    esp_err_t err = bno055_read_data(i2c_num, BNO055_QUATERNION_DATA_W_LSB_ADDR, x_buffer, 8);
    if( err != ESP_OK ) return err;

    return _bno055_buf_to_quaternion(x_buffer, quat);
}

esp_err_t _bno055_buf_to_lin_accel(uint8_t *buffer, bno055_vec3_t* lin_accel) {

    int16_t x, y, z;
    // combine MSB and LSB into 16-bit int
    x = (((uint16_t)buffer[1]) << 8) | ((uint16_t)buffer[0]);
    y = (((uint16_t)buffer[3]) << 8) | ((uint16_t)buffer[2]);
    z = (((uint16_t)buffer[5]) << 8) | ((uint16_t)buffer[4]);

    const double conv_coeff = 1e-2;  // we assume m/s^2 units
    lin_accel->x = conv_coeff * x;
    lin_accel->y = conv_coeff * y;
    lin_accel->z = conv_coeff * z;

    return ESP_OK;
}

esp_err_t bno055_get_lin_accel(i2c_port_t i2c_num, bno055_vec3_t* lin_accel) {

    esp_err_t err = bno055_read_data(i2c_num, BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR, x_buffer, 6);
    if( err != ESP_OK ) return err;
    
    return _bno055_buf_to_lin_accel(x_buffer, lin_accel);
}

esp_err_t _bno055_buf_to_gravity(uint8_t *buffer, bno055_vec3_t* gravity) {

    int16_t x, y, z;
    // combine MSB and LSB into 16-bit int
    x = (((uint16_t)buffer[1]) << 8) | ((uint16_t)buffer[0]);
    y = (((uint16_t)buffer[3]) << 8) | ((uint16_t)buffer[2]);
    z = (((uint16_t)buffer[5]) << 8) | ((uint16_t)buffer[4]);

    const double conv_coeff = 1e-2;  // we assume m/s^2 units
    gravity->x = conv_coeff * x;
    gravity->y = conv_coeff * y;
    gravity->z = conv_coeff * z;

    return ESP_OK;
}

esp_err_t bno055_get_gravity(i2c_port_t i2c_num, bno055_vec3_t* gravity){
    esp_err_t err = bno055_read_data(i2c_num, BNO055_GRAVITY_DATA_X_LSB_ADDR, x_buffer, 6);
    if( err != ESP_OK ) return err;
    
    return _bno055_buf_to_gravity(x_buffer, gravity);
}

esp_err_t bno055_get_fusion_data(i2c_port_t i2c_num, bno055_quaternion_t* quat, bno055_vec3_t* lin_accel, bno055_vec3_t* gravity){

    esp_err_t err = bno055_read_data(i2c_num, BNO055_QUATERNION_DATA_W_LSB_ADDR, x_buffer, 20);
    if( err != ESP_OK ) return err;
    
    _bno055_buf_to_quaternion(x_buffer, quat);
    _bno055_buf_to_lin_accel(x_buffer+8, lin_accel);
    _bno055_buf_to_gravity(x_buffer+14, gravity);
    
    return ESP_OK;
}

