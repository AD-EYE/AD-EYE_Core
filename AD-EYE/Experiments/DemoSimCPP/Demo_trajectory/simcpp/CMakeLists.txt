cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)

project(TrajectoryDemo VERSION 2019.3 LANGUAGES CXX)

# Find Prescan package
find_package( Prescan 2019.3 REQUIRED)
include(${Prescan_DIR}/PrescanUtils.cmake)

add_executable(trajectoryDemo
    main.cpp)

target_link_libraries(trajectoryDemo ${Prescan_LIBS})

prescan_generate_helper_scripts(TARGET trajectoryDemo EXPERIMENT_DIR "${CMAKE_SOURCE_DIR}/..")
