CC = g++
CFLAGS = -I. -I../../libs -L../../libs/sole -Wall

all: main clear

main: ../engine-types.o ../engine-constants.hpp ../engine-types.hpp engine.spec.o
	$(CC) -o main ../engine-types.o engine.spec.o

clear:
	rm -rf ../engine-types.o engine.spec.o