cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(CMAKE_BUILD_TYPE Debug)


if (${CAN} STREQUAL CAN_DRIVE)
    set(CMAKE_TOOLCHAIN_FILE "/usr/local/driveworks/samples/cmake/Toolchain-V5L.cmake")
    set(CMAKE_MODULE_PATH /usr/local/driveworks/samples/cmake)
    set(SDK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(SDK_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(VIBRANTE_PDK "$ENV{HOME}/nvidia_clean/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux")
endif()

project(canlib VERSION 1.0)

find_package(catkin REQUIRED COMPONENTS
    roscpp
)


catkin_package(
  CATKIN_DEPENDS
    roscpp
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

file(GLOB DBC_FILES DBC/*.cpp )

if (${CAN} STREQUAL CAN_DRIVE)
  add_definitions(-DCAN_DRIVE)
  include(can-px2.cmake NO_POLICY_SCOPE) 
elseif (${CAN} STREQUAL CAN_SOCKET)
  add_definitions(-DCAN_SOCKET)
  set(CAN_SRC HAL/can_socketcan.cpp)
else()
  include(can-dummy.cmake NO_POLICY_SCOPE)
  add_definitions(-DCAN_DUMMY)
endif()

include_directories(
    ${SDK_BINARY_DIR}/configured
    /usr/local/driveworks/include
    /usr/local/cuda/include
    ./HAL
    ./E2E/inc
)

message(${DBC_FILES})
add_executable(main
  ${DBC_FILES}
  src/main.cpp
  src/dbc_reader.cpp
  src/can_frame.cpp
  src/can_receiver.cpp
  src/can_sender.cpp
  src/e2e_protector.cpp
  src/E2E/src/E2E_P01.c
  src/E2E/src/E2E_P05.c
  src/Crc/src/Crc_8.c
  src/Crc/src/Crc_16.c
)

target_link_libraries(
  main
  ${catkin_LIBRARIES}
)

target_sources(main
  PRIVATE ${CAN_SRC}
)


target_link_libraries(main
  pthread
)

