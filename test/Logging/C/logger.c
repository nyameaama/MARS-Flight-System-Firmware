/**
 * @file logger.c
 * @brief logger function definitions
 *
 *
 * @date January 24th, 2024
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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../PTAM/C/_ptam.h"
#include "logger.h"

/**
 * @brief Queries all required ptam registers, formats them, logs them, and returns the log
 *
 * @param void
 * @return const char*
 */
const char*
EVENT_LOG_SDD(void)
{
    // Implement C variant of PTAM here
    DataType datatype;

    const char* ID = (const char*)retrieveData("stateDescript", &datatype);
    if (ID == NULL)
    {
        LOG_ERROR(CRITICAL, "LOG SDD ACCESSED NULL MEMORY");
        return ID;
    }

    const int* state_data = (const int*)retrieveData("state", &datatype);
    if (state_data == NULL)
    {
        LOG_ERROR(CRITICAL, "LOG SDD ACCESSED NULL MEMORY");
        return ID;
    }

    const double* FLS = (const double*)retrieveData("WingFL", &datatype);
    if (FLS == NULL)
    {
        LOG_ERROR(CRITICAL, "LOG SDD ACCESSED NULL MEMORY");
        return ID;
    }

    const double* FRS = (const double*)retrieveData("WingFR", &datatype);
    if (FRS == NULL)
    {
        LOG_ERROR(CRITICAL, "LOG SDD ACCESSED NULL MEMORY");
        return ID;
    }

    const double* RLS = (const double*)retrieveData("WingRL", &datatype);
    if (RLS == NULL)
    {
        LOG_ERROR(CRITICAL, "LOG SDD ACCESSED NULL MEMORY");
        return ID;
    }

    const double* RRS = (const double*)retrieveData("WingRR", &datatype);
    if (RRS == NULL)
    {
        LOG_ERROR(CRITICAL, "LOG SDD ACCESSED NULL MEMORY");
        return ID;
    }

    const char* formatted_time = convert_time(72000);  // Corrected function name

    const char* log_ev = "LOG_SSD";

    char buffer[512];  // Adjust the buffer size as needed

    // Use snprintf for formatting and concatenation
    snprintf(buffer, sizeof(buffer), "\n\n%s:\n", log_ev);
    strcat(buffer, "\t{\n");
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tID: %s\n", ID);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tTIME: %s\n",
             formatted_time);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tDATA: %ls\n",
             state_data);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tWING-FL-POS: %lf\n",
             *FLS);  // Use %f for double
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tWING-FR-POS: %lf\n",
             *FRS);  // Use %f for double
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tWING-RL-POS: %lf\n",
             *RLS);  // Use %f for double
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tWING-RR-POS: %lf\n",
             *RRS);  // Use %f for double
    strcat(buffer, "\t}\n\n\0");

    // Allocate memory for the result
    char* formatted_output = malloc(strlen(buffer) + 1);

    // Check if the allocation was successful
    if (formatted_output == NULL)
    {
        // Handle allocation failure
        printf("Formatted string returned NULL...");
        return NULL;
    }

    // Copy the result to the allocated memory
    strcpy(formatted_output, buffer);

    return formatted_output;
}

/**
 * @brief Queries all required ptam registers, formats them, logs them, and returns the log
 *
 * @param void
 * @return std::string
 */
const char*
EVENT_LOG_SSL(void)
{
    // Implement C variant of PTAM here
    DataType datatype;

    const char* ID = "LOG_SSL";

    const char* state = (const char*)retrieveData("stateDescript", &datatype);
    if (state == NULL)
    {
        printf("LOG SSL error: %p\n", state);
        return ID;
    }

    const int* state_data = (const int*)retrieveData("state", &datatype);
    if (state_data == NULL)
    {
        printf("LOG SSL error: %ls\n", state_data);
        return ID;
    }

    const char* log_ev = "LOG_SSL";

    const char* formatted_time = convert_time(72000);

    char buffer[512];  // Adjust the buffer size as needed

    // Use snprintf for formatting and concatenation
    snprintf(buffer, sizeof(buffer), "\n\n%s:\n", log_ev);
    strcat(buffer, "\t{\n");
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tID: %s\n", ID);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tTIME: %s\n",
             formatted_time);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tMACHINE-STATE: %ls\n",
             state_data);  // Assuming state_data is an integer
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tSTATE: %s\n", state);
    strcat(buffer, "\t}\n\n\0");

    // Allocate memory for the result
    char* formatted_output = malloc(strlen(buffer) + 1);

    // Check if the allocation was successful
    if (formatted_output == NULL)
    {
        // Handle allocation failure | Add log macros here
        printf("Formatted string returned NULL...");
        return NULL;
    }

    // Copy the result to the allocated memory
    strcpy(formatted_output, buffer);

    return formatted_output;
}

/**
 * @brief Called when an error rises. Formats data and logs it
 *
 * @param ID
 * @param exceptionType
 * @param additionalInfo
 * @return std::string
 */
const char*
EVENT_LOG_SEL(const char* ID, MarsExceptionType exceptionType, const char* additionalInfo)
{
    // Implement C variant of PTAM here
    DataType datatype;

    const int* state_data = (const int*)retrieveData("state", &datatype);
    if (state_data == NULL)
    {
        printf("LOG SEL error: %ls\n", state_data);
        return ID;
    }

    const char* formatted_time = convert_time(72000);

    const char* exceptionTypeStr = exception_t_to_str(exceptionType);

    const char* log_ev = "LOG_SEL";

    char buffer[512];  // Adjust the buffer size as needed

    // Use snprintf for formatting and concatenation
    snprintf(buffer, sizeof(buffer), "\n\n%s:\n", log_ev);
    strcat(buffer, "\t{\n");
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tID: %s\n", ID);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tTIME: %s\n",
             formatted_time);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tMACHINE-STATE: %ls\n",
             state_data);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tEXCEPTION-TYPE: %s\n",
             exceptionTypeStr);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tINFO: %s\n",
             additionalInfo);
    strcat(buffer, "\t}\n\n\0");

    // Allocate memory for the result
    char* formatted_output = malloc(strlen(buffer) + 1);

    // Check if the allocation was successful
    if (formatted_output == NULL)
    {
        // Handle allocation failure
        printf("Formatted string returned NULL...");
        return NULL;
    }

    // Copy the result to the allocated memory
    strcpy(formatted_output, buffer);

    return formatted_output;
}

const char*
SERVO_EVENT_LOG(double throttle, double SERVO_FR, double SERVO_FL, double SERVO_RR, double SERVO_RL)
{
    const char* servo_evt = "SERVO_EVENT_LOG";

    char buffer[512];
    snprintf(buffer, sizeof(buffer), "\n\n%s:\n", servo_evt);
    strcat(buffer, "\t{\n");
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tMACHINE-THROTTLE: %f\n",
             throttle);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer),
             "\t\tFRONT-RIGHT-SERVO: %f\n", SERVO_FR);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tFRONT-LEFT-SERVO: %f\n",
             SERVO_FL);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tREAR-RIGHT-SERVO: %f\n",
             SERVO_RR);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "\t\tREAR-LEFT-SERVO: %f\n",
             SERVO_RL);
    strcat(buffer, "\t}\n\n\0");

    char* formatted_output = malloc(strlen(buffer) + 1);
    if (formatted_output == NULL)
    {
        // Handle allocation failure
        LOG_ERROR(CRITICAL, "Formatted string returned NULL...");
        return NULL;
    }
    strcpy(formatted_output, buffer);

    return formatted_output;
}

/**
 * @brief converts mars_exception_type to int
 *
 * @param exception_type
 * @return const char*
 */
const char*
exception_t_to_str(MarsExceptionType exception_type)
{
    switch (exception_type)
    {
    case ROUTINE_SOFT_FAIL:
        return "ROUTINE_SOFT_FAIL";
    case ROUTINE_HARD_FAIL:
        return "ROUTINE_HARD_FAIL";
    default:
        return "UNKNOWN";
    }
    return "Could not return MARS type";
}

/**
 * @brief Get the event id from log message
 *
 * @param formatted_data
 * @return const char*
 */
const char*
get_event_id(const char* formatted_data)
{
    const char* eventID = "";  // Default value if not found

    // Find the position of "ID: "
    const char* start = strstr(formatted_data, "ID: ");
    if (start != NULL)
    {
        start += 4;  // Move to the start of the actual ID (skip "ID: ")

        // Find the position of the newline character '\n'
        const char* end = strchr(start, '\n');
        if (end != NULL)
        {
            // Calculate the length of the ID substring
            size_t length = end - start;

            // Allocate memory for the ID substring
            char* ID = (char*)malloc(length + 1);
            if (ID != NULL)
            {
                // Copy the ID substring to the allocated memory
                strncpy(ID, start, length);
                ID[length] = '\0';  // Null-terminate the string

                // Update the eventID pointer
                eventID = ID;
            }
        }
    }

    return eventID;
}

/**
 * @brief Get the event time from log message
 *
 * @param formatted_data
 * @return uint64_t
 */
uint64_t
get_event_time(const char* formatted_data)
{
    uint64_t eventTime = 0;

    // Find the position of "TIME: "
    const char* start = strstr(formatted_data, "TIME: ");
    if (start != NULL)
    {
        start += 6;  // Move to the start of the actual time value (skip "TIME: ")

        // Find the position of the newline character '\n'
        const char* end = strchr(start, '\n');
        if (end != NULL)
        {
            // Calculate the length of the time value substring
            size_t length = end - start;

            // Allocate memory for the time value substring
            char* timeStr = malloc(length + 1);
            if (timeStr != NULL)
            {
                // Copy the time value substring to the allocated memory
                strncpy(timeStr, start, length);
                timeStr[length] = '\0';  // Null-terminate the string

                // Convert the string to uint64_t
                sscanf(timeStr, "%" SCNu64, &eventTime);

                // Free the allocated memory for timeStr
                free(timeStr);
            }
        }
    }

    return eventTime;
}

/**
 * @brief Converts timestamp into H-M-S-M format
 *
 * @param ms
 * @return const char*
 */
const char*
convert_time(uint64_t ms)
{
    // Calculate seconds
    uint64_t seconds = ms / 1000;

    // Extract hours, minutes, and remaining seconds
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    // Extract remaining milliseconds
    int remaining_milliseconds = ms % 1000;

    // Calculate the required size for the time string
    size_t buffer_size =
        snprintf(NULL, 0, "%02d:%02d:%02d.%03d", hours, minutes, secs, remaining_milliseconds) + 1;

    // Allocate memory for the time string
    char* time_string = malloc(buffer_size);
    if (time_string == NULL)
    {
        printf("Formatted string returned NULL...");
        return NULL;
    }

    // Format and build the time string
    snprintf(time_string, buffer_size, "%02d:%02d:%02d.%03d", hours, minutes, secs,
             remaining_milliseconds);

    return time_string;
}

/**
 * @brief Get the event state from log message
 *
 * @param formatted_data
 * @return uint8_t
 */
uint8_t
get_event_state(const char* formatted_data)
{
    uint8_t eventState = 0;

    // Find the position of "MACHINE-STATE: "
    const char* start = strstr(formatted_data, "MACHINE-STATE: ");
    if (start != NULL)
    {
        start += 15;  // Move to the start of the actual state value (skip "MACHINE-STATE: ")

        // Find the position of the newline character '\n'
        const char* end = strchr(start, '\n');
        if (end != NULL)
        {
            // Calculate the length of the state value substring
            size_t length = end - start;

            // Allocate memory for the state value substring
            char* stateStr = malloc(length + 1);
            if (stateStr != NULL)
            {
                // Copy the state value substring to the allocated memory
                strncpy(stateStr, start, length);
                stateStr[length] = '\0';  // Null-terminate the string

                // Convert the string to uint8_t
                sscanf(stateStr, "%" SCNu8, &eventState);

                // Free the allocated memory for stateStr
                free(stateStr);
            }
        }
    }

    return eventState;
}

/**
 * @brief Get the event value from log message
 *
 * @param formatted_data
 * @return uint8_t
 */
uint8_t
get_event_exptn(const char* formatted_data)
{
    uint8_t eventEXPT = 0;

    // Find the position of "EXCEPTION-TYPE: "
    const char* start = strstr(formatted_data, "EXCEPTION-TYPE: ");
    if (start != NULL)
    {
        start +=
            16;  // Move to the start of the actual exception type value (skip "EXCEPTION-TYPE: ")

        // Find the position of the newline character '\n'
        const char* end = strchr(start, '\n');
        if (end != NULL)
        {
            // Calculate the length of the exception type value substring
            size_t length = end - start;

            // Allocate memory for the exception type value substring
            char* stateStr = malloc(length + 1);
            if (stateStr != NULL)
            {
                // Copy the exception type value substring to the allocated memory
                strncpy(stateStr, start, length);
                stateStr[length] = '\0';  // Null-terminate the string

                // Convert the string to uint8_t
                sscanf(stateStr, "%" SCNu8, &eventEXPT);

                // Free the allocated memory for stateStr
                free(stateStr);
            }
        }
    }

    return eventEXPT;
}

/**
 * @brief Specifcally logs an event along with specified tag
 *
 * @param label
 * @param data
 * @return const char*
 */
const char*
LOG_INFO(const char* label, const char* data)
{
    // Get the formatted time
    const char* formatted_time = convert_time(72000);  // Corrected function name

    // Define log_ev and other variables (if needed)
    const char* log_ev = "LOG_INFO";

    // Calculate the size of the buffer needed
    size_t buffer_size = 512;  // Adjust as needed
    buffer_size += strlen(log_ev) + strlen(label) + snprintf(NULL, 0, "%s", data);

    // Allocate memory for the buffer
    char* buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
        // Handle allocation failure
        return NULL;
    }

    // Use snprintf for formatting and concatenation
    snprintf(buffer, buffer_size, "\n\n%s:\n", log_ev);
    strcat(buffer, "\t{\n");
    snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), "\t\tTIME: %s\n",
             formatted_time);
    snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), "\t\t%s: %s \n", label, data);
    strcat(buffer, "\t}\n\n\0");

    return buffer;
}

/**
 * @brief deparse info data from given formatted string
 *
 * @param formatted_data
 * @return const char*
 */
const char*
get_info(const char* formatted_data)
{
    const char* eventINFO = "";  // Default value if not found

    // Find the position of "INFO: "
    const char* start = strstr(formatted_data, "INFO: ");
    if (start != NULL)
    {
        start += 6;  // Move to the start of the actual INFO (skip "INFO: ")

        // Find the position of the newline character '\n' after INFO
        const char* end = strchr(start, '\n');
        if (end != NULL)
        {
            // Calculate the length of INFO and extract it
            size_t info_length = end - start;
            char* info = malloc(info_length + 1);
            if (info == NULL)
            {
                // Handle allocation failure
                return NULL;
            }

            strncpy(info, start, info_length);
            info[info_length] = '\0';

            eventINFO = info;
        }
    }

    return eventINFO;
}

/**
 * @brief Pass formatted data and a specified label to retrieve data
 *
 * @param formatted_data
 * @param label
 * @return const char*
 */
const char*
get_tag(const char* formatted_data, const char* label)
{
    const char* eventTAG = "";  // Default value if not found

    // Find the position of the label
    const char* start = strstr(formatted_data, label);
    if (start != NULL)
    {
        start += strlen(label);

        // Find the position of the newline character '\n' after the label
        const char* end = strchr(start, '\n');
        if (end != NULL)
        {
            // Calculate the length of the TAG and extract it
            size_t tag_length = end - start;
            char* tag = malloc(tag_length + 1);
            if (tag == NULL)
            {
                // Handle allocation failure
                return NULL;
            }

            strncpy(tag, start, tag_length);
            tag[tag_length] = '\0';

            eventTAG = tag;
        }
    }

    // Concatenate "\n \n" to the extracted TAG
    size_t eventTAG_length = strlen(eventTAG) + strlen("\n \n") + 1;
    char* final_eventTAG = malloc(eventTAG_length);
    if (final_eventTAG == NULL)
    {
        // Handle allocation failure
        return NULL;
    }

    strcpy(final_eventTAG, eventTAG);
    strcat(final_eventTAG, "\n \n");

    return final_eventTAG;
}