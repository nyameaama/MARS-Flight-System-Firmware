/*MIT License

Copyright (c) 2023 limitless Aeronautics

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

#include "_state.h"

char* stateDescript;
uint8_t state = 1;

//____________________________________________________________
/* Change state to prep
===========================================================================
|    void
===========================================================================
*/
    uint8_t SWITCH2PREP(){
        //Change variable
        uint8_t change = 0;
        //PREP -> 1
        if(compareX(stateDescript, PREP)){
            change = 1;
            state = 1;
        } 
        return change;
    }

//____________________________________________________________
/* Change state to armed
===========================================================================
|    void
===========================================================================
*/
    uint8_t SWITCH2ARMED(){
        //Change variable
        uint8_t change = 0;
        //ARMED -> 2
        if(compareX(stateDescript, ARMED)){
            change = 1;
            state = 2;
        }
        return change;
    }

//____________________________________________________________
/* Change state to bypass
===========================================================================
|    void
===========================================================================
*/
    uint8_t SWITCH2BYPASS(){
        //Change variable
        uint8_t change = 0;
        //BYPASS -> 3
        if(compareX(stateDescript, BYPASS)){
            change = 1;
            state = 3;
        }
        return change;
    }

//____________________________________________________________
/* Handler to update state description
===========================================================================
|    void
===========================================================================
*/
    void updateState(char* state){
        //Update state description value
        stateDescript = state;
    }

//____________________________________________________________
/* Compare two strings of type <std::string>
===========================================================================
|    void
===========================================================================
*/
    //If output = 1, strings match
    uint8_t compareX(char* x, char* y){
        return strcmp(x, y);
    }