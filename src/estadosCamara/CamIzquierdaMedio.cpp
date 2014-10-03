
#include "CamIzquierdaMedio.hpp"
#include "CamIzquierdaArriba.hpp"
 
CamIzquierdaMedio::CamIzquierdaMedio(){

  Arbotix::peticion("g");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamIzquierdaMedio::mostrarImagen(){
  imshow("Original", this->imgOriginal);
  cv::waitKey(10);
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
    return camSiguiente.ubicarPelota();
  }

}





