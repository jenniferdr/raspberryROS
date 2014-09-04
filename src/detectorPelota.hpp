#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <stdlib.h>

#ifndef DETECTORPELOTA_H
#define DETECTORPELOTA_H

namespace detectorPelota 
{
  void obtenerPosicion(int &x ,int &y);
  bool esVisible(cv::Mat);
  void crearControlesPelota();

}
#endif
