# Compiler

CC = g++

# Flags to the compiler

CFLAGS = -Wall

all: H7

H7: shima.cpp 
	$(CC) $(CFLAGS) shima.cpp -o shima

clean:
	rm -rf H7
