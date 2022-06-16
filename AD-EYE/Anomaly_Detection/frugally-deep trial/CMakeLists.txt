cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(frugally)

find_package(OpenCV REQUIRED)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(frugally main.cpp ssim.cpp)
target_link_libraries(frugally PUBLIC ${PROJECT_SOURCE_DIR}/includes)


target_link_libraries(frugally PUBLIC ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

target_include_directories(frugally PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/includes"

)
