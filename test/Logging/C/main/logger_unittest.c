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
#include "../../../PTAM/C/_ptam.h"
#include "../logger.h"
#include <inttypes.h>

void EVENT_LOG_SDD_TEST(void)
{
    printf("\n-----------------------------------------------------------\n");

    //  Store the machine data
    double stateVal = 3.14;
    storeData("stateDescript", "LOG_SDD_DATA", STRING);
    storeData("state", &stateVal, DOUBLE);
    // printf("Made entry LOG-EVENT-SDD_TEST");

    // Store the sensor data
    double WingFL = 111;
    double WingFR = 222;
    double WingRL = 333;
    double WingRR = 444;
    storeData("WingFL", &WingFL, DOUBLE);
    storeData("WingFR", &WingFR, DOUBLE);
    storeData("WingRL", &WingRL, DOUBLE);
    storeData("WingRR", &WingRR, DOUBLE);

    const char* evt_log_sdd_res = EVENT_LOG_SDD();

    printf(" %s %s", evt_log_sdd_res, "\n\n");

    uint64_t time = get_event_time(evt_log_sdd_res);
    uint8_t state = get_event_state(evt_log_sdd_res);
    const char* ID = get_event_id(evt_log_sdd_res);

    printf("%s %"SCNu64 "%s", "Captured time: ", time, "\n");
    printf("%s %d %s", "Captured state: ", state, "\n");
    printf("%s %s %s", "Captured ID: ", ID, "\n\n");

    deleteContainer("WingFL");
    deleteContainer("WingFR");
    deleteContainer("WingRL");
    deleteContainer("WingRR");
    printf("\n");
    printf("\n-----------------------------------------------------------\n");
}

void EVENT_LOG_SSL_TEST(void)
{
    printf("\n-----------------------------------------------------------\n");

    double stateVal = 4.14;
    storeData("stateDescript", "LOG_SSL_DATA", DOUBLE);
    storeData("state", &stateVal, DOUBLE);

    const char* evt_log_ssl_res = EVENT_LOG_SSL();

    printf(" %s %s", evt_log_ssl_res, "\n\n");

    uint64_t time = get_event_time(evt_log_ssl_res);
    uint8_t state = get_event_state(evt_log_ssl_res);
    const char* ID = get_event_id(evt_log_ssl_res);

    printf("%s %"SCNu64 "%s", "Captured time: ", time, "\n");
    printf("%s %d %s", "Captured state: ", state, "\n");
    printf("%s %s %s", "Captured ID: ", ID, "\n\n");

    deleteContainer("stateDescript");
    deleteContainer("state");
    printf("\n");
    printf("\n-----------------------------------------------------------\n");
}

void EVENT_LOG_SEL_TEST(void)
{
    printf("\n-----------------------------------------------------------\n");

    double stateVal = 5.14;
    storeData("state", &stateVal, DOUBLE);

    const char* evt_log_sel_res =
        EVENT_LOG_SEL("UAV-SEL-TEST-HARD-FAIL", ROUTINE_HARD_FAIL, "Submodule Down");

    printf("%s %s", evt_log_sel_res, "\n");

    evt_log_sel_res =
        EVENT_LOG_SEL("UAV-SEL-TEST-SOFT-FAIL", ROUTINE_SOFT_FAIL, "Submodule Unresponsive");

    printf("%s %s", evt_log_sel_res, "\n");

    uint8_t state = get_event_state(evt_log_sel_res);

    printf("End of state: %d %s", state, "\n\n");

    deleteContainer("state");
    printf("\n");
    printf("\n-----------------------------------------------------------\n");
}

void LOG_EVENT_COMMON(void)
{
    printf("\n-----------------------------------------------------------\n");
    const char* data = "Data message test";
    data = LOG_INFO("LOG_INFO", data);
    const char* info_get = get_info(data);

    printf("%s %sData: ", data, "\n");
    printf("%s %sINFO: DATA ", info_get, "\n");

    const char* formatted_data = get_tag(data, "TIME: ");

    printf("%s %s", formatted_data, "\n");
    printf("\n-----------------------------------------------------------\n");
}

#ifdef ESP_TARGET
void app_main(void)
{
    EVENT_LOG_SDD_TEST();
    EVENT_LOG_SSL_TEST();
    EVENT_LOG_SEL_TEST();
    LOG_EVENT_COMMON();
}

#else 

int main(void)
{
    EVENT_LOG_SDD_TEST();
    EVENT_LOG_SSL_TEST();
    EVENT_LOG_SEL_TEST();
    LOG_EVENT_COMMON();

    return 0;
}

#endif