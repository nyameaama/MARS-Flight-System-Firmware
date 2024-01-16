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

#ifndef ONBOARD_DIS
#define ONBOARD_DIS

#define GOOD_CONNECTION 1
#define BAD_CONNECTION 0

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

class _ONBOARD_DISPLAY
{
  public:
    void _init_();

    void _showBoot();

    void stateARMED();

    void stateBYPASS();

    void _stateDisplay();

    void _stateConnection(uint8_t x);

    void state_wingAngleRL(uint8_t value);

    void state_wingAngleRR(uint8_t value);

    void state_wingAngleFL(uint8_t value);

    void state_wingAngleFR(uint8_t value);
};

#endif  // ONBOARD_DIS