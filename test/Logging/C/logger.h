/**
 * @file logger.h
 * @brief logger prototype functions
 *
 *
 * @date January 24, 2024
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas R. Jackson
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

#ifndef __LOGGING__H_
#define __LOGGING__H_

#include <inttypes.h>  //Replace with homemade inttypes
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/logtypes.h"

/**
 * @brief Sensor Data Dump(SDD) is ran periodically to collect system data
 *
 * @return uint8_t
 */
const char* EVENT_LOG_SDD(void);

/**
 * @brief System State Logs(SSL) is ran periodically to collect the system state
 *
 * @return uint8_t
 */
const char* EVENT_LOG_SSL(void);

/**
 * @brief System Error Logs(SEL) is called by failing routines in submodules
 *
 * @param id
 * @param _param1
 * @param info
 * @return uint8_t
 */
const char* EVENT_LOG_SEL(const char* ID, MarsExceptionType exceptionType,
                          const char* additionalInfo);

/**
 * @brief converts MarsExceptionType to string
 *
 * @param MarsExceptionType
 * @return const char*
 */
const char* exception_t_to_str(MarsExceptionType exceptionType);

/**
 * @brief Get the event id from log message
 *
 * @param formatted_data
 * @return const char*
 */
const char* get_event_id(const char* formatted_data);

/**
 * @brief Get the event time from log message
 *
 * @param formatted_data
 * @return uint64_t
 */
uint64_t get_event_time(const char* formatted_data);

/**
 * @brief Converts timestampt into H-M-S-M format
 *
 * @param ms
 * @return const char*
 */
const char* convert_time(uint64_t ms);

/**
 * @brief Get the event state from log message
 *
 * @param formatted_data
 * @return uint8_t
 */
uint8_t get_event_state(const char* formatted_data);

/**
 * @brief Get the event value from log message
 *
 * @param formatted_data
 * @return uint8_t
 */
uint8_t get_event_exptn(const char* formatted_data);

/**
 * @brief Specifcally logs an event along with specified tag
 *
 * @param label
 * @param data
 * @return const char*
 */
const char* LOG_INFO(const char* label, const char* data);

/**
 * @brief deparse info data from given formatted string
 *
 * @param formatted_data
 * @return const char*
 */
const char* get_info(const char* formatted_data);

/**
 * @brief Pass formatted data and a specified label to retrieve data
 *
 * @param formatted_data
 * @param label
 * @return const char*
 */
const char* get_tag(const char* formatted_data, const char* label);

#endif /* __LOGGING__H_ */