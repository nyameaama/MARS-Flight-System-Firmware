/**
 * @file logger_config.h
 * @brief logger configuration file containing macros
 *
 *
 * @date November 10th, 2023
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
#ifndef logger_config_h
#define logger_config_h

#include <stdio.h>
#include "esp_timer.h"
#include <sstream>
#include <iostream>


// Logger version
#define LOGGER_VERSION 1.00

// Logger verbosity
#ifdef LOG_VERBOSITY_LOW

#include <stdio.h>
#include "esp_timer.h"
#include <sstream>


#define Message "LOG_VERBOSITY_LOW ACTIVE \n\n"

// Define a macro for logging with severity levels
#define LOG(level, format, ...) \
    printf("[%s] %s:%d - " format "\n", level, __FILE__, __LINE__, ##__VA_ARGS__)

// Define specific macros for different log levels
#define LOG_DEBUG(format, ...) do { LOG("DEBUG", format, ##__VA_ARGS__); } while (0)
#define LOG_INFO(format, ...)  LOG("INFO", format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  LOG("WARN", format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG("ERROR", format, ##__VA_ARGS__)


#endif /* LOG_VERBOSITY_LOW */

#ifdef LOG_VERBOSITY_MEDIUM



#endif /* LOG_VERBOSITY_MEDIUM */

#ifdef LOG_VERBOSITY_HIGH

#endif /* LOG_VERBOSITY_HIGH */



#endif /* logger_config_h */