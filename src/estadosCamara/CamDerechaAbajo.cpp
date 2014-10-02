#include "CamDerechaAbajo.hpp"
#include "CamDerechaMedio.hpp"
 
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
    std::cout << "estoy en CamDerechaAbajo";
    Arbotix::peticion("d");
    return true;

  } else {
    // Pasar a la siguiente clase
    CamDerechaMedio camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}





