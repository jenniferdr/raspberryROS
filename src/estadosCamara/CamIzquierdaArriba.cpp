
#include "CamAbajoMedio.hpp"
#include "CamIzquierdaArriba.hpp"
 
CamIzquierdaArriba::CamIzquierdaArriba(){

  Arbotix::peticion("f");  // Definir camAbajoMedio
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
    
    Arbotix::peticion("a");
    return true;

  } else {
    // Pasar a la siguiente clase
    //CamAbajoMedio camSiguiente;
    return false;// camSiguiente.ubicarPelota();
  }

}
