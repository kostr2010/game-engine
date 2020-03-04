CC = g++
CFLAGS = -I. -I../../libs -L../../libs/sole -Wall

all: main clear

main: engine.spec.cc ../main-classes/main-classes.cc ../factories/entity-factory.cc ../factories/ability-factory.cc ../constants/constants.cc ../main-classes/main-classes.hpp ../factories/entity-factory.hpp ../factories/ability-factory.hpp ../constants/constants.hpp
	$(CC) -o main -fprofile-arcs -ftest-coverage engine.spec.cc ../main-classes/main-classes.cc ../factories/entity-factory.cc ../factories/ability-factory.cc ../constants/constants.cc

clear:
	cd ../../ && find . -type f -name '*.cc' -delete