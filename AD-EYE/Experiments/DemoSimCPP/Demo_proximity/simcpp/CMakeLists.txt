cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
project(SimcppExample VERSION 2019.3 LANGUAGES CXX)

set(SIMCPP_TARGET simcpp)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

#-------------------------------------------------------
# OpenCV .zip Extraction & Building
#-------------------------------------------------------
set(OCV_VER 4.1.1)
get_filename_component(OPENCV_ROOT "${CMAKE_SOURCE_DIR}/../opencv" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(ZIPFN "${OPENCV_ROOT}/opencv-${OCV_VER}.zip")
set(OPENCV_VCSVERSION ${OCV_VER})
set(CPACK_PACKAGE_VERSION "${OPENCV_VCSVERSION}")

if(NOT EXISTS ${ZIPFN})
    message(FATAL_ERROR  "OpenCV library not found. Please download opencv-${OCV_VER}.zip from https://opencv.org/releases/ and place the file in the folder: ${OPENCV_ROOT}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${ZIPFN} WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Build OPENCV Statically
if(UNIX)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Built as dynamic libs?:")
endif()

add_subdirectory("${CMAKE_BINARY_DIR}/opencv-${OCV_VER}/" "opencv-build")
set("OpenCV_DIR" "${CMAKE_BINARY_DIR}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
#-------------------------------------------------------

#-------------------------------------------------------
# FIND PACKAGES
#-------------------------------------------------------
find_package( Prescan 2019.3 REQUIRED )
find_package( OpenCV REQUIRED COMPONENTS core highgui imgproc)

#-------------------------------------------------------
# Demo sources & headers
#-------------------------------------------------------
set (HEADER_FILES ProximityDemo.h Utils.h)
set (SOURCE_FILES main.cpp ProximityDemo.cpp)

#-------------------------------------------------------
# Final Target Linking
#-------------------------------------------------------
add_executable( ${SIMCPP_TARGET} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries( ${SIMCPP_TARGET} ${Prescan_LIBS} ${OpenCV_LIBS})
install(TARGETS ${SIMCPP_TARGET} DESTINATION ${CMAKE_BINARY_DIR})

#-------------------------------------------------------
# Generate prescanrun script
#-------------------------------------------------------
include(${Prescan_DIR}/PrescanUtils.cmake)
prescan_generate_helper_scripts(TARGET ${SIMCPP_TARGET} EXPERIMENT_DIR "${CMAKE_SOURCE_DIR}/..")