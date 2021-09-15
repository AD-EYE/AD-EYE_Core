#! /usr/bin/env bash

#Exit the script if one of the command fails
set -e

#Ask if the program should be installed with CUDA
while true; do
    read -p "Do you wish to install this program with CUDA? (y/n)" yn
    case $yn in
        [Yy]* ) WITH_CUDA="true"; break;;
        [Nn]* ) WITH_CUDA="false"; break;;
        * ) echo "Please answer 'y' or 'n'.";;
    esac
done

#clone repo
#cd $HOME
#sudo rm -rf AD-EYE_Core
#echo "Cloning the AD-EYE Repository"
#git clone https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core.git
cd ~/AD-EYE_Core
#git checkout dev

#Autoware dependencies
echo -e "\nInstalling Autoware dependencies"
cd autoware.ai
./autoware.ai.repos.run

#System dependencies
echo -e "\nInstalling system dependencies"
sudo apt-get update
{ #try
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc

sudo apt-get install -y python-catkin-pkg python-rosdep ros-$ROS_DISTRO-catkin gksu
sudo apt-get install -y python3-pip python3-colcon-common-extensions python3-setuptools python3-vcstool
sudo apt-get install openni2-doc openni2-utils openni-doc openni-utils libopenni0 libopenni-sensor-pointclouds0 libopenni2-0 libopenni-sensor-pointclouds-dev libopenni2-dev libopenni-dev libproj-dev
pip3 install -U setuptools
} || { #catch
    echo -e "\e[1;31m It seems that ros kinetic isn't installed, follow this tutorial to install it : https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core/wiki/Install-ROS-Kinetic\e[0m"
    exit
}

#Ros dependencies
echo -e "\nInstalling ROS dependencies"
if [ ! -f "/etc/ros/rosdep/sources.list.d/20-default.list" ]; then
	sudo rosdep init
fi
rosdep update --include-eol-distros
rosdep install -y --from-paths src --ignore-src --rosdistro $ROS_DISTRO

if [ "$WITH_CUDA" = "true" ]; then
    echo -e "\nBuilding Autoware with CUDA support"
    AUTOWARE_COMPILE_WITH_CUDA=1 colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
else
    echo -e "\nBuilding Autoware without CUDA support"
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
fi

echo -e "\nUpdating ~/.bashrc file"
# make modifications to bashrc to source the right workspaces
echo "source $HOME/AD-EYE_Core/autoware.ai/install/setup.bash --extend" >> ~/.bashrc
source ~/.bashrc

cd ..

#meet AD-EYE dependencies
echo -e "\nInstalling adeye dependencies"
sudo apt-get install libhdf5-openmpi-dev
sudo apt-get -y install ros-kinetic-costmap-2d ros-kinetic-navigation ros-kinetic-grid-map
sudo apt-get install ros-kinetic-rosbridge-suite

exec bash

#build adeye
echo -e "\nBuilding AD-EYE"
cd AD-EYE/ROS_Packages
catkin_make

echo -e "\nUpdating ~/.bashrc file"
echo "source $HOME/AD-EYE_Core/AD-EYE/ROS_Packages/devel/setup.bash --extend" >> ~/.bashrc

cd ~/AD-EYE_Core

#refresh bash
source ~/.bashrc
