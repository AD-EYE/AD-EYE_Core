#! /usr/bin/env bash

#Exit the script if one of the command fails
set -e

#default options
WITH_CUDA="true"

#Parsing command line options
for arg in $@
do
    if [ $arg == '--with-cuda' ]; then
        WITH_CUDA="true"
    else
        echo "Usage :"
        echo " $0 [--with-cuda]"
        echo ""
        echo -e "\tUse 'with-cuda' long option if you want to install"
        echo -e "\tAutoware with CUDA support"
        exit 0
    fi
done

#clone repo
cd $HOME
#sudo rm -rf AD-EYE_Core
echo "Cloning the AD-EYE Repository"
#git clone https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core.git
cd ~/AD-EYE_Core
git checkout dev

#Autoware dependencies
echo -e "\nInstalling Autoware dependencies"
cd autoware.ai
./autoware.ai.repos.run

#System dependencies
echo -e "\nInstalling system dependencies"
sudo apt-get update
sudo apt-get install -y python-catkin-pkg python-rosdep ros-$ROS_DISTRO-catkin gksu
sudo apt-get install -y python3-pip python3-colcon-common-extensions python3-setuptools python3-vcstool
sudo apt-get install openni2-doc openni2-utils openni-doc openni-utils libopenni0 libopenni-sensor-pointclouds0 libopenni2-0 libopenni-sensor-pointclouds-dev libopenni2-dev libopenni-dev libproj-dev
pip3 install -U setuptools

#Ros dependencies
echo -e "\nInstalling ROS dependencies"
rosdep update
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
