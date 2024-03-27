#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/gatt.h>

#include <dk_buttons_and_leds.h>

#include "bt_data.h"
#include "../bt_attributes/bt_attributes.h"


struct bt_conn *my_conn = NULL;

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2

static struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	(BT_LE_ADV_OPT_CONNECTABLE |
	 BT_LE_ADV_OPT_USE_IDENTITY), /* Connectable advertising and use identity address */
	800, /* Min Advertising Interval 500ms (800*0.625ms) */
	801, /* Max Advertising Interval 500.625ms (801*0.625ms) */
	NULL); /* Set to NULL for undirected advertising */

LOG_MODULE_REGISTER(BLE_GATT_SERVER, LOG_LEVEL_INF);

/* Create variable that holds callback for MTU negotiation */
static struct bt_gatt_exchange_params exchange_params;
/* Forward declaration of exchange_func(): */
static void exchange_func(struct bt_conn *conn, uint8_t att_err,
			  struct bt_gatt_exchange_params *params);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)
#define RUN_LED_BLINK_INTERVAL 1000

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),

};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, GATTS_SERVICE_UUID_TEST_VAL),
};

/*  Define the function to update the connection's data length */
static void update_data_length(struct bt_conn *conn)
{
	int err;
	struct bt_conn_le_data_len_param my_data_len = {
		.tx_max_len = BT_GAP_DATA_LEN_MAX,
		.tx_max_time = BT_GAP_DATA_TIME_MAX,
	};
	err = bt_conn_le_data_len_update(my_conn, &my_data_len);
	if(err){
		LOG_ERR("data len update failed (err %d)", err);
	}
}
/* Implement callback function for MTU exchange */
static void exchange_func(struct bt_conn *conn, uint8_t att_err,
			  struct bt_gatt_exchange_params *params)
{
	LOG_INF("MTU exchange %s", att_err == 0 ? "successful" : "failed");
	if (!att_err) {
		uint16_t payload_mtu =
			bt_gatt_get_mtu(conn) - 3; // 3 bytes used for Attribute headers.
		LOG_INF("New MTU: %d bytes", payload_mtu);
	}
}

/* Define the function to update the connection's MTU */
static void update_mtu(struct bt_conn *conn)
{
	int err;
	exchange_params.func = exchange_func;

	err = bt_gatt_exchange_mtu(conn, &exchange_params);
	if (err) {
		LOG_ERR("bt_gatt_exchange_mtu failed (err %d)", err);
	}
}

/**
 * @brief Application read and write fuctions
 * 
*/
char* readDataCharacteristic1(void) {
    static char imu1Data[200];
    float accX = 1.1f, accY = 1.2f, accZ = 1.3f, gyroX = 2.1f, gyroY = 2.2f, gyroZ = 2.3f, temp = 36.6f;
    snprintf(imu1Data, sizeof(imu1Data), "[IMU1-ACCX, %.2f, IMU1-ACCY, %.2f, IMU1-ACCZ, %.2f, IMU1-GYROX, %.2f, IMU1-GYROY, %.2f, IMU1-GYROZ, %.2f, IMU1-TEMP, %.2f]", 
             accX, accY, accZ, gyroX, gyroY, gyroZ, temp);
    return imu1Data;
}

char* readDataCharacteristic2(void) {
    static char imu2Data[200];
    float accX = 3.1f, accY = 3.2f, accZ = 3.3f, gyroX = 4.1f, gyroY = 4.2f, gyroZ = 4.3f, temp = 37.6f;
    snprintf(imu2Data, sizeof(imu2Data), "[IMU2-ACCX, %.2f, IMU2-ACCY, %.2f, IMU2-ACCZ, %.2f, IMU2-GYROX, %.2f, IMU2-GYROY, %.2f, IMU2-GYROZ, %.2f, IMU2-TEMP, %.2f]", 
             accX, accY, accZ, gyroX, gyroY, gyroZ, temp);
    return imu2Data;
}

char* readDataCharacteristic3(void) {
    static char imu3Data[200];
    float accX = 5.1f, accY = 5.2f, accZ = 5.3f, gyroX = 6.1f, gyroY = 6.2f, gyroZ = 6.3f, temp = 38.6f;
    snprintf(imu3Data, sizeof(imu3Data), "[IMU3-ACCX, %.2f, IMU3-ACCY, %.2f, IMU3-ACCZ, %.2f, IMU3-GYROX, %.2f, IMU3-GYROY, %.2f, IMU3-GYROZ, %.2f, IMU3-TEMP, %.2f]", 
             accX, accY, accZ, gyroX, gyroY, gyroZ, temp);
    return imu3Data;
}

char* readDataCharacteristic4(void) {
    static char mag1Data[200];
    float accX = 5.1f, accY = 5.2f, accZ = 5.3f, magX = 6.1f, magY = 6.2f, magZ = 6.3f, temp = 38.6f;
    snprintf(mag1Data, sizeof(mag1Data), "[MAG1-ACCX, %.2f, MAG1-ACCY, %.2f, MAG1-ACCZ, %.2f, MAG1-MAGX, %.2f, MAG1-MAGY, %.2f, MAG1-MAGZ, %.2f, MAG1-TEMP, %.2f]", 
             accX, accY, accZ, magX, magY, magZ, temp);
    return mag1Data;
}

char* readDataCharacteristic5(void) {
    static char mag2Data[200];
    float accX = 5.1f, accY = 5.2f, accZ = 5.3f, magX = 6.1f, magY = 6.2f, magZ = 6.3f, temp = 38.6f;
    snprintf(mag2Data, sizeof(mag2Data), "[MAG2-ACCX, %.2f, MAG2-ACCY, %.2f, MAG2-ACCZ, %.2f, MAG2-MAGX, %.2f, MAG2-MAGY, %.2f, MAG2-MAGZ, %.2f, MAG2-TEMP, %.2f]", 
             accX, accY, accZ, magX, magY, magZ, temp);
    return mag2Data;
}

char* readDataCharacteristic6(void) {
    static char mag3Data[200];
    float accX = 5.1f, accY = 5.2f, accZ = 5.3f, magX = 6.1f, magY = 6.2f, magZ = 6.3f, temp = 38.6f;
    snprintf(mag3Data, sizeof(mag3Data), "[MAG3-ACCX, %.2f, MAG3-ACCY, %.2f, MAG3-ACCZ, %.2f, MAG3-MAGX, %.2f, MAG3-MAGY, %.2f, MAG3-MAGZ, %.2f, MAG3-TEMP, %.2f]", 
             accX, accY, accZ, magX, magY, magZ, temp);
    return mag3Data;
}

char* readDataCharacteristic7(void) {
    static char baro1Data[200];
    float baro1Pressure = 5.1f, baro1Temperature = 5.2f;
    snprintf(baro1Data, sizeof(baro1Data), "[BARO1_Pressure, %.2f, BARO1_Temp, %.2f]", 
             baro1Pressure, baro1Temperature);
    return baro1Data;
}

char* readDataCharacteristic8(void) {
    static char baro2Data[200];
    float baro2Pressure = 5.1f, baro2Temperature = 5.2f;
    snprintf(baro2Data, sizeof(baro2Data), "[BARO2_Pressure, %.2f, BARO2_Temp, %.2f]", 
             baro2Pressure, baro2Temperature);
    return baro2Data;
}

char* readDataCharacteristic9(void) {
    static char baro3Data[200];
    float baro3Pressure = 5.1f, baro3Temperature = 5.2f;
    snprintf(baro3Data, sizeof(baro3Data), "[BARO3_Pressure, %.2f, BARO3_Temp, %.2f]", 
             baro3Pressure, baro3Temperature);
    return baro3Data;
}

char* readDataCharacteristic10(void) {
    static char enc1Data[200];
    float enc1hallX = 5.1f, enc1hallY = 5.2f, enc1hallZ = 5.3f, enc1temp = 6.1f;
    snprintf(enc1Data, sizeof(enc1Data), "[ENC1-HALLX, %.2f, ENC1-HALLY, %.2f, ENC1-HALLZ, %.2f, ENC1-TEMP, %.2f]", 
             enc1hallX, enc1hallY, enc1hallZ, enc1temp);
    return enc1Data;
}

char* readDataCharacteristic11(void) {
    static char enc2Data[200];
    float enc2hallX = 5.1f, enc2hallY = 5.2f, enc2hallZ = 5.3f, enc2temp = 6.1f;
    snprintf(enc2Data, sizeof(enc2Data), "[ENC2-HALLX, %.2f, ENC2-HALLY, %.2f, ENC2-HALLZ, %.2f, ENC2-TEMP, %.2f]", 
             enc2hallX, enc2hallY, enc2hallZ, enc2temp);
    return enc2Data;
}

char* readDataCharacteristic12(void) {
    static char enc3Data[200];
    float enc3hallX = 5.1f, enc3hallY = 5.2f, enc3hallZ = 5.3f, enc3temp = 6.1f;
    snprintf(enc3Data, sizeof(enc3Data), "[ENC3-HALLX, %.2f, ENC3-HALLY, %.2f, ENC3-HALLZ, %.2f, ENC3-TEMP, %.2f]", 
             enc3hallX, enc3hallY, enc3hallZ, enc3temp);
    return enc3Data;
}

char* readDataCharacteristic13(void) {
    static char enc4Data[200];
    float enc4hallX = 5.1f, enc4hallY = 5.2f, enc4hallZ = 5.3f, enc4temp = 6.1f;
    snprintf(enc4Data, sizeof(enc4Data), "[ENC4-HALLX, %.2f, ENC4-HALLY, %.2f, ENC4-HALLZ, %.2f, ENC4-TEMP, %.2f]", 
             enc4hallX, enc4hallY, enc4hallZ, enc4temp);
    return enc4Data;
}

char* readDataCharacteristic14(void) {
    static char miscData[200];
    float wing1 = 5.1f, wing2 = 5.2f, wing3 = 5.3f, wing4 = 6.1f, throttle = 6.2f, vTemp = 6.3f, voltage = 38.6f, current = 3.3f, batt_percent = 7.7f, latitude = 1.0357f, longitude = 3.4898f, altitude = 105, satellites = 6, velocity = 68;
    snprintf(miscData, sizeof(miscData), "[WING1, %.2f, WING2, %.2f, WING3, %.2f, WING4, %.2f, THROTTLE, %.2f, VTEMP, %.2f, VOLTAGE, %.2f, CURRENT, %.2f, BATT_PERCENT, %.2f, LAT, %.2f, LONG, %.2f, ALT, %.2f, SAT, %.2f, VEL, %.2f]", 
             wing1, wing2, wing3, wing4, throttle, vTemp, voltage, current, batt_percent, latitude, longitude, altitude, satellites, velocity);
    return miscData;
}

char* readDataCharacteristic15(void) {
    static char settingsData[200];
    float serialNo = 5.1f, firmware_version = 5.2f;
    snprintf(settingsData, sizeof(settingsData), "[SERIAL_NO, %.2f, FIRMWARE_VERSION, %.2f]", 
             serialNo, firmware_version);
    return settingsData;
}

char* writeDataCharacteristic16(char *str, uint16_t len) {

    char buffer[250];
    memset(buffer, 0, 250);
	memcpy(buffer, str, len-1);
	LOG_INF("write callback 16 %s", buffer);

    return "Data not implemented";
}

char* writeDataCharacteristic17(char *str, uint16_t len) {

    char buffer[250];
    memset(buffer, 0, 250);
	memcpy(buffer, str, len-1);
	LOG_INF("write callback 17 %s", buffer);

    return "Data not implemented";
}

char* writeDataCharacteristic18(char *str, uint16_t len) {

    char buffer[250];
    memset(buffer, 0, 250);
	memcpy(buffer, str, len-1);
	LOG_INF("write callback 18 %s", buffer);

    return "Data not implemented";
}

char* writeDataCharacteristic19(char *str, uint16_t len) {

    char buffer[250];
    memset(buffer, 0, 250);
	memcpy(buffer, str, len-1);
	LOG_INF("write callback 19 %s", buffer);

    return "Data not implemented";
}

char* writeDataCharacteristic20(char *str, uint16_t len) {

    char buffer[250];
    memset(buffer, 0, 250);
	memcpy(buffer, str, len-1);
	LOG_INF("write callback 20 %s", buffer);

    return "Data not implemented";
}


/**
 * @brief ble Connection callbacks
*/
static void on_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
		return;
	}
	printk("Connected\n");
    my_conn = bt_conn_ref(conn);
	dk_set_led_on(CON_STATUS_LED);

	update_data_length(my_conn);
	update_mtu(my_conn);
}

static void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);
    bt_conn_unref(my_conn);
	dk_set_led_off(CON_STATUS_LED);
}

struct bt_conn_cb connection_callbacks = {
	.connected = on_connected,
	.disconnected = on_disconnected,
};


/**
 * @brief Application callbacks structure
 * 
*/

/* Declare a varaible app_callbacks of type my_custom_callbacks and initiate 
 * its members to the applications call back functions*/

static struct my_custom_callbacks app_callbacks = {

    .readCharacteristics1 = readDataCharacteristic1,
    .readCharacteristics2 = readDataCharacteristic2,
    .readCharacteristics3 = readDataCharacteristic3,
    .readCharacteristics4 = readDataCharacteristic4,
    .readCharacteristics5 = readDataCharacteristic5,
    .readCharacteristics6 = readDataCharacteristic6,
    .readCharacteristics7 = readDataCharacteristic7,
    .readCharacteristics8 = readDataCharacteristic8,
    .readCharacteristics9 = readDataCharacteristic9,
    .readCharacteristics10 = readDataCharacteristic10,
    .readCharacteristics11 = readDataCharacteristic11,
    .readCharacteristics12 = readDataCharacteristic12,
    .readCharacteristics13 = readDataCharacteristic13,
    .readCharacteristics14 = readDataCharacteristic14,
    .readCharacteristics15 = readDataCharacteristic15,

    .writeCharacteristics16 = writeDataCharacteristic16,
    .writeCharacteristics17 = writeDataCharacteristic17,
    .writeCharacteristics18 = writeDataCharacteristic18,
    .writeCharacteristics19 = writeDataCharacteristic19,
    .writeCharacteristics20 = writeDataCharacteristic20,

};


/**
 * @brief Application main entry point
 * 
*/

void ble_gatt_start()
{
    int blink_status = 0;
	int err;

	LOG_INF("Starting Ble Gatt Server \n");
    
	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)\n", err);
		return;
	}

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_conn_cb_register(&connection_callbacks);

	/* Pass your application callback functions stored in app_callbacks to the MY LBS service */
    err = my_custom_characteristics_init(&app_callbacks);
	if(err){
		LOG_ERR("failed to init Gatt server (err: %d)", err);
		return;
	}

	LOG_INF("Bluetooth initialized\n");
	err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)\n", err);
		return;
	}

	LOG_INF("Advertising successfully started\n");

	for (;;) {
		dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
	}
    
}