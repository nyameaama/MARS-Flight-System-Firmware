/**
 * @file _spiffs.hpp
 * @brief Spiffs API declarations
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

#ifndef _spiffs_api_hpp_
#define _spiffs_api_hpp_

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "example";

/**
 * @brief Handles SPIFFS filesystem operations.
 */
class SpiffsHandler
{
public:
    /**
     * @brief Constructor for the SpiffsHandler class.
     *
     * @param base_path Base path for the SPIFFS filesystem.
     * @param partition_label Label of the SPIFFS partition.
     * @param max_files Maximum number of files that can be open simultaneously.
     */
    SpiffsHandler(const char *base_path, const char *partition_label, size_t max_files);

    /**
     * @brief Destructor for the SpiffsHandler class.
     */
    ~SpiffsHandler();

    /**
     * @brief Initializes SPIFFS with the provided configuration.
     *
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t init_spiffs();

    /**
     * @brief Checks the consistency of the SPIFFS filesystem.
     *
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t check_spiffs();

    /**
     * @brief Retrieves information about the SPIFFS partition.
     *
     * @param total Pointer to store the total size of the partition.
     * @param used Pointer to store the used size of the partition.
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t get_spiffs_info(size_t &total, size_t &used);

    /**
     * @brief Writes data to a file in the SPIFFS filesystem.
     *
     * @param path Path to the file.
     * @param data Data to be written to the file.
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t write_to_file(const char *path, const char *data);

    /**
     * @brief Reads data from a file in the SPIFFS filesystem.
     *
     * @param path Path to the file.
     * @param buffer Buffer to store the read data.
     * @param buffer_size Size of the buffer.
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t read_from_file(const char *path, char *buffer, size_t buffer_size);

    /**
     * @brief Renames a file in the SPIFFS filesystem.
     *
     * @param old_path Current path of the file.
     * @param new_path New path for the file.
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t rename_file(const char *old_path, const char *new_path);

    /**
     * @brief Deletes a file from the SPIFFS filesystem.
     *
     * @param path Path to the file to be deleted.
     * @return esp_err_t ESP_OK on success, otherwise an error code.
     */
    esp_err_t delete_file(const char *path);

    /**
     * @brief Unmounts the SPIFFS filesystem.
     */
    void unmount_spiffs();

private:
    const char *base_path_;       /**< Base path for the SPIFFS filesystem. */
    const char *partition_label_; /**< Label of the SPIFFS partition. */
    size_t max_files_;            /**< Maximum number of files that can be open simultaneously. */
    bool is_initialized_;         /**< Flag indicating whether SPIFFS is initialized. */
};

#endif /* _spiffs_api_hpp_ */