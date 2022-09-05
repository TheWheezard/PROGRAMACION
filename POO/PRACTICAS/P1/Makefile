EXES = test-P1-auto test-P1-consola
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -pedantic
CPPFLAGS = -DP1 -I../Tests-auto -I.
VPATH = ../Tests-auto:.
DIR = ../../Lopez_Sierra_Javier/P1/

CLASSES = cadena.o fecha.o


.PHONY: all clean


all: $(CLASSES) $(EXES)

classes: $(CLASSES)

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(CLASSES)	
	$(CXX) $(CXXFLAGS) $^ -o $@

test-P1-consola: test-fechacadena-consola.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

dist: 
	ls -1 $(DIR)fecha.hpp $(DIR)fecha.cpp $(DIR)cadena.hpp $(DIR)cadena.cpp $(DIR)Makefile | \
	tar -cvzf ../Lopez_Sierra_Javier.tar.gz -T -

clean: 
	@$(RM) $(EXES) *.o