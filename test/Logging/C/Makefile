# Makefile for logger 

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -ggdb

# Source files
SRCS = ../../PTAM/C/_ptam.c logger.c main/logger_unittest.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executables
Logger_Target = Log_testing_suite

# Rule to build Logger_Target
$(Logger_Target): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
