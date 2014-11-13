#include "CamDerecha.hpp"
#include "CamIzquierda.hpp"

/* 
 * 4 Izquierda
 * 5 Derecha
*/
 
CamDerecha::CamDerecha(){
  // Cambiar posicion de la cámara
  Arbotix::peticion("o");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamDerecha::mostrarImagen(){
cv::Size sizeImgOrig = this->imgOriginal.size();
  cv::Mat imgLines = cv::Mat::zeros(  sizeImgOrig , CV_8UC3 );

  // Puntos para seccionar la imagen
/*   ______________________
 *  |           "          |
 *  |           "          |
 *  |      L1- >"          |
 *  |           "          |
 *  |           "          |
 *  |___________"__________|
 *
 */

  // L1
  verticalIni = cvPoint(imgLines.size().width*1/2,0);
  verticalFin =
    cvPoint(imgLines.size().width*1/2,(imgLines.size().height));
  // Dibujar division de la pantalla
  // L1
  line(imgLines, verticalIni, verticalFin, cvScalar(0,255,0), 1);
  imgOriginal = imgOriginal + imgLines;
  
  imshow("Original", this->imgOriginal);
  cv::waitKey(10);
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamDerecha::ubicarPelota(){

  if (detectorArco::esVisible(this->imgOriginal)){
	  int estado = cuadrantePelota();
	  if (estado == 4)
		  Arbotix::peticion("5");
	  if (estado == 5)
		  Arbotix::peticion("3");
	  return true;

  } else {
	  CamIzquierda camSiguiente;
	  return camSiguiente.ubicarPelota
	  
  }

int CamDerecha::cuadrantePelota(){
  detectorArco::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
    return 4; 
  }else if(estaEnDerecha()){
    return 5;
  }
}


bool CamDerecha::estaEnDerecha(){
  
  if (this->posX > verticalIni.x){
    return true;
  }
  return false;
}

bool CamDerecha::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}
}
