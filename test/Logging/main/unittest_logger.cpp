
/**
 * @file unittest_logger.cpp
 * @brief logger unit test
 *
 * Testing various functions from the logger.cpp translation unit to verify update functionality
 *
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

#include "../../statemachine/_ptam.h"
#include "../logger.hpp"

extern "C"
{
        void app_main(void)
        {
                printf("Made entry point...\n\n");
                Logger Log;
                auto result = Log.EVENT_LOG_SDD();
                uint64_t time = Log.get_event_time(result);
                uint8_t state = Log.get_event_state(result);
                std::cout << state;
                std::string ID = Log.get_event_id(result);
                std::cout << result << "\n\nTime captured from callback: " << time << "\n\nID: " << ID;

                result = Log.EVENT_LOG_SSL();
                std::cout << result;
                time = Log.get_event_time(result);
                state = Log.get_event_state(result);
                std::cout << state;
                ID = Log.get_event_id(result);
                std::cout << result << "\n\nTime captured from callback: " << time << "\n\nID: " << ID;

                result = Log.EVENT_LOG_SEL("UAV-SEL-TEST-HARD-FAIL", mars_exception_t::ROUTINE_HARD_FAIL, "Submodule Down");
                std::cout << result;

                result = Log.EVENT_LOG_SEL("UAV-SEL-TEST-SOFT-FAIL", mars_exception_t::ROUTINE_SOFT_FAIL, "Submodule nonresponsive");
                std::cout << result;

                state = Log.get_event_state(result);
                std::cout << state;

                std::string data = "Data message test";
                data = Log.LOG_INFO(data);

                std::cout << data;

                data = "Data message test";
                std::string label = "CUSTOM";
                data = Log.LOG_INFO(label, data);

                std::cout << data;


                int64_t data_2 = 10'000;
                label = "CUSTOM INT";
                std::string marker = Log.LOG_INFO(label, data_2);

                std::cout << marker;

        }
}
