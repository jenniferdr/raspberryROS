#include "CamArribaArribaMedio.hpp"
#include "CamDerechaAbajo.hpp"
 
CamArribaArribaMedio::CamArribaArribaMedio(){

  Arbotix::peticion("camArribaArribaMedio");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamArribaArribaMedio::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    Arbotix::peticion("w");
    return true;

  } else {
    // Pasar a la siguiente clase
    CamDerechaAbajo camSiguiente;
    //return false/*
	camSiguiente.ubicarPelota();
  }

}





