#include "ros/ros.h"
#include "rosserial_arduino/Test.h"
#include <cstdlib>
#include <stdlib.h>
#include <string>

namespace Arbotix{
 
  void iniciarServicio(ros::ServiceClient *cliente);

  bool peticion(std::string pet);
}
