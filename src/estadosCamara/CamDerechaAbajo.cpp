#include "CamDerechaAbajo.hpp"
#include "CamIzquierdaAbajo.hpp"
#include "../AprendizajeQ.hpp"
 
CamDerechaAbajo::CamDerechaAbajo(){
  Arbotix::peticion("u");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamDerechaAbajo::mostrarImagen(){
  imshow("Original", this->imgOriginal);
  cv::waitKey(10);
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamDerechaAbajo::ubicarPelota(){
  
  if (detectorPelota::esVisible(this->imgOriginal)){
    
    AprendizajeQ::actualizarValor(12);
    AprendizajeQ::tomarAccion(12);

    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaAbajo camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}





