set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
add_definitions("-Wfatal-errors")


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

target_link_libraries(main
  pthread
)

