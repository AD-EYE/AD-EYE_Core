set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
add_definitions("-Wfatal-errors")


include_directories(
    ${SDK_BINARY_DIR}/configured
    /usr/local/driveworks/include
    /usr/local/cuda/include
    ./HAL
    ./E2E/inc
)
