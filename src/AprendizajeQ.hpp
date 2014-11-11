#include <iomanip> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#ifndef APRENDIZAJEQ
#define APRENDIZAJEQ

namespace AprendizajeQ {


  float distancia (int estado);
  float maxQ(int estado);
  float recompensa(int estadoViejo ,int estadoNuevo);
  


  void leerValores();
  void escribirValores();

  void tomarAccion(int estado);
  void actualizarValor(int estado);

}
#endif
