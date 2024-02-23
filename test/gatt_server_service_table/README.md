| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-H2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# ESP-IDF Gatt Server Service Table

This example shows how to create a GATT service with an attribute table defined in one place. Provided API releases the user from adding attributes one by one as implemented in BLUEDROID.

## How to Use Example
After flashing this code open nrf mobile app and connect with deice 
You will see charcteristics on app where you can perform read write 
Operation using errors as indicating in nrf connect app


## Code Output

```
I (0) cpu_start: Starting scheduler on APP CPU.
I (512) BTDM_INIT: BT controller compile version [1342a48]
I (522) system_api: Base MAC address is not set
I (522) system_api: read default base MAC address from EFUSE
I (522) phy_init: phy_version 4670,719f9f6,Feb 18 2021,17:07:07
I (942) GATTS_TABLE_DEMO: create attribute table successfully, the number handle = 8

I (942) GATTS_TABLE_DEMO: SERVICE_START_EVT, status 0, service_handle 40
I (962) GATTS_TABLE_DEMO: advertising start successfully
```
Note: If you face any problem you can drop message in my gig text box.

