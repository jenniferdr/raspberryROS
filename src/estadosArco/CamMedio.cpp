//Secciones de la camara 
/* 
 * 1 central
 * 2 Izquierda
 * 3 Derecha
*/

#include "CamMedio.hpp"
#include "CamDerecha.hpp"

 
CamMedio::CamMedio(){

  Arbotix::peticion("t");

  this->imgOriginal = Camara::obtenerImagen();
  mostrarImagen();
  this->enPosicion = false;  
}

void CamMedio::mostrarImagen(){
  cv::Size sizeImgOrig = this->imgOriginal.size();
  cv::Mat imgLines = cv::Mat::zeros(  sizeImgOrig , CV_8UC3 );

  // Puntos para seccionar la imagen
/*   ______________________
 *  |    "           "    |
 *  |    "           "    |
 *  |L1->"      L2-> "    |
 *  |    "           "    |
 *  |    "           "    |
 *  |____"___________"____|
 *
 */

  // L1
  verticalIni = cvPoint(imgLines.size().width*3/12,0);
  verticalFin =
    cvPoint(imgLines.size().width*3/12,(imgLines.size().height));
  // L2
  verticalIni2 = cvPoint(imgLines.size().width*2/3,0);
  verticalFin2 =
    cvPoint(imgLines.size().width*2/3,imgLines.size().height);


  // Dibujar division de la pantalla
  // L1
  line(imgLines, verticalIni, verticalFin, cvScalar(0,255,0), 1);
  // L2
  line(imgLines, verticalIni2, verticalFin2, cvScalar(0,255,0), 1);

  imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal);
  cv::waitKey(10);

}

bool CamMedio::irPosicion(bool &pateoDerecha){
  int maxGiros = 10; // Numero de veces a girar sin ver la pelota
  int vuelta = 1;

  while(vuelta < maxGiros){
    bool ArcoAlaVista = ubicarPelota();
    if(ArcoAlaVista && this->enPosicion)return true;

    Arbotix::peticion("y"); // Mover camara medio
    this->imgOriginal = Camara::obtenerImagen();
    mostrarImagen();
	// Rodear
    if(! ArcoAlaVista) {
      vuelta++;
	  if (pateoDerecha)
		  Arbotix:: peticion("4");
	  else
		  Arbotix:: peticion("3");
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
bool CamMedio::ubicarPelota(){
  
  if (detectorArco::esVisible(this->imgOriginal)){
    int estado = cuadrantePelota();
    if ( estado == 1 ){
      this->enPosicion = true;
    }else{
      if (estado == 2)
	Arbotix::peticion("4"); // Girar a la izquierda
      if (estado == 3)
	Arbotix::peticion("3"); // Girar a la derecha
    }
    return true;
    
  } else {
    std:: cout << " no la vi en camara 1" << std::endl; 
    CamDerecha siguiente;
    return siguiente.ubicarPelota();
  }

}

int CamMedio::cuadrantePelota(){
  detectorArco::obtenerPosicion(this->posX,this->posY);

  if (estaEnIzquierda()){
    return 2; 
  }else if(estaEnCentro()){
    return 1;
  }else if(estaEnDerecha()){
    return 3;
  }
}

bool CamMedio::estaEnCentro(){
  
  if (this->posX > verticalIni.x 
      && this->posX < verticalIni2.x ){
    
    return true;
  }
  return false;
}

bool CamMedio::estaEnDerecha(){
  
  if (this->posX > verticalIni2.x){
    return true;
  }
  return false;
}

bool CamMedio::estaEnIzquierda(){
  
  if (this->posX < verticalIni.x){
    return true;
  }
  return false;
}








