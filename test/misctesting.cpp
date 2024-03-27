#include <stdio.h>

// Define the log_message struct
struct log_message
{
    const char* ID;
    const char* message;
};

// Declare the external function SYSTEM_LOG() that takes a pointer to log_message as a parameter
extern const char * SYSTEM_LOG(const struct log_message *msg);

int main() {
    // Create an instance of log_message
    struct log_message msg = {"12345", "This is a log message"};

    // Call SYSTEM_LOG() with a pointer to the log_message instance
    const char *result = SYSTEM_LOG(&msg);

    // Print the result returned by SYSTEM_LOG()
    printf("System log: %s\n", result);

    return 0;
}
