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


#include "_ptam.h"

struct DataContainer dataContainers[MAX_DATA_SIZE];
int numContainers = 0;

//____________________________________________________________
/* Utillity subroutines -> Retrieve container
===========================================================================
|    
===========================================================================
*/
struct DataContainer* findContainer(const char* containerName) {
    for (int i = 0; i < numContainers; ++i) {
        if (strcmp(dataContainers[i].name, containerName) == 0) {
            return &dataContainers[i];
        }
    }
    EVENT_LOG_SEL("PTAM_PROCESS", ROUTINE_SOFT_FAIL, "Container undefined access");
    return NULL;
}

//____________________________________________________________
/* Main subroutines -> stores value of datatypes (const char*, const void*, typedef)
===========================================================================
|    Designated ID   This creates the PTAM register with this ID an can only be referenced with this ID string
|    Data Value      Data value of types const char*, const void*, typedef
===========================================================================
*/

void storeData(const char* containerName, const void* data, DataType dataType) {
    struct DataContainer* container = findContainer(containerName);
    if (container == NULL) {
        if (numContainers >= MAX_DATA_SIZE) {
            //Error: Maximum number of containers reached
            EVENT_LOG_SEL("PTAM_PROCESS", ROUTINE_SOFT_FAIL, "Maximum number of containers reached");
            return;
        }

        container = &dataContainers[numContainers++];
        strncpy(container->name, containerName, MAX_DATA_SIZE - 1);
        container->name[MAX_DATA_SIZE - 1] = '\0';
    }

    switch (dataType) {
        case STRING:
            strncpy(container->stringData, (const char*)data, MAX_DATA_SIZE - 1);
            container->dataType = STRING;
            break;
        case DOUBLE:
            container->doubleData = *((const double*)data);
            container->dataType = DOUBLE;
            break;
        default:
            //Error: datatype
            EVENT_LOG_SEL("PTAM_PROCESS", ROUTINE_SOFT_FAIL, "undefined datatype");
            break;
    }
}

//____________________________________________________________
/* Main subroutines -> retrieves all the values from PTAM container of appropriate typdef
===========================================================================
|   Designated ID   This references the PTAM container assigned with this ID
===========================================================================
*/
const void* retrieveData(const char* containerName, DataType* dataType) {
    struct DataContainer* container = findContainer(containerName);
    if (container != NULL) {
        *dataType = container->dataType;
        switch (*dataType) {
            case STRING:
                return container->stringData;
            case DOUBLE:
                return &(container->doubleData);
            default:
                //Error: datatype
                EVENT_LOG_SEL("PTAM_PROCESS", ROUTINE_SOFT_FAIL, "undefined datatype");
                break;
        }
    }
    //Container not found
    EVENT_LOG_SEL("PTAM_PROCESS", ROUTINE_SOFT_FAIL, "Container undefined access");
    return NULL;
}

//____________________________________________________________
/* Main subroutine -> Clear data in specific PTAM register
===========================================================================
|    Designated ID   This references the PTAM register assigned with this ID/container
===========================================================================
*/
void deleteContainer(const char* containerName) {
    struct DataContainer* container = findContainer(containerName);
    if (container != NULL) {
        // Move the last container to the deleted position
        *container = dataContainers[numContainers - 1];
        numContainers--;
    } else {
        //Error: Container not found
        EVENT_LOG_SEL("PTAM_PROCESS", ROUTINE_SOFT_FAIL, "Container undefined access");
    }
}