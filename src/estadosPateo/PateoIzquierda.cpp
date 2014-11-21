
#include "PateoIzquierda.hpp"

/* 
 * 6 Izquierda
 * 7 Derecha
*/
 
PateoIzquierda::PateoIzquierda(){
  // Cambiar posicion de la cámara

  Arbotix::peticion("e");

  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void PateoIzquierda::mostrarImagen(){
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
bool PateoIzquierda::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
	  int estado = cuadrantePelota();
	  if (estado == 6)
		  Arbotix::peticion("4");
	  if (estado == 7)
		  Arbotix::peticion("6");
	  return true;

  } else {
	  // ultima camara
	  return false;
	  
  }
}
int PateoIzquierda::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
    return 6; 
  }else if(estaEnDerecha()){
    return 7;
  }
}


bool PateoIzquierda::estaEnDerecha(){
  
  if (this->posX > verticalIni.x){
    return true;
  }
  return false;
}

bool PateoIzquierda::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}

