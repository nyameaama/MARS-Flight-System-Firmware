#include"../components/Comms/_broadcast.h"
#include"../components/HALX/mg90s_servo.h"
#include"../components/HALX/MPU6050.h"
#include"../components/HALX/ssd1306.h"
#include"../components/HALX/ssd1306_fonts.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include<cmath>


//#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

extern "C" {
    void app_main() {
        esp_log_level_set("TAG", ESP_LOG_INFO);
        // Wait for Wi-Fi to initialize
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
        //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    //ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    //wifi_init_softap();
        BroadcastedServer server;
        server.wifi_init_softap();

/*
    SSD1306_Init();
    printf("SSD1306 Initialized..\n");
    
    char str[16];
    SSD1306_GotoXY(0,30);
    sprintf(str,"HIVE PLATFORM");
    SSD1306_Puts(str, &Font_7x10, SSD1306_COLOR_WHITE);
    printf("printed text\n");
    SSD1306_UpdateScreen();
    vTaskDelay(1);
    SSD1306_GotoXY(10,10);


uint8_t flag,flag2 = 1;
    int16_t ax,ay,az;
    int16_t gx,gy,gz;
    MPU6050 *obj = new MPU6050();
	
    while (1) {
         if(obj -> MPU_Get_Accelerometer(&ax,&ay,&az) == 0){
            ESP_LOGI("TAG","IMU ACCX: %d",ax);
            ESP_LOGI("TAG","IMU ACCY: %d",ay);
            ESP_LOGI("TAG","IMU ACCZ: %d",az);
        }
        if(obj -> MPU_Get_Gyroscope(&gx,&gy,&gz) == 0){
            ESP_LOGI("TAG","IMU GYROX: %d",gx);
            ESP_LOGI("TAG","IMU GYROY: %d",gy);
            ESP_LOGI("TAG","IMU GYROZ: %d",gz);
        }
        */

        /*float roll  = atan2f(ay, az) * (180.0 / 3.14159);
        float pitch = atan2f(-ax, sqrtf(ay * ay + az * az)) * (180.0 / 3.14159);
        ESP_LOGI("TAG","IMU ROLL: %f",roll);
        ESP_LOGI("TAG","IMU PITCH: %f",pitch);*/
        // Process and use the accelerometer and gyroscopic values as needed

        vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to allow other tasks to run
    //}

    }

}


/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

//You can get these value from the datasheet of servo you use, in general pulse width varies between 1000 to 2000 microsecond
#define SERVO_MIN_PULSEWIDTH 1000 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2000 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 90       //Maximum angle in degree upto which servo can rotate
#define servo_pin 16              //gpio pin of servo

static void mcpwm_example_gpio_initialize(void)
{
    //printf("initializing mcpwm servo control gpio......\n");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, servo_pin); //Set GPIO 33 as PWM0A, to which servo is connected
}

static uint32_t servo_per_degree_init(uint32_t degree_of_rotation)
{
    uint32_t cal_pulsewidth = 0;
    cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
    return cal_pulsewidth;
}

void mcpwm_example_servo_control(void *arg)
{
    uint32_t angle, count;
    //1. mcpwm gpio initialization
    mcpwm_example_gpio_initialize();

    //2. initial mcpwm configuration
    //printf("Configuring Initial Parameters of mcpwm......\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50; //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwm_config.cmpr_a = 0;     //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;     //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config); //Configure PWM0A & PWM0B with above settings
    while (1)
    {
        for (count = 0; count < 180; count++)
        {
            //printf("Angle of rotation: %d\n", count);
            angle = servo_per_degree_init(count);
            //printf("pulse width: %dus\n", angle);
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
            vTaskDelay(10); //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation at 5V
        }
    }
}
*/
/*
extern "C" {
void app_main(void)
{
    WingTranslate *obj = new WingTranslate();
    obj -> mcpwm_servo_control(180,1);
    obj -> mcpwm_servo_control(90,1);
    delete obj;
    //printf("Testing servo motor.......\n");
    //xTaskCreate(mcpwm_example_servo_control, "mcpwm_example_servo_control", 4096, NULL, 2, NULL);
}
}*/