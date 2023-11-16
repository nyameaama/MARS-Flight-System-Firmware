/**
 * @file _spiffs_unittest.cpp
 * @brief Spiffs API unit testing
 *
 * @date November 13th, 2023
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas Jackson (LukasJacksonEG@gmail.com)
 *
 * @license MIT License
 *          Copyright (c) 2023 Limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */

#include <iostream>
#include "../_spiffs.hpp"

extern "C"
{

    void app_main(void)
    {
        const char *base_path = "/spiffs";
        const char *partition_label = NULL;
        size_t max_files = 5;

        // Create an instance of SpiffsHandler
        SpiffsHandler spiffs_handler(base_path, partition_label, max_files);

        // Initialize SPIFFS
        esp_err_t init_ret = spiffs_handler.init_spiffs();
        if (init_ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS");
            return;
        }

        // Check SPIFFS consistency
        esp_err_t check_ret = spiffs_handler.check_spiffs();
        if (check_ret != ESP_OK)
        {
            ESP_LOGE(TAG, "SPIFFS consistency check failed");
            return;
        }

        // Get SPIFFS information
        size_t total, used;
        esp_err_t info_ret = spiffs_handler.get_spiffs_info(total, used);
        if (info_ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to get SPIFFS information");
            return;
        }

        // Write data to a file
        const char *data_to_write = "Hello World!";
        const char *file_path = "/spiffs/hello.txt";
        esp_err_t write_ret = spiffs_handler.write_to_file(file_path, data_to_write);
        if (write_ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to write to file");
            return;
        }

        // Confirm the existence of the old file before renaming
        FILE *test_file = fopen(file_path, "r");
        if (test_file != NULL)
        {
            fclose(test_file);
            ESP_LOGI(TAG, "File '%s' exists before renaming", file_path);
        }
        else
        {
            ESP_LOGE(TAG, "File '%s' does not exist before renaming. errno: %d", file_path, errno);
            perror("Error description");
            return;
        }

        // Check if destination file exists before renaming
        const char *new_file_path = "/spiffs/foo.txt";
        struct stat st;
        if (stat(new_file_path, &st) == 0)
        {
            // Delete it if it exists
            spiffs_handler.delete_file(new_file_path);
        }

        // Rename the file
        esp_err_t rename_ret = spiffs_handler.rename_file(file_path, new_file_path);
        if (rename_ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to rename file");
            return;
        }

        // Read data from the renamed file
        char read_buffer[64];
        esp_err_t read_ret = spiffs_handler.read_from_file(new_file_path, read_buffer, sizeof(read_buffer));
        if (read_ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to read from file: %s", new_file_path);
            return;
        }

        // Print the read data
        ESP_LOGI(TAG, "Read from file: '%s'", read_buffer);

        // Unmount SPIFFS
        spiffs_handler.unmount_spiffs();

        // Log completion
        ESP_LOGI(TAG, "SPIFFS operations completed successfully");

        // Delay for a while before returning
        vTaskDelay(2000 / portTICK_PERIOD_MS);

        // Return from app_main
        ESP_LOGI(TAG, "Returned from app_main()");
    }
}