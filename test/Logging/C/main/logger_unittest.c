/**
 * @file logger_unittest.c
 * @brief logger function testing
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
#include <etest.h>
#include "../logger.h"

TEST(LogEvent, SDD)
{
    const char* evt_log_sdd_res = EVENT_LOG_SDD();

    printf(" %s %s", evt_log_sdd_res, "\n\n");

    uint64_t time = get_event_time(evt_log_sdd_res);
    uint8_t state = get_event_state(evt_log_sdd_res);
    const char* ID = get_event_id(evt_log_sdd_res);

    printf("%s %d", "Captured time: ", time);
    printf("%s %d", "Captured state: ", state);
    printf("%s %d", "Captured ID: ", ID);
}

TEST(LogEvent, SSL)
{
    const char* evt_log_ssl_res = EVENT_LOG_SSL();

    printf(" %s %s", evt_log_ssl_res, "\n\n");

    uint64_t time = get_event_time(evt_log_ssl_res);
    uint8_t state = get_event_state(evt_log_ssl_res);
    const char* ID = get_event_id(evt_log_ssl_res);

    printf("%s %d", "Captured time: ", time);
    printf("%s %d", "Captured state: ", state);
    printf("%s %d", "Captured ID: ", ID);
}

TEST(LogEvent, SEL)
{
    const char* evt_log_sel_res =
        EVENT_LOG_SEL("UAV-SEL-TEST-HARD-FAIL", ROUTINE_HARD_FAIL, "Submodule Down");

    printf("%s ", evt_log_sel_res);

    evt_log_sel_res =
        EVENT_LOG_SEL("UAV-SEL-TEST-SOFT-FAIL", ROUTINE_SOFT_FAIL, "Submodule Unresponsive");

    printf("%s ", evt_log_sel_res);

    uint8_t state = get_event_state(evt_log_sel_res);

    printf("%d", state);
}

TEST(LogInfo, INFO)
{
    const char* data = "Data message test";
    data = LOG_INFO("LOG_INFO", data);
    const char* info_get = get_info(data);

    printf("%s Data: ", data);
    printf("%s INFO: DATA ", info_get);

    const char* formatted_data = get_tag(data, "TIME: ");

    printf("%s", formatted_data);
}

int
main(void)
{
    RUN_ETESTS();

    return 0;
}