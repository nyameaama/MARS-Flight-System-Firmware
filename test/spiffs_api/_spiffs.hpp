/**
 * @file _spiffs.hpp
 * @brief Spiffs API declarations
 *
 *
 * @date November 12th, 2023
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas Jackson (LukasJacksonEG@gmail.com)
 *
 * @license MIT License
 *          Copyright (c) 2023 limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
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

#ifdef _spiffs_test
static const char *TAG = "spiffs_api"

#endif /* _spiffs_test */

static const char *TAG = "example"

class _spiffs_l
{
public:
    /**
     * @brief Configuration structure for esp_vfs_spiffs_register
     *
     * @param base_path 
     * @param partition_label 
     * @param max_files 
     * @param format_if_mount_failed 
     * @return esp_vfs_spiffs_conf_t 
     */
    esp_vfs_spiffs_conf_t _spiffs_config(const char* base_path, const char* partition_label, size_t max_files, bool format_if_mount_failed);

    /**
     * @brief
     *
     * @param config
     * @return esp_err_t
     */
    esp_err_t _spiffs_register(esp_err_t &config);

    /**
     * @brief Check spiffs partition label
     *
     * @param config->partition_label
     *
     * @return esp_err_t
     */
    esp_err_t _spiffs_partition_check(esp_vfs_spiffs_conf_t config.partition_label);

    /**
     * @brief Get spiffs information
     *
     * @param config->partition_label
     * @param &total
     * @param &used
     *
     * @return esp_err_t
     */
    esp_err_t _spiffs_info(esp_vfs_spiffs_conf_t config.partition_label, &total, &used)

    _spiffs_l()
}

#endif /* _spiffs_api_hpp_ */