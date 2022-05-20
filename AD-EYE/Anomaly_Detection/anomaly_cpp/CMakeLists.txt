cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(anomaly_detection)

set (CMAKE_PREFIX_PATH /home/adeye/Downloads/libtorch)

find_package (Torch REQUIRED)

option(DOWNLOAD_MNIST "Download the MNIST dataset from the internet" ON)
if (DOWNLOAD_MNIST)
  message(STATUS "Downloading MNIST dataset")
  message(STATUS ${CMAKE_CURRENT_LIST_DIR})
  execute_process(
    
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/download_mnist.py
      -d ${CMAKE_BINARY_DIR}/data
    ERROR_VARIABLE DOWNLOAD_ERROR)
  if (DOWNLOAD_ERROR)
    message(FATAL_ERROR "Error downloading MNIST dataset: ${DOWNLOAD_ERROR}")
  endif()
endif()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable (${PROJECT_NAME} anomaly.cpp)
target_link_libraries (${PROJECT_NAME} "${TORCH_LIBRARIES}")
set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# if (MSVC)
#   file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
#   add_custom_command(TARGET mnist
#                      POST_BUILD
#                      COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                      ${TORCH_DLLS}
#                      $<TARGET_FILE_DIR:mnist>)
# endif (MSVC)