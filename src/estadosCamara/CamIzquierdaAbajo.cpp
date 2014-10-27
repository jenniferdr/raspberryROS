#include "CamIzquierdaArriba.hpp"
#include "CamIzquierdaAbajo.hpp"
#include "AprendizajeQ.hpp"
 
CamIzquierdaAbajo::CamIzquierdaAbajo(){
  Arbotix::peticion("p");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamIzquierdaAbajo::mostrarImagen(){
  imshow("Original", this->imgOriginal);
  cv::waitKey(10);
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamIzquierdaAbajo::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    AprendizajeQ::actualizarValor(12);
    AprendizajeQ::tomarAccion(12);
    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaArriba camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}





