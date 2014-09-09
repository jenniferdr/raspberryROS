
#include "CamIzquierdaMedio.hpp"
#include "CamIzquierdaAbajo.hpp"
 
CamIzquierdaAbajo::CamIzquierdaAbajo(){

  Arbotix::peticion("camIzquierdaAbajo");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamIzquierdaAbajo::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    Arbotix::peticion("a");
    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaMedio camSiguiente;
    //return false/*
	camSiguiente.ubicarPelota();
  }

}





