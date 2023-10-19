/**
 * @file logger.cpp
 * @brief Logger API
 *
 * Functions defined from logger.hpp prototypes
 *
 * @date August 18th 2023
 * @copyright Copyright (c) 2023 limitless Aeronautics
 *
 * @author Lukas Jackson
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

#include "../statemachine/_ptam.h"
#include "logger.hpp"
#include "esp_timer.h"

/**
 * @brief Queries all required ptam registers, formats them, logs them, and returns the log
 *
 * @param void
 * @return std::string
 */
std::string Logger::EVENT_LOG_SDD(void)
{
    SharedMemory &obj = SharedMemory::getInstance();

    /* Query ptam registers for required data */
    std::string ID = obj.getLastString("stateDescript");
    int state_data = obj.getLastInt("state");

    double FLS = obj.getLastDouble("WingFL");

    double FRS = obj.getLastDouble("WingFR");

    double RLS = obj.getLastDouble("WingRL");

    double RRS = obj.getLastDouble("WingRR");

    uint64_t end_time = esp_timer_get_time();
    uint64_t elapsed_time = end_time;

    std::string log_ev = "LOG_SDD";

    // Build the formatted string combining format and data
    std::string formatted_output;
    formatted_output += "\n\n" + log_ev + ":\n";
    formatted_output += "\t{\n";
    formatted_output += "\t\tID: " + ID + "\n";
    formatted_output += "\t\tTIME: " + std::to_string(elapsed_time) + "\n";
    formatted_output += "\t\tDATA: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tMACHINE-STATE: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tWING-FL-POS: " + std::to_string(FLS) + "\n";
    formatted_output += "\t\tWING-FR-POS: " + std::to_string(FRS) + "\n";
    formatted_output += "\t\tWING-RL-POS: " + std::to_string(RLS) + "\n";
    formatted_output += "\t\tWING-RR-POS: " + std::to_string(RRS) + "\n";
    formatted_output += "\t}\n\n";

    return formatted_output;
}

/**
 * @brief Queries all required ptam registers, formats them, logs them, and returns the log
 *
 * @param void
 * @return std::string
 */
std::string Logger::EVENT_LOG_SSL(void)
{
    SharedMemory &obj = SharedMemory::getInstance();

    /* Query ptam registers */
    std::string state = obj.getLastString("stateDescript");
    std::string ID = "LOG_SSL_ID";

    int state_data = obj.getLastInt("state");

    uint64_t end_time = esp_timer_get_time();
    uint64_t elapsed_time = end_time;

    /* Format and output data */
    std::string log_ev = "LOG_SSL";

    std::string formatted_output;
    formatted_output += "\n\n" + log_ev + ":\n";
    formatted_output += "\t{\n";
    formatted_output += "\t\tID: " + ID + "\n";
    formatted_output += "\t\tTIME: " + std::to_string(elapsed_time) + "\n";
    formatted_output += "\t\tMACHINE-STATE: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tSTATE: " + state + "\n";
    formatted_output += "\t}\n\n";

    return formatted_output;
}

/**
 * @brief Called when an error rises. Formats data and logs it
 *
 * @param ID
 * @param exception_type
 * @param additional_info
 * @return std::string
 */
std::string Logger::EVENT_LOG_SEL(std::string ID, mars_exception_t::Type exception_type,
                                  std::string additional_info)
{
    SharedMemory &obj = SharedMemory::getInstance();

    /* Get ptam data */
    int state_data = obj.getLastInt("state");

    uint64_t end_time = esp_timer_get_time();
    uint64_t elapsed_time = end_time;

    /* Check which routine fail occurred */
    std::string exceptionTypeStr;
    switch (exception_type)
    {
    case mars_exception_t::ROUTINE_SOFT_FAIL:
        exceptionTypeStr = "ROUTINE_SOFT_FAIL";
        break;
    case mars_exception_t::ROUTINE_HARD_FAIL:
        exceptionTypeStr = "ROUTINE_HARD_FAIL";
        break;
    default:
        exceptionTypeStr = "UNKNOWN";
        break;
    }
    /* Format and output the data */
    std::string log_ev = "LOG_SEL";

    std::string formatted_output;
    formatted_output += "\n\n" + log_ev + ":\n";
    formatted_output += "\t{\n";
    formatted_output += "\t\tID: " + ID + "\n";
    formatted_output += "\t\tTIME: " + std::to_string(elapsed_time) + "\n";
    formatted_output += "\t\tMACHINE-STATE: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tEXCEPTION-TYPE: " + std::to_string(exception_type) + "\n";
    formatted_output += "\t\tINFO: " + additional_info + "\n";
    formatted_output += "\t}\n\n";

    return formatted_output;
}

/**
 * @brief Parses a log to return the ID of the specific event
 *
 * @param formatted_data
 * @return std::string
 */
std::string Logger::get_event_id(std::string formatted_data)
{
    std::string eventID = ""; // Default value if not found

    size_t start = formatted_data.find("ID: ");
    if (start != std::string::npos)
    {
        start += 4; // Move to the start of the actual ID (skip "ID: ")
        size_t end = formatted_data.find("\n", start);
        if (end != std::string::npos)
        {
            std::string ID = formatted_data.substr(start, end - start);
            eventID = ID;
        }
    }
    return eventID;
}

/**
 * @brief Parses a log to return the time of the specific event
 *
 * @param formatted_data
 * @return uint64_t
 */
uint64_t Logger::get_event_time(std::string formatted_data)
{
    uint64_t eventTime = 0;

    size_t start = formatted_data.find("TIME: ");
    if (start != std::string::npos)
    {
        start += 6;
        size_t end = formatted_data.find("\n", start);
        if (end != std::string::npos)
        {
            std::string timeStr = formatted_data.substr(start, end - start);
            eventTime = std::stoull(timeStr);
        }
    }
    return eventTime;
}

/**
 * @brief Parses a log to return the machine state of the specifc event
 *
 * @param formatted_data 
 * @return uint8_t 
 */
uint8_t Logger::get_event_state(std::string formatted_data)
{
    uint8_t eventState = 0;

    size_t start = formatted_data.find("MACHINE-STATE: ");
    if (start != std::string::npos)
    {
        start += 15;
        size_t end = formatted_data.find("\n", start);
        if(end!=std::string::npos)
        {
            std::string stateStr = formatted_data.substr(start, end-start);
            eventState = std::stoul(stateStr);
        }
    }
    return eventState;
}

/**
 * @brief Parses a SEL log to return the event exception
 * 
 * @param formatted_data 
 * @return uint8_t 
 */
uint8_t Logger::get_event_exptn(std::string formatted_data)
{
    uint8_t eventEXPT = 0;

    size_t start = formatted_data.find("EXCEPTION-TYPE: ");
    if (start != std::string::npos)
    {
        start += 16;
        size_t end = formatted_data.find("\n", start);
        if(end!=std::string::npos)
        {
            std::string stateStr = formatted_data.substr(start, end-start);
            eventEXPT = std::stoul(stateStr);
        }
    }
    return eventEXPT;
}

std::string Logger::LOG_EVENT(int8_t log_data)
{
    std::string formatted_data;

    formatted_data += "LOG-MSG[" + log_data + "]";
    return formatted_data;
}

std::string Logger::LOG_EVENT(std::string log_data)
{
    std::string formatted_data;

    formatted_data += "LOG-MSG[" + log_data + "]";
    return formatted_data;
}