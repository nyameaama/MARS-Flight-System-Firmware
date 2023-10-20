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

#include "onboardDisplay.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void _ONBOARD_DISPLAY::_init_(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    
  }
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::_showBoot(){
  display.fillScreen(WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(2.5);
  display.setCursor(27,10);
  display.println("HIVE 2");
  display.display();
}

void _ONBOARD_DISPLAY::_stateDisplay(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(9,8);
  display.println("ACTIVE");
  display.display();
}

void _ONBOARD_DISPLAY::stateARMED(){
  display.fillScreen(WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(2.5);
  display.setCursor(35,10);
  display.println("ARMED");
  display.display();
}

void _ONBOARD_DISPLAY::stateBYPASS(){
  display.fillScreen(WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(2.5);
  display.setCursor(27,10);
  display.println("BYPASS");
  display.display();
}

void _ONBOARD_DISPLAY::_stateConnection(uint8_t x){
  display.fillScreen(WHITE);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  if(x == GOOD_CONNECTION){
    display.setCursor(10,8);
    display.println("GC-ESTABL");
  }else{
    display.setCursor(5,8);
    display.println("NO-RESPNSE");
  }
  display.display();
}

void _ONBOARD_DISPLAY::state_wingAngleRL(uint8_t value){
  display.setTextSize(1);
  display.setCursor(0,30);
  display.println(value);
  display.display();
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::state_wingAngleRR(uint8_t value){
  display.setTextSize(1);
  display.setCursor(0,30);
  display.println(value);
  display.display();
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::state_wingAngleFL(uint8_t value){
  display.setTextSize(1);
  display.setCursor(0,30);
  display.println(value);
  display.display();
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::state_wingAngleFR(uint8_t value){
  display.setTextSize(1);
  display.setCursor(0,30);
  display.println(value);
  display.display();
  display.clearDisplay();
}