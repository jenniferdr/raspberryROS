#include "CamDerechaArriba.hpp"
#include "../AprendizajeQ.hpp"
 
CamDerechaArriba::CamDerechaArriba(){
  // Cambiar posicion de la cámara
  Arbotix::peticion("i");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamDerechaArriba::mostrarImagen(){
  imshow("Original", this->imgOriginal);
  cv::waitKey(10);
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamDerechaArriba::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    AprendizajeQ::actualizarValor(11);
    AprendizajeQ::tomarAccion(11);

    return true;

  } else {
    // Esta es la última posicion de cámara
    return false;
  }

}





