#ifndef BT_DATA_H_
#define BT_DATA_H_

#include <stdio.h>
#include <stdint.h>

char* readDataCharacteristic1(void);
char* readDataCharacteristic2(void);
char* readDataCharacteristic3(void);
char* readDataCharacteristic4(void);
char* readDataCharacteristic5(void);
char* readDataCharacteristic6(void);
char* readDataCharacteristic7(void);
char* readDataCharacteristic8(void);
char* readDataCharacteristic9(void);
char* readDataCharacteristic10(void);
char* readDataCharacteristic11(void);
char* readDataCharacteristic12(void);
char* readDataCharacteristic13(void);
char* readDataCharacteristic14(void);
char* readDataCharacteristic15(void);

char* writeDataCharacteristic16(char *str, uint16_t len);
char* writeDataCharacteristic17(char *str, uint16_t len);
char* writeDataCharacteristic18(char *str, uint16_t len);
char* writeDataCharacteristic19(char *str, uint16_t len);
char* writeDataCharacteristic20(char *str, uint16_t len);


/* Ble gatt server start Declaration */
void ble_gatt_start(void);

#endif // BT_DATA_H_