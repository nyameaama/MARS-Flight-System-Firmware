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

#ifndef DATA_MODULE_H
#define DATA_MODULE_H

#define MAX_DATA_SIZE 256

#include <stdio.h>
#include <string.h>
#include "../Logging/logger.h"

typedef enum {
    STRING,
    DOUBLE
} DataType;

struct DataContainer {
    char name[MAX_DATA_SIZE];
    char stringData[MAX_DATA_SIZE];
    double doubleData;
    DataType dataType;
};

//____________________________________________________________
/* Main subroutines -> stores value of datatypes (const char*, const void*, typedef)
===========================================================================
|    Designated ID   This creates the PTAM register with this ID an can only be referenced with this ID string
|    Data Value      Data value of types const char*, const void*, typedef
===========================================================================
*/
void storeData(const char* containerName, const void* data, DataType dataType);

//____________________________________________________________
/* Main subroutines -> retrieves all the values from PTAM container of appropriate typdef
===========================================================================
|   Designated ID   This references the PTAM container assigned with this ID
===========================================================================
*/
const void* retrieveData(const char* containerName, DataType* dataType);

//____________________________________________________________
/* Main subroutine -> Clear data in specific PTAM register
===========================================================================
|    Designated ID   This references the PTAM register assigned with this ID/container
===========================================================================
*/
void deleteContainer(const char* containerName);

#endif // DATA_MODULE_H