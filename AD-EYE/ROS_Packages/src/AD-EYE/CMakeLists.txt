cmake_minimum_required(VERSION 2.8.3)
project(adeye)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  grid_map_core
  grid_map_ros
  grid_map_msgs
  geometry_msgs
  nav_msgs
  std_msgs
  tf
  rcv_common_msgs
  cpp_utils
  planner_utils
)


catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    roscpp
    grid_map_core
    grid_map_msgs
    nav_msgs
    std_msgs
    geometry_msgs
  DEPENDS
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)


#add_library(${PROJECT_NAME}
#   include/vectormaploader.h
#)

add_executable(
  GridMapCreator
  src/GridMapCreator_node.cpp
)

add_executable(
  flattening
  src/flattening_node.cpp
)

add_executable(
  controlSwitch
  src/controlSwitch_node.cpp
)

add_executable(
  safetySupervisor
  src/safetySupervisor.cpp
)


target_link_libraries(
  GridMapCreator
  ${catkin_LIBRARIES}
)

target_link_libraries(
  flattening
  ${catkin_LIBRARIES}
)

target_link_libraries(
  controlSwitch
  ${catkin_LIBRARIES}
)

target_link_libraries(
  safetySupervisor
  ${catkin_LIBRARIES}
)

#add_dependencies(${PROJECT_NAME}
#  ${catkin_EXPORTED_TARGETS}
#)

add_dependencies(controlSwitch
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(GridMapCreator
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(safetySupervisor
  ${catkin_EXPORTED_TARGETS}
)
# Mark executables and/or libraries for installation
install(
  TARGETS GridMapCreator flattening controlSwitch safetySupervisor
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


# Mark cpp header files for installation
install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
