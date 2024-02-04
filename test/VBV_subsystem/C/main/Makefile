# Makefile for memory_allocator

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -ggdb

# Source files
SRCS = ../../../PTAM/C/_ptam.c ../VBV.c VBV_unit_testing.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executables
VBV_Testing_target = VBV_Unit_Testing_Suite

# Rule to build mem_alloc.out
VBV:
	$(CC) $(CFLAGS) -o $(VBV_Testing_target) $(SRCS)
