//Secciones de la camara 
/* 12 Zona de pateo izquierda
 * 13 Zona de pateo derecha
 */
#include "CamDerechaArriba.hpp"
#include "../AprendizajeQ.hpp"
 
CamDerechaArriba::CamDerechaArriba(){
  // Cambiar posicion de la cámara
  Arbotix::peticion("o");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamDerechaArriba::mostrarImagen(){
  cv::Size sizeImgOrig = this->imgOriginal.size();
  cv::Mat imgLines = cv::Mat::zeros(  sizeImgOrig , CV_8UC3 );

/* _________________________________
 * |               "               | 
 * |               "               |
 * |            1->"               |
 * |               "               |
 * |               "               |
 * |               "               |
 * |_______________"_______________|
 */
  // Puntos para seccionar la imagen
  // Linea 1
  verticalIni = cvPoint(imgLines.size().width*1/2,0);
  verticalFin =
    cvPoint(imgLines.size().width*1/2,imgLines.size().height);
 
  // Dibujar division de la pantalla
  line(imgLines, verticalIni, verticalFin, cvScalar(0,255,0), 1);

  imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal);
  cv::waitKey(10);
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamDerechaArriba::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();
    AprendizajeQ::actualizarValor(estado);
    AprendizajeQ::tomarAccion(estado);

    return true;

  } else {
    // Esta es la última posicion de cámara
    return false;
  }

}
int CamDerechaArriba::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
	  return 12; 
  }else if(estaEnDerecha()){
	  return 13;
  }
}
bool CamDerechaArriba::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}
bool CamDerechaArriba::estaEnDerecha(){
  
  if (this->posX > verticalIni.x){
    return true;
  }
  return false;
}



