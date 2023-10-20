#include"_SD_FileSystem.h"

#define MAX_CHAR_SIZE 50

#define PIN_NUM_MISO    (gpio_num_t) 19 
#define PIN_NUM_MOSI    (gpio_num_t) 23
#define PIN_NUM_CLK     (gpio_num_t) 18
#define PIN_NUM_CS      (gpio_num_t) 5

void SD_FILESYSTEM::SDFS_initialize(){
    esp_err_t ret;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    //ESP_LOGI("TAG", "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    //ESP_LOGI("TAG", "Using SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(spi_host_device_t(host.slot), &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE("TAG", "Failed to initialize bus.");
        return;
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = spi_host_device_t(host.slot);

    //ESP_LOGI("TAG", "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            //ESP_LOGE("TAG", "Failed to mount filesystem. "
                     //"If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            //ESP_LOGE("TAG", "Failed to initialize the card (%s). "
                     //"Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return;
    }
    //ESP_LOGI("TAG", "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
}

void SD_FILESYSTEM::SDFS_deinitialize(){
    // All done, unmount partition and disable SPI peripheral
    //esp_vfs_fat_sdcard_unmount(mount_point, card);
    //ESP_LOGI(TAG, "Card unmounted");

    //deinitialize the bus after all devices are removed
    //spi_bus_free(spi_host_device_t(host.slot));
}

esp_err_t SD_FILESYSTEM::SDFS_write_file(const char *path, char *data)
{
    ESP_LOGI("TAG", "Opening file %s", path);
    FILE *f = fopen(path, "a");
    if (f == NULL) {
        ESP_LOGE("TAG", "Failed to open file for writing");
        return ESP_FAIL;
    }
    fprintf(f, data);
    fclose(f);
    ESP_LOGI("TAG", "File written");

    return ESP_OK;
}

esp_err_t SD_FILESYSTEM::SDFS_read_file(const char *path)
{
    ESP_LOGI("TAG", "Reading file %s", path);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        ESP_LOGE("TAG", "Failed to open file for reading");
        return ESP_FAIL;
    }
    char line[MAX_CHAR_SIZE];
    fgets(line, sizeof(line), f);
    fclose(f);

    // strip newline
    char *pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI("TAG", "Read from file: '%s'", line);

    return ESP_OK;
}

void SD_FILESYSTEM::create_directory(const char *path) {
    if (mkdir(path, 0777) == -1) {
        // Handle the error, if any
        perror("mkdir");
    } else {
        printf("Directory created successfully: %s\n", path);
    }
}
