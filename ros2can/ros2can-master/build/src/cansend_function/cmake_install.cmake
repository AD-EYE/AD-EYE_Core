# Install script for directory: /home/adeye/AD-EYE_Core/ros2can/ros2can-master/src/cansend_function

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/adeye/AD-EYE_Core/ros2can/ros2can-master/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "samples")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/adeye/AD-EYE_Core/ros2can/ros2can-master/build/src/cansend_function/cansend_function")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function"
         OLD_RPATH "/usr/local/driveworks-1.2/targets/aarch64-Linux/lib:/usr/local/cuda/targets/aarch64-linux/lib:/usr/local/cuda/targets/aarch64-linux/lib/stubs:/home/adeye/nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux/targetfs/usr/lib/aarch64-linux-gnu:/home/adeye/nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux/lib-target:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/adeye/nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cansend_function")
    endif()
  endif()
endif()

