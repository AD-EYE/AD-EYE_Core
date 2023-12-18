cmake .. -DVIBRANTE_PDK=/home/adeye/nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref-linux -DNVIDIA_SDK_DIR=/home/adeye/nvidia/nvidia_sdk -DCMAKE_TOOLCHAIN_FILE=/home/adeye/dw_samples/cmake/Toolchain-V5L.cmake -DCMAKE_BUILD_TYPE=Debug 

make -j6 camera_gmsl_publisher  VERBOSE=1

