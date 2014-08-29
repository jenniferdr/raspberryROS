#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "RaspiCamCV.h" // para controlar la Pi-camara

Class DeteccionPelota{

  /* Valor HSV del color */

  // Matiz
  int matizInf = 0;
  int matizSup = 30; 

  // Saturacion
  int satInf = 70; 
  int satSup = 231;

  // Valor
  int valInf = 101;
  int valSup = 255;

  double posX;
  double posY;

public bool esVisible(imgOriginal){
  
  imgPelota = filtrarPelota(imgOriginal);
  Moments pMomentos = moments(imgPelota);
  double dArea = pMomentos.m00;

  if(dArea > 10000){ 
    posX = pMomentos.m01 / dArea;
    posY = pMomentos.m10 / dArea;
    return true;
  }else{ 
    return false;
  }
}

public par obtenerPosicion(){
  return new par ( pos X Y );
}

void crearControlesPelota(){
  // Crea una nueva ventana
  namedWindow("HSV Pelota",CV_WINDOW_AUTOSIZE); 
  
  // Crear un control para cambiar el Matiz (0 - 179)
  createTrackbar("MatizInf", "HSV Pelota", &matizInf, 179);
  createTrackbar("MatizSup","HSV Pelota", &matizSup, 179);
    
  // Crear un control para cambiar la saturacion (0-255)
  createTrackbar("SaturacionInf", "HSV Pelota", &satInf, 255);
  createTrackbar("SaturacionSup", "HSV Pelota", &satSup, 255);
    
  // Crear un control para cambiar el valor (0-255)
  createTrackbar("ValorInf","HSV Pelota", &valInf, 255);
  createTrackbar("ValorSup","HSV Pelota", &valSup, 255);
}

Mat filtrarPelota(imgOriginal){

  Mat imgHSV;
  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

  Mat imgFiltrada;
  inRange(imgHSV, Scalar(matizInf, satInf, valInf),
	  Scalar(matizSup, satSup, valSup), imgFiltrada);
    
  //morphological opening (removes small objects from the foreground)
  erode(imgFiltrada, imgFiltrada,
	getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgFiltrada,imgFiltrada,
	  getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  
  //morphological closing (removes small holes from the foreground)
  dilate( imgFiltrada, imgFiltrada, 
	  getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgFiltrada, imgFiltrada,
	getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

  return imgFiltrada;
}

};
