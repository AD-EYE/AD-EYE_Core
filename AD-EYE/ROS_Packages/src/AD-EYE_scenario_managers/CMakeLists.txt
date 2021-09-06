cmake_minimum_required(VERSION 3.0.2)
project(adeye_scenario_managers)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


find_package(
    catkin REQUIRED
    roscpp
  )

catkin_package(
    CATKIN_DEPENDS
    roscpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)



add_executable(
  Scenario1
  src/scenario_1.cpp
)
target_link_libraries(
  Scenario1
  ${catkin_LIBRARIES}
)
add_dependencies(
  Scenario1
  ${catkin_EXPORTED_TARGETS}
)


# Mark executables and/or libraries for installation
install(
  TARGETS Scenario1
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


# Mark cpp header files for installation
install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)