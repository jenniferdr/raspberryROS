
#include "CamDerechaArriba.hpp"
#include "CamDerechaMedio.hpp"
 
CamDerechaMedio::CamDerechaMedio(){

  Arbotix::peticion("camDerechaMedio");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamDerechaMedio::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    Arbotix::peticion("d");
    return true;

  } else {
    // Pasar a la siguiente clase
    CamDerechaArriba camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}





