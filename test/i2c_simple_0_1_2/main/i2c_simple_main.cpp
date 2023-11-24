#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "bmi088.h"

static const char *TAG = "BM1088 Module";
extern "C"{
void app_main(void)
{
    //uint8_t data[2];
    //ESP_ERROR_CHECK(i2c_master_init());
    //ESP_LOGI(TAG, "I2C initialized successfully");

    /* Read the BM1088 GYRO_CHIP_ID REGISTER, on power up the register should have the value 0x0F */
    //ESP_ERROR_CHECK(bm1088_gyro_read(GYRO_CHIP_ID, data, 1));
    //ESP_LOGI(TAG, "GYRO_CHIP_ID_REGISTER_VALUE = %X", data[0]);

    /* Read the BM1088 ACC_PWR_CTRL REGISTER to check power on reset */
    //uint8_t check_por[2];
    //ESP_ERROR_CHECK(bm1088_accel_read(ACC_PWR_CTRL, check_por, 1));
    //vTaskDelay(1/ portTICK_PERIOD_MS);

    /* Enable accel module by writing 0x04 to power control register */
    //uint8_t acc_pwr_ctr = 0x04;
    //acc_pwr_ctr |= check_por[0];

    //ESP_ERROR_CHECK(bm1088_accel_write_byte(ACC_PWR_CTRL, acc_pwr_ctr));
    //vTaskDelay(50/ portTICK_PERIOD_MS);
    //ESP_ERROR_CHECK(bm1088_accel_read(ACC_PWR_CTRL, check_por, 1));
    
    //if (check_por[0] == acc_pwr_ctr)
    //{
    //    ESP_LOGI(TAG, "Accelerometer configured successfully");
    //}
    //else ESP_LOGI(TAG, "Accelerometer not configured ");

    //xTaskCreate(bm1088_init, "BM1088 MODULE", 4*1024, NULL, 5, NULL);
    BMI088_IMU *obj = new BMI088_IMU();
    obj -> IMU_INIT();
    while(1){
        ESP_LOGI(TAG, "accel_read_rawX = %f", obj -> accel_read_rawX());
        ESP_LOGI(TAG, "accel_read_rawY = %f", obj -> accel_read_rawY());
        ESP_LOGI(TAG, "accel_read_rawZ = %f", obj -> accel_read_rawZ());

        ESP_LOGI(TAG, "gyro_read_rawX = %f", obj -> gyro_read_rawX());
        ESP_LOGI(TAG, "gyro_read_rawY = %f", obj -> gyro_read_rawY());
        ESP_LOGI(TAG, "gyro_read_rawZ = %f", obj -> gyro_read_rawZ());
        /*ESP_LOGI(TAG, "pitch = %f", obj -> angle_read_pitch());
        ESP_LOGI(TAG, "roll = %f", obj -> angle_read_roll());
        ESP_LOGI(TAG, "yaw = %f", obj -> angle_read_yaw());*/

        ESP_LOGI(TAG, "pitch = %f", obj -> readAugmentedIMUData(PITCH));
        ESP_LOGI(TAG, "roll = %f", obj -> readAugmentedIMUData(ROLL));
        ESP_LOGI(TAG, "yaw = %f", obj -> readAugmentedIMUData(YAW));

        vTaskDelay(pdMS_TO_TICKS(200));
    }
    delete obj;
}
}