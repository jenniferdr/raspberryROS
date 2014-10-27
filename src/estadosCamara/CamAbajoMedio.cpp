//Secciones de la camara 
/* 1 Zona de pateo izquierda
 * 2 Zona de pateo derecha
 * 3 central
 * 4 Izquierda
 * 5 Derecha
*/

#include "CamAbajoMedio.hpp"
#include "CamArribaMedio.hpp"
#include "AprendizajeQ.hpp"

CamAbajoMedio::CamAbajoMedio(){

  Arbotix::peticion("r");  
  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
  this->enZonaPateo = false;
}

void CamAbajoMedio::mostrarImagen(){
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

  verticalIni3 = 
    cvPoint(imgLines.size().width*3/12,imgLines.size().height*5/6);
  verticalFin3 =
    cvPoint(imgLines.size().width*3/12,imgLines.size().height);

  verticalIni4 = 
    cvPoint(imgLines.size().width*5/12,imgLines.size().height*5/6);
  verticalFin4 =
    cvPoint(imgLines.size().width*5/12,imgLines.size().height);
    
  verticalIni5 = 
    cvPoint(imgLines.size().width*2/3,imgLines.size().height*5/6);
  verticalFin5 =
    cvPoint(imgLines.size().width*2/3,imgLines.size().height);

  // Dibujar division de la pantalla
  line(imgLines, horizontalIni, horizontalFin, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni, verticalFin, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni2, verticalFin2, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni3, verticalFin3, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni4, verticalFin4, cvScalar(0,255,0), 1);
  line(imgLines, verticalIni5, verticalFin5, cvScalar(0,255,0), 1);


  imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal);
  cv::waitKey(10);

}

bool CamAbajoMedio::irZonaPateo(bool &pateoDerecha){
  int maxGiros = 5; // Numero de veces a girar sin ver la pelota
  int vuelta = 1;

  while(vuelta < maxGiros){
    bool pelotaAlaVista = ubicarPelota(pateoDerecha); // OJO
    if(pelotaAlaVista && this->enZonaPateo){
      // Llegamos a la meta, tomar recompensa
      int estado = pateoDerecha ? 2 : 1 ;
      AprendizajeQ::actualizarValor(estado);
      return true;
    }

    Arbotix::peticion("r"); // Mover camara abajo-medio
    this->imgOriginal = Camara::obtenerImagen();
    mostrarImagen();

    if(! pelotaAlaVista) {
      vuelta++;
      // Estado 14: no la vió 
      AprendijajeQ::actualizarValor(14);
      AprendizajeQ::tomarAccion(14);
      Arbotix:: peticion("a");
    }
  }

  // Alcanzó el numero max de giros sin encontrar pelota
  return false;
}

/* Devuelve true si vio la pelota en cualquier posicion 
 * de la camara
 * Devuelve false si no la vio en ninguna posicion
 * de camara
 */ 
bool CamAbajoMedio::ubicarPelota(bool &pateoDerecha){
  this->enZonaPateo = false;
  if (detectorPelota::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();

    AprendijajeQ::actualizarValor(estado);
    if (estado == 1 or estado == 2){
      this->enzonaPateo = true;
      if(estado==1) pateoDerecha = false;
      if(estado==2) pateoDerecha = true;
    }else{
      AprendizajeQ::tomarAccion(estado);
    }
    return true;

  } else {
    std:: cout << " no la vi en camara 1"; 
    CamArribaMedio cam_arriba_medio;
    return cam_arriba_medio.ubicarPelota();
  }

}

int CamAbajoMedio::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
    return 4; 
  }else if(estaEnMedioArriba()){
    return 3;
  }else if(estaEnDerecha()){
    return 5;
  }else if(estaEnPateoIzquierda()){
    return 1;
  }else if(estaEnPateoDerecha()){
    return 2;
  }
}

bool CamAbajoMedio::estaEnMedioArriba(){
  
  if (this->posX > verticalIni.x 
      && this->posX < verticalIni2.x
      && this->posY < horizontalIni.y ){

    return true;
  }
  return false;
}

bool CamAbajoMedio::estaEnDerecha(){
  
  if (this->posX > verticalIni2.x){
    return true;
  }
  return false;
}

bool CamAbajoMedio::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}

bool CamAbajoMedio::estaEnPateoIzquierda(){
  
  if (this->posX > verticalIni3.x 
      && this->posX < verticalIni4.x
      && this->posY > horizontalIni.y ){

    return true;
  }
  return false;
}

bool CamAbajoMedio::estaEnPateoDerecha(){
  
  if (this->posX > verticalIni4.x 
      && this->posX < verticalIni5.x
      && this->posY > horizontalIni.y ){

    return true;
  }
  return false;
}






