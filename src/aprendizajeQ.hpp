#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#define APRENDIZAJEQ

/*
 * Aprendizaje por Reforzamiento
 * Las recompensas se definen de [0-1]
 * Los Castigos se defien de [0-1]
 */
#define K 1
#define NUM_ESTADOS 14
#define NUM_ACCION 7
namespace AprendizajeQ {
  int estadoViejo ;
  int accion = -1;
  int Q[NUM_ESTADOS][NUM_ACCION];

  void leerValores();
  //void escribirValores();

  void tomarAccion(int);
  
  void actualizarValor(int);

  int recompensa(int,int);
  int distancia(int);
  int maxQ(int);


}

#endif
