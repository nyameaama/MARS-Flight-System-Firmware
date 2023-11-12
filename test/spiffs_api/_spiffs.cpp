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

esp_err_t _spiffs_l::_spiffs_register(&config)
{
    esp_err_t ret = esp_vfs_spiffs_register(&config);

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
        ESP_LOGE(TAG, "Initialized SPIFFS ");
        return ret;
    }

#ifdef SPIFFS_CHECK

    ESP_LOGI(TAG, "Performing SPIFFS_check().");
    ret = esp_spiffs_check(config.partition_label);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
        return;
    } else {
        ESP_LOGI(TAG, "SPIFFS_check() successful");
    }


    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(conf.partition_label);
        return;
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    if (used > total) {
        ESP_LOGW(TAG, "Number of used bytes cannot be larger than total. Performing SPIFFS_check().");
        ret = esp_spiffs_check(conf.partition_label);
        // Could be also used to mend broken files, to clean unreferenced pages, etc.
        // More info at https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiffs_check
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
            return;
        } else {
            ESP_LOGI(TAG, "SPIFFS_check() successful");
        }
    }
#endif /* SPIFFS_CHECK */
    return ESP_ERR_OK
}

FILE* _spiffs_l::edit_file(const char* filename)
{
    ESP_LOGI(TAG, "Opening file for writing: %s", filename);
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing: %s", filename);
    }
    return f;
}

void _spiffs_l::writeToFile(FILE* f, const char* data) {
    if (f) {
        fprintf(f, "%s\n", data);
        fclose(f);
        ESP_LOGI(TAG, "Data written to file");
    }
}

void _spiffs_l::checkAndDeleteFile(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        ESP_LOGI(TAG, "File %s exists, deleting it.", filename);
        unlink(filename);
    }
}

void _spiffs_l::renameFile(const char* oldname, const char* newname) {
    ESP_LOGI(TAG, "Renaming file from %s to %s", oldname, newname);
    if (rename(oldname, newname) != 0) {
        ESP_LOGE(TAG, "Rename failed");
    }
}

char* _spiffs_l::readFile(const char* filename) {
    ESP_LOGI(TAG, "Reading file: %s", filename);
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading: %s", filename);
        return NULL;
    }

    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);

    char* pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    
    ESP_LOGI(TAG, "Read from file: '%s'", line);
    
    char* content = strdup(line); // You can return the content if needed.
    return content;
}