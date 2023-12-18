# Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.

project(camera_gmsl_publisher C CXX)

#-------------------------------------------------------------------------------
# Project files
#-------------------------------------------------------------------------------
set(PUBLIC_DOCS
    README.md
)

set(SOURCES
    main.cpp
)

message(${Driveworks_LIBRARIES})

set(LIBRARIES
    dw_samples_framework
    ${Driveworks_LIBRARIES}
    lodepng-src
    nvmedia_ipp
    
)

# Add ros packages
find_package(roscpp REQUIRED)

#for glfw
#find_package(glfw REQUIRED)
find_package(X11 REQUIRED)
#find_package(Xrandr REQUIRED)
#find_package(std_msgs REQUIRED)

#include_directories(${roscpp_INCLUDE_DIRS})
#include_directories(${std_msgs_INCLUDE_DIRS})
if (NOT DEFINED NVIDIA_SDK_DIR)
    set(NVIDIA_SDK_DIR "/home/adeye/nvidia/nvidia_sdk")
endif()
include_directories(${NVIDIA_SDK_DIR}/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux/targetfs/opt/ros/kinetic/include)
include_directories(${NVIDIA_SDK_DIR}/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux/targetfs/usr/include)
include_directories(${NVIDIA_SDK_DIR}/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux/targetfs/usr/include/aarch64-linux-gnu)
#-------------------------------------------------------------------------------
# Final target
#-------------------------------------------------------------------------------

link_directories(${NVIDIA_SDK_DIR}/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux/targetfs/opt/ros/kinetic/lib 
${CMAKE_CURRENT_LIST_DIR}/../../../libboost
)

#/usr/aarch64-linux-gnu/lib/

add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})
# Add libaries for ROS

#${roscpp_LIBRARIES} ${std_msgs_LIBRARIES}
#boost_thread boost_chrono log4cxx boost_regex libconsole_bridge

#message(${roscpp_LIBRARIES} ${std_msgs_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES} roscpp rosconsole roscpp_serialization rostime X11)



set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Samples")

# ------------------------------------------------------------------------------
# Install target
# ------------------------------------------------------------------------------
sdk_add_sample(${PROJECT_NAME})
