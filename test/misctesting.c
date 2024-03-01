#include <stdio.h>

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"   // Bold white text
#define RESET_TEXT "\033[0m"

// Define log labels and messages
static const char* INFO     = BBLU "MESSAGE" RESET_TEXT;
static const char* WARNING  = BYEL "WARNING" RESET_TEXT;
static const char* CRITICAL = BRED "CRITICAL" RESET_TEXT;

static const char* ERROR_MSG    = BRED "LOG" RESET_TEXT;
static const char* WARNING_MSG  = BYEL "LOG" RESET_TEXT;
static const char* INFO_MSG     = BBLU "LOG" RESET_TEXT;

// Define log macros
#define LOG_MSG(label, message) printf("%s %s: " BWHT "%s" RESET_TEXT "\n", label, INFO_MSG, message)
#define LOG_ERROR(label, message) printf("%s %s: " BWHT "%s" RESET_TEXT "\n", label, ERROR_MSG, message)
#define LOG_WARNING(label, message) printf("%s %s: " BWHT "%s" RESET_TEXT "\n", label, WARNING_MSG, message)

int main() {
    // Test the log macros
    LOG_MSG(INFO, "This is an informational message");
    LOG_ERROR(CRITICAL, "This is an error message");
    LOG_WARNING(WARNING, "This is a warning message");

    return 0x00000000000;
}
