#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>   // para strings
#include <iomanip>  // para controlar presicion punto flotante
#include <sstream>  // conversion de string a numeros

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "RaspiCamCV.h" // para controlar la Pi-camara

#include "ros/ros.h"
#include "rosserial_arduino/Test.h"
#include <cstdlib>

using namespace cv;
using namespace std;

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

  double posX;
  double posY;

  void obtenerPosicion(double &x, double &y){
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
      posX = pMomentos.m01 / dArea;
      posY = pMomentos.m10 / dArea;
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


int main (int argc, char ** argv) {
 
  /*ros::init(argc, argv, "test_srv");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<rosserial_arduino::Test>("moverRobot");
    rosserial_arduino::Test srv;
  */
  // capturar la camara en vivo. Camara 0 
  RaspiCamCvCapture * camara = raspiCamCvCreateCameraCapture(0);
  
  /*if (!camara.isOpened()) {
    cout << "No se pudo abrir la camara" << endl;
    return -1;
    }*/

  Mat imgOriginal = raspiCamCvQueryFrame(camara);
  Size sizeImgOrig = imgOriginal.size();

  // Puntos para seccionar la imagen
  CvPoint horizonIni = cvPoint(00,(sizeImgOrig.height)/2);
  CvPoint horizonFin =
    cvPoint(sizeImgOrig.width,(sizeImgOrig.height)/2); 
  CvPoint verticalIni =
    cvPoint((sizeImgOrig.width)/2,(sizeImgOrig.height)/2);
  CvPoint verticalFin =
    cvPoint(((sizeImgOrig.width)/2), sizeImgOrig.height); 

  while (1){
    imgOriginal = raspiCamCvQueryFrame(camara);
    //por hacer> verificar si no hubo error  
 
    Mat imgLines = Mat::zeros(  sizeImgOrig , CV_8UC3 );

    // Dibujar division de la pantalla
    line(imgLines, horizonIni, horizonFin, cvScalar(0,255,0), 1);
    line(imgLines, verticalIni,verticalFin, cvScalar(0,255,0), 1);

    if (detectorPelota::esVisible(imgOriginal)){
      double posX;
      double posY;
      detectorPelota::obtenerPosicion(posX,posY);
      
      circle(imgLines,Point2f(posX,posY),50,Scalar(255,0,0),1,CV_AA,0);
      
      /*******  Seguir Pelota **********/
      if (posY < horizonIni.y){
	//srv.request.input = "w";
	cout << " Camino hacia adelante" << endl ;
	
      } else if (posX < verticalIni.x){
	//srv.request.input = "a";
	cout << " Camino a la Izq"  << endl;
	
      } else { 
	//srv.request.input = "d";
	cout << " Camino a la Derecha" << endl ; 
      }
      /*if (client.call(srv)){
	ROS_INFO("Sum: %s", srv.response.output.c_str());
	}else{
	ROS_ERROR("Failed to call service moverRobot");
	return 1;
	}*/
      
    }
    
    imgOriginal = imgOriginal + imgLines;
    imshow("Original", imgOriginal);
    
    if (waitKey(30) == 27) break; // Esc
 
  }
  return 0;
  
}






