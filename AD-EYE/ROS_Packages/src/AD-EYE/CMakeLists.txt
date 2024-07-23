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
  autoware_msgs
  op_planner
  op_ros_helpers
  tf2_ros
  adeye_utils
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
    autoware_msgs
    op_planner
    op_ros_helpers
    tf2_ros
    adeye_utils
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


add_library(
  vectorMap src/vectormap.cpp
)

add_library(
  PID src/PID.cpp
  #src/vehicle_controller.cpp
)

add_library(
  experimentRecording src/experiment_recording.cpp
)

add_executable(
  GridMapCreator
  src/grid_map_creator.cpp
)

add_executable(
  flattening
  src/flattening_node.cpp
)

add_executable(
  controlSwitch
  src/control_switch.cpp
)

add_executable(
  safetySupervisor
  src/safety_supervisor.cpp
)

add_executable(
  radar_broadcaster
  src/radar_broadcaster.cpp
)

add_executable(
  collisionDetector
  src/collision_detector.cpp
)

add_executable(
  objectsFrameAdapter
  src/objects_frame_adapter.cpp
)

add_executable(
  cameraObjectListFuse
  src/camera_object_list_fuse.cpp
)

add_executable(
  lidarRadarFuse
  src/lidar_radar_fuse.cpp
)

add_executable(
  safetyChannelPerception
  src/safety_channel_perception.cpp
)


add_executable(
  laneMapImager
        src/lane_map_imager.cpp
)

add_executable(
  goalSequencer
  src/goal_sequencer.cpp
)

# add_executable(
#   PID_controller
#   src/PID.cpp
# )

add_executable(
  vehicle_controller
  src/vehicle_controller.cpp
)

target_link_libraries(
  GridMapCreator
  ${catkin_LIBRARIES}
  vectorMap
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
  SafetyFaultMonitors
)

# target_link_libraries(
#   PID
#   ${catkin_LIBRARIES}
#   PIDController
# )

target_link_libraries(
  radar_broadcaster
  ${catkin_LIBRARIES}
)

target_link_libraries(
  collisionDetector
  ${catkin_LIBRARIES}
)

target_link_libraries(
  objectsFrameAdapter
  ${catkin_LIBRARIES}
)

target_link_libraries(
  cameraObjectListFuse
  ${catkin_LIBRARIES}
)

target_link_libraries(
  lidarRadarFuse
  ${catkin_LIBRARIES}
)

target_link_libraries(
  safetyChannelPerception
  ${catkin_LIBRARIES}
)

target_link_libraries(
  laneMapImager
  ${catkin_LIBRARIES}
)

target_link_libraries(
  goalSequencer
  ${catkin_LIBRARIES}
)

# target_link_libraries(
#   PID_controller
#   ${catkin_LIBRARIES}
# )

target_link_libraries(
  vehicle_controller
  ${catkin_LIBRARIES}
  PID
)

add_dependencies(controlSwitch
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(GridMapCreator
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(safetySupervisor
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(radar_broadcaster
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(collisionDetector
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(objectsFrameAdapter
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(cameraObjectListFuse
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(lidarRadarFuse
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(safetyChannelPerception
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(laneMapImager
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(goalSequencer
  ${catkin_EXPORTED_TARGETS}
)

# add_dependencies(PID_controller
#   ${catkin_EXPORTED_TARGETS}
# )

add_dependencies(vehicle_controller
  ${catkin_EXPORTED_TARGETS}
)

# Add the executable, libraries and dependencies for sensor monitor node
add_executable(
  sensorMonitor
  src/sensor_monitor.cpp
)

target_link_libraries(
  sensorMonitor
  ${catkin_LIBRARIES}
)

add_dependencies(sensorMonitor
  ${catkin_EXPORTED_TARGETS}
)



add_executable(
  ExperimentC
  src/experimentC.cpp
)
target_link_libraries(
  ExperimentC
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  experimentRecording
)
add_dependencies(
  ExperimentC
  ${catkin_EXPORTED_TARGETS}
)


add_library(SafetyFaultMonitors
        src/safety_fault_monitors/safety_fault_monitor.cpp
        src/safety_fault_monitors/active_nodes_checker.cpp
        src/safety_fault_monitors/geofencing_checker.cpp
        src/safety_fault_monitors/car_off_road_checker.cpp
        src/safety_fault_monitors/obstacles_in_critical_area_checker.cpp
        src/safety_fault_monitors/sensor_checker.cpp)
target_link_libraries(
        SafetyFaultMonitors
        ${catkin_LIBRARIES}
)

add_executable(
  TestFault
        src/safety_fault_monitors/fault_monitors_unit_tests.cpp
)
target_link_libraries(
  TestFault
  ${catkin_LIBRARIES}
        SafetyFaultMonitors
)
add_dependencies(
  TestFault
  ${catkin_EXPORTED_TARGETS}
)


# Mark executables and/or libraries for installation
install(
  TARGETS GridMapCreator flattening controlSwitch safetySupervisor collisionDetector radar_broadcaster objectsFrameAdapter cameraObjectListFuse lidarRadarFuse safetyChannelPerception ExperimentC
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

catkin_install_python(PROGRAMS src/camera_broadcaster.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_install_python(PROGRAMS src/zed_driver.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
