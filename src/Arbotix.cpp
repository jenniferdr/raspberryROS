#include "Arbotix.hpp"

namespace Arbotix{
  ros::ServiceClient client;
 
  void iniciarServicio(){
    //ros::init(argc, argv, "test_srv");
    ros::NodeHandle n;
    client= n.serviceClient<rosserial_arduino::Test>("moverRobot");
  }

  bool peticion(std::string pet){
    rosserial_arduino::Test srv;
    srv.request.input = pet;
    std::cout << srv.request.input ;
    if (client.call(srv)){
      ROS_INFO("Sum: %s", srv.response.output.c_str());
      std::cout << " true" << std::endl ; 
      return true;
    }else{
      ROS_ERROR("Failed to call service moverRobot");
      std::cout << " false" << std::endl ; 
      return false;
    }
  }
}
