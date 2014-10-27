//Secciones de la camara 
/* 6 Abajo
 * 7 central
 * 8 Izquierda
 * 9 Derecha
*/

#include "CamArribaMedio.hpp"
#include "CamDerechaAbajo.hpp"
#include "AprendizajeQ.hpp"
 
CamArribaMedio::CamArribaMedio(){
  Arbotix::peticion("y");
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
  
}

void CamArribaMedio::mostrarImagen(){
  cv::Size sizeImgOrig = this->imgOriginal.size();
  cv::Mat imgLines = cv::Mat::zeros(  sizeImgOrig , CV_8UC3 );

  // Puntos para seccionar la imagen
  verticalIni = cvPoint(imgLines.size().width*3/12,0);
  verticalFin =
    cvPoint(imgLines.size().width*3/12,(imgLines.size().height)*5/6);
 
  verticalIni2 = cvPoint(imgLines.size().width*2/3,0);
  verticalFin2 =
    cvPoint(imgLines.size().width*2/3,imgLines.size().height*5/6);

  horizontalIni = cvPoint(0,imgLines.size().height*5/6);
  horizontalFin =
    cvPoint(imgLines.size().width,imgLines.size().height*5/6);


  // Dibujar division de la pantalla
  line(imgLines, horizontalIni, horizontalFin, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni, verticalFin, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni2, verticalFin2, cvScalar(0,255,0), 1);

  imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal);
  cv::waitKey(10);

}


// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool CamArribaMedio::ubicarPelota(){

  if (detectorPelota::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();
    AprendizajeQ::actualizarValor(estado);
    AprendizajeQ::tomarAccion(estado);
    return true;

  } else {
    CamDerechaAbajo camSiguiente;
    return camSiguiente.ubicarPelota();
  }

}

int CamArribaMedio::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
    return 8; 
  }else if(estaEnCentro()){
    return 7;
  }else if(estaEnDerecha()){
    return 9;
  }else if(estaEnAbajo()){
    return 6;
  }
}

bool CamArribaMedio::estaEnCentro(){
  
  if (this->posX > verticalIni.x 
      && this->posX < verticalIni2.x
      && this->posY < horizontalIni.y ){

    return true;
  }
  return false;
}

bool CamArribaMedio::estaEnDerecha(){
  
  if (this->posX > verticalIni2.x){
    return true;
  }
  return false;
}

bool CamArribaMedio::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}


bool CamArribaMedio::estaEnAbajo(){
  
  if (this->posY > horizontalIni.y ){

    return true;
  }
  return false;
}






