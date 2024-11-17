# Define the compiler and the flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable
TARGET = test

# Find all .c files in the current directory
SRCS = $(wildcard *.c)

# Define the object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to link the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove compiled files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
