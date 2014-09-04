
#include "Camara.hpp"

namespace Camara{
  RaspiCamCvCapture *camara;
  
  bool iniciarCamara(){
    camara = raspiCamCvCreateCameraCapture(0);
    return true;
  }

  cv::Mat obtenerImagen(){
    return raspiCamCvQueryFrame(camara);

     /*if (!camara.isOpened()) {
    cout << "No se pudo abrir la camara" << endl;
    return -1;
    }*/
  }
} 
