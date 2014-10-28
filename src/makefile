all: main

main: AprendizajeQ.o  main.o

	g++ -std=c++11 -O2 -o main AprendizajeQ.o main.o 

aprendizajeQ.o: AprendizajeQ.cpp AprendizajeQ.hpp

	g++ -std=c++11 -O2 -c AprendizajeQ.cpp

main.o: main.cpp AprendizajeQ.hpp

	g++ -std=c++11 -O2 -c main.cpp


clean:

	rm *.o  main
