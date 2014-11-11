#include "RaspiCamCV.h" // para controlar la Pi-camara
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <stdlib.h>
//#include "opencv2/xphoto.hpp"
#include "opencv2/opencv.hpp" // Mat

#ifndef CAMARA_H
#define CAMARA_H

namespace Camara{
    
  bool iniciarCamara();

  cv::Mat obtenerImagen();
} 

#endif
