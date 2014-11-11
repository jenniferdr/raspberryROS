#include "Camara.hpp"
#include "detectorPelota.hpp"
namespace Camara{
  RaspiCamCvCapture *camara;
  
  bool iniciarCamara(){
    camara = raspiCamCvCreateCameraCapture(0);
    return true;
  }

  cv::Mat obtenerImagen(){
    cv::Mat imagen;
    int t = 0 ;
    int posX,posY;
    while (t < 10){
      
      imagen =raspiCamCvQueryFrame(camara);
      cv::Mat prueba;
      // cv::xphoto::balanceWhite(imagen,prueba,cv::xphoto:: WHITE_BALANCE_SIMPLE, 0.0, 255.0, 0.0,255.0 );
      if (detectorPelota::esVisible(imagen)){
	detectorPelota::obtenerPosicion(posX,posY);
	circle(imagen,cv::Point2f(posX,posY), 20,cv::Scalar(255,0,0),1,CV_AA,0);
	}
      imshow ("Original_mayor_Numframes", imagen);
      cv::waitKey(10);
      t++;
    }
    return imagen;

     /*if (!camara.isOpened()) {
    cout << "No se pudo abrir la camara" << endl;
    return -1;
    }*/
  }
} 
