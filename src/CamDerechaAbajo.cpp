//Secciones de la camara 
/* 1 Arriba-Medio
 * 2 Derecha-Arriba
 * 3 Izquierda-Arriba
 * 4 Izquierda-Inferior
 * 5 Izquierda-Inferior-Patada
 * 6 Derecha-Inferior-Patada
 * 7 Derecha-Inferior
*/

#include "CamAbajoMedio.hpp"
 
CamDerechaAbajo::CamDerechaAbajo(){

  Arbotix::peticion("camDerechaAbajo");  // Definir camAbajoMedio
  this->imgOriginal = Camara::obtenerImagen();
  
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamAbajoMedio::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    
    Arbotix::peticion("d");
    return true;

  } else {
    // Pasar a la siguiente clase
    //CamArribaMedio camArriba = new CamArribaMedio();
    return false/*camArriba.ubicarPelota()*/;
  }

}





