cmake_minimum_required(VERSION 3.0.2)
project(adeye_utils)

find_package(catkin REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  grid_map_core
  grid_map_ros
  grid_map_msgs
  tf
  cpp_utils
  op_ros_helpers
  tf2_ros
)


catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    roscpp
    tf
    grid_map_core
    grid_map_msgs
    op_ros_helpers
    tf2_ros
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(
  trajectoryVisualizer
  src/trajectory_visualizer.cpp
)
target_link_libraries(
  trajectoryVisualizer
  ${catkin_LIBRARIES}
)

add_library(
  ${PROJECT_NAME}
  src/point_cloud_to_occupancy_grid.cpp
)
target_link_libraries(
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(
  pointCloudToOccupancyGrid
  src/point_cloud_to_occupancy_grid_wrapper.cpp
  src/point_cloud_to_occupancy_grid.cpp
)
target_link_libraries(
  pointCloudToOccupancyGrid
  ${catkin_LIBRARIES}
)
add_dependencies(pointCloudToOccupancyGrid
  ${catkin_EXPORTED_TARGETS}
)

add_executable(
  pointCloudFrameChanger
  src/point_cloud_frame_changer.cpp
)
target_link_libraries(
  pointCloudFrameChanger
  ${catkin_LIBRARIES}
)
add_dependencies(pointCloudFrameChanger
  ${catkin_EXPORTED_TARGETS}
)
  
add_executable(
  pointCloudAccumulator
  src/point_cloud_accumulator.cpp
)
target_link_libraries(
  pointCloudAccumulator
  ${catkin_LIBRARIES}
)
add_dependencies(pointCloudAccumulator
  ${catkin_EXPORTED_TARGETS}
)

add_executable(
  layerVisualizer
  src/layer_visualizer.cpp
)

target_link_libraries(
  layerVisualizer
  ${catkin_LIBRARIES}
)

add_dependencies(layerVisualizer
  ${catkin_EXPORTED_TARGETS}
)


# Mark executables and/or libraries for installation
install(
  TARGETS trajectoryVisualizer pointCloudFrameChanger pointCloudToOccupancyGrid ${PROJECT_NAME}
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
