/**
 * @file _spiffs.cpp
 * @brief Spiffs API definitions
 *
 * @date November 12th, 2023
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

#include "_spiffs.hpp"

SpiffsHandler::SpiffsHandler(const char *base_path, const char *partition_label, size_t max_files)
    : base_path_(base_path), partition_label_(partition_label), max_files_(max_files), is_initialized_(false) {}

// Destructor
SpiffsHandler::~SpiffsHandler()
{
    if (is_initialized_)
    {
        unmount_spiffs();
    }
}

// Function to initialize SPIFFS
esp_err_t SpiffsHandler::init_spiffs()
{
    ESP_LOGI(TAG, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
        .base_path = base_path_,
        .partition_label = partition_label_,
        .max_files = max_files_,
        .format_if_mount_failed = true};

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
    }
    else
    {
        is_initialized_ = true;
    }

    return ret;
}

// Function to check SPIFFS consistency
esp_err_t SpiffsHandler::check_spiffs()
{
#ifdef CONFIG_EXAMPLE_SPIFFS_CHECK_ON_START
    ESP_LOGI(TAG, "Performing SPIFFS_check().");
    esp_err_t ret = esp_spiffs_check(partition_label_);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
    }
    else
    {
        ESP_LOGI(TAG, "SPIFFS_check() successful");
    }
    return ret;
#else
    // If CONFIG_EXAMPLE_SPIFFS_CHECK_ON_START is not defined, you might want to handle it differently.
    // You can return ESP_OK or handle it according to your needs.
    return ESP_OK;
#endif
}

// Function to get SPIFFS partition information
esp_err_t SpiffsHandler::get_spiffs_info(size_t &total, size_t &used)
{
    esp_err_t ret = esp_spiffs_info(partition_label_, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(partition_label_);
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return ret;
}

// Function to write data to a file
esp_err_t SpiffsHandler::write_to_file(const char *path, const char *data)
{
    ESP_LOGI(TAG, "Opening file");
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }
    fprintf(f, "%s\n", data);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    return ESP_OK;
}

// Function to read data from a file
esp_err_t SpiffsHandler::read_from_file(const char *path, char *buffer, size_t buffer_size)
{
    ESP_LOGI(TAG, "Reading file");
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return ESP_FAIL;
    }
    fgets(buffer, buffer_size, f);
    fclose(f);

    // strip newline
    char *pos = strchr(buffer, '\n');
    if (pos)
    {
        *pos = '\0';
    }

    ESP_LOGI(TAG, "Read from file: '%s'", buffer);

    return ESP_OK;
}

// Function to rename a file
esp_err_t SpiffsHandler::rename_file(const char *old_path, const char *new_path)
{
    ESP_LOGI(TAG, "Renaming file");
    if (rename(old_path, new_path) != 0)
    {
        ESP_LOGE(TAG, "Rename failed");
        return ESP_FAIL;
    }

    return ESP_OK;
}

// Function to delete a file
esp_err_t SpiffsHandler::delete_file(const char *path)
{
    ESP_LOGI(TAG, "Deleting file");
    if (unlink(path) != 0)
    {
        ESP_LOGE(TAG, "Delete failed");
        return ESP_FAIL;
    }

    return ESP_OK;
}

// Function to unmount SPIFFS
void SpiffsHandler::unmount_spiffs()
{
    if (is_initialized_)
    {
        esp_vfs_spiffs_unregister(partition_label_);
        ESP_LOGI(TAG, "SPIFFS unmounted");
        is_initialized_ = false;
    }
}