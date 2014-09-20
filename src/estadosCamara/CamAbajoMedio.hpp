//Secciones de la camara 
/* 1 Arriba-Medio
 * 2 Derecha-Arriba
 * 3 Izquierda-Arriba
 * 4 Izquierda-Inferior
 * 5 Izquierda-Inferior-Patada
 * 6 Derecha-Inferior-Patada
 * 7 Derecha-Inferior
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>   
#include <iomanip>  // para controlar presicion punto flotante
#include <sstream>  // conversion de string a numeros

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "rosserial_arduino/Test.h"
#include <cstdlib>

#include "../detectorPelota.hpp"
#include "../Camara.hpp"
#include "../Arbotix.hpp"

#ifndef H_CamAbajoMedio
#define H_CamAbajoMedio

class CamAbajoMedio{

private:
  bool enZonaPateo;
  cv::Mat imgOriginal;
  // posicion de la pelota
  int posX;
  int posY;

  // Puntos para seccionar imagen
  // Linea vertical izquierda
  CvPoint verticalIni;
  CvPoint verticalFin;
 
  // Linea vertical derecha
  CvPoint verticalIni2;
  CvPoint verticalFin2;

  // linea horizontal
  CvPoint horizontalIni;
  CvPoint horizontalFin;

  // linea vertical area de pateo
  CvPoint verticalIni3;
  CvPoint verticalFin3;

  // linea vertical del medio del area de pateo
  CvPoint verticalIni4;
  CvPoint verticalFin4;
    
  // Linea derecha area de pateo
  CvPoint verticalIni5;
  CvPoint verticalFin5;
   
public:
  

   CamAbajoMedio();
  void mostrarImagen();

  bool irZonaPateo(bool &pateoDerecha);

  // Devuelve true si ubicó la pelota en alguna camara
  // Devuelve false si no la vio en ninguna camara 
  bool ubicarPelota(bool &pateoDerecha);

  int cuadrantePelota();

  bool estaEnMedioArriba();

  bool estaEnDerecha();

  bool estaEnIzquierda();

  bool estaEnPateoIzquierda();

  bool estaEnPateoDerecha();
  
};

#endif
