//Secciones de la camara 
/* 15 Zona de pateo izquierda
 * 14 Zona de pateo derecha
 */

#include "CamIzquierdaArriba.hpp"
#include "CamIzquierdaAbajo.hpp"
#include "../AprendizajeQ.hpp"
 
CamIzquierdaAbajo::CamIzquierdaAbajo(){
  Arbotix::peticion("p");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamIzquierdaAbajo::mostrarImagen(){
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
bool CamIzquierdaAbajo::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();
    AprendizajeQ::actualizarValor(estado);
    AprendizajeQ::tomarAccion(estado);
    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaArriba camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}

int CamIzquierdaAbajo::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
	  return 15; 
  }else if(estaEnDerecha()){
	  return 14;
  }
}
bool CamIzquierdaAbajo::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}
bool CamIzquierdaAbajo::estaEnDerecha(){
  
  if (this->posX > verticalIni.x){
    return true;
  }
  return false;
}






