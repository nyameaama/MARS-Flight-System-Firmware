#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"

static const char *TAG = "i2c-slave";

#define LED_PIN 2

#define I2C_SLAVE_SCL_IO 22      /*!< gpio number for I2C master clock */
#define I2C_SLAVE_SDA_IO 21      /*!< gpio number for I2C master data  */
#define I2C_SLAVE_FREQ_HZ 100000 /*!< I2C master clock frequency */
#define I2C_SLAVE_TX_BUF_LEN 255 /*!< I2C master doesn't need buffer */
#define I2C_SLAVE_RX_BUF_LEN 255 /*!< I2C master doesn't need buffer */
#define ESP_SLAVE_ADDR 0x0A

#define WRITE_BIT I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ   /*!< I2C master read */
#define ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0          /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                /*!< I2C ack value */
#define NACK_VAL 0x1               /*!< I2C nack value */

int i2c_slave_port = 0;
static esp_err_t i2c_slave_init(void)
{
    /**
    i2c_config_t conf_slave = {
        .sda_io_num = I2C_SLAVE_SDA_IO, // select GPIO specific to your project
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SLAVE_SCL_IO, // select GPIO specific to your project
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .mode = I2C_MODE_SLAVE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = ESP_SLAVE_ADDR, // address of your project
        .clk_flags = 0,
    };
    */

    i2c_config_t conf_slave;
    conf_slave.sda_io_num = I2C_SLAVE_SDA_IO;
    conf_slave.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf_slave.scl_io_num = I2C_SLAVE_SCL_IO;
    conf_slave.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf_slave.mode = I2C_MODE_SLAVE;
    conf_slave.slave.addr_10bit_en = 0;
    conf_slave.slave.slave_addr = ESP_SLAVE_ADDR;
    conf_slave.clk_flags = 0;
    

    esp_err_t err = i2c_param_config(i2c_port_t(i2c_slave_port), &conf_slave);
    if (err != ESP_OK)
    {
        return err;
    }
    return i2c_driver_install(i2c_port_t(i2c_slave_port), conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

extern "C"
{
    void app_main(void)
    {
        uint8_t received_data[I2C_SLAVE_RX_BUF_LEN] = {0};

        esp_rom_gpio_pad_select_gpio(LED_PIN);
        gpio_set_direction(gpio_num_t(LED_PIN), GPIO_MODE_OUTPUT);

        ESP_ERROR_CHECK(i2c_slave_init());
        ESP_LOGI(TAG, "I2C Slave initialized successfully");
        const uint8_t i2c_size[] = "I2C Connection Successful!";

        while (1)
        {
            i2c_slave_read_buffer(i2c_port_t(i2c_slave_port), received_data, I2C_SLAVE_RX_BUF_LEN, 100 / portTICK_PERIOD_MS);
            i2c_reset_rx_fifo(i2c_port_t(i2c_slave_port));

            if (strncmp((const char *)received_data, "LED_ON", 6) == 0)
            {
                ESP_LOGI(TAG, "Data Recived = %s", received_data);
                gpio_set_level(gpio_num_t(LED_PIN), 1);
            }
            else if (strncmp((const char *)received_data, "LED_OFF", 7) == 0)
            {
                ESP_LOGI(TAG, "Data Recived = %s", received_data);
                gpio_set_level(gpio_num_t(LED_PIN), 0);
            }
            else if (strncmp((const char *)received_data, (const char *)i2c_size, sizeof(i2c_size)) == 0)
            {
                ESP_LOGI(TAG, "Data Recived = %s", received_data);
            }

            memset(received_data, 0, I2C_SLAVE_RX_BUF_LEN);
        }
    }
}