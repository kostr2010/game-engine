CC = g++
CFLAGS = -I. -Wall

all:
	+$(MAKE) -C ability
	+$(MAKE) -C entity

main: engine.o
	$(CC) -o main engine.o