#include "ros/ros.h"
#include "rosserial_arduino/Test.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_srv");
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<rosserial_arduino::Test>("test_srv2");
  rosserial_arduino::Test srv;
  srv.request.input = "hola";
  if (client.call(srv)){

//  ros::service::waitForService("test_srv2");
  
     ROS_INFO("Sum: %s", srv.response.output.c_str());
  
  }else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
