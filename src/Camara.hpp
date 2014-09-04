#include "RaspiCamCV.h" // para controlar la Pi-camara

#include "opencv2/opencv.hpp" // Mat

#ifndef CAMARA_H
#define CAMARA_H

namespace Camara{
    
  bool iniciarCamara();

  cv::Mat obtenerImagen();
} 

#endif
