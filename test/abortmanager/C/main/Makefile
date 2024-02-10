# Makefile for abort manager unit test

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -ggdb -lm

# Source files
SRCS =  ../abort.c abortmngrUnitTest.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executables
Abort_Testing_target = Abort_Unit_Testing_Suite

# Rule to build Abort_Unit_Testing_Suite
a-test:
	$(CC) $(CFLAGS) -o $(Abort_Testing_target) $(SRCS)
