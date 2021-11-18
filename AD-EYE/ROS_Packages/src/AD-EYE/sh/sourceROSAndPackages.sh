export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:/home/adeye/ssdcaffe/build/lib:$LD_LIBRARY_PATH
source /opt/ros/kinetic/setup.bash
source $HOME/AD-EYE_Core/autoware.ai/install/setup.bash --extend
source $HOME/AD-EYE_Core/AD-EYE/ROS_Packages/devel/setup.bash --extend
