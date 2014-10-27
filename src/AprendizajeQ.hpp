#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifndef APRENDIZAJEQ
#define APRENDIZAJEQ

/*
 * Aprendizaje por Reforzamiento
 * Las recompensas se definen de [0-1]
 * Los Castigos se defien de [0-1]
 * Las Acciones se definen de la siguiente manera:
 * a0 = caminar poco
 * a1 = caminar
 * a2 = caminar mucho
 * a3 = girar derecha
 * a4 = girar izquierda
 * a5 = girar poco derecha
 * a6 = girar poco izquierda
 */

#define K 1
#define NUM_ESTADOS 14
#define NUM_ACCION 7
namespace AprendizajeQ {
	
  void leerValores();
  void escribirValores();
	
  void tomarAccion(int);
	
  void actualizarValor(int);
	
  int recompensa(int,int);
  int distancia(int);
  int maxQ(int);
}

#endif
