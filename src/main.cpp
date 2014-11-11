//#include "AprendizajeQ.hpp"
#include <stdlib.h>
#include <iostream>
#include <time.h>

int main(){
  float max ;
  srand(time(NULL));
  std::cout << (rand()%7) << std::endl;
  std::cout << (rand()%7) << std::endl;
 std::cout << (rand()%7) << std::endl;
 std::cout << (rand()%7) << std::endl;
 std::cout << (rand()%7) << std::endl;
  //AprendizajeQ::actualizarValor(3);
 /*Q[3][0] = 0.1;
    Q[3][1] = 0.2;
    Q[3][2] = 0.3;
    Q[3][3] = 0.4;
    Q[3][4] = 0.5;
    Q[3][5] = 0.6;
    Q[3][6] = 0.0;
    Q[4][3] = 0.7;
    Q[4][5] = 0.3;
 */
  //std::cout << max << std::endl;
    //AprendizajeQ::leerValores();
   	AprendizajeQ::leerValores();
	AprendizajeQ::escribirValores();
//	AprendizajeQ::leerValores();
  //AprendizajeQ::escribirValores();
	
	//std::cout << distancia<< std::endl;
	
	return 0;

}
