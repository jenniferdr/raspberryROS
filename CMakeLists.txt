cmake_minimum_required(VERSION 2.8.3)
project(humanoide_aprendizaje)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

find_package(OpenCV REQUIRED)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

SET(RASPICAM_CV $ENV{HOME}/git/robidouille/raspicam_cv)
SET(USERLAND $ENV{HOME}/git/raspberrypi/userland)

include_directories(${RASPICAM_CV} /home/pi/catkin_wsJ/src/humanoide/ )
include_directories(/usr/local/include)

SET(MMAL_LIBS
    ${USERLAND}/build/lib/libmmal_core.so
    ${USERLAND}/build/lib/libmmal_util.so
    ${USERLAND}/build/lib/libmmal_vc_client.so
    ${USERLAND}/build/lib/libvcos.so)
SET(BCM_LIBS ${USERLAND}/build/lib/libbcm_host.so)
SET(GLES_LIBS ${USERLAND}/build/lib/libGLESv2.so)
SET(EGL_LIBS ${USERLAND}/build/lib/libEGL.so)
SET(DISPLAY_CAMERA_LIBS
    ${RASPICAM_CV}/libraspicamcv.a
    ${MMAL_LIBS} ${BCM_LIBS} ${OpenCV_LIBS} )


add_executable(servicetest2 src/detectar.cpp src/detectorPelota.cpp src/Camara.cpp src/Arbotix.cpp
               src/AprendizajeQ.cpp
               src/estadosCamara/CamAbajoMedio.cpp src/estadosCamara/CamArribaArribaMedio.cpp 
               src/estadosCamara/CamDerechaAbajo.cpp src/estadosCamara/CamDerechaMedio.cpp 
               src/estadosCamara/CamDerechaArriba.cpp  src/estadosCamara/CamArribaMedio.cpp 
               src/estadosCamara/CamIzquierdaAbajo.cpp src/estadosCamara/CamIzquierdaMedio.cpp 
               src/estadosCamara/CamIzquierdaArriba.cpp )

target_link_libraries(servicetest2 ${catkin_LIBRARIES}  ${DISPLAY_CAMERA_LIBS} ${LD_LIBRARY_PATH} ${OpenCV_LIBS})

