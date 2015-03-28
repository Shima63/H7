# Compiler

CC = g++

# Flags to the compiler

CFLAGS = -Wall

all: H7

H7: shima.cpp
	$(CC) $(CFLAGS) print.cpp earthquake.cpp station.cpp shima.cpp -o shima 

clean:
	rm -rf shima​