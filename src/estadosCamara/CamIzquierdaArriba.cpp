#include "CamDerechaArriba.hpp"
#include "CamIzquierdaArriba.hpp"
#include "AprendijajeQ.hpp"
 
CamIzquierdaArriba::CamIzquierdaArriba(){
  Arbotix::peticion("f");
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
    
    AprendizajeQ::actualizarValor(10);
    AprendizajeQ::tomarAccion(10);
    return true;

  } else {
    // Pasar a la siguiente clase
    CamDerechaArriba camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}
