//Secciones de la camara 
/* 11 Zona de pateo izquierda
 * 10 Zona de pateo derecha
 */
 
#include "CamDerechaArriba.hpp"
#include "CamIzquierdaArriba.hpp"
#include "../AprendizajeQ.hpp"
 
CamIzquierdaArriba::CamIzquierdaArriba(){
  Arbotix::peticion("g");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamIzquierdaArriba::mostrarImagen(){
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
bool CamIzquierdaArriba::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();
    AprendizajeQ::actualizarValor(estado);
    AprendizajeQ::tomarAccion(estado);
    return true;

  } else {
    // Pasar a la siguiente clase
    CamDerechaArriba camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}
int CamIzquierdaArriba::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
	  return 11; 
  }else if(estaEnDerecha()){
	  return 10;
  }
}
bool CamIzquierdaArriba::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}
bool CamIzquierdaArriba::estaEnDerecha(){
  
  if (this->posX > verticalIni.x){
    return true;
  }
  return false;
}






