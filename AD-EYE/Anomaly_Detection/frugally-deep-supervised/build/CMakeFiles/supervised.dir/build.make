# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build

# Include any dependencies generated for this target.
include CMakeFiles/supervised.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/supervised.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/supervised.dir/flags.make

CMakeFiles/supervised.dir/main_supervised.cpp.o: CMakeFiles/supervised.dir/flags.make
CMakeFiles/supervised.dir/main_supervised.cpp.o: ../main_supervised.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/supervised.dir/main_supervised.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/supervised.dir/main_supervised.cpp.o -c /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/main_supervised.cpp

CMakeFiles/supervised.dir/main_supervised.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/supervised.dir/main_supervised.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/main_supervised.cpp > CMakeFiles/supervised.dir/main_supervised.cpp.i

CMakeFiles/supervised.dir/main_supervised.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/supervised.dir/main_supervised.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/main_supervised.cpp -o CMakeFiles/supervised.dir/main_supervised.cpp.s

CMakeFiles/supervised.dir/main_supervised.cpp.o.requires:

.PHONY : CMakeFiles/supervised.dir/main_supervised.cpp.o.requires

CMakeFiles/supervised.dir/main_supervised.cpp.o.provides: CMakeFiles/supervised.dir/main_supervised.cpp.o.requires
	$(MAKE) -f CMakeFiles/supervised.dir/build.make CMakeFiles/supervised.dir/main_supervised.cpp.o.provides.build
.PHONY : CMakeFiles/supervised.dir/main_supervised.cpp.o.provides

CMakeFiles/supervised.dir/main_supervised.cpp.o.provides.build: CMakeFiles/supervised.dir/main_supervised.cpp.o


# Object files for target supervised
supervised_OBJECTS = \
"CMakeFiles/supervised.dir/main_supervised.cpp.o"

# External object files for target supervised
supervised_EXTERNAL_OBJECTS =

supervised: CMakeFiles/supervised.dir/main_supervised.cpp.o
supervised: CMakeFiles/supervised.dir/build.make
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_stitching3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_superres3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_videostab3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_aruco3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_bgsegm3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_bioinspired3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_ccalib3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_cvv3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_dpm3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_face3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_fuzzy3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_hdf3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_img_hash3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_line_descriptor3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_optflow3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_reg3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_rgbd3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_saliency3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_stereo3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_structured_light3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_surface_matching3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_tracking3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_xfeatures2d3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_ximgproc3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_xobjdetect3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_xphoto3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_shape3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_photo3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_datasets3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_plot3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_text3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_dnn3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_ml3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_video3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_calib3d3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_features2d3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_highgui3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_videoio3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_viz3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_phase_unwrapping3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_flann3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgcodecs3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_objdetect3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgproc3.so.3.3.1
supervised: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_core3.so.3.3.1
supervised: CMakeFiles/supervised.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable supervised"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/supervised.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/supervised.dir/build: supervised

.PHONY : CMakeFiles/supervised.dir/build

CMakeFiles/supervised.dir/requires: CMakeFiles/supervised.dir/main_supervised.cpp.o.requires

.PHONY : CMakeFiles/supervised.dir/requires

CMakeFiles/supervised.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/supervised.dir/cmake_clean.cmake
.PHONY : CMakeFiles/supervised.dir/clean

CMakeFiles/supervised.dir/depend:
	cd /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build /home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/frugally-deep-supervised/build/CMakeFiles/supervised.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/supervised.dir/depend

