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
CMAKE_SOURCE_DIR = /home/adeye/ros2can/canlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adeye/ros2can/canlib/build

# Include any dependencies generated for this target.
include CMakeFiles/test_can_sender.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_can_sender.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_can_sender.dir/flags.make

CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o: CMakeFiles/test_can_sender.dir/flags.make
CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o: ../tests/test_can_sender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adeye/ros2can/canlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o -c /home/adeye/ros2can/canlib/tests/test_can_sender.cpp

CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adeye/ros2can/canlib/tests/test_can_sender.cpp > CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.i

CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adeye/ros2can/canlib/tests/test_can_sender.cpp -o CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.s

CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.requires:

.PHONY : CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.requires

CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.provides: CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_can_sender.dir/build.make CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.provides.build
.PHONY : CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.provides

CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.provides.build: CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o


# Object files for target test_can_sender
test_can_sender_OBJECTS = \
"CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o"

# External object files for target test_can_sender
test_can_sender_EXTERNAL_OBJECTS =

test_can_sender: CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o
test_can_sender: CMakeFiles/test_can_sender.dir/build.make
test_can_sender: lib/libgtest_main.a
test_can_sender: lib/libgtest.a
test_can_sender: CMakeFiles/test_can_sender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adeye/ros2can/canlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_can_sender"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_can_sender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_can_sender.dir/build: test_can_sender

.PHONY : CMakeFiles/test_can_sender.dir/build

CMakeFiles/test_can_sender.dir/requires: CMakeFiles/test_can_sender.dir/tests/test_can_sender.cpp.o.requires

.PHONY : CMakeFiles/test_can_sender.dir/requires

CMakeFiles/test_can_sender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_can_sender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_can_sender.dir/clean

CMakeFiles/test_can_sender.dir/depend:
	cd /home/adeye/ros2can/canlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adeye/ros2can/canlib /home/adeye/ros2can/canlib /home/adeye/ros2can/canlib/build /home/adeye/ros2can/canlib/build /home/adeye/ros2can/canlib/build/CMakeFiles/test_can_sender.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_can_sender.dir/depend

