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

#include"_wingDynamics.h"

uint8_t _WING_DYNAMICS::_translateRight(uint8_t range, uint8_t _mode){
    _motors *obj = new _motors();
    //Lateral
    if(_mode == 1){
        for(uint8_t i = obj -> returnServoPos(); i <= range;i++){
            obj -> adjustServoFWRIGHT(i);
            obj -> adjustServoRWRIGHT(i);
        }
    }
    if(_mode == 0){
        obj -> adjustServoFWRIGHT(range);
        obj -> adjustServoRWRIGHT(range);
    }
    delete obj;
    return range;
}

uint8_t _WING_DYNAMICS::_translateLeft(uint8_t range, uint8_t _mode){
    _motors *obj = new _motors();
    if(_mode == 1){
        for(uint8_t i = obj -> returnServoPos(); i <= range; i++){
            obj -> adjustServoFWLEFT(i);
            obj -> adjustServoRWLEFT(i);
        }
    }
    if(_mode == 0){
        obj -> adjustServoFWLEFT(range);
        obj -> adjustServoRWLEFT(range);
    }
    delete obj;
    return range;
}

uint8_t _WING_DYNAMICS::_translateUp(uint8_t range, uint8_t _mode){
    _motors *obj = new _motors();
    if(_mode == 1){
        for(uint8_t i = obj -> returnServoPos(); i <=  range; i++){
           obj -> adjustServoRWLEFT(range);
           obj -> adjustServoRWRIGHT(range); 
        }
    }
    if(_mode == 0){
        obj -> adjustServoRWLEFT(range);
        obj -> adjustServoRWRIGHT(range);
    }
    delete obj;
    return range;
}

uint8_t _WING_DYNAMICS::_translateDown(uint8_t range,uint8_t _mode){
    _motors *obj = new _motors();
    if(_mode == 1){
        for(uint8_t i = obj -> returnServoPos();i <= range;i++){
            std::cout << obj -> adjustServoFWLEFT(range);
            std::cout << obj -> adjustServoFWRIGHT(range);
        }
    }
    if(_mode == 0){
        obj -> adjustServoFWLEFT(range);
        obj -> adjustServoFWRIGHT(range);
    }
    delete obj;
    return range;
}