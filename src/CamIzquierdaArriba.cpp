
#include "CamAbajoMedio.hpp"
#include "CamIzquierdaArriba.hpp"
 
CamIzquierdaArriba::CamIzquierdaArriba(){

  Arbotix::peticion("camIzquierdaArriba");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
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
