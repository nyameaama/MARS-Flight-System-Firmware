/**
 * @file logger.hpp
 * @brief API toolkit for logger
 *
 * This is the main logger module where prototypes are declared
 *
 * @date August 18th 2023
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

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

/* Log includes */
#include "include/logtypes.h"
#include <iomanip>
#include "esp_timer.h"
#include <time.h>


class Logger
{

public:
    /**
     * @brief Sensor Data Dump(SDD) is ran periodically to collect system data
     *
     * @return uint8_t
     */
    std::string EVENT_LOG_SDD(void);

    /**
     * @brief System State Logs(SSL) is ran periodically to collect the system state
     *
     * @return uint8_t
     */
    std::string EVENT_LOG_SSL(void);

    /**
     * @brief System Error Logs(SEL) is called by failing routines in submodules
     *
     * @param id
     * @param _param1
     * @param info
     * @return uint8_t
     */
    std::string EVENT_LOG_SEL(std::string ID, mars_exception_t::Type exceptionType,
                              std::string additionalInfo);

    /**
     * @brief Get the event id from log message
     *
     * @param formatted_data
     * @return std::string
     */
    std::string get_event_id(std::string formatted_data);

    /**
     * @brief Get the event time from log message
     * 
     * @param formatted_data 
     * @return uint64_t
     */
    uint64_t get_event_time(std::string formatted_data);

    /**
     * @brief Return the current runtime in H-M-S-M
     *
     * @param milliseconds
     *
     * @deprecated Please use convert_time() directly and pass milliseconds(ms).
     *
     */
    [[deprecated("This function is useless, please use convert_time() directly and pass milliseconds(ms).")]]
    uint64_t get_timestamp(uint64_t milliseconds);

    /**
     * @brief Converts timestampt into H-M-S-M format
     * 
     * @param ms 
     * @return std::string 
     */
    std::string convert_time(uint64_t ms);

    /**
     * @brief Get the event state from log message
     *
     * @param formatted_data
     * @return uint8_t 
     */
    uint8_t get_event_state(std::string formatted_data);

    /**
     * @brief Get the event value from log message
     * 
     * @param formatted_data 
     * @return uint8_t 
     */
    uint8_t get_event_exptn(std::string formatted_data);

    /**
     * @brief Logs integer data
     *
     * @param log_data
     * @return void
     */
    std::string LOG_EVENT(int8_t log_data);

    /**
     * @brief Logs string data
     *
     * @param log_data
     * @return void
     */
    std::string LOG_EVENT(std::string log_data);

    /**
     * @brief Specifically logs an info event
     *
     * @param info
     * @return std::string
     */
    std::string LOG_INFO(std::string data);

    /**
     * @brief Specifcally logs an event along with specified tag
     *
     * @param label
     * @param data
     * @return std::string
     */
    std::string LOG_INFO(std::string label, std::string data);

    /**
     * @brief Specifcally logs an event along with specified tag
     *
     * @param label
     * @param data
     * @return std::string
     */
    std::string LOG_INFO(std::string label, int64_t data);

    /**
     * @brief deparse info data from given formatted string
     *
     * @param formatted_data 
     * @return std::string
     */
    std::string get_info(std::string formatted_data);

    /**
     * @brief Pass formatted data and a specified label to retrieve data
     * 
     * @param formatted_data 
     * @param label 
     * @return std::string 
     */
    std::string get_tag(std::string formatted_data, std::string label);

};

#endif /* LOGGER_HPP_ */
