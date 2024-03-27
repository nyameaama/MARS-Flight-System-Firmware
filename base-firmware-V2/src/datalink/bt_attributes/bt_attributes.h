#ifndef BT_ATTRIBUTES_H_
#define BT_ATTRIBUTES_H_

#include <zephyr/types.h>

/* Define the 128 bit UUIDs for the GATT service and its characteristics in */
#define GATTS_SERVICE_UUID_TEST_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6143, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_1_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6144, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_2_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6145, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_3_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6146, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_4_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6147, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_5_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6148, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_6_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6149, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_7_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6150, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_8_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6151, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_9_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6152, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_10_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6153, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_11_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6154, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_12_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6155, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_13_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6156, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_14_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6157, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_15_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6158, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_16_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6159, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_17_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6160, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_18_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6161, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_19_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6162, 0x46BA, 0x9BBC, 0x0ED5D5777873)

#define GATTS_CHAR_UUID_TEST_20_VAL \
   BT_UUID_128_ENCODE(0x615FCB0D, 0x6163, 0x46BA, 0x9BBC, 0x0ED5D5777873)


#define GATTS_SERVICE_UUID_TEST            BT_UUID_DECLARE_128(GATTS_SERVICE_UUID_TEST_VAL)
#define GATTS_CHAR_UUID_TEST_1             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_1_VAL)
#define GATTS_CHAR_UUID_TEST_2             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_2_VAL)
#define GATTS_CHAR_UUID_TEST_3             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_3_VAL)
#define GATTS_CHAR_UUID_TEST_4             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_4_VAL)
#define GATTS_CHAR_UUID_TEST_5             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_5_VAL)
#define GATTS_CHAR_UUID_TEST_6             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_6_VAL)
#define GATTS_CHAR_UUID_TEST_7             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_7_VAL)
#define GATTS_CHAR_UUID_TEST_8             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_8_VAL)
#define GATTS_CHAR_UUID_TEST_9             BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_9_VAL)
#define GATTS_CHAR_UUID_TEST_10            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_10_VAL)
#define GATTS_CHAR_UUID_TEST_11            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_11_VAL)
#define GATTS_CHAR_UUID_TEST_12            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_12_VAL)
#define GATTS_CHAR_UUID_TEST_13            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_13_VAL)
#define GATTS_CHAR_UUID_TEST_14            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_14_VAL)
#define GATTS_CHAR_UUID_TEST_15            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_15_VAL)
#define GATTS_CHAR_UUID_TEST_16            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_16_VAL)
#define GATTS_CHAR_UUID_TEST_17            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_17_VAL)
#define GATTS_CHAR_UUID_TEST_18            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_18_VAL)
#define GATTS_CHAR_UUID_TEST_19            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_19_VAL)
#define GATTS_CHAR_UUID_TEST_20            BT_UUID_DECLARE_128(GATTS_CHAR_UUID_TEST_20_VAL)


/** @brief Callback type for read and write operations . */

typedef char* (*read_characteristics_1_t)(void);
typedef char* (*read_characteristics_2_t)(void);
typedef char* (*read_characteristics_3_t)(void);
typedef char* (*read_characteristics_4_t)(void);
typedef char* (*read_characteristics_5_t)(void);
typedef char* (*read_characteristics_6_t)(void);
typedef char* (*read_characteristics_7_t)(void);
typedef char* (*read_characteristics_8_t)(void);
typedef char* (*read_characteristics_9_t)(void);
typedef char* (*read_characteristics_10_t)(void);
typedef char* (*read_characteristics_11_t)(void);
typedef char* (*read_characteristics_12_t)(void);
typedef char* (*read_characteristics_13_t)(void);
typedef char* (*read_characteristics_14_t)(void);
typedef char* (*read_characteristics_15_t)(void);

typedef char* (*write_characteristics_16_t)(char *str, uint16_t len);
typedef char* (*write_characteristics_17_t)(char *str, uint16_t len);
typedef char* (*write_characteristics_18_t)(char *str, uint16_t len);
typedef char* (*write_characteristics_19_t)(char *str, uint16_t len);
typedef char* (*write_characteristics_20_t)(char *str, uint16_t len);


/* @brief my custom callbacks for read and write operations */
struct my_custom_callbacks {
   read_characteristics_1_t readCharacteristics1;
   read_characteristics_2_t readCharacteristics2;
   read_characteristics_3_t readCharacteristics3;
   read_characteristics_4_t readCharacteristics4;
   read_characteristics_5_t readCharacteristics5;
   read_characteristics_6_t readCharacteristics6;
   read_characteristics_7_t readCharacteristics7;
   read_characteristics_8_t readCharacteristics8;
   read_characteristics_9_t readCharacteristics9;
   read_characteristics_10_t readCharacteristics10;
   read_characteristics_11_t readCharacteristics11;
   read_characteristics_12_t readCharacteristics12;
   read_characteristics_13_t readCharacteristics13;
   read_characteristics_14_t readCharacteristics14;
   read_characteristics_15_t readCharacteristics15;

   write_characteristics_16_t writeCharacteristics16;
   write_characteristics_17_t writeCharacteristics17;
   write_characteristics_18_t writeCharacteristics18;
   write_characteristics_19_t writeCharacteristics19;
   write_characteristics_20_t writeCharacteristics20;

};

/** @brief Initialize the custom  Service.
 *
 * This function registers application callback functions
 * 
 *
 * @param[in] callbacks Struct containing pointers to callback functions
 *			used by the service. This pointer can be NULL
 *			if no callback functions are defined.
 *
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int my_custom_characteristics_init(struct my_custom_callbacks *callbacks);



#endif /* BT_ATTRIBUTES_H_ */
