cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

if (PX2)
    set(CMAKE_TOOLCHAIN_FILE "/usr/local/driveworks/samples/cmake/Toolchain-V5L.cmake")
    set(CMAKE_MODULE_PATH /usr/local/driveworks/samples/cmake)
    set(SDK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(SDK_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(VIBRANTE_PDK "$ENV{HOME}/nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCRUISE/DriveSDK/drive-t186ref-linux")
endif()

project(canlib VERSION 1.0)


file(GLOB DBC_FILES DBC/*.cpp )


if (PX2)
    include(can-px2.cmake NO_POLICY_SCOPE)
    add_compile_options(-DCAN_HAL_PX2)
else()
    include(can-dummy.cmake NO_POLICY_SCOPE)
    add_compile_options(-DCAN_HAL_DUMMY)
endif()

