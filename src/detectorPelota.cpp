
#include "detectorPelota.hpp"

using namespace cv;

namespace detectorPelota{

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

  int posX;
  int posY;

  void obtenerPosicion(int &x, int &y){
    x = posX;
    y = posY;
  }

  Mat filtrarPelota(Mat imgOriginal){

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

  bool esVisible(Mat imgOriginal){
  
    Mat imgPelota = filtrarPelota(imgOriginal);
    Moments pMomentos = moments(imgPelota);
    double dArea = pMomentos.m00;

    if(dArea > 10000){ 
      posY = pMomentos.m01 / dArea;
      posX = pMomentos.m10 / dArea;
    
      std::cout << "posicion pelota: " << posX << " " << posY << std::endl;
      return true;
    }else{ 
      return false;
    }
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
}
