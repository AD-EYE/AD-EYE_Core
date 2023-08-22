#-------------------------------------------------------------------------------
# System packages
#-------------------------------------------------------------------------------

find_package(CUDA REQUIRED)

#-------------------------------------------------------------------------------
# Basic configuration
#-------------------------------------------------------------------------------

include(/usr/local/driveworks/samples/cmake/ArchConfiguration.cmake)
include(/usr/local/driveworks/samples/cmake/CommonConfiguration.cmake)
set(/usr/local/driveworks/samples/cmake/SDK_BINARY_DIR ${CMAKE_BINARY_DIR})

if(VIBRANTE)
  set(vibrante_DIR "/usr/local/driveworks-1.2/samples/3rdparty/${SDK_ARCH_DIR}/vibrante" CACHE PATH '' FORCE)
  find_package(vibrante REQUIRED CONFIG)
  if(NOT VIBRANTE_V5Q)
      set(vibrante_Xlibs_DIR "/usr/local/driveworks-1.2/samples/3rdparty/${SDK_ARCH_DIR}/vibrante_Xlibs" CACHE PATH '' FORCE)
      find_package(vibrante_Xlibs CONFIG REQUIRED)
  endif()
  find_package(EGL REQUIRED)
  add_definitions(-DDW_USE_NVMEDIA)
  add_definitions(-DDW_USE_EGL)
  set(DW_USE_NVMEDIA ON)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
else()
  add_subdirectory(/usr/local/driveworks-1.2/samples/3rdparty/src/glew /usr/local/driveworks-1.2/samples/3rdparty/src)
endif()

# Hide settings in default cmake view
mark_as_advanced(vibrante_DIR vibrante_Xlibs_DIR)

#-------------------------------------------------------------------------------
# Driveworks SDK
#-------------------------------------------------------------------------------

find_package(Driveworks REQUIRED)
include_directories(${Driveworks_INCLUDE_DIR})


list(APPEND Driveworks_LIBRARIES ${CUDA_LIBRARIES} ${CUDA_cublas_LIBRARY})
list(APPEND Driveworks_LIBRARIES ${vibrante_LIBRARIES} ${vibrante_Xlibs_LIBRARIES} nvmedia ${EGL_LIBRARIES})

#-------------------------------------------------------------------------------
# Src
#-------------------------------------------------------------------------------

set(DRIVEWORKS_DATAPATH "/usr/local/driveworks/data")

configure_file(/usr/local/driveworks/samples/src/framework/DataPath.hpp.in
               ${SDK_BINARY_DIR}/DataPath.hpp)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
add_definitions("-Wfatal-errors")


include_directories(
    ${SDK_BINARY_DIR}/configured
    /usr/local/driveworks/include
    /usr/local/cuda/include
    ./HAL
    ./E2E/inc
)

  
add_executable(main
    main.cpp
    dbc.cpp
    dbc_reader.cpp
    can_frame.cpp
    can_sender.cpp
    e2e_protector.cpp
    HAL/can_px2.cpp
    E2E/src/E2E_P01.c
    E2E/src/E2E_P05.c
    Crc/src/Crc_8.c
    Crc/src/Crc_16.c
)


target_link_libraries(main
  ${Driveworks_LIBRARIES}
)


enable_testing()

add_subdirectory(googletest)

#add_executable(test_can_controller tests/test_can_controller.cpp)
add_executable(test_can_sender tests/test_can_sender.cpp)

target_link_libraries(test_can_sender
  GTest::gtest_main
)

add_test(NAME CANSenderTest.Test1 COMMAND test_can_sender)




