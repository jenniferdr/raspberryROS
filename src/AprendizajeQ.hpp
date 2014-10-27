
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef APRENDIZAJEQ
#define APRENDIZAJEQ

namespace AprendizajeQ {

  void leerValores();
  void escribirValores();

  void tomarAccion(int estado);
  void actualizarValor(int estado);
	int distancia (int estado);
	int maxQ(int estado);
	double recompensa(int estadoViejo ,int estadoNuevo);
}

#endif
