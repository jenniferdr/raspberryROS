
#include "Camara.hpp"

namespace Camara{
  RaspiCamCvCapture *camara;
  
  bool iniciarCamara(){
    camara = raspiCamCvCreateCameraCapture(0);
    return true;
  }

  cv::Mat obtenerImagen(){
    cv::Mat imagen;
    int t = 0 ;
    while (t < 10){
      imagen =raspiCamCvQueryFrame(camara); 
      imshow ("sera?", imagen);
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
