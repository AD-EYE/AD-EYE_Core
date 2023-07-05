# Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.

project(cansend_function C CXX)

include(/usr/local/driveworks/samples/cmake/FindDriveworks.cmake)
#-------------------------------------------------------------------------------
# Project files
#-------------------------------------------------------------------------------
set(PUBLIC_DOCS
    README.md
)

set(SOURCES
    cansend.cpp
)

set(LIBRARIES
    dw_samples_framework
  	${Driveworks_LIBRARIES}
)

#-------------------------------------------------------------------------------
# Final target
#-------------------------------------------------------------------------------
SET(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} ${DRIVEWORKS_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Ros2can-master")


# ------------------------------------------------------------------------------
# Install target
# ------------------------------------------------------------------------------
sdk_add_sample(${PROJECT_NAME})



