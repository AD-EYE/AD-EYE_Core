This experiment directory contains a "simcpp" folder where the source code to run a c++ simulation
of this experiment resides.

Required software installation to build the source:
- CMake version 3.7 or above
- C++11 compatible 64 bit compiler (e.g. Visual Studio 2015).
- Prescan installation version 2019.3 or above
- opencv-4.1.1.zip should exist inside the experiment directory at the location opencv/opencv-4.1.1.zip. 
  You can download opencv-4.1.1.zip sources from https://opencv.org/releases/ 

Below are examples on how to build and run the source code:

##############################
CMake GUI (Windows, Visual Studio 2015)

1. Start CMake GUI, choose the "simcpp" folder as source and specify a <build> folder in this experiment directory.
2. Click "Add Entry" in CMake GUI, enter name "Prescan_DIR", choose type "PATH" and in the value
   field enter path of <PrescanInstallPath>/lib/cmake
3. Press "Configure" in CMake GUI. You will be asked to specify the generator. Choose
   "Visual Studio 14 2015" and 64 bits platform ("x64") and press "Finish".
4. Press "Generate" in CMake GUI. Visual Studio project files are now generated into the <build>
   directory. Also a "prescanrun.bat" is created in this experiment directory.
5. Build this solution either in Visual Studio or through the command line. Use "psdev.bat" from
   the <build> directory to open the project in Visual Studio with the correct path settings.
6. Run "psrun.bat" from the <build> directory to run the demo acoording to the latest build 
   configuration. The artifact itself can be found within <build> directory under a folder named
   after the build configuration (such as Debug or Release). Make sure Prescan Process Manager is 
   already started.

##############################
cmake command line (Windows, Visual Studio)

1. Open a supported visual studio command prompt console
2. Create and change directory to a <build> folder inside the experiment directory
3. To configure cmake:
   cmake -DPrescan_DIR="<PrescanInstallPath>\lib\cmake" ..\simcpp
4. To build project:
   cmake --build . --config Release
5. To run the demo (make sure Prescan Process Manager is already started):
   psrun.bat

##############################
cmake command line (Linux, GCC)

1. Open a shell console
2. Create and change directory to a <build> folder inside the experiment directory
3. To configure cmake:
   cmake -DPrescan_DIR="<PrescanInstallPath>/lib/cmake" -DBUILD_TYPE=Release ../simcpp
4. To build project:
   make
5. To run the demo (make sure the DeploymentService is already started):
   ./psrun.sh