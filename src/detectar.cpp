#include <stdio.h>
#include "ros/ros.h"
#include "detectorPelota.hpp"
#include "Camara.hpp"
#include "Arbotix.hpp"
#include "AprendizajeQ.hpp"
#include "estadosCamara/CamAbajoMedio.hpp"
//#include "estadosArco/CamMedio.hpp"
#include <ctime>
using namespace cv;
using namespace std;


int main (int argc, char ** argv) {
  time_t ahora = time(0);
  tm *t = localtime(&ahora);
  std::cout << "El tiempo inicial es: "<< 1+ t->tm_hour << "h" << 1 +t->tm_min << "m" << t->tm_sec<< "s" << std::endl;
  //detectorPelota::crearControlesPelota();


  ros::init(argc, argv, "test_srv");
  ros::NodeHandle n;
  ros::ServiceClient cliente;
  cliente = n.serviceClient<rosserial_arduino::Test>("moverRobot");
  Arbotix::iniciarServicio(&cliente);

  Camara::iniciarCamara();
  //inicializar valores Q
  AprendizajeQ::leerValores();

  CamAbajoMedio pitazo;
  bool pateoDerecha;
  if (pitazo.irZonaPateo(pateoDerecha)){
    //CamMedio posicion;
    //	  if (posicion.irPosicion(pateoDerecha)){
    if (pateoDerecha == true) {
      Arbotix::peticion("q");	
      
    } else {
      Arbotix::peticion("e");
    }	    
    cout << "Pateo" ;
    //	  }
  } else {
	  cout << "No la vio por ningun lado"; 
  }
  
  //respaldar valores Q en archivo
  AprendizajeQ::escribirValores();
  ahora = time(0);
  t = localtime(&ahora);
  std::cout << "El tiempo final es: "<< 1+ t->tm_hour << "h" << 1 + t->tm_min << "m" << t->tm_sec<< "s" << std::endl;
  
  
  return 0;
  
}






