#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "rom/gpio.h"
#include "esp_timer.h"

#define RADIO_BUSY_PIN   33  //can change pin numbers according to user requirements
#define RADIO_nRESET_PIN 2
#define RADIO_NSS_PIN    14
#define GPIO_MOSI 12
#define GPIO_MISO 13
#define GPIO_SCLK 15

#define SENDER_HOST HSPI_HOST
#define MAX_HAL_BUFFER_SIZE   0xFFF

void SX1280HalWaitOnBusy( void );

void SX1280HalWakeup( void );

void SX1280HalWriteRegisters( uint16_t address, uint8_t *buffer, uint16_t size );

void SX1280HalWriteRegister( uint16_t address, uint8_t value );

void SX1280HalReadRegisters( uint16_t address, uint8_t *buffer, uint16_t size );

uint8_t SX1280HalReadRegister( uint16_t address );

void SX1280HalWriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size );

void SX1280HalReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size );

void SX1280HalReset( void );

void _initSX1280();