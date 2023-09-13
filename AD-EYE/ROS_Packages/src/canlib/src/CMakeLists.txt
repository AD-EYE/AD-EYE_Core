cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(CMAKE_BUILD_TYPE Debug)


if(NOT CAN)
    set(CAN CAN_DUMMY)
endif()


if (${CAN} STREQUAL CAN_DRIVE)
    set(CMAKE_TOOLCHAIN_FILE "/usr/local/driveworks/samples/cmake/Toolchain-V5L.cmake")
    set(CMAKE_MODULE_PATH /usr/local/driveworks/samples/cmake)
    set(SDK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(SDK_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(VIBRANTE_PDK "$ENV{HOME}/nvidia_clean/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux")
endif()

project(canlib VERSION 1.0)

include_directories(
  ./fmt/include
  ./spdlog/include
  ./inih/include
  ./bitpacker/include
)


file(GLOB DBC_FILES DBC/*.cpp )
file(GLOB FMT_SRC fmt/src/*.cc)

set(COMMON_SRC
  can_receiver.cpp
  can_sender.cpp
  ${FMT_SRC}
)


link_libraries(
  pthread
)


add_executable(main
  ${DBC_FILES}
  ${COMMON_SRC}
  HAL/can_socketcan.cpp
  main.cpp
  dbc_reader.cpp
  can_frame.cpp
  e2e_protector.cpp
  E2E/src/E2E_P01.c
  E2E/src/E2E_P05.c
  Crc/src/Crc_8.c
  Crc/src/Crc_16.c
)


add_executable(receiver
  ${DBC_FILES}
  ${COMMON_SRC}
  HAL/can_socketcan.cpp
  receiver.cpp
  dbc_reader.cpp
  can_frame.cpp
  can_receiver.cpp
  e2e_protector.cpp
  E2E/src/E2E_P01.c
  E2E/src/E2E_P05.c
  Crc/src/Crc_8.c
  Crc/src/Crc_16.c
)


include(cmake/tests.cmake NO_POLICY_SCOPE)


if (${CAN} STREQUAL CAN_DRIVE)
  add_definitions(-DCAN_DRIVE)
  include(cmake/can-px2.cmake NO_POLICY_SCOPE) 
elseif (${CAN} STREQUAL CAN_SOCKET)
  add_definitions(-DCAN_SOCKET)
  set(CAN_SRC HAL/can_socketcan.cpp)
else()
  include(cmake/can-dummy.cmake NO_POLICY_SCOPE)
  add_definitions(-DCAN_DUMMY)
endif()


target_sources(main
  PRIVATE ${CAN_SRC}
)


target_link_libraries(receiver
  pthread
)

