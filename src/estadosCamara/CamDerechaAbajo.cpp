//Secciones de la camara 
/* 16 Zona de pateo izquierda
 * 17 Zona de pateo derecha
 */
#include "CamDerechaAbajo.hpp"
#include "CamIzquierdaAbajo.hpp"
#include "../AprendizajeQ.hpp"
 
CamDerechaAbajo::CamDerechaAbajo(){
  Arbotix::peticion("u");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
}

void CamDerechaAbajo::mostrarImagen(){
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
bool CamDerechaAbajo::ubicarPelota(){
  
  if (detectorPelota::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();
    AprendizajeQ::actualizarValor(estado);
    AprendizajeQ::tomarAccion(estado);

    return true;

  } else {
    // Pasar a la siguiente clase
    CamIzquierdaAbajo camSiguiente;
    return camSiguiente.ubicarPelota();
  }
}

int CamDerechaAbajo::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
	  return 16; 
  }else if(estaEnDerecha()){
	  return 17;
  }
}
bool CamDerechaAbajo::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}
bool CamDerechaAbajo::estaEnDerecha(){
  
  if (this->posX > verticalIni.x){
    return true;
  }
  return false;
}



