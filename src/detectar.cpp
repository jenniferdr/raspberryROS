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

/* Valor HSV de la pelota (Hue, Saturation y Value) */
int iLowH = 0;
int iHighH = 30; // Color especifico a buscar

int iLowS = 70; 
int iHighS = 231;

int iLowV = 101;
int iHighV = 255;

void crearControlesPelota();
Mat filtrarPelota(Mat imgHSV);

int main (int argc, char ** argv) {
 
  /*
    ros::init(argc, argv, "test_srv");
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

    //Convertir el cuadro de BGR a HSV
    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
 
    Mat imgPelota = filtrarPelota(imgHSV); 

    Moments pMomentos = moments(imgPelota);
    double dM01 = pMomentos.m01;
    double dM10 = pMomentos.m10;
    double dArea = pMomentos.m00;
    
    if (dArea > 10000){
      
      int posX = dM10 / dArea;
      int posY = dM01 / dArea;
      
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

void crearControlesPelota(){
// Crea una nueva ventana
  namedWindow("HSV Pelota",CV_WINDOW_AUTOSIZE); 
  
  // Crear un control para cambiar la HUE (0 - 179)
  createTrackbar("LowH", "HSV Pelota", &iLowH, 179);
  createTrackbar("HighH","HSV Pelota", &iHighH, 179);
    
  // Crear un control para cambiar la saturacion (0-255)
  createTrackbar("LowS", "HSV Pelota", &iLowS, 255);
  createTrackbar("HighS", "HSV Pelota", &iHighS, 255);
    
  // Crear un control para cambiar el valor (0-255)
  createTrackbar("LowV","HSV Pelota", &iLowV, 255);
  createTrackbar("HighV","HSV Pelota", &iHighV, 255);
}


Mat filtrarPelota(Mat imgHSV){

  Mat imgFiltrada;

  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV),
	  Scalar(iHighH, iHighS, iHighV), imgFiltrada);
    
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


