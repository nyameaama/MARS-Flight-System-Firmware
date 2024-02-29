# Makefile for Vehicle boot-up validator (VBV)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wunused-variable -Wextra -std=c11 -pedantic

CFLAGS_DEBUG = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -ggdb

CFLAGS_SO = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -fPIC -shared

CFLAGS_SO_DEBUG = -Wall -Wunused-variable -Wextra -std=c11 -pedantic -ggdb -fPIC -shared

# Source files
SRCS = ../../../PTAM/C/_ptam.c ../VBV.c VBV_unit_testing.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executables
VBV_Testing_target = VBV_Unit_Testing_Suite

# Rule to build VBV_Unit_Testing_Suite
VBV:
	$(CC) $(CFLAGS) -o $(VBV_Testing_target) $(SRCS)

VBV_so:
	$(CC) $(CFLAGS_SO) -o vbv_sub.so $(SRCS)

VBV_so_debug:
	$(CC) $(CFLAGS_SO_DEBUG) -o VBV_sub_d.so $(SRCS)

VBV_Debug:
	$(CC) $(CFLAGS_DEBUG) -o vbv_sub $(SRCS)