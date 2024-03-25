#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include "bt_attributes.h"

#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(BLE_GATT_SERVER);

static struct my_custom_callbacks custom_callbacks;

/* Implement the read callback function of the custom characteristic */
static ssize_t read_callback_1(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics1){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics1(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value));
	}
	return 0;
}

static ssize_t read_callback_2(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics2){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics2(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_3(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{

	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics3){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics3(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_4(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics4){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics4(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_5(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics5){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics5(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_6(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics6){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics6(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_7(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics7){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics7(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_8(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics8){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics8(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_9(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics9){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics9(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_10(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics10){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics10(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_11(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics11){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics11(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_12(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics12){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics12(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_13(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics13){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics13(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_14(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics14){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics14(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t read_callback_15(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				void *buff,
				uint16_t len,
				uint16_t offset)
{
	LOG_DBG("Attributes read, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.readCharacteristics15){
		// call the application callback function
		const char *value = custom_callbacks.readCharacteristics15(); 
		return bt_gatt_attr_read(conn, attr, buff, len, offset, value, strlen(value)); 
	}
	return 0;
}

static ssize_t write_callback_16(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				const void *buff,
				uint16_t len,
				uint16_t offset, uint8_t flags)
{
	LOG_INF("Attributes write, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.writeCharacteristics16){
		//Read the recieved value
		char *val = ((char *)buff);
		//call the application callback function
		custom_callbacks.writeCharacteristics16(val, len);
	}

	return len;
}

static ssize_t write_callback_17(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				const void *buff,
				uint16_t len,
				uint16_t offset, uint8_t flags)
{
	LOG_INF("Attributes write, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.writeCharacteristics17){
		//Read the recieved value
		char *val = ((char *)buff);
		//call the application callback function
		custom_callbacks.writeCharacteristics17(val, len);
	}

	return len;
}

static ssize_t write_callback_18(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				const void *buff,
				uint16_t len,
				uint16_t offset, uint8_t flags)
{
	LOG_INF("Attributes write, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.writeCharacteristics18){
		//Read the recieved value
		char *val = ((char *)buff);
		//call the application callback function
		custom_callbacks.writeCharacteristics18(val, len);
	}

	return len;
}

static ssize_t write_callback_19(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				const void *buff,
				uint16_t len,
				uint16_t offset, uint8_t flags)
{
	LOG_INF("Attributes write, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.writeCharacteristics19){
		//Read the recieved value
		char *val = ((char *)buff);
		//call the application callback function
		custom_callbacks.writeCharacteristics19(val, len);
	}

	return len;
}

static ssize_t write_callback_20(struct bt_conn *conn,
                const struct bt_gatt_attr *attr,
				const void *buff,
				uint16_t len,
				uint16_t offset, uint8_t flags)
{
	LOG_INF("Attributes write, handle: %u, conn: %p", attr->handle, (void *)conn);
	if(custom_callbacks.writeCharacteristics20){
		//Read the recieved value
		char *val = ((char *)buff);
		//call the application callback function
		custom_callbacks.writeCharacteristics20(val, len);
	}

	return len;
}

/* custom Service Declaration */
/* Create and add the custom service to the Bluetooth LE stack */
BT_GATT_SERVICE_DEFINE(custom_service,
BT_GATT_PRIMARY_SERVICE(GATTS_SERVICE_UUID_TEST),

/* Create and add Characteristics */
BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_1,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_1,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_2,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_2,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_3,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_3,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_4,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_4,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_5,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_5,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_6,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_6,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_7,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_7,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_8,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_8,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_9,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_9,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_10,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_10,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_11,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_11,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_12,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_12,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_13,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_13,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_14,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_14,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_15,
        BT_GATT_CHRC_READ,
		BT_GATT_PERM_READ,
		read_callback_15,
		NULL,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_16,
        BT_GATT_CHRC_WRITE,
		BT_GATT_PERM_WRITE,
		NULL,
		write_callback_16,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_17,
        BT_GATT_CHRC_WRITE,
		BT_GATT_PERM_WRITE,
		NULL,
		write_callback_17,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_18,
        BT_GATT_CHRC_WRITE,
		BT_GATT_PERM_WRITE,
		NULL,
		write_callback_18,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_19,
        BT_GATT_CHRC_WRITE,
		BT_GATT_PERM_WRITE,
		NULL,
		write_callback_19,
		NULL),

BT_GATT_CHARACTERISTIC(GATTS_CHAR_UUID_TEST_20,
        BT_GATT_CHRC_WRITE,
		BT_GATT_PERM_WRITE,
		NULL,
		write_callback_20,
		NULL),

);
/* A function to register application callbacks for custom characteristics  */
int my_custom_characteristics_init(struct my_custom_callbacks *callbacks)
{
	if (callbacks) {

		custom_callbacks.readCharacteristics1 = callbacks->readCharacteristics1;
        custom_callbacks.readCharacteristics2 = callbacks->readCharacteristics2;
		custom_callbacks.readCharacteristics3 = callbacks->readCharacteristics3;
		custom_callbacks.readCharacteristics4 = callbacks->readCharacteristics4;
		custom_callbacks.readCharacteristics5 = callbacks->readCharacteristics5;
		custom_callbacks.readCharacteristics6 = callbacks->readCharacteristics6;
		custom_callbacks.readCharacteristics7 = callbacks->readCharacteristics7;
		custom_callbacks.readCharacteristics8 = callbacks->readCharacteristics8;
		custom_callbacks.readCharacteristics9 = callbacks->readCharacteristics9;
		custom_callbacks.readCharacteristics10 = callbacks->readCharacteristics10;
		custom_callbacks.readCharacteristics11 = callbacks->readCharacteristics11;
		custom_callbacks.readCharacteristics12 = callbacks->readCharacteristics12;
		custom_callbacks.readCharacteristics13 = callbacks->readCharacteristics13;
		custom_callbacks.readCharacteristics14 = callbacks->readCharacteristics14;
		custom_callbacks.readCharacteristics15 = callbacks->readCharacteristics15;
		
		custom_callbacks.writeCharacteristics16 = callbacks->writeCharacteristics16;
		custom_callbacks.writeCharacteristics17 = callbacks->writeCharacteristics17;
		custom_callbacks.writeCharacteristics18 = callbacks->writeCharacteristics18;
		custom_callbacks.writeCharacteristics19 = callbacks->writeCharacteristics19;
		custom_callbacks.writeCharacteristics20 = callbacks->writeCharacteristics20;
	}

	return 0;
}
