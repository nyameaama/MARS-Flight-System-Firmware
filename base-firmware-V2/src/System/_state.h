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

#ifndef _STATE_
#define _STATE_

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "stdlib.h"

#define PREP "PREP"
#define ARMED "ARMED"
#define BYPASS "BYPASS"

//____________________________________________________________
/* Change state to prep
===========================================================================
|    void
===========================================================================
*/
uint8_t SWITCH2PREP();

//____________________________________________________________
/* Change state to armed
===========================================================================
|    void
===========================================================================
*/
uint8_t SWITCH2ARMED();

//____________________________________________________________
/* Change state to bypass
===========================================================================
|    void
===========================================================================
*/
uint8_t SWITCH2BYPASS();

//____________________________________________________________
/* Compare two strings of type <std::string>
===========================================================================
|    void
===========================================================================
*/
uint8_t compareX(char* x, char* y);

//____________________________________________________________
/* Handler to update state description
===========================================================================
|    void
===========================================================================
*/
void updateState(char* state);


#endif  //_STATE_