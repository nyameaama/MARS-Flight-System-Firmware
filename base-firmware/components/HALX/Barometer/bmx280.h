/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef _BMX280_H_
#define _BMX280_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>
#include <stdint.h>
#include "driver/i2c.h"
#include "sdkconfig.h"

#define BMXAPI extern

/**
 * Anonymous structure to driver settings.
 */
typedef struct bmx280_t bmx280_t;

#include "bmx280_bits.h"

/**
 * Create an instance of the BMX280 driver.
 * @param port The I2C port to use.
 * @return A non-null pointer to the driver structure on success.
 */
BMXAPI bmx280_t* bmx280_create(i2c_port_t port);
/**
 * Destroy your the instance.
 * @param bmx280 The instance to destroy.
 */
BMXAPI void bmx280_close(bmx280_t* bmx280);

/**
 * Probe for the sensor and read calibration data.
 * @param bmx280 Driver structure.
 */
BMXAPI esp_err_t bmx280_init(bmx280_t* bmx280);
/**
 * Configure the sensor with the given parameters.
 * @param bmx280 Driver structure.
 * @param configuration The configuration to use.
 */
BMXAPI esp_err_t bmx280_configure(bmx280_t* bmx280, bmx280_config_t* cfg);

/**
 * Set the sensor mode of operation.
 * @param bmx280 Driver structure.
 * @param mode The mode to set the sensor to.
 */
BMXAPI esp_err_t bmx280_setMode(bmx280_t* bmx280, bmx280_mode_t mode);
/**
 * Get the sensor current mode of operation.
 * @param bmx280 Driver structure.
 * @param mode Pointer to write current mode to.
 */
BMXAPI esp_err_t bmx280_getMode(bmx280_t* bmx280, bmx280_mode_t* mode);

/**
 * Returns true if sensor is currently sampling environment conditions.
 * @param bmx280 Driver structure.
 */
BMXAPI bool bmx280_isSampling(bmx280_t* bmx280);

/**
 * Read sensor values as fixed point numbers.
 * @param bmx280 Driver structure.
 * @param temperature The temperature in C (0.01 degree C increments)
 * @param pressure The pressure in Pa (1/256 Pa increments)
 * @param humidity The humidity in %RH (1/1024 %RH increments) (UINT32_MAX when invlaid.)
 */
BMXAPI esp_err_t bmx280_readout(bmx280_t* bmx280, int32_t* temperature, uint32_t* pressure,
                                uint32_t* humidity);

/**
 * Convert sensor readout to floating point values.
 * @param tin Input temperature.
 * @param pin Input pressure.
 * @param hin Input humidity.
 * @param tout Output temperature. (C)
 * @param pout Output pressure. (Pa)
 * @param hout Output humidity. (%Rh)
 */
static inline void
bmx280_readout2float(int32_t* tin, uint32_t* pin, uint32_t* hin, float* tout, float* pout,
                     float* hout)
{
    if (tin && tout)
        *tout = (float)*tin * 0.01f;
    if (pin && pout)
        *pout = (float)*pin * (1.0f / 256.0f);
    if (hin && hout)
        *hout = (*hin == UINT32_MAX) ? -1.0f : (float)*hin * (1.0f / 1024.0f);
}

/**
 * Read sensor values as floating point numbers.
 * @param bmx280 Driver structure.
 * @param temperature The temperature in C.
 * @param pressure The pressure in Pa.
 * @param humidity The humidity in %RH.
 */
static inline esp_err_t
bmx280_readoutFloat(bmx280_t* bmx280, float* temperature, float* pressure, float* humidity)
{
    int32_t t;
    uint32_t p, h;
    esp_err_t err = bmx280_readout(bmx280, &t, &p, &h);

    if (err == ESP_OK)
    {
        bmx280_readout2float(&t, &p, &h, temperature, pressure, humidity);
    }

    return err;
}

#ifdef __cplusplus
};
#endif

#endif
