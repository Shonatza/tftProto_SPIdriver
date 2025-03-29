# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -Iinclude   # Include headers from /include
LDFLAGS = -lbcm2835            # Link Raspberry Pi BCM2835 library

# Source and object files
SRC_DIR = .
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
TARGET = tftDriver.exe

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run with sudo
run: $(TARGET)
	sudo ./$(TARGET)

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean