# Makefile for lab5 - Binary Search Tree
# ECE 2230, Fall 2025
# Zade Hyatt
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
LDFLAGS = -lm

# Target executable
TARGET = lab5

# Source files
SOURCES = lab5.c tree.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Compile source files to object files
%.o: %.c tree.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean

