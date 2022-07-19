cmake_minimum_required(VERSION 3.0.2)
project(adeye_scenario_managers)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


find_package(
        catkin REQUIRED
        roscpp
        autoware_msgs
        op_planner
        op_ros_helpers
)

catkin_package(
        CATKIN_DEPENDS
        roscpp
        autoware_msgs
        op_planner
        op_ros_helpers
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

add_executable(
        Scenario2
        src/scenario_2.cpp
)
target_link_libraries(
        Scenario2
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario2
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario3
        src/scenario_3.cpp
)
target_link_libraries(
        Scenario3
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario3
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario4
        src/scenario_4.cpp
)
target_link_libraries(
        Scenario4
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario4
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario5
        src/scenario_5.cpp
)
target_link_libraries(
        Scenario5
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario5
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario6
        src/scenario_6.cpp
)
target_link_libraries(
        Scenario6
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario6
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario7
        src/scenario_7.cpp
)
target_link_libraries(
        Scenario7
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario7
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario8
        src/scenario_8.cpp
)
target_link_libraries(
        Scenario8
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario8
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario9
        src/scenario_9.cpp
)
target_link_libraries(
        Scenario9
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario9
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario10
        src/scenario_10.cpp
)
target_link_libraries(
        Scenario10
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario10
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario11
        src/scenario_11.cpp
)
target_link_libraries(
        Scenario11
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario11
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario12
        src/scenario_12.cpp
)
target_link_libraries(
        Scenario12
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario12
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario13
        src/scenario_13.cpp
)
target_link_libraries(
        Scenario13
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario13
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario14
        src/scenario_14.cpp
)
target_link_libraries(
        Scenario14
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario14
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario15
        src/scenario_15.cpp
)
target_link_libraries(
        Scenario15
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario15
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario16
        src/scenario_16.cpp
)
target_link_libraries(
        Scenario16
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario16
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario17
        src/scenario_17.cpp
)
target_link_libraries(
        Scenario17
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario17
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario18
        src/scenario_18.cpp
)
target_link_libraries(
        Scenario18
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario18
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario19
        src/scenario_20.cpp
)
target_link_libraries(
        Scenario19
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario19
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario20
        src/scenario_20.cpp
)
target_link_libraries(
        Scenario20
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario20
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario22
        src/scenario_22.cpp
)
target_link_libraries(
        Scenario22
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario22
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario23
        src/scenario_23.cpp
)
target_link_libraries(
        Scenario23
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario23
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario24
        src/scenario_24.cpp
)
target_link_libraries(
        Scenario24
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario24
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        Scenario26
        src/scenario_26.cpp
)
target_link_libraries(
        Scenario26
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario26
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario27
        src/scenario_27.cpp
)
target_link_libraries(
        Scenario27
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario27
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario28
        src/scenario_28.cpp
)
target_link_libraries(
        Scenario28
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario28
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario29
        src/scenario_29.cpp
)
target_link_libraries(
        Scenario29
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario29
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario30
        src/scenario_30.cpp
)
target_link_libraries(
        Scenario30
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario30
        ${catkin_EXPORTED_TARGETS}
)


add_executable(
        Scenario31
        src/scenario_31.cpp
)
target_link_libraries(
        Scenario31
        ${catkin_LIBRARIES}
)
add_dependencies(
        Scenario31
        ${catkin_EXPORTED_TARGETS}
)

add_executable(
        FaultExperimentManager
        src/fault_experiment_manager.cpp
)
target_link_libraries(
        FaultExperimentManager
        ${catkin_LIBRARIES}
)
add_dependencies(
        FaultExperimentManager
        ${catkin_EXPORTED_TARGETS}
)





# Mark executables and/or libraries for installation
install(
        TARGETS Scenario1 Scenario2 Scenario3 Scenario4 Scenario5 Scenario6 Scenario7 Scenario8 Scenario9 Scenario10
        Scenario11 Scenario12 Scenario13 Scenario14 Scenario15 Scenario16 Scenario17 Scenario18 Scenario19 Scenario20
        Scenario22 Scenario23 Scenario24 Scenario26 Scenario27 Scenario28 Scenario29 Scenario30 Scenario31
        FaultExperimentManager
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