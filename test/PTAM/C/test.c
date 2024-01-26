#include "_ptam.h"
#include <stdio.h>

int main() {
    // Store string in container "C1"
    storeData("C1", "Test Packet 1", STRING);

    // Retrieve and print string data from container "C1"
    DataType dataType;
    const char* retrievedString = (const char*)retrieveData("C1", &dataType);
    if (retrievedString != NULL && dataType == STRING) {
        printf("Module A retrieved string data: %s\n", retrievedString);
    }

    // Store double in container "C2"
    double doubleValue = 3.1184;
    storeData("C2", &doubleValue, DOUBLE);

    // Retrieve and print double data from container "C2"
    const double* retrievedDouble = (const double*)retrieveData("C2", &dataType);
    if (retrievedDouble != NULL && dataType == DOUBLE) {
        printf("Module A retrieved double data: %f\n", *retrievedDouble);
    }

    // Delete container "C1"
    deleteContainer("C1");
}
