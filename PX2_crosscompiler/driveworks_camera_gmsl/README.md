Before cmake: (If not using a docker image)

- install sdk manager and install and download driveworks packages
	might have to manually type the commands for a few cases like certificate not signed and pending install
- install cuda cross compilation libraries
	$ sudo dpkg --add-architecture arm64
	$ sudo apt-get update
	$ sudo apt-get install cuda-cross-aarch64-9-2

	$ sudo apt install g++-aarch64-linux-gnu -y
	$ sudo apt install gcc-aarch64-linux-gnu -y
Example make and build

VIBRANTE_PDK: directory where sdk manager installed nvidia
DRIVEWORKS_DIR: path to driveworks

- Go to build folder and execute cmake command:

	cmake .. -DVIBRANTE_PDK=/home/ubuntu/nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux -DCMAKE_TOOLCHAIN_FILE=./../cmake/Toolchain-V5L.cmake -DCMAKE_BUILD_TYPE=Debug -DDRIVEWORKS_DIR=/usr/local/driveworks/targets/aarch64-Linux

- Execute build command
	make -j6 camera_gmsl_publisher  VERBOSE=1








