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

#add_executable (greedy_projection gp3.cpp)
#target_link_libraries (greedy_projection ${PCL_LIBRARIES})

add_executable (main main.cpp)
target_link_libraries (main ${PCL_LIBRARIES} ${Boost_LIBRARIES})

#add_executable (main_old main_old.cpp)
#target_link_libraries (main_old ${PCL_LIBRARIES} ${Boost_LIBRARIES})

#add_executable (viewer_mesh viewer_mesh.cpp)
#target_link_libraries (viewer_mesh ${PCL_LIBRARIES})

#add_executable (viewer_point_cloud viewer_point_cloud.cpp)
#target_link_libraries (viewer_point_cloud ${PCL_LIBRARIES})

add_executable (validation validation.cpp)
target_link_libraries (validation ${PCL_LIBRARIES} ${Boost_LIBRARIES})