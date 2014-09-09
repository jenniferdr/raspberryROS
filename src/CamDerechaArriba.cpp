
#include "CamDerechaArriba.hpp"
#include "CamIzquierdaAbajo.hpp"
 
CamDerechaArriba::CamDerechaArriba(){

  Arbotix::peticion("camDerechaArriba");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamDerechaArriba::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    Arbotix::peticion("d");
    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaAbajo camSiguiente;
    //return false/*
	camSiguiente.ubicarPelota();
  }

}





