# generated from catkin/cmake/template/pkgConfig.cmake.in

# append elements to a list and remove existing duplicates from the list
# copied from catkin/cmake/list_append_deduplicate.cmake to keep pkgConfig
# self contained
macro(_list_append_deduplicate listname)
  if(NOT "${ARGN}" STREQUAL "")
    if(${listname})
      list(REMOVE_ITEM ${listname} ${ARGN})
    endif()
    list(APPEND ${listname} ${ARGN})
  endif()
endmacro()

# append elements to a list if they are not already in the list
# copied from catkin/cmake/list_append_unique.cmake to keep pkgConfig
# self contained
macro(_list_append_unique listname)
  foreach(_item ${ARGN})
    list(FIND ${listname} ${_item} _index)
    if(_index EQUAL -1)
      list(APPEND ${listname} ${_item})
    endif()
  endforeach()
endmacro()

# pack a list of libraries with optional build configuration keywords
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_pack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  set(_argn ${ARGN})
  list(LENGTH _argn _count)
  set(_index 0)
  while(${_index} LESS ${_count})
    list(GET _argn ${_index} lib)
    if("${lib}" MATCHES "^(debug|optimized|general)$")
      math(EXPR _index "${_index} + 1")
      if(${_index} EQUAL ${_count})
        message(FATAL_ERROR "_pack_libraries_with_build_configuration() the list of libraries '${ARGN}' ends with '${lib}' which is a build configuration keyword and must be followed by a library")
      endif()
      list(GET _argn ${_index} library)
      list(APPEND ${VAR} "${lib}${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}${library}")
    else()
      list(APPEND ${VAR} "${lib}")
    endif()
    math(EXPR _index "${_index} + 1")
  endwhile()
endmacro()

# unpack a list of libraries with optional build configuration keyword prefixes
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_unpack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  foreach(lib ${ARGN})
    string(REGEX REPLACE "^(debug|optimized|general)${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}(.+)$" "\\1;\\2" lib "${lib}")
    list(APPEND ${VAR} "${lib}")
  endforeach()
endmacro()


if(freespace_planner_CONFIG_INCLUDED)
  return()
endif()
set(freespace_planner_CONFIG_INCLUDED TRUE)

# set variables for source/devel/install prefixes
if("TRUE" STREQUAL "TRUE")
  set(freespace_planner_SOURCE_PREFIX /home/adeye/AD-EYE_Core/autoware.ai/src/autoware/core_planning/freespace_planner)
  set(freespace_planner_DEVEL_PREFIX /home/adeye/AD-EYE_Core/autoware.ai/devel)
  set(freespace_planner_INSTALL_PREFIX "")
  set(freespace_planner_PREFIX ${freespace_planner_DEVEL_PREFIX})
else()
  set(freespace_planner_SOURCE_PREFIX "")
  set(freespace_planner_DEVEL_PREFIX "")
  set(freespace_planner_INSTALL_PREFIX /home/adeye/AD-EYE_Core/autoware.ai/install)
  set(freespace_planner_PREFIX ${freespace_planner_INSTALL_PREFIX})
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "WARNING: package 'freespace_planner' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message("${_msg}")
endif()

# flag project as catkin-based to distinguish if a find_package()-ed project is a catkin project
set(freespace_planner_FOUND_CATKIN_PROJECT TRUE)

if(NOT " " STREQUAL " ")
  set(freespace_planner_INCLUDE_DIRS "")
  set(_include_dirs "")
  if(NOT " " STREQUAL " ")
    set(_report "Check the issue tracker '' and consider creating a ticket if the problem has not been reported yet.")
  elseif(NOT " " STREQUAL " ")
    set(_report "Check the website '' for information and consider reporting the problem.")
  else()
    set(_report "Report the problem to the maintainer 'Akihito OHSATO <aohsato@gmail.com>' and request to fix the problem.")
  endif()
  foreach(idir ${_include_dirs})
    if(IS_ABSOLUTE ${idir} AND IS_DIRECTORY ${idir})
      set(include ${idir})
    elseif("${idir} " STREQUAL "include ")
      get_filename_component(include "${freespace_planner_DIR}/../../../include" ABSOLUTE)
      if(NOT IS_DIRECTORY ${include})
        message(FATAL_ERROR "Project 'freespace_planner' specifies '${idir}' as an include dir, which is not found.  It does not exist in '${include}'.  ${_report}")
      endif()
    else()
      message(FATAL_ERROR "Project 'freespace_planner' specifies '${idir}' as an include dir, which is not found.  It does neither exist as an absolute directory nor in '/home/adeye/AD-EYE_Core/autoware.ai/src/autoware/core_planning/freespace_planner/${idir}'.  ${_report}")
    endif()
    _list_append_unique(freespace_planner_INCLUDE_DIRS ${include})
  endforeach()
endif()

set(libraries "")
foreach(library ${libraries})
  # keep build configuration keywords, target names and absolute libraries as-is
  if("${library}" MATCHES "^(debug|optimized|general)$")
    list(APPEND freespace_planner_LIBRARIES ${library})
  elseif(${library} MATCHES "^-l")
    list(APPEND freespace_planner_LIBRARIES ${library})
  elseif(${library} MATCHES "^-")
    # This is a linker flag/option (like -pthread)
    # There's no standard variable for these, so create an interface library to hold it
    if(NOT freespace_planner_NUM_DUMMY_TARGETS)
      set(freespace_planner_NUM_DUMMY_TARGETS 0)
    endif()
    # Make sure the target name is unique
    set(interface_target_name "catkin::freespace_planner::wrapped-linker-option${freespace_planner_NUM_DUMMY_TARGETS}")
    while(TARGET "${interface_target_name}")
      math(EXPR freespace_planner_NUM_DUMMY_TARGETS "${freespace_planner_NUM_DUMMY_TARGETS}+1")
      set(interface_target_name "catkin::freespace_planner::wrapped-linker-option${freespace_planner_NUM_DUMMY_TARGETS}")
    endwhile()
    add_library("${interface_target_name}" INTERFACE IMPORTED)
    if("${CMAKE_VERSION}" VERSION_LESS "3.13.0")
      set_property(
        TARGET
        "${interface_target_name}"
        APPEND PROPERTY
        INTERFACE_LINK_LIBRARIES "${library}")
    else()
      target_link_options("${interface_target_name}" INTERFACE "${library}")
    endif()
    list(APPEND freespace_planner_LIBRARIES "${interface_target_name}")
  elseif(TARGET ${library})
    list(APPEND freespace_planner_LIBRARIES ${library})
  elseif(IS_ABSOLUTE ${library})
    list(APPEND freespace_planner_LIBRARIES ${library})
  else()
    set(lib_path "")
    set(lib "${library}-NOTFOUND")
    # since the path where the library is found is returned we have to iterate over the paths manually
    foreach(path /home/adeye/AD-EYE_Core/autoware.ai/devel/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lattice_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/waypoint_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/waypoint_maker/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/way_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_utilities/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_simulation_package/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_local_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_global_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_kf_contour_track/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_ros_helpers/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lane_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/ff_waypoint_follower/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/dp_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/waypoint_follower/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vision_ssd_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vision_segment_enet_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vision_lane_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vision_darknet_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vision_beyond_track/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vehicle_socket/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vehicle_model/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vehicle_description/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/trafficlight_recognizer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_simu/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/op_utility/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_euclidean_cluster_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vector_map_server/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/road_occupancy_processor/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/costmap_generator/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/object_map/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/naive_motion_predict/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/map_file/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/libvectormap/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/imm_ukf_pda_track/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/decision_maker/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vector_map/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/vector_map_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/udon_socket/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/twist_generator/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/tablet_socket/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/runtime_manager/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/mqtt_socket/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/tablet_socket_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/state_machine_lib/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/sound_player/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/points2image/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/rosinterface/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/rosbag_controller/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/roi_object_filter/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/range_vision_fusion/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/pos_db/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/points_preprocessor/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/points_downsampler/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/pixel_cloud_fusion/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_localizer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/pcl_omp_registration/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/pc2_downsampler/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/oculus_socket/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/obj_db/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/ndt_tku/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/ndt_gpu/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/ndt_cpu/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/multi_lidar_calibrator/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/marker_downsampler/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/map_tools/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/map_tf_generator/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/log_tools/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_shape_estimation/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_point_pillars/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_naive_l_shape_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_fake_perception/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/lidar_apollo_cnn_seg_detect/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/kitti_launch/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/kitti_player/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/kitti_box_publisher/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/integrated_viewer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/image_processor/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/graph_tools/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/gnss_localizer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/gnss/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/glviewer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/gazebo_world_description/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/freespace_planner/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/fastvirtualscan/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/ekf_localizer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/detected_objects_visualizer/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/decision_maker_panel/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/data_preprocessor/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/calibration_publisher/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_health_checker/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_system_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_rviz_plugins/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_connector/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_camera_lidar_calibrator/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/astar_search/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/amathutils_lib/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_map_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_launcher_rviz/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_launcher/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_external_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_config_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_can_msgs/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_build_flags/lib;/home/adeye/AD-EYE_Core/autoware.ai/install/autoware_bag_tools/lib;/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/devel/lib;/opt/ros/kinetic/lib)
      find_library(lib ${library}
        PATHS ${path}
        NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
      if(lib)
        set(lib_path ${path})
        break()
      endif()
    endforeach()
    if(lib)
      _list_append_unique(freespace_planner_LIBRARY_DIRS ${lib_path})
      list(APPEND freespace_planner_LIBRARIES ${lib})
    else()
      # as a fall back for non-catkin libraries try to search globally
      find_library(lib ${library})
      if(NOT lib)
        message(FATAL_ERROR "Project '${PROJECT_NAME}' tried to find library '${library}'.  The library is neither a target nor built/installed properly.  Did you compile project 'freespace_planner'?  Did you find_package() it before the subdirectory containing its code is included?")
      endif()
      list(APPEND freespace_planner_LIBRARIES ${lib})
    endif()
  endif()
endforeach()

set(freespace_planner_EXPORTED_TARGETS "")
# create dummy targets for exported code generation targets to make life of users easier
foreach(t ${freespace_planner_EXPORTED_TARGETS})
  if(NOT TARGET ${t})
    add_custom_target(${t})
  endif()
endforeach()

set(depends "roscpp;tf;nav_msgs;geometry_msgs;visualization_msgs;autoware_msgs;astar_search")
foreach(depend ${depends})
  string(REPLACE " " ";" depend_list ${depend})
  # the package name of the dependency must be kept in a unique variable so that it is not overwritten in recursive calls
  list(GET depend_list 0 freespace_planner_dep)
  list(LENGTH depend_list count)
  if(${count} EQUAL 1)
    # simple dependencies must only be find_package()-ed once
    if(NOT ${freespace_planner_dep}_FOUND)
      find_package(${freespace_planner_dep} REQUIRED NO_MODULE)
    endif()
  else()
    # dependencies with components must be find_package()-ed again
    list(REMOVE_AT depend_list 0)
    find_package(${freespace_planner_dep} REQUIRED NO_MODULE ${depend_list})
  endif()
  _list_append_unique(freespace_planner_INCLUDE_DIRS ${${freespace_planner_dep}_INCLUDE_DIRS})

  # merge build configuration keywords with library names to correctly deduplicate
  _pack_libraries_with_build_configuration(freespace_planner_LIBRARIES ${freespace_planner_LIBRARIES})
  _pack_libraries_with_build_configuration(_libraries ${${freespace_planner_dep}_LIBRARIES})
  _list_append_deduplicate(freespace_planner_LIBRARIES ${_libraries})
  # undo build configuration keyword merging after deduplication
  _unpack_libraries_with_build_configuration(freespace_planner_LIBRARIES ${freespace_planner_LIBRARIES})

  _list_append_unique(freespace_planner_LIBRARY_DIRS ${${freespace_planner_dep}_LIBRARY_DIRS})
  list(APPEND freespace_planner_EXPORTED_TARGETS ${${freespace_planner_dep}_EXPORTED_TARGETS})
endforeach()

set(pkg_cfg_extras "")
foreach(extra ${pkg_cfg_extras})
  if(NOT IS_ABSOLUTE ${extra})
    set(extra ${freespace_planner_DIR}/${extra})
  endif()
  include(${extra})
endforeach()
