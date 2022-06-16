cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(supervised)

find_package(OpenCV REQUIRED)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(supervised main_supervised.cpp)
target_link_libraries(supervised PUBLIC ${PROJECT_SOURCE_DIR}/includes)


target_link_libraries(supervised PUBLIC ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

target_include_directories(supervised PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/includes"

)
