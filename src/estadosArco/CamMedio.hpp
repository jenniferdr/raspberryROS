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

#include "../detectorArco.hpp"
#include "../Camara.hpp"
#include "../Arbotix.hpp"

#ifndef H_CamMedio
#define H_CamMedio

class CamMedio{

private:
	bool enPosicion; 
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

public:
  

	CamMedio();
	void mostrarImagen();
	bool irPosicion(bool &pateoDerecha);
	// Devuelve true si ubicó la pelota en alguna camara
	// Devuelve false si no la vio en ninguna camara 
	bool ubicarPelota(bool &pateoDerecha);

	int cuadrantePelota();
	
	bool estaEnCentro();
	
	bool estaEnDerecha();
	
	bool estaEnIzquierda();
	
	
  
};

#endif
