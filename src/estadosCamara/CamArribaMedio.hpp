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

#ifndef H_CamArribaMedio
#define H_CamArribaMedio

class CamArribaMedio{

private:
 
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
   
public:
  

  CamArribaMedio();
  void mostrarImagen();

  // Devuelve true si ubicó la pelota en alguna camara
  // Devuelve false si no la vio en ninguna camara 
  bool ubicarPelota();

  int cuadrantePelota();

  bool estaEnCentro();

  bool estaEnDerecha();

  bool estaEnIzquierda();

  bool estaEnAbajo();
  
};

#endif
