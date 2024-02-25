# Makefile for abort manager unit test

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wunused-variable -Wextra -std=c++17 -pedantic -ggdb -lm

CFLAGS_R2 = -Wall -Wunused-variable -Wextra -std=c++17 -pedantic -g -lm


# Source files
SRCS =  ../abort.cpp abortmngrUnitTest.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executables
Abort_Testing_target = Abort_Unit_Testing_Suite

# Rule to build Abort_Unit_Testing_Suite
a-test:
	$(CC) $(CFLAGS) -o $(Abort_Testing_target) $(SRCS) -lstdc++

r2_test:
	$(CC) $(CFLAGS_R2) -o $(Abort_Testing_target) $(SRCS) -lstdc++