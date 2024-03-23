
/****************************************************************************
*
* This demo showcases creating a GATT database using a predefined attribute table.
* It acts as a GATT server and can send adv data, be connected by client.
* Run the gatt_client demo, the client demo will automatically connect to the gatt_server_service_table demo.
* Client demo will enable GATT server's notify after connection. The two devices will then exchange
* data.
*
****************************************************************************/


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "gatts_table_creat_demo.h"
#include "esp_gatt_common_api.h"

#include"bt_data.h"

#define GATTS_TABLE_TAG "GATTS_TABLE_DEMO"

#define PROFILE_NUM                 1
#define PROFILE_APP_IDX             0
#define ESP_APP_ID                  0x55
#define SAMPLE_DEVICE_NAME          "ESP_GATTS_DEMO"
#define SVC_INST_ID                 0

/* The max length of characteristic value. When the GATT client performs a write or prepare write operation,
*  the data length must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
*/
#define GATTS_DEMO_CHAR_VAL_LEN_MAX 500
#define PREPARE_BUF_MAX_SIZE        1024
#define CHAR_DECLARATION_SIZE       (sizeof(uint8_t))

#define ADV_CONFIG_FLAG             (1 << 0)
#define SCAN_RSP_CONFIG_FLAG        (1 << 1)

static uint8_t adv_config_done       = 0;

uint16_t heart_rate_handle_table[HRS_IDX_NB];

typedef struct {
    uint8_t                 *prepare_buf;
    int                     prepare_len;
} prepare_type_env_t;

static prepare_type_env_t prepare_write_env;

#define CONFIG_SET_RAW_ADV_DATA
#ifdef CONFIG_SET_RAW_ADV_DATA
static uint8_t raw_adv_data[] = {
        /* flags */
        0x02, 0x01, 0x06,
        /* tx power*/
        0x02, 0x0a, 0xeb,
        /* service uuid */
        0x03, 0x03, 0xFF, 0x00,
        /* device name */
        0x0f, 0x09, 'E', 'S', 'P', '_', 'G', 'A', 'T', 'T', 'S', '_', 'D','E', 'M', 'O'
};
static uint8_t raw_scan_rsp_data[] = {
        /* flags */
        0x02, 0x01, 0x06,
        /* tx power */
        0x02, 0x0a, 0xeb,
        /* service uuid */
        0x03, 0x03, 0xFF,0x00
};

#else
static uint8_t service_uuid[16] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    //first uuid, 16bit, [12],[13] is the value
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

/* The length of adv data must be less than 31 bytes */
static esp_ble_adv_data_t adv_data = {
    .set_scan_rsp        = false,
    .include_name        = true,
    .include_txpower     = true,
    .min_interval        = 0x0006, //slave connection min interval, Time = min_interval * 1.25 msec
    .max_interval        = 0x0010, //slave connection max interval, Time = max_interval * 1.25 msec
    .appearance          = 0x00,
    .manufacturer_len    = 0,    //TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data = NULL, //test_manufacturer,
    .service_data_len    = 0,
    .p_service_data      = NULL,
    .service_uuid_len    = sizeof(service_uuid),
    .p_service_uuid      = service_uuid,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

// scan response data
static esp_ble_adv_data_t scan_rsp_data = {
    .set_scan_rsp        = true,
    .include_name        = true,
    .include_txpower     = true,
    .min_interval        = 0x0006,
    .max_interval        = 0x0010,
    .appearance          = 0x00,
    .manufacturer_len    = 0, //TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data = NULL, //&test_manufacturer[0],
    .service_data_len    = 0,
    .p_service_data      = NULL,
    .service_uuid_len    = sizeof(service_uuid),
    .p_service_uuid      = service_uuid,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};
#endif /* CONFIG_SET_RAW_ADV_DATA */

static esp_ble_adv_params_t adv_params = {
    .adv_int_min         = 0x20,
    .adv_int_max         = 0x40,
    .adv_type            = ADV_TYPE_IND,
    .own_addr_type       = BLE_ADDR_TYPE_PUBLIC,
    .channel_map         = ADV_CHNL_ALL,
    .adv_filter_policy   = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

struct gatts_profile_inst {
    esp_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    esp_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    esp_bt_uuid_t char_uuid;
    esp_gatt_perm_t perm;
    esp_gatt_char_prop_t property;
    uint16_t descr_handle;
    esp_bt_uuid_t descr_uuid;
};

static void gatts_profile_event_handler(esp_gatts_cb_event_t event,
					esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */
static struct gatts_profile_inst heart_rate_profile_tab[PROFILE_NUM] = {
    [PROFILE_APP_IDX] = {
        .gatts_cb = gatts_profile_event_handler,
        .gatts_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
    },
};

/* Service */
static const uint16_t GATTS_SERVICE_UUID_TEST       = 0x13d4; //000013d4-0000-1000-8000-00805f9b34fb
static const uint16_t GATTS_CHAR_UUID_TEST_1        = 0xFF01; //0000ff01-0000-1000-8000-00805f9b34fb
static const uint16_t GATTS_CHAR_UUID_TEST_2        = 0xFF02; //0000ff02-0000-1000-8000-00805f9b34fb
static const uint16_t GATTS_CHAR_UUID_TEST_3        = 0xFF03; //0000ff03-0000-1000-8000-00805f9b34fb
static const uint16_t GATTS_CHAR_UUID_TEST_4        = 0xFF04;
static const uint16_t GATTS_CHAR_UUID_TEST_5        = 0xFF05;
static const uint16_t GATTS_CHAR_UUID_TEST_6        = 0xFF06;
static const uint16_t GATTS_CHAR_UUID_TEST_7        = 0xFF07;
static const uint16_t GATTS_CHAR_UUID_TEST_8        = 0xFF08;
static const uint16_t GATTS_CHAR_UUID_TEST_9        = 0xFF09;
static const uint16_t GATTS_CHAR_UUID_TEST_10       = 0xFF0A;
static const uint16_t GATTS_CHAR_UUID_TEST_11       = 0xFF0B;
static const uint16_t GATTS_CHAR_UUID_TEST_12       = 0xFF0C;
static const uint16_t GATTS_CHAR_UUID_TEST_13       = 0xFF0D;
static const uint16_t GATTS_CHAR_UUID_TEST_14       = 0xFF0E;
static const uint16_t GATTS_CHAR_UUID_TEST_15       = 0xFF0F;
static const uint16_t GATTS_CHAR_UUID_TEST_16       = 0xFF10;
static const uint16_t GATTS_CHAR_UUID_TEST_17       = 0xFF11;
static const uint16_t GATTS_CHAR_UUID_TEST_18       = 0xFF12;
static const uint16_t GATTS_CHAR_UUID_TEST_19       = 0xFF13;
static const uint16_t GATTS_CHAR_UUID_TEST_20       = 0xFF14;

static const uint16_t primary_service_uuid         = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid   = ESP_GATT_UUID_CHAR_DECLARE;
static const uint8_t char_prop_read                = ESP_GATT_CHAR_PROP_BIT_READ;
static const uint8_t char_prop_write               = ESP_GATT_CHAR_PROP_BIT_WRITE;
//static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
//static const uint8_t char_prop_read_write_notify   = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;

/* *Callbacks for 15 Read characteristics --> user can define custom values here 
   *values will can be read using nrf app or print log on console user can define 
   *size and values according to his requirements                               */
static const uint8_t char_value_1[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_2[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_3[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_4[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_5[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_6[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_7[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_8[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_9[4]                  = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_10[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_11[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_12[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_13[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_14[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_15[4]                 = {0x11, 0x22, 0x33, 0x44};

static const uint8_t char_value_16[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_17[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_18[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_19[4]                 = {0x11, 0x22, 0x33, 0x44};
static const uint8_t char_value_20[4]                 = {0x11, 0x22, 0x33, 0x44};
/* Full Database Description - Used to add attributes into the database */
static const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] =
{
    // Service Declaration
    [IDX_SVC]        =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
      sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID_TEST), (uint8_t *)&GATTS_SERVICE_UUID_TEST}},

    /* Characteristic_1 Declaration */
    [IDX_CHAR_1]     =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_1 Value */
    [IDX_CHAR_VAL_1] =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_1, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_1), (uint8_t *)char_value_1}},

    /* Characteristic_2 Declaration */
    [IDX_CHAR_2]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_2 Value */
    [IDX_CHAR_VAL_2]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_2, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_2), (uint8_t *)char_value_2}},

    /* Characteristic_3 Declaration */
    [IDX_CHAR_3]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_3 Value */
    [IDX_CHAR_VAL_3]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_3, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_3), (uint8_t *)char_value_3}},

    /* Characteristics_4 Declaration */
    [IDX_CHAR_4]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_4 Value */
    [IDX_CHAR_VAL_4]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_4, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_4), (uint8_t *)char_value_4}},
    /* Characteristics_5 Declaration */
    [IDX_CHAR_5]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_5 Value */
    [IDX_CHAR_VAL_5]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_5, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_5), (uint8_t *)char_value_5}},
    /* Characteristics_6 Declaration */
    [IDX_CHAR_6]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_6 Value */
    [IDX_CHAR_VAL_6]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_6, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_6), (uint8_t *)char_value_6}},
    /* Characteristics_7 Declaration */
    [IDX_CHAR_7]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_7 Value */
    [IDX_CHAR_VAL_7]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_7, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_7), (uint8_t *)char_value_7}},
    /* Characteristics_8 Declaration */
    [IDX_CHAR_8]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_8 Value */
    [IDX_CHAR_VAL_8]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_8, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_8), (uint8_t *)char_value_8}},
    /* Characteristics_9 Declaration */
    [IDX_CHAR_9]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_9 Value */
    [IDX_CHAR_VAL_9]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_9, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_9), (uint8_t *)char_value_9}},
    /* Characteristics_10 Declaration */
    [IDX_CHAR_10]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_10 Value */
    [IDX_CHAR_VAL_10]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_10, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_10), (uint8_t *)char_value_10}},

    /* Characteristics_11 Declaration */
    [IDX_CHAR_11]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_11 Value */
    [IDX_CHAR_VAL_11]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_11, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_11), (uint8_t *)char_value_11}},


    /* Characteristics_12 Declaration */
    [IDX_CHAR_12]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_12 Value */
    [IDX_CHAR_VAL_12]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_12, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_12), (uint8_t *)char_value_12}},
    /* Characteristics_13 Declaration */
    [IDX_CHAR_13]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_13 Value */
    [IDX_CHAR_VAL_13]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_13, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_13), (uint8_t *)char_value_13}},
    /* Characteristics_14 Declaration */
    [IDX_CHAR_14]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_14 Value */
    [IDX_CHAR_VAL_14]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_14, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_14), (uint8_t *)char_value_14}},
    /* Characteristics_15 Declaration */
    [IDX_CHAR_15]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}},

    /* Characteristic_15 Value */
    [IDX_CHAR_VAL_15]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_15, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_15), (uint8_t *)char_value_15}},
    /* Characteristics_16 Declaration */
    [IDX_CHAR_16]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write}},

    /* Characteristic_16 Value */
    [IDX_CHAR_VAL_16]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_16, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_16), (uint8_t *)char_value_16}},
    /* Characteristics_17 Declaration */
    [IDX_CHAR_17]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write}},

    /* Characteristic_17 Value */
    [IDX_CHAR_VAL_17]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_17, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_17), (uint8_t *)char_value_17}},
    /* Characteristics_18 Declaration */
    [IDX_CHAR_18]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write}},

    /* Characteristic_18 Value */
    [IDX_CHAR_VAL_18]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_18, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_18), (uint8_t *)char_value_18}},
    /* Characteristics_19 Declaration */
    [IDX_CHAR_19]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write}},

    /* Characteristic_19 Value */
    [IDX_CHAR_VAL_19]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_19, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_19), (uint8_t *)char_value_19}},
    /* Characteristics_20 Declaration */
    [IDX_CHAR_20]      =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write}},

    /* Characteristic_20 Value */
    [IDX_CHAR_VAL_20]  =
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_16, (uint8_t *)&GATTS_CHAR_UUID_TEST_20, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
      GATTS_DEMO_CHAR_VAL_LEN_MAX, sizeof(char_value_20), (uint8_t *)char_value_20}},
};

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    #ifdef CONFIG_SET_RAW_ADV_DATA
        case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
    #else
        case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0){
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
    #endif
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
            /* advertising start complete event to indicate advertising start successfully or failed */
            if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(GATTS_TABLE_TAG, "advertising start failed");
            }else{
                ESP_LOGI(GATTS_TABLE_TAG, "advertising start successfully");
            }
            break;
        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(GATTS_TABLE_TAG, "Advertising stop failed");
            }
            else {
                ESP_LOGI(GATTS_TABLE_TAG, "Stop adv successfully\n");
            }
            break;
        case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
            break;
        default:
            break;
    }
}

void example_prepare_write_event_env(esp_gatt_if_t gatts_if, prepare_type_env_t *prepare_write_env, esp_ble_gatts_cb_param_t *param)
{
    ESP_LOGI(GATTS_TABLE_TAG, "prepare write, handle = %d, value len = %d", param->write.handle, param->write.len);
    esp_gatt_status_t status = ESP_GATT_OK;
    if (prepare_write_env->prepare_buf == NULL) {
        prepare_write_env->prepare_buf = (uint8_t *)malloc(PREPARE_BUF_MAX_SIZE * sizeof(uint8_t));
        prepare_write_env->prepare_len = 0;
        if (prepare_write_env->prepare_buf == NULL) {
            ESP_LOGE(GATTS_TABLE_TAG, "%s, Gatt_server prep no mem", __func__);
            status = ESP_GATT_NO_RESOURCES;
        }
    } else {
        if(param->write.offset > PREPARE_BUF_MAX_SIZE) {
            status = ESP_GATT_INVALID_OFFSET;
        } else if ((param->write.offset + param->write.len) > PREPARE_BUF_MAX_SIZE) {
            status = ESP_GATT_INVALID_ATTR_LEN;
        }
    }
    /*send response when param->write.need_rsp is true */
    if (param->write.need_rsp){
        esp_gatt_rsp_t *gatt_rsp = (esp_gatt_rsp_t *)malloc(sizeof(esp_gatt_rsp_t));
        if (gatt_rsp != NULL){
            gatt_rsp->attr_value.len = param->write.len;
            gatt_rsp->attr_value.handle = param->write.handle;
            gatt_rsp->attr_value.offset = param->write.offset;
            gatt_rsp->attr_value.auth_req = ESP_GATT_AUTH_REQ_NONE;
            memcpy(gatt_rsp->attr_value.value, param->write.value, param->write.len);
            esp_err_t response_err = esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, status, gatt_rsp);
            if (response_err != ESP_OK){
               ESP_LOGE(GATTS_TABLE_TAG, "Send response error");
            }
            free(gatt_rsp);
        }else{
            ESP_LOGE(GATTS_TABLE_TAG, "%s, malloc failed", __func__);
        }
    }
    if (status != ESP_GATT_OK){
        return;
    }
    memcpy(prepare_write_env->prepare_buf + param->write.offset,
           param->write.value,
           param->write.len);
    prepare_write_env->prepare_len += param->write.len;

}

void example_exec_write_event_env(prepare_type_env_t *prepare_write_env, esp_ble_gatts_cb_param_t *param){
    if (param->exec_write.exec_write_flag == ESP_GATT_PREP_WRITE_EXEC && prepare_write_env->prepare_buf){
        esp_log_buffer_hex(GATTS_TABLE_TAG, prepare_write_env->prepare_buf, prepare_write_env->prepare_len);
    }else{
        ESP_LOGI(GATTS_TABLE_TAG,"ESP_GATT_PREP_WRITE_CANCEL");
    }
    if (prepare_write_env->prepare_buf) {
        free(prepare_write_env->prepare_buf);
        prepare_write_env->prepare_buf = NULL;
    }
    prepare_write_env->prepare_len = 0;
}

static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    switch (event) {
        case ESP_GATTS_REG_EVT:{
            esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(SAMPLE_DEVICE_NAME);
            if (set_dev_name_ret){
                ESP_LOGE(GATTS_TABLE_TAG, "set device name failed, error code = %x", set_dev_name_ret);
            }
    #ifdef CONFIG_SET_RAW_ADV_DATA
            esp_err_t raw_adv_ret = esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
            if (raw_adv_ret){
                ESP_LOGE(GATTS_TABLE_TAG, "config raw adv data failed, error code = %x ", raw_adv_ret);
            }
            adv_config_done |= ADV_CONFIG_FLAG;
            esp_err_t raw_scan_ret = esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
            if (raw_scan_ret){
                ESP_LOGE(GATTS_TABLE_TAG, "config raw scan rsp data failed, error code = %x", raw_scan_ret);
            }
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
    #else
            //config adv data
            esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
            if (ret){
                ESP_LOGE(GATTS_TABLE_TAG, "config adv data failed, error code = %x", ret);
            }
            adv_config_done |= ADV_CONFIG_FLAG;
            //config scan response data
            ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
            if (ret){
                ESP_LOGE(GATTS_TABLE_TAG, "config scan response data failed, error code = %x", ret);
            }
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
    #endif
            esp_err_t create_attr_ret = esp_ble_gatts_create_attr_tab(gatt_db, gatts_if, HRS_IDX_NB, SVC_INST_ID);
            if (create_attr_ret){
                ESP_LOGE(GATTS_TABLE_TAG, "create attr table failed, error code = %x", create_attr_ret);
            }
        }
       	    break;
        case ESP_GATTS_READ_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "ESP_GATTS_READ_EVT");
            //CHARACTERISTIC 1
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_1]) {
              // Get Data
              const char* output = readDataCharacteristic1(); // Ensure this is null-terminated and remains valid
              ESP_LOGE(GATTS_TABLE_TAG, "Characteristic output: %s", output);
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 2
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_2]) {
              // Get Data
              const char* output = readDataCharacteristic2(); // Ensure this is null-terminated and remains valid
              ESP_LOGE(GATTS_TABLE_TAG, "Characteristic output: %s", output);
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 3
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_3]) {
              // Get Data
              const char* output = readDataCharacteristic3(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 4
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_4]) {
              // Get Data
              const char* output = readDataCharacteristic4(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 5
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_5]) {
              // Get Data
              const char* output = readDataCharacteristic5(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 6
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_6]) {
              // Get Data
              const char* output = readDataCharacteristic6(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 7
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_7]) {
              // Get Data
              const char* output = readDataCharacteristic7(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 8
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_8]) {
              // Get Data
              const char* output = readDataCharacteristic8(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 9
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_9]) {
              // Get Data
              const char* output = readDataCharacteristic9(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 10
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_10]) {
              // Get Data
              const char* output = readDataCharacteristic10(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 11
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_11]) {
              // Get Data
              const char* output = readDataCharacteristic11(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 12
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_12]) {
              // Get Data
              const char* output = readDataCharacteristic12(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 13
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_13]) {
              // Get Data
              const char* output = readDataCharacteristic13(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 14
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_14]) {
              // Get Data
              const char* output = readDataCharacteristic14(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

            //CHARACTERISTIC 15
            if (param->read.handle == heart_rate_handle_table[IDX_CHAR_VAL_15]) {
              // Get Data
              const char* output = readDataCharacteristic15(); // Ensure this is null-terminated and remains valid
              if (output == NULL) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Failed to get data for characteristic 1");
                  return;
              }

              // Prepare the response
              esp_gatt_rsp_t rsp;
              memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
              rsp.attr_value.handle = param->read.handle;
              rsp.attr_value.len = strlen(output);

              // Make sure not to exceed the maximum length
              if (rsp.attr_value.len > ESP_GATT_MAX_ATTR_LEN) {
                  rsp.attr_value.len = ESP_GATT_MAX_ATTR_LEN;
              }

              memcpy(rsp.attr_value.value, output, rsp.attr_value.len);

              // Send the response
              esp_err_t ret = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
              if (ret != ESP_OK) {
                  ESP_LOGE(GATTS_TABLE_TAG, "Send response failed: %s", esp_err_to_name(ret));
              }
            }

       	    break;
        case ESP_GATTS_WRITE_EVT:
            if (!param->write.is_prep){
                // the data length of gattc write  must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
                ESP_LOGI(GATTS_TABLE_TAG, "GATT_WRITE_EVT, handle = %d, value len = %d, value :", param->write.handle, param->write.len);
                esp_log_buffer_hex(GATTS_TABLE_TAG, param->write.value, param->write.len);
                /* send response when param->write.need_rsp is true*/
                if (param->write.need_rsp){
                    esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
                }
            }else{
                /* handle prepare write */
                example_prepare_write_event_env(gatts_if, &prepare_write_env, param);
            }
      	    break;
        case ESP_GATTS_EXEC_WRITE_EVT:
            // the length of gattc prepare write data must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
            ESP_LOGI(GATTS_TABLE_TAG, "ESP_GATTS_EXEC_WRITE_EVT");
            example_exec_write_event_env(&prepare_write_env, param);
            break;
        case ESP_GATTS_MTU_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            break;
        case ESP_GATTS_CONF_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "ESP_GATTS_CONF_EVT, status = %d, attr_handle %d", param->conf.status, param->conf.handle);
            break;
        case ESP_GATTS_START_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "SERVICE_START_EVT, status %d, service_handle %d", param->start.status, param->start.service_handle);
            break;
        case ESP_GATTS_CONNECT_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "ESP_GATTS_CONNECT_EVT, conn_id = %d", param->connect.conn_id);
            esp_log_buffer_hex(GATTS_TABLE_TAG, param->connect.remote_bda, 6);
            esp_ble_conn_update_params_t conn_params = {0};
            memcpy(conn_params.bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));
            /* For the iOS system, please refer to Apple official documents about the BLE connection parameters restrictions. */
            conn_params.latency = 0;
            conn_params.max_int = 0x20;    // max_int = 0x20*1.25ms = 40ms
            conn_params.min_int = 0x10;    // min_int = 0x10*1.25ms = 20ms
            conn_params.timeout = 400;    // timeout = 400*10ms = 4000ms
            //start sent the update connection parameters to the peer device.
            esp_ble_gap_update_conn_params(&conn_params);
            break;
        case ESP_GATTS_DISCONNECT_EVT:
            ESP_LOGI(GATTS_TABLE_TAG, "ESP_GATTS_DISCONNECT_EVT, reason = 0x%x", param->disconnect.reason);
            esp_ble_gap_start_advertising(&adv_params);
            break;
        case ESP_GATTS_CREAT_ATTR_TAB_EVT:{
            if (param->add_attr_tab.status != ESP_GATT_OK){
                ESP_LOGE(GATTS_TABLE_TAG, "create attribute table failed, error code=0x%x", param->add_attr_tab.status);
            }
            else if (param->add_attr_tab.num_handle != HRS_IDX_NB){
                ESP_LOGE(GATTS_TABLE_TAG, "create attribute table abnormally, num_handle (%d) \
                        doesn't equal to HRS_IDX_NB(%d)", param->add_attr_tab.num_handle, HRS_IDX_NB);
            }
            else {
                ESP_LOGI(GATTS_TABLE_TAG, "create attribute table successfully, the number handle = %d\n",param->add_attr_tab.num_handle);
                memcpy(heart_rate_handle_table, param->add_attr_tab.handles, sizeof(heart_rate_handle_table));
                esp_ble_gatts_start_service(heart_rate_handle_table[IDX_SVC]);
            }
            break;
        }
        case ESP_GATTS_STOP_EVT:
        case ESP_GATTS_OPEN_EVT:
        case ESP_GATTS_CANCEL_OPEN_EVT:
        case ESP_GATTS_CLOSE_EVT:
        case ESP_GATTS_LISTEN_EVT:
        case ESP_GATTS_CONGEST_EVT:
        case ESP_GATTS_UNREG_EVT:
        case ESP_GATTS_DELETE_EVT:
        default:
            break;
    }
}


static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{

    /* If event is register event, store the gatts_if for each profile */
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            heart_rate_profile_tab[PROFILE_APP_IDX].gatts_if = gatts_if;
        } else {
            ESP_LOGE(GATTS_TABLE_TAG, "reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }
    do {
        int idx;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
            /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
            if (gatts_if == ESP_GATT_IF_NONE || gatts_if == heart_rate_profile_tab[idx].gatts_if) {
                if (heart_rate_profile_tab[idx].gatts_cb) {
                    heart_rate_profile_tab[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}

void app_main(void)
{
    esp_err_t ret;

    /* Initialize NVS. */
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        ESP_LOGE(GATTS_TABLE_TAG, "gatts register error, error code = %x", ret);
        return;
    }

    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){
        ESP_LOGE(GATTS_TABLE_TAG, "gap register error, error code = %x", ret);
        return;
    }

    ret = esp_ble_gatts_app_register(ESP_APP_ID);
    if (ret){
        ESP_LOGE(GATTS_TABLE_TAG, "gatts app register error, error code = %x", ret);
        return;
    }

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(GATTS_TABLE_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }
}
