CC = g++
CFLAGS = -I. -I../libs -L../libs/sole -Wall

all: main clear

main: engine.o engine-types.o engine-constants.hpp engine-types.hpp
	$(CC) -o main engine.o engine-types.o

clear:
	rm -rf engine.o engine-types.o