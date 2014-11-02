#include "CamDerechaArriba.hpp"
#include "CamIzquierdaArriba.hpp"
#include "../AprendizajeQ.hpp"
 
CamIzquierdaArriba::CamIzquierdaArriba(){
  Arbotix::peticion("g");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamIzquierdaArriba::mostrarImagen(){
  imshow("Original", this->imgOriginal);
  cv::waitKey(10);
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamIzquierdaArriba::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    AprendizajeQ::actualizarValor(9);
    AprendizajeQ::tomarAccion(9);
    return true;

  } else {
    // Pasar a la siguiente clase
    CamDerechaArriba camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}
