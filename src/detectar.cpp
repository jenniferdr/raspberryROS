#include <stdio.h>
#include "ros/ros.h"
#include "detectorPelota.hpp"
#include "Camara.hpp"
#include "Arbotix.hpp"
#include "AprendizajeQ.hpp"
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
  //inicializar valores Q
  AprendijajeQ::leerValores();

  CamAbajoMedio pitazo;
  bool pateoDerecha;
  if (pitazo.irZonaPateo(pateoDerecha)){
    
    if (pateoDerecha ==true) {
      Arbotix::peticion("q");	
	
    } else {
      Arbotix::peticion("e");
    }	    
    cout <<"yeiiii";    
  } else {
    cout << "frieguense todos"; 
  }
  
  //respaldar valores Q en archivo
  AprendizajeQ::escribirValores();
  cv::waitKey(10000);
  return 0;
  
}






