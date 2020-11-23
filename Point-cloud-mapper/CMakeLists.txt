cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(point_cloud_processing)

set(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PCL 1.7.2 REQUIRED)
find_package(Boost COMPONENTS thread REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories(${PCL_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcd_to_square_mesh pcd_to_square_mesh.cpp)
target_link_libraries (pcd_to_square_mesh ${PCL_LIBRARIES} ${Boost_LIBRARIES})

add_executable (validation validation.cpp)
target_link_libraries (validation ${PCL_LIBRARIES} ${Boost_LIBRARIES})

add_executable (outlier_remover outlier_remover.cpp)
target_link_libraries (outlier_remover ${PCL_LIBRARIES} ${Boost_LIBRARIES})