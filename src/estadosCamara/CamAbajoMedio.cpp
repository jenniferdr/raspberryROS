//Secciones de la camara 
/* 0 Zona de pateo izquierda
 * 1 Zona de pateo derecha
 * 2 Central Abajo
 * 3 Central Arriba
 * 4 Izquierda
 * 5 Derecha
 */


#include "CamAbajoMedio.hpp"
#include "CamArribaMedio.hpp"
#include "../AprendizajeQ.hpp"

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

/* ____________________________________
 * |       "      7             "     | 
 * |       "      ^             "     |
 * |    1->"      |         2-> "     |
 * |  3    "  ----------------- "     |
 * |  ^    "                    "     |
 * |  |8 <-"""""""""""""""""""" "     |
 * |""""""""""""""""""""""""""""""""""|
 * |       "->4     :->5     6<-"     |
 * |_______"________: __________"_____|
 */
  
  // Linea 1
  verticalIni = cvPoint(imgLines.size().width*3/12,0);
  verticalFin =
    cvPoint(imgLines.size().width*3/12,(imgLines.size().height)*5/6);
 
  // Linea 2
  verticalIni2 = cvPoint(imgLines.size().width*9/12,0);
  verticalFin2 =
    cvPoint(imgLines.size().width*9/12,imgLines.size().height*5/6);
  /*
  // Linea 3
  horizontalIni = cvPoint(0,imgLines.size().height*7/9);
  horizontalFin =
    cvPoint(imgLines.size().width,imgLines.size().height*7/9);
  */
// Linea 3
  horizontalIni = cvPoint(0,imgLines.size().height*5/6);
  horizontalFin =
    cvPoint(imgLines.size().width,imgLines.size().height*5/6);

  // Linea 4
  verticalIni3 = 
    cvPoint(imgLines.size().width*3/12,imgLines.size().height*5/6);
  verticalFin3 =
    cvPoint(imgLines.size().width*3/12,imgLines.size().height);
  
  // Linea 5
  verticalIni4 = 
    cvPoint(imgLines.size().width*6/12,imgLines.size().height*5/6);
  verticalFin4 =
    cvPoint(imgLines.size().width*6/12,imgLines.size().height);
    
  // Linea 6
  verticalIni5 = 
    cvPoint(imgLines.size().width*9/12,imgLines.size().height*5/6);
  verticalFin5 =
    cvPoint(imgLines.size().width*9/12,imgLines.size().height);

  // Linea 7
  horizontalIni2 = 
    cvPoint(imgLines.size().width*3/12,(imgLines.size().height)*4/9);
  horizontalFin2 =
    cvPoint(imgLines.size().width*9/12, (imgLines.size().height)*4/9);

  // Linea 8
  horizontalIni3 = 
    cvPoint(imgLines.size().width*3/12,(imgLines.size().height)*8/11);
  horizontalFin3 =
    cvPoint(imgLines.size().width*9/12, (imgLines.size().height)*8/11);

  
  // Dibujar division de la pantalla
  line(imgLines, horizontalIni, horizontalFin, cvScalar(0,255,0), 1);
  line(imgLines, horizontalIni2, horizontalFin2, cvScalar(0,255,0), 1);
  line(imgLines, horizontalIni3, horizontalFin3, cvScalar(0,255,0), 1);
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
      int estado = pateoDerecha ? 1 : 0 ;
      AprendizajeQ::actualizarValor(estado);
      return true;
    }

    Arbotix::peticion("r"); // Mover camara abajo-medio
    this->imgOriginal = Camara::obtenerImagen();
    mostrarImagen();

    if(! pelotaAlaVista) {
      vuelta++;
      // Estado 13: no la vió
      std::cout << "actualizar valor estado 13" << std::endl;
      AprendizajeQ::actualizarValor(13);
      std::cout << "Despues de actualizar valor, tomare accion " << std::endl;
      AprendizajeQ::tomarAccion(13);
      std::cout << "Ya tome la accion "<< std::endl;
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
    
    std::cout << "Actualizar valor camAbajMedio estado " << estado << std::endl;
    AprendizajeQ::actualizarValor(estado);
    if (estado == 0 or estado == 1){
      this->enZonaPateo = true;
      if(estado==0) pateoDerecha = false;
      if(estado==1) pateoDerecha = true;
    }else{
      std::cout << "Tomar accion con estado " << estado << std::endl;
      AprendizajeQ::tomarAccion(estado);
      std::cout << "Ya tome la accion" << std::endl;
    }
    return true;

  } else {
    std:: cout << " no la vi en camara 1" << std::endl; 
    CamArribaMedio cam_arriba_medio;
    return cam_arriba_medio.ubicarPelota();
  }

}

int CamAbajoMedio::cuadrantePelota(){
  detectorPelota::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
	  return 4; 
  }else if(estaEnMedioAbajo()){
	  return 2;
  }else if(estaEnMedioArriba()){
	  return 3;
  }else if(estaEnDerecha()){
	  return 5;
  }else if(estaEnPateoIzquierda()){
	  return 0;
  }else if(estaEnPateoDerecha()){
	  return 1;
  }
}

bool CamAbajoMedio::estaEnMedioAbajo(){

	if (this->posX > verticalIni.x 
      && this->posX < verticalIni2.x
      && this->posY < horizontalIni3.y
	  && this->posY > horizontalIni2.y ){

    return true;
  }
  return false;
}
bool CamAbajoMedio::estaEnMedioArriba(){
  
  if (this->posX > verticalIni.x 
      && this->posX < verticalIni2.x
      && this->posY < horizontalIni2.y){

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
      && this->posY > horizontalIni3.y
	  && this->posY < horizontalIni.y){

    return true;
  }
  return false;
}

bool CamAbajoMedio::estaEnPateoDerecha(){
  
  if (this->posX > verticalIni4.x 
      && this->posX < verticalIni5.x
      && this->posY > horizontalIni3.y 
	  && this->posY < horizontalIni.y){
    return true;
  }
  return false;
}






