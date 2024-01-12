#ifndef SD_CARD
#define SD_CARD

#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#define MOUNT_POINT "/sdcard"

class SD_FILESYSTEM
{
  public:
    static void SDFS_initialize();

    static void SDFS_deinitialize();

    static esp_err_t SDFS_write_file(const char* path, char* data);

    static esp_err_t SDFS_read_file(const char* path);

    static void create_directory(const char* path);
};

#endif  // SD_CARD