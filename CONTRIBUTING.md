Repository Structure

|--Root
|   | -- Component Circuits
|   | -- DevGroundM
|   | -- LIAM
|   | -- MATLAB
|   | -- assets
|   | -- base-firmware
|   | -- test
|   | LICENSE
|   | README
|   | CONTRIBUTING.md --> THIS FILE

Initial Description:

Component Circuits
    - This subdirectory contains documents with diagrams representing sensor schematics and how they are interfaced with the board

DevGroundM
    - This subdirectory contains the html file for the webpage hosted by the vehicle during initialization and flight setup

LIAM`
    - This subdirectory contains the code for the LIAM sub project. Lightweight Intelligent Aerial Mapper is an internal project aimed at developing advanced onboard autonomous flight planning and navigation algorithms for HIVE platform vehicles

assets
    - This subdirectory contains assets related to the development of the drone such as datasheets and research papers used for the Navigation and Control Algorithms

base-firmware
    - This subdirectory contains the main source files for the vehicle firmware. It is an ESP-IDF project built with Cmake. 

test
    - This subdirectory contains all the test and sample code written and tested before addition to main firmware source files. This is where a lot of work is done debugging and it contains a separate ESP-IDF project in order to test drivers on the board.

    |--test
    |   |
    |   | -- PID
    |   | -- PTAM
    |   | -- WingOutputs
    |   | -- atmegaChipTesting
    |   | -- server
    |   |   | --server-test (ESP-IDF Project)
    |   | -- statemachine
    |   | README


# Code Style and Code Commenting

To maintain maintenance and code readability, we have implemented a standard that all repository contributors of Limitless Aeronautics should follow.

## Coding style

The majority of the code written is in either C/C++, or Assembly language. C++ code with follow the clang_format coding style to increase readability and prevent confusion among new contributors and new commits from established contributors.

For example,

```
Loglevel_t Logger::create_log_message(flight_data_t &flight_data)
{
    SharedMemory &sharedMemory = SharedMemory::getInstance();
    std::ofstream logFile("Logging_Results.txt");
    if (logFile.is_open())
    {
        logFile << "\nLOG EVENT:" << std::endl;
        logFile << "\t{" << std::endl;
        logFile << "\t\tID: " << flight_data.id << std::endl;
        logFile << "\t\tTIME: " << flight_data.timestamp << std::endl;
        logFile << "\t\tDATA: " << flight_data.data << std::endl;
        logFile << "\t\tMACHINE STATE: " << machine_state << std::endl;
        logFile << "\t}\n\n" << std::endl;

        logFile.close();
    }
    else
    {
        return status = LOG_ERROR;
    }

    sharedMemory.storeMessage(flight_data);
    return status = LOG_INFO;
}
```

The code presented here is an example of clang format being used. You may already be familiar with the style as it is learned early on in developer's career.


## Commenting

When writing new functions, it is required that you use the boxing or Doxygen commenting sytle to document your code. With Doxygen being the most preferred as it gives use the ability to generate documentation instead of manually creating the docs after the code.

**Doxygen Commenting Style**

```/**
 * @brief Creates a log message based on flight data and stores it in a file.
 *
 * This function takes flight data as input and creates a log message containing
 * information such as ID, timestamp, data, and machine state. The log message
 * is stored in a file named "Logging_Results.txt". Additionally, the log message
 * is stored in shared memory using the SharedMemory class.
 *
 * @param[in] flight_data The flight data structure containing ID, timestamp, and data.
 * @return The status of the log creation and storage. Returns LOG_INFO on success,
 *         or LOG_ERROR if the log file couldn't be opened for writing.
 */
Loglevel_t Logger::create_log_message(flight_data_t &flight_data) {
    SharedMemory &sharedMemory = SharedMemory::getInstance();
    std::ofstream logFile("Logging_Results.txt");
    if (logFile.is_open()) {
        logFile << "\nLOG EVENT:" << std::endl;
        logFile << "\t{" << std::endl;
        logFile << "\t\tID: " << flight_data.id << std::endl;
        logFile << "\t\tTIME: " << flight_data.timestamp << std::endl;
        logFile << "\t\tDATA: " << flight_data.data << std::endl;
        logFile << "\t\tMACHINE STATE: " << machine_state << std::endl;
        logFile << "\t}\n\n" << std::endl;

        logFile.close();
    } else {
        return status = LOG_ERROR;
    }

    sharedMemory.storeMessage(flight_data);
    return status = LOG_INFO;
}
```

**Box Commenting Style**

```
//____________________________________________________________
/* Creates a log message based on flight data and stores it in a file.
===========================================================================
|    flight_data   The flight data structure containing event information
|    status        The status of the log creation and storage
|    LOG_ERROR     Logging Error Level
|    LOG_INFO      Logging Information level
===========================================================================
*/
Loglevel_t Logger::create_log_message(flight_data_t& flight_data) {
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    std::ofstream logFile("Logging_Results.txt");
    if (logFile.is_open()) {
        logFile << "\nLOG EVENT:" << std::endl;
        logFile << "\t{" << std::endl;
        logFile << "\t\tID: " << flight_data.id << std::endl;
        logFile << "\t\tTIME: " << flight_data.timestamp << std::endl;
        logFile << "\t\tDATA: " << flight_data.data << std::endl;
        logFile << "\t\tMACHINE STATE: " << machine_state << std::endl;
        logFile << "\t}\n\n" << std::endl;

        logFile.close();
    } else {
        return status = LOG_ERROR;
    }

    sharedMemory.storeMessage(flight_data);
    return status = LOG_INFO;
}
```


# Code interfacing

Our coding style involves declaring our necessary function prototypes and other tools within header files, then defining them within the translation unit(source file) to provide the needed APIs for future use.

For example, we would declare a function prototype named func_prototype within a class in a file name tool.h(pp) to later define within a translation unit:


**tool.h(pp)**

```
class toolbox
{
    toolbox(){}

public:
    /* Apply our commenting style here */
    void func_prototype(void);

private:


}
```

We require functions pertaining to certain functionality within a subsystem to be declared within a class because of the modularity it comes with it. Everything we need will be within the scope of the class, so we can then easily reference the API to get what we need without conflicts.



## Visualization

Code visualization is a helpful way to describe what something does without having to do much speaking and more drawing

Take a look at the following snippet:

```;/////////////////////////////////////////////////////////////////////////////
; Name:        boot.asm
; Purpose:     Main boot sector code
; Author:      Lukas Jackson
; Modified by:
; Created:     7/22/2023
; Copyright:   (c) [2023] Lukas Jackson
; Licence:     GNU Public License (GPL)
;/////////////////////////////////////////////////////////////////////////////

;Define the bit mode and set the starting address. [Boot->0x7c00]
[bits 16]
[org 0x7c00]


section .text
    global _start

    ; -----------------------------------------------------------------------
    ; Memory Segments:
    ; -----------------------------------------------------------------------
    ; 0x0000  |-----------------|
    ;         |                 |
    ;         |                 |
    ;         |                 |
    ;         |   Bootloader    |    ; The bootloader is loaded at address 0x0000
    ;         |                 |
    ;         |                 |
;0x7C00/CS:IP |-----------------|    ; The CS:IP register points to 0x0000:0x7C00 CS = Code Segment & IP = Instruction Pointer.
    ;         |   Code Segment  |    ; The code segment starts at 0x0000:0x7C00
    ; 0x7C00  |                 |
    ;         |                 |
    ;         |-----------------|
    ;         |     Reserved    |    ; Reserved memory region, may vary by system
    ;         |-----------------|
    ;         |   Data Segment  |    ; The data segment starts at 0x0000:0x10000
    ; 0x10000 |                 |
    ;         |                 |
    ;         |-----------------|
    ;         |  Extra Segment  |    ; The extra segment starts at 0x0000:0x20000
    ; 0x20000 |                 |
    ;         |                 |
    ;         |-----------------|
    ;         |  Stack Segment  |    ; The stack segment starts at 0x0000:0xFFFF0
    ; 0xFFFF0 |                 |
    ;         |                 |
    ;         |-----------------|
    ;         |     BIOS        |    ; BIOS and system-specific regions
    ;         |                 |
    ; 1MB+    |-----------------|
    ; -----------------------------------------------------------------------

_start:
    ;Set up the segment registers
    xor ax, ax      ;Use bitwise XOR to compare ax with itself. AX = 0x0000
    mov ds, ax      ;Set ds(Data Segment) to the value of ax(Which is 0 or 0x0000)
    mov es, ax      ;Set ex(Extra Segment) to the same as both ds and ax.

    ;Set up the stack.
    mov ax, 0x9000  ;Loads 0x9000 into ax where 0x9000 is the address for the stack
    mov ss, ax      ;Set the ss(Stack Segment) to the value of ax
    mov sp, 0xFFFF  ;Set the sp(Stack Pointer) to to 0xFFFF to initialize the stack

;Call the print_noun function
    call print_noun

    ;Activate an infinite loop to prevent crashes.
    cli             ;Disables interrupts
    hlt             ;Halts the processor


;Create the print_noun function
print_noun:
    ;Print the operating system's name on the screen

    ;To be safe, we will set up the segment registers again.
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov si, msg
    mov ah, 0x0E

.repeat:
    lodsb           ;Loads the byte pointed to by SI into AL and increments SI
    cmp al, 0       ;Compares al with 0 to verify if the next increment is null(empty)
    je .done        ;Jumps to .done label if it is empty
    
    int 0x10        ;Call the bios interrupt to print the character
    jmp .repeat     ;Repeat until null terminator is detected

.done:
    ret        ;Return from the function called from

msg db 'Booting into Curtains OS', 0    ;String that is null terminated.

times 510-($-$$) db 0   ;Pad the rest of the sector to reach 510 bytes
dw 0xAA55           ;PC boot signature.
```
In the figure, the author shows a clear representation of memory segments without having to go into too much writing on it. Though it is not a strict requirement, it is greatly appreciated if you add a little visual context to your code so that we can understand more faster and without having to read through a bunch of functions.



## Code summary

Just like functions having a summary, and/or visualization, you also have the option to summarize the usage of the file with a quick explaination at the top using simple commenting.

For long paragraph comments, you should use the forward slash (/) and the asterisk (*) symbols to create a comment block.


**Comment Block**
```
/* This is a comment block contained onto one line */

/*
This is a comment block spanning a few lines
Code I put within these barriers are interpreted as comments.
*/
```

**Functions within a program**

Just like a summary, you can also list of the name of each function prototype, class, enum, ect. inside a summary to reduce the need to manually search for functions.


**Function summaries**
```
`example.h(pp)

/* Within this file contain the following functions:

void function_prototype1        Function that returns nothing
int function_getter             Function getter
void*(*Function)(int, int)      Function pointer with no return value
int*(Function)(void*, int)      Function pointer that returns a pointer to an integer

*/
```

# Comment indentation

Shown above in the example were very evenly aligned comments. The indentation of comments is a unique detail to add to your code when collaborating with us. This helps to keep comments more organised and not all over the place.


