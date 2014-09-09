
#include "CamIzquierdaMedio.hpp"
#include "CamIzquierdaArriba.hpp"
 
CamIzquierdaMedio::CamIzquierdaMedio(){

  Arbotix::peticion("camIzquierdaMedio");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamIzquierdaMedio::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
	  Arbotix::peticion("a");
    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaArriba camSiguiente;
    //return false/*
	camSiguiente.ubicarPelota();
  }

}





