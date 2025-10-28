# Makefile for CSPC32 Assignment 2 - Task #2a

# --- Configuration ---
CC = gcc
# Flags: -Wall (Warnings), -std=c99 (C Standard), -g (Debugging info)
CFLAGS = -Wall -std=c99 -g 

# Define the directory where source files reside
SRCDIR = code

# Define the final executable name
TARGET = social_platform

# Define all source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# Define all object files (e.g., code/post.o, code/comment.o)
# The substitution replaces the .c extension with .o
OBJS = $(patsubst $(SRCDIR)/%.c,$(SRCDIR)/%.o,$(SRCS))

# --- Targets ---

# Default target: builds the executable
all: $(TARGET)

# 1. Rule to link all object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# 2. Rule to compile each .c file into a .o object file
# This uses VPATH to find the source files and -I to find the header files.
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(SRCDIR)

# Rule to clean up generated files (object files and executable)
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean