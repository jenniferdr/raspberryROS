#include "Arbotix.hpp"
namespace Arbotix{
  ros::ServiceClient *client;
  int peticionesHechas = 0;
 
  void iniciarServicio(ros::ServiceClient *cliente){
    //ros::init(argc, argv, "test_srv");
    ros::NodeHandle n;
    client= cliente;
  }
// Intentar Arbotix::client

  bool peticion(std::string pet){
    peticionesHechas = peticionesHechas + 1;
    std::cout << " peticiones hechas: " << peticionesHechas << std::endl ; 

    rosserial_arduino::Test srv;
    srv.request.input = pet;
    std::cout << srv.request.input ;
    
      std::cout << " voy a hacer el slepp" << std::endl ; 
    sleep(4);
      std::cout << " sali del sleep :)" << std::endl ;
    if (client->call(srv)){
      
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
