all: main

main: AprendizajeQ.o  main.o

	g++   -o main AprendizajeQ.o main.o 

aprendizajeQ.o: AprendizajeQ.cpp AprendizajeQ.hpp

	g++  -c AprendizajeQ.cpp

main.o: main.cpp AprendizajeQ.hpp

	g++  -c main.cpp


clean:

	rm *.o  main
