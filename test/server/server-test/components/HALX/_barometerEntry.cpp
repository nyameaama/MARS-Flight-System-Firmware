#include"_barometerEntry.h"
#include"bmx280.h"

static gpio_num_t i2c_gpio_sda = GPIO_NUM_21;
static gpio_num_t i2c_gpio_scl = GPIO_NUM_22;
#define I2C_NUM I2C_NUM_1
#define I2C_MASTER_FREQ_HZ 100000 /*!< I2C master clock frequency. no higher than 1MHz for now */

double GroundRef = 0;
bmx280_t* bmx280;

void VEHICLE_BARO::init_barometer(void){
    esp_err_t i2c_err;
    i2c_config_t i2c_conf;
    i2c_conf.mode = I2C_MODE_MASTER;
    i2c_conf.sda_io_num = i2c_gpio_sda;         
    i2c_conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_conf.scl_io_num = i2c_gpio_scl;         
    i2c_conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_conf.master.clk_speed = I2C_MASTER_FREQ_HZ;  // select frequency 
    i2c_conf.clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */

    i2c_err = i2c_param_config(I2C_NUM,&i2c_conf);
    if(i2c_err != ESP_OK) printf(" barometer parameter config error code: %d \r\n",i2c_err);
    i2c_err = i2c_driver_install(I2C_NUM,I2C_MODE_MASTER, 0,0, 0);
    if(i2c_err != ESP_OK) printf(" barometer driver install error code: %d \r\n ",i2c_err);

    //Driver installed so we can zero out for altitude readings
    double zero_ref = pushPressure();
    GroundRef = zero_ref;
}

void VEHICLE_BARO::startMeasurement(){
    /*bmx280_t**/ bmx280 = bmx280_create(I2C_NUM_1);
    ESP_ERROR_CHECK(bmx280_init(bmx280));
    bmx280_config_t bmx_cfg = BMX280_DEFAULT_CONFIG;
    ESP_ERROR_CHECK(bmx280_configure(bmx280, &bmx_cfg));
    ESP_ERROR_CHECK(bmx280_setMode(bmx280, BMX280_MODE_FORCE));
        do {
            vTaskDelay(pdMS_TO_TICKS(1));
        } while(bmx280_isSampling(bmx280));
}

float VEHICLE_BARO::pushTemperature(){
    startMeasurement();
    float temp = 0, pres = 0, hum = 0;
    ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, &temp, &pres, &hum));
    bmx280_close(bmx280);
    
    return temp;
}

float VEHICLE_BARO::pushPressure(){
    startMeasurement();
    float temp = 0, pres = 0, hum = 0;
    ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, &temp, &pres, &hum));
    bmx280_close(bmx280);
    return pres;
}

float VEHICLE_BARO::pushHumidity(){
    startMeasurement();
    float temp = 0, pres = 0, hum = 0;
    ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, &temp, &pres, &hum));
    bmx280_close(bmx280);
    return hum;
}

double VEHICLE_BARO::pushAltitude(double seaLevelhPa){
    //Get reference altitude from zeroed point
    double zer_pressure = GroundRef;
    // Calculate altitude using the barometric formula
    double zer_altitude = (1.0 - pow((zer_pressure / seaLevelhPa), 0.190284)) * 44330.8;
    //We can now use this to get a computed altitude
    double curr_altitude;
    double curr_pressure = pushPressure();
    curr_altitude = (1.0 - pow((curr_pressure / seaLevelhPa), 0.190284)) * 44330.8;
    //Subtract current altitude and reference altitude to get relative altitude
    double relative_altitude = curr_altitude - zer_altitude;
    return relative_altitude;
}