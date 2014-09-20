#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>   
#include <iomanip>  // para controlar presicion punto flotante
#include <sstream>  // conversion de string a numeros

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "ros/ros.h"
#include "rosserial_arduino/Test.h"
#include <cstdlib>

#include "detectorPelota.hpp"
#include "Camara.hpp"
#include "Arbotix.hpp"
#include "estadosCamara/CamAbajoMedio.hpp"
using namespace cv;
using namespace std;


int main (int argc, char ** argv) {
 
  //detectorPelota::crearControlesPelota();

  ros::init(argc, argv, "test_srv");
  ros::NodeHandle n;
  ros::ServiceClient cliente;
  cliente = n.serviceClient<rosserial_arduino::Test>("moverRobot");
  Arbotix::iniciarServicio(&cliente);

  Camara::iniciarCamara();
  
  CamAbajoMedio pitazo;
  bool pateoDerecha;
  if (pitazo.irZonaPateo(pateoDerecha)){
    
    cout <<"yeiiii";
    
  } else {
    cout << "frieguense todos"; 
  }
  
  cv::waitKey(10000);
  return 0;
  
}






