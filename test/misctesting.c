#include <stdio.h>
#include <string.h>

int main() {
    const char* myString = "Hello, World!";  // Example string

    // Find the size of the string (including the null terminator)
    size_t stringSize = strlen(myString) + 1;

    // Calculate the total size in bytes
    size_t totalSize = stringSize * sizeof(char);

    printf("Size of the string: %zu bytes\n", totalSize);

    return 0;
}
