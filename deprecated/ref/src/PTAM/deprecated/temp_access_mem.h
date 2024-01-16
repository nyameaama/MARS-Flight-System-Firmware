/*MIT License

Copyright (c) 2020 Nyameaama Gambrah

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

#ifndef PTAM_
#define PTAM_

#include "../../util/defi.h"
/*
    PTAM implementation is a series of statically allocated 1D arrays
    which correspond to their respective data type

    Each data pair has two values
*/

// Arrays declared
// SPACE DECLARED FOR 5 PAIRS (~10)
#define length 10

class PTAM
{
  public:
    // Method to add data to program temp access memory
    // Returns the size of data sent
    //+3 Overload

    uint8_t PTAM_ADD_BASE_DOUBLE(char* baseID, double data);

    uint8_t PTAM_ADD_BASE_8(char* baseID, uint8_t data);

    uint8_t PTAM_ADD_BASE_32(char* baseID, uint32_t data);

    uint8_t PTAM_ADD_BASE_CHAR(char* baseID, char* data);

    // Method to retrieve data from program temp access memory
    // Returns queried data
    //!!!Disclaimer!!!
    // Unable to use templates so used messy workaround
    //!!!!!!!!!!!!!!!!!!
    char* PTAM_RETRIEVE_BASE_CHAR(char* baseID);

    uint8_t PTAM_RETRIEVE_BASE_8(char* baseID);

    uint32_t PTAM_RETRIEVE_BASE_32(char* baseID);

    double PTAM_RETRIEVE_BASE_DOUBLE(char* baseID);

    // Method to clear entire PTAM data for next program cycle
    // void PTAM_CLEAR_ALL();
};

#endif