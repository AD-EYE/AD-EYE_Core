cmake_minimum_required(VERSION 2.8.3)
project(adeye_msgs)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs message_generation)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  categorized_pose.msg  
  categorized_poses.msg
  NewTwistS.msg #added by gökce
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
  geometry_msgs  # Or other packages containing msgs
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rcv_common_msgs
  CATKIN_DEPENDS message_runtime
#  DEPENDS system_lib
)

# add_custom_target(dummy_target)
# add_dependencies(dummy_target ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
