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

#ifndef H_CamIzquierdaArriba
#define H_CamIzquierdaArriba

class CamIzquierdaArriba{

private:

  cv::Mat imgOriginal;
  CvPoint verticalIni; 
  CvPoint verticalFin; 
  int posX;
  int posY;

public:
  

  CamIzquierdaArriba();
  void mostrarImagen();


  // Devuelve true si ubicó la pelota en alguna camara
  // Devuelve false si no la vio en ninguna camara 
  bool ubicarPelota();
 int cuadrantePelota();
  bool estaEnDerecha();
  bool estaEnIzquierda();

};

#endif
