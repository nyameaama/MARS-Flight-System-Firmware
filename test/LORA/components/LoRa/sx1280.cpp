#include"sx1280.h"

spi_device_handle_t handle;
esp_err_t ret;

static uint8_t halTxBuffer[MAX_HAL_BUFFER_SIZE] = {0x00};
static uint8_t halRxBuffer[MAX_HAL_BUFFER_SIZE] = {0x00};

uint8_t readReg;
/*!
 * \brief Represents all possible opcode understood by the radio
 */
typedef enum RadioCommands_u
{
    RADIO_GET_STATUS                        = 0xC0,
    RADIO_WRITE_REGISTER                    = 0x18,
    RADIO_READ_REGISTER                     = 0x19,
    RADIO_WRITE_BUFFER                      = 0x1A,
    RADIO_READ_BUFFER                       = 0x1B,
    RADIO_SET_SLEEP                         = 0x84,
    RADIO_SET_STANDBY                       = 0x80,
    RADIO_SET_FS                            = 0xC1,
    RADIO_SET_TX                            = 0x83,
    RADIO_SET_RX                            = 0x82,
    RADIO_SET_RXDUTYCYCLE                   = 0x94,
    RADIO_SET_CAD                           = 0xC5,
    RADIO_SET_TXCONTINUOUSWAVE              = 0xD1,
    RADIO_SET_TXCONTINUOUSPREAMBLE          = 0xD2,
    RADIO_SET_PACKETTYPE                    = 0x8A,
    RADIO_GET_PACKETTYPE                    = 0x03,
    RADIO_SET_RFFREQUENCY                   = 0x86,
    RADIO_SET_TXPARAMS                      = 0x8E,
    RADIO_SET_CADPARAMS                     = 0x88,
    RADIO_SET_BUFFERBASEADDRESS             = 0x8F,
    RADIO_SET_MODULATIONPARAMS              = 0x8B,
    RADIO_SET_PACKETPARAMS                  = 0x8C,
    RADIO_GET_RXBUFFERSTATUS                = 0x17,
    RADIO_GET_PACKETSTATUS                  = 0x1D,
    RADIO_GET_RSSIINST                      = 0x1F,
    RADIO_SET_DIOIRQPARAMS                  = 0x8D,
    RADIO_GET_IRQSTATUS                     = 0x15,
    RADIO_CLR_IRQSTATUS                     = 0x97,
    RADIO_CALIBRATE                         = 0x89,
    RADIO_SET_REGULATORMODE                 = 0x96,
    RADIO_SET_SAVECONTEXT                   = 0xD5,
    RADIO_SET_AUTOTX                        = 0x98,
    RADIO_SET_AUTOFS                        = 0x9E,
    RADIO_SET_LONGPREAMBLE                  = 0x9B,
    RADIO_SET_UARTSPEED                     = 0x9D,
    RADIO_SET_RANGING_ROLE                  = 0xA3,
}RadioCommands_t;

/*!
 * \brief Used to block execution waiting for low state on radio busy pin.
 *        Essentially used in SPI communications
 */
void SX1280HalWaitOnBusy( void )
{
    while( gpio_get_level(RADIO_BUSY_PIN) == 1 );
}

void SX1280HalWakeup( void )
{
    gpio_set_level(RADIO_NSS_PIN, 0);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    //Total data length in bits
    t.length=2*8;
    halTxBuffer[0] = RADIO_GET_STATUS;
    halTxBuffer[1] = 0x00;
    t.tx_buffer=halTxBuffer;
    t.rx_buffer=NULL;
    ret=spi_device_transmit(handle, &t);

    gpio_set_level(RADIO_NSS_PIN, 1);

    // Wait for chip to be ready.
    SX1280HalWaitOnBusy( );
}

/*!
 * \brief Register Write.
 *        
 */
void SX1280HalWriteRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    //Total data length in bits
    t.length=((uint8_t )size + 3)*8;
    halTxBuffer[0] = RADIO_WRITE_REGISTER;
    halTxBuffer[1] = ( address & 0xFF00 ) >> 8;
    halTxBuffer[2] = address & 0x00FF;
    memcpy( halTxBuffer + 3, buffer, size );
    t.tx_buffer=halTxBuffer;
    t.rx_buffer=NULL;
    //Wait for slave to be ready before sending
    SX1280HalWaitOnBusy( );
    gpio_set_level(RADIO_NSS_PIN, 0);
    ret=spi_device_transmit(handle, &t);
    gpio_set_level(RADIO_NSS_PIN, 1);
    SX1280HalWaitOnBusy( );
    
}

void SX1280HalWriteRegister( uint16_t address, uint8_t value )
{
    SX1280HalWriteRegisters( address, &value, 1 );
}

/*!
 * \brief Register Read.
 *        
 */
void SX1280HalReadRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    //Total data length in bits
    t.length=((uint8_t )size + 4)*8;
    halTxBuffer[0] = RADIO_READ_REGISTER;
    halTxBuffer[1] = ( address & 0xFF00 ) >> 8;
    halTxBuffer[2] = address & 0x00FF;
    halTxBuffer[3] = 0x00;
    for( uint16_t index = 0; index < size; index++ )
    {
        halTxBuffer[4+index] = 0x00;
    }
    t.tx_buffer=halTxBuffer;
    t.rx_buffer=halRxBuffer;
    //Wait for slave to be ready before sending
    SX1280HalWaitOnBusy( );
    gpio_set_level(RADIO_NSS_PIN, 0);
    ret=spi_device_transmit(handle, &t);
    memcpy( buffer, halRxBuffer + 4, size );
    gpio_set_level(RADIO_NSS_PIN, 1);
    SX1280HalWaitOnBusy( );
}

uint8_t SX1280HalReadRegister( uint16_t address )
{
    uint8_t data;

    SX1280HalReadRegisters( address, &data, 1 );

    return data;
}

/*!
 * \brief Buffer Write.
 *        
 */
void SX1280HalWriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    //Total data length in bits
    t.length=((uint8_t )size + 2)*8;
    halTxBuffer[0] = RADIO_WRITE_BUFFER;
    halTxBuffer[1] = offset;
    memcpy( halTxBuffer + 2, buffer, size );
    t.tx_buffer=halTxBuffer;
    t.rx_buffer=NULL;
    //Wait for slave to be ready before sending
    SX1280HalWaitOnBusy( );
    gpio_set_level(RADIO_NSS_PIN, 0);
    ret=spi_device_transmit(handle, &t);
    gpio_set_level(RADIO_NSS_PIN, 1);
    SX1280HalWaitOnBusy( );
}

/*!
 * \brief Buffer Read.
 *        
 */
void SX1280HalReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    //Total data length in bits
    t.length=((uint8_t )size + 4)*8;
    halTxBuffer[0] = RADIO_READ_BUFFER;
    halTxBuffer[1] = offset;
    halTxBuffer[2] = 0x00;
    for( uint16_t index = 0; index < size; index++ )
    {
        halTxBuffer[3+index] = 0x00;
    }
    t.tx_buffer=halTxBuffer;
    t.rx_buffer=halRxBuffer;
    //Wait for slave to be ready before sending
    SX1280HalWaitOnBusy( );
    gpio_set_level(RADIO_NSS_PIN, 0);
    ret=spi_device_transmit(handle, &t);
    memcpy( buffer, halRxBuffer + 3, size );
    gpio_set_level(RADIO_NSS_PIN, 1);
    SX1280HalWaitOnBusy( );
}

/*!
 * \brief Reset sx1280 module to wake up from sleep/deep sleep mode.
 *        
 */
void SX1280HalReset( void )
{
    vTaskDelay( 20/portTICK_PERIOD_MS );
    gpio_set_level(RADIO_nRESET_PIN, 0);
    vTaskDelay( 50/portTICK_PERIOD_MS );
    gpio_set_level(RADIO_nRESET_PIN, 1);
    vTaskDelay( 20/portTICK_PERIOD_MS );
}

void _initSX1280(){
    //Configuration for the SPI bus
    spi_bus_config_t buscfg={
        .mosi_io_num=GPIO_MOSI,
        .miso_io_num=GPIO_MISO,
        .sclk_io_num=GPIO_SCLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1
    };

    //Configuration for the SPI device on the other side of the bus
    spi_device_interface_config_t devcfg={
        .command_bits=0,
        .address_bits=0,
        .dummy_bits=0,
        .clock_speed_hz=5000000,
        .duty_cycle_pos=128,        //50% duty cycle
        .mode=0,
        //.spics_io_num=GPIO_CS,    //manually control chip select pin
        .cs_ena_posttrans=3,        //Keep the CS low 3 cycles after transaction, to stop slave from missing the last bit when CS has less propagation delay than CLK
        .queue_size=3
    };

    //GPIO config , chip select and busy pin.
    gpio_pad_select_gpio(RADIO_NSS_PIN);
    gpio_pad_select_gpio(RADIO_BUSY_PIN);
    gpio_pad_select_gpio(RADIO_nRESET_PIN);

    gpio_set_direction(RADIO_BUSY_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(RADIO_NSS_PIN ,GPIO_MODE_OUTPUT);
    gpio_set_level(RADIO_NSS_PIN, 1);

    //GPIO config for the Reset line.
    gpio_config_t io_conf={
        .mode=GPIO_MODE_OUTPUT_OD,
        .pull_up_en=1,
        .pin_bit_mask=(1<<RADIO_nRESET_PIN),
        
    };
    gpio_config(&io_conf);
    gpio_set_level(RADIO_nRESET_PIN, 1);

    //Initialize the SPI bus and add the device we want to send stuff to.
    ret=spi_bus_initialize(SENDER_HOST, &buscfg, SPI_DMA_CH_AUTO);
    assert(ret==ESP_OK);
    ret=spi_bus_add_device(SENDER_HOST, &devcfg, &handle);
    assert(ret==ESP_OK);

    //Wake up device from sleep
    SX1280HalWakeup();
    //or you can reset sx1280 before any read or write operation
    //SX1280HalReset();
}