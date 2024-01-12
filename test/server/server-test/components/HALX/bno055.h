
#ifndef _BNO055_H_
#define _BNO055_H_

#include "driver/gpio.h"  // gpio_num_t, gpio_pullup_t

typedef enum
{
    I2C_NUMBER_0 = 0,  // I2C port 0
    I2C_NUMBER_1,      // I2C port 1
    I2C_NUMBER_MAX
} i2c_number_t;

typedef enum
{
    BNO055_ADDRESS_A = 0x28,
    BNO055_ADDRESS_B = 0x29
} bno055_addr_t;

// Chip ID
#define BNO055_ID (0xA0)

// ESP-BNO errors
#define BNO_ERR_NOT_OPEN (0xB05501)
#define BNO_ERR_ALREADY_OPEN (0xB05502)
#define BNO_ERR_NOT_IN_RANGE (0xB05503)
#define BNO_ERR_WRONG_OPMODE (0xB05504)

typedef enum
{

    BNO055_CHIP_ID_ADDR = 0x00,
    BNO055_ACCEL_ID_ADDR = 0x01,
    BNO055_MAG_ID_ADDR = 0x02,
    BNO055_GYRO_ID_ADDR = 0x03,
    BNO055_SW_REV_ID_LSB_ADDR = 0x04,
    BNO055_SW_REV_ID_MSB_ADDR = 0x05,
    BNO055_BL_REV_ID_ADDR = 0X06,
    BNO055_PAGE_ID_ADDR = 0X07,

    // Data
    BNO055_ACCEL_DATA_X_LSB_ADDR = 0X08,
    BNO055_ACCEL_DATA_X_MSB_ADDR = 0X09,
    BNO055_ACCEL_DATA_Y_LSB_ADDR = 0X0A,
    BNO055_ACCEL_DATA_Y_MSB_ADDR = 0X0B,
    BNO055_ACCEL_DATA_Z_LSB_ADDR = 0X0C,
    BNO055_ACCEL_DATA_Z_MSB_ADDR = 0X0D,
    BNO055_MAG_DATA_X_LSB_ADDR = 0X0E,
    BNO055_MAG_DATA_X_MSB_ADDR = 0X0F,
    BNO055_MAG_DATA_Y_LSB_ADDR = 0X10,
    BNO055_MAG_DATA_Y_MSB_ADDR = 0X11,
    BNO055_MAG_DATA_Z_LSB_ADDR = 0X12,
    BNO055_MAG_DATA_Z_MSB_ADDR = 0X13,
    BNO055_GYRO_DATA_X_LSB_ADDR = 0X14,
    BNO055_GYRO_DATA_X_MSB_ADDR = 0X15,
    BNO055_GYRO_DATA_Y_LSB_ADDR = 0X16,
    BNO055_GYRO_DATA_Y_MSB_ADDR = 0X17,
    BNO055_GYRO_DATA_Z_LSB_ADDR = 0X18,
    BNO055_GYRO_DATA_Z_MSB_ADDR = 0X19,
    BNO055_EULER_H_LSB_ADDR = 0X1A,
    BNO055_EULER_H_MSB_ADDR = 0X1B,
    BNO055_EULER_R_LSB_ADDR = 0X1C,
    BNO055_EULER_R_MSB_ADDR = 0X1D,
    BNO055_EULER_P_LSB_ADDR = 0X1E,
    BNO055_EULER_P_MSB_ADDR = 0X1F,
    BNO055_QUATERNION_DATA_W_LSB_ADDR = 0X20,
    BNO055_QUATERNION_DATA_W_MSB_ADDR = 0X21,
    BNO055_QUATERNION_DATA_X_LSB_ADDR = 0X22,
    BNO055_QUATERNION_DATA_X_MSB_ADDR = 0X23,
    BNO055_QUATERNION_DATA_Y_LSB_ADDR = 0X24,
    BNO055_QUATERNION_DATA_Y_MSB_ADDR = 0X25,
    BNO055_QUATERNION_DATA_Z_LSB_ADDR = 0X26,
    BNO055_QUATERNION_DATA_Z_MSB_ADDR = 0X27,
    BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR = 0X28,
    BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR = 0X29,
    BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR = 0X2A,
    BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR = 0X2B,
    BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR = 0X2C,
    BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR = 0X2D,
    BNO055_GRAVITY_DATA_X_LSB_ADDR = 0X2E,
    BNO055_GRAVITY_DATA_X_MSB_ADDR = 0X2F,
    BNO055_GRAVITY_DATA_Y_LSB_ADDR = 0X30,
    BNO055_GRAVITY_DATA_Y_MSB_ADDR = 0X31,
    BNO055_GRAVITY_DATA_Z_LSB_ADDR = 0X32,
    BNO055_GRAVITY_DATA_Z_MSB_ADDR = 0X33,

    BNO055_TEMP_ADDR = 0X34,

    // Status
    BNO055_CALIB_STAT_ADDR = 0X35,
    BNO055_SELFTEST_RESULT_ADDR = 0X36,
    BNO055_INTR_STAT_ADDR = 0X37,

    BNO055_SYS_CLK_STAT_ADDR = 0X38,
    BNO055_SYS_STAT_ADDR = 0X39,
    BNO055_SYS_ERR_ADDR = 0X3A,

    // Units selection
    BNO055_UNIT_SEL_ADDR = 0X3B,
    BNO055_DATA_SELECT_ADDR = 0X3C,

    // Mode selection
    BNO055_OPR_MODE_ADDR = 0X3D,
    BNO055_PWR_MODE_ADDR = 0X3E,

    BNO055_SYS_TRIGGER_ADDR = 0X3F,
    BNO055_TEMP_SOURCE_ADDR = 0X40,

    // Axis remapping
    BNO055_AXIS_MAP_CONFIG_ADDR = 0X41,
    BNO055_AXIS_MAP_SIGN_ADDR = 0X42,

    // Soft iron calibration matrix 3x3
    BNO055_SIC_MATRIX_0_LSB_ADDR = 0X43,
    BNO055_SIC_MATRIX_0_MSB_ADDR = 0X44,
    BNO055_SIC_MATRIX_1_LSB_ADDR = 0X45,
    BNO055_SIC_MATRIX_1_MSB_ADDR = 0X46,
    BNO055_SIC_MATRIX_2_LSB_ADDR = 0X47,
    BNO055_SIC_MATRIX_2_MSB_ADDR = 0X48,
    BNO055_SIC_MATRIX_3_LSB_ADDR = 0X49,
    BNO055_SIC_MATRIX_3_MSB_ADDR = 0X4A,
    BNO055_SIC_MATRIX_4_LSB_ADDR = 0X4B,
    BNO055_SIC_MATRIX_4_MSB_ADDR = 0X4C,
    BNO055_SIC_MATRIX_5_LSB_ADDR = 0X4D,
    BNO055_SIC_MATRIX_5_MSB_ADDR = 0X4E,
    BNO055_SIC_MATRIX_6_LSB_ADDR = 0X4F,
    BNO055_SIC_MATRIX_6_MSB_ADDR = 0X50,
    BNO055_SIC_MATRIX_7_LSB_ADDR = 0X51,
    BNO055_SIC_MATRIX_7_MSB_ADDR = 0X52,
    BNO055_SIC_MATRIX_8_LSB_ADDR = 0X53,
    BNO055_SIC_MATRIX_8_MSB_ADDR = 0X54,

    // Accelerometer Offsets
    ACCEL_OFFSET_X_LSB_ADDR = 0X55,
    ACCEL_OFFSET_X_MSB_ADDR = 0X56,
    ACCEL_OFFSET_Y_LSB_ADDR = 0X57,
    ACCEL_OFFSET_Y_MSB_ADDR = 0X58,
    ACCEL_OFFSET_Z_LSB_ADDR = 0X59,
    ACCEL_OFFSET_Z_MSB_ADDR = 0X5A,

    // Magnetometer Offsets
    MAG_OFFSET_X_LSB_ADDR = 0X5B,
    MAG_OFFSET_X_MSB_ADDR = 0X5C,
    MAG_OFFSET_Y_LSB_ADDR = 0X5D,
    MAG_OFFSET_Y_MSB_ADDR = 0X5E,
    MAG_OFFSET_Z_LSB_ADDR = 0X5F,
    MAG_OFFSET_Z_MSB_ADDR = 0X60,

    // Gyroscope Offsets
    GYRO_OFFSET_X_LSB_ADDR = 0X61,
    GYRO_OFFSET_X_MSB_ADDR = 0X62,
    GYRO_OFFSET_Y_LSB_ADDR = 0X63,
    GYRO_OFFSET_Y_MSB_ADDR = 0X64,
    GYRO_OFFSET_Z_LSB_ADDR = 0X65,
    GYRO_OFFSET_Z_MSB_ADDR = 0X66,

    // Radius
    ACCEL_RADIUS_LSB_ADDR = 0X67,
    ACCEL_RADIUS_MSB_ADDR = 0X68,
    MAG_RADIUS_LSB_ADDR = 0X69,
    MAG_RADIUS_MSB_ADDR = 0X6A
} bno055_reg_t;

typedef enum
{
    POWER_MODE_NORMAL = 0X00,
    POWER_MODE_LOWPOWER = 0X01,
    POWER_MODE_SUSPEND = 0X02
} bno055_powermode_t;

typedef enum
{
    // Operation modes
    OPERATION_MODE_CONFIG = 0X00,
    OPERATION_MODE_ACCONLY = 0X01,
    OPERATION_MODE_MAGONLY = 0X02,
    OPERATION_MODE_GYRONLY = 0X03,
    OPERATION_MODE_ACCMAG = 0X04,
    OPERATION_MODE_ACCGYRO = 0X05,
    OPERATION_MODE_MAGGYRO = 0X06,
    OPERATION_MODE_AMG = 0X07,
    OPERATION_MODE_IMUPLUS = 0X08,
    OPERATION_MODE_COMPASS = 0X09,
    OPERATION_MODE_M4G = 0X0A,
    OPERATION_MODE_NDOF_FMC_OFF = 0X0B,
    OPERATION_MODE_NDOF = 0X0C
} bno055_opmode_t;

typedef enum
{
    REMAP_CONFIG_P0 = 0x21,
    REMAP_CONFIG_P1 = 0x24,  // default
    REMAP_CONFIG_P2 = 0x24,
    REMAP_CONFIG_P3 = 0x21,
    REMAP_CONFIG_P4 = 0x24,
    REMAP_CONFIG_P5 = 0x21,
    REMAP_CONFIG_P6 = 0x21,
    REMAP_CONFIG_P7 = 0x24
} bno055_axis_remap_config_t;

typedef enum
{
    REMAP_SIGN_P0 = 0x04,
    REMAP_SIGN_P1 = 0x00,  // default
    REMAP_SIGN_P2 = 0x06,
    REMAP_SIGN_P3 = 0x02,
    REMAP_SIGN_P4 = 0x03,
    REMAP_SIGN_P5 = 0x01,
    REMAP_SIGN_P6 = 0x07,
    REMAP_SIGN_P7 = 0x05
} bno055_axis_remap_sign_t;

typedef struct
{
    int16_t accel_offset_x;
    int16_t accel_offset_y;
    int16_t accel_offset_z;
    int16_t mag_offset_x;
    int16_t mag_offset_y;
    int16_t mag_offset_z;
    int16_t gyro_offset_x;
    int16_t gyro_offset_y;
    int16_t gyro_offset_z;

    int16_t accel_radius;
    int16_t mag_radius;
} bno055_offsets_t;

typedef struct
{
    uint8_t i2c_address;          // BNO055_ADDRESS_A or BNO055_ADDRESS_B
    gpio_num_t sda_io_num;        // GPIO number for I2C sda signal
    gpio_pullup_t sda_pullup_en;  // Internal GPIO pull mode for I2C sda signal
    gpio_num_t scl_io_num;        // GPIO number for I2C scl signal
    gpio_pullup_t scl_pullup_en;  // Internal GPIO pull mode for I2C scl signal
    uint32_t clk_speed;           // I2C clock frequency: 100000 or 400000
    int timeout;                  // in 80 MHz ticks, should be <= 0xFFFFF
    bool use_ext_oscillator;      // Use external oscillator
} bno055_config_t;

typedef struct
{
    uint8_t chip_id;
    uint8_t accel_id;
    uint8_t mag_id;
    uint8_t gyro_id;
    uint16_t sw_rev;
    uint8_t bl_rev;
} bno055_chip_info_t;

typedef struct
{
    double w;
    double x;
    double y;
    double z;
} bno055_quaternion_t;

typedef struct
{
    double x;
    double y;
    double z;
} bno055_vec3_t;

esp_err_t bno055_read_register(i2c_port_t i2c_num, bno055_reg_t reg, uint8_t* p_reg_val);
esp_err_t bno055_write_register(i2c_port_t i2c_num, bno055_reg_t reg, uint8_t reg_val);
esp_err_t bno055_read_data(i2c_port_t i2c_num, bno055_reg_t start_reg, uint8_t* buffer,
                           uint8_t n_bytes);

esp_err_t bno055_set_default_conf(bno055_config_t* p_bno_conf);

esp_err_t bno055_open(i2c_port_t i2c_num, bno055_config_t* p_bno_conf);
esp_err_t bno055_close(i2c_port_t i2c_num);
esp_err_t bno055_get_chip_info(i2c_port_t i2c_num, bno055_chip_info_t* chip_inf);
void bno055_displ_chip_info(bno055_chip_info_t chip_inf);
esp_err_t bno055_set_opmode(i2c_port_t i2c_num, bno055_opmode_t mode);
esp_err_t bno055_get_opmode(i2c_port_t i2c_num, bno055_opmode_t* mode);
esp_err_t bno055_set_ext_crystal_use(i2c_port_t i2c_num, bool use_ext);
esp_err_t bno055_get_temperature(i2c_port_t i2c_num, uint8_t* temperature);

//   System Status
//   ---------------------------------
//   0 = Idle
//   1 = System Error
//   2 = Initializing Peripherals
//   3 = System Initialization
//   4 = Executing Self-Test
//   5 = Sensor fusion algorithm running
//   6 = System running without fusion algorithms
esp_err_t bno055_get_system_status(i2c_port_t i2c_num, uint8_t* system_status);

//	Self Test Results
//	--------------------------------
//	1 = test passed, 0 = test failed
//
//	Bit 0 = Accelerometer self test
//	Bit 1 = Magnetometer self test
//	Bit 2 = Gyroscope self test
//	Bit 3 = MCU self test
//
//	0x0F = all tests OK
esp_err_t bno055_get_self_test_result(i2c_port_t i2c_num, uint8_t* self_test_result);

//	System Error
//	---------------------------------
//	0 = No error
//	1 = Peripheral initialization error
//	2 = System initialization error
//	3 = Self test result failed
//	4 = Register map value out of range
//	5 = Register map address out of range
//	6 = Register map write error
//	7 = BNO low power mode not available for selected operat ion mode
//	8 = Accelerometer power mode not available
//	9 = Fusion algorithm configuration error
//	A = Sensor configuration error
esp_err_t bno055_get_system_error(i2c_port_t i2c_num, uint8_t* system_error);

esp_err_t bno055_displ_sys_status(i2c_port_t i2c_num);

// each field can have values from 0 to 3
// 3 indicates fully calibrated; 0 indicates not calibrated
// uint8_t* system - Current system calibration status, depends on status of all sensors
esp_err_t bno055_get_calib_status(i2c_port_t i2c_num, uint8_t* system, uint8_t* gyro,
                                  uint8_t* accel, uint8_t* mag);
esp_err_t bno055_get_calib_status_byte(i2c_port_t i2c_num, uint8_t* calib);

esp_err_t bno055_get_quaternion(i2c_port_t i2c_num, bno055_quaternion_t* quat);
esp_err_t bno055_get_lin_accel(i2c_port_t i2c_num, bno055_vec3_t* lin_accel);
esp_err_t bno055_get_gravity(i2c_port_t i2c_num, bno055_vec3_t* gravity);

esp_err_t bno055_get_fusion_data(i2c_port_t i2c_num, bno055_quaternion_t* quat,
                                 bno055_vec3_t* lin_accel, bno055_vec3_t* gravity);

#endif  // _BNO055_H_
