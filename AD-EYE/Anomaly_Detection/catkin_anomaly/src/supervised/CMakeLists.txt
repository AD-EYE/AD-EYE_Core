cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(supervised)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package()


find_package(OpenCV REQUIRED)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_executable(supervised src/supervised.cpp)
target_link_libraries(supervised PUBLIC ${PROJECT_SOURCE_DIR}/src/needed_includes)


target_link_libraries(supervised PUBLIC 
${OpenCV_LIBS} 
${catkin_LIBRARIES}
)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


target_include_directories(supervised PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/src/needed_includes"

)


set_property (TARGET supervised PROPERTY CXX_STANDARD 14)
add_dependencies(supervised ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})