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

#include <inttypes.h>  //Replace with custom inttypes
#include "include/logtypes.h"

// Define color escape codes for log output

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"  // Bold white text
#define RESET_TEXT "\033[0m"

// Define log labels and messages
static const char* INFO = BBLU "MESSAGE" RESET_TEXT;
static const char* WARNING = BYEL "WARNING" RESET_TEXT;
static const char* CRITICAL = BRED "CRITICAL" RESET_TEXT;

static const char* ERROR_MSG = BRED "LOG" RESET_TEXT;
static const char* WARNING_MSG = BYEL "LOG" RESET_TEXT;
static const char* INFO_MSG = BBLU "LOG" RESET_TEXT;

// Define log macros
#define LOG_MSG(label, message) \
    printf("%s %s: " BWHT "%s" RESET_TEXT "\n", label, INFO_MSG, message)
#define LOG_ERROR(label, message) \
    printf("%s %s: " BWHT "%s" RESET_TEXT "\n", label, ERROR_MSG, message)
#define LOG_WARNING(label, message) \
    printf("%s %s: " BWHT "%s" RESET_TEXT "\n", label, WARNING_MSG, message)

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
 * @brief Servo event log is ran to pass various servo data and throttle
 *
 * @param throttle
 * @param servo1
 * @param servo2
 * @param servo3
 * @param servo4
 * @return uint8_t
 */
const char* SERVO_EVENT_LOG(double throttle, double SERVO_FR, double SERVO_FL, double SERVO_RR,
                            double SERVO_RL);

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