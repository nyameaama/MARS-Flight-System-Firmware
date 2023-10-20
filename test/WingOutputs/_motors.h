#ifndef _MOTORSD
#define _MOTORSD

/*MIT License

Copyright (c) 2023 Limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#//include"../../util/defi.h"
#include<stdio.h>
#include<cstdint>

class _motors {
    public:
        _motors();
    public:
        //Motor firmware modules mapped to range 0 - 180 | Neutral = 90
        uint8_t adjustServoFWLEFT(uint8_t range);

        uint8_t adjustServoFWRIGHT(uint8_t range);

        uint8_t adjustServoRWLEFT(uint8_t range);

        uint8_t adjustServoRWRIGHT(uint8_t range);

        uint8_t mainThrottle(uint8_t range);

        uint8_t returnServoPos();

    private:
        uint8_t _init();
    
        uint8_t computeOptimumDelay(uint8_t delta);

};

#endif //_MOTORSD