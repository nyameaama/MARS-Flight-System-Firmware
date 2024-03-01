# Makefile for logger unit test

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -ggdb

# Source files
SRCS = ../../../PTAM/C/_ptam.c ../logger.c logger_unittest.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executables
Logger_Testing_target = Logger_Unit_Testing_Suite

# Rule to build Logger_Unit_Testing_Suite
log_test: $(OBJS)
	$(CC) $(CFLAGS) -o $(Logger_Testing_target) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(Logger_Testing_target) $(OBJS)

.PHONY: clean
