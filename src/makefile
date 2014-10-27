all: main

main: aprendizajeQ.o  main.o

	g++ -std=c++11 -O2 -o main aprendizajeQ.o main.o 

aprendizajeQ.o: aprendizajeQ.cpp aprendizajeQ.hpp

	g++ -std=c++11 -O2 -c aprendizajeQ.cpp

main.o: main.cpp aprendizajeQ.hpp

	g++ -std=c++11 -O2 -c main.cpp


clean:

	rm *.o  main
