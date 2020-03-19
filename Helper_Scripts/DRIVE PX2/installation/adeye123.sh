#!/bin/bash -i

<<COMMENT
COMMENT

# SWAP file
# Source: https://devanswers.co/guide-creating-swap-space-ubuntu-16-04/
cd ~
sudo fallocate -l 4G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
        # Results:
        # Setting up swapspace version 1, size = 1024 MiB (1073737728 bytes)
        # no label, UUID=801104b5-1967-458d-a564-8d63e7a24403
sudo swapon /swapfile
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab



# ROS Kineitc
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
echo "#############################################update"
sudo apt-get update
echo "############################################build-essential"
sudo apt-get install -y build-essential cmake python-pip
echo "#################################################check-install"
sudo apt-get install -y checkinstall
echo "########################################python-rosdep"
sudo apt-get install -y python-rosdep python-rosinstall-generator python-wstool python-rosinstall build-essential
echo "#########################################libavuntil"
sudo apt-get install -y libavutil-ffmpeg54
echo "######################################libswresample"
sudo apt-get install -y libswresample-ffmpeg1
echo "##############################3##libavformat"
sudo apt-get install -y libavformat-ffmpeg56
echo "####################################libswscale"
sudo apt-get install -y libswscale-ffmpeg3
echo "####################################aptitude"
sudo apt-get install aptitude

#<<COMMENT
#echo -e '\033[0;32m############################################################

#choose -q.

#############################################################\033[0m'
#COMMENT 

echo "####################################aptitude install libssl-dev"
sudo aptitude install libssl-dev

#echo -e '\033[0;32m############################################################

#choose -n, -y, -y. PLEASE notice the solution provided should NOT have any packages to remove.

#############################################################\033[0m '
echo "####################################aptitude install libssl-dev 2ND TIME"
sudo aptitude install libssl-dev

echo "################################################################ros-kinetic-desktop-full "
sudo apt-get install -y ros-kinetic-desktop-full

echo -e '\033[0;32m############################################################

ros-kinetic-desktop-full DONE!

############################################################\033[0m' 

echo "##########################################ros-kinetic-nmea-msgs"
sudo apt-get install -y ros-kinetic-nmea-msgs ros-kinetic-nmea-navsat-driver ros-kinetic-sound-play ros-kinetic-jsk-visualization ros-kinetic-grid-map ros-kinetic-gps-common

echo "##########################################ros-kinetic-controller-manager"
sudo apt-get install -y ros-kinetic-controller-manager ros-kinetic-ros-control ros-kinetic-ros-controllers ros-kinetic-gazebo-ros-control ros-kinetic-joystick-drivers

echo "##########################################libnlopt-dev"
sudo apt-get install -y libnlopt-dev freeglut3-dev qtbase5-dev libqt5opengl5-dev libssh2-1-dev libarmadillo-dev libpcap-dev gksu libgl1-mesa-dev libglew-dev

echo "##########################################ros-kinetic-camera-info-manager-py"
sudo apt-get install -y ros-kinetic-camera-info-manager-py ros-kinetic-camera-info-manager

echo "##########################################rosdep init"
sudo rosdep init

echo "##########################################rosdep update"
rosdep update

echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc

echo "##########################################python-rosinstall"
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential

# ssdCaffe
cd ~
echo -e '\033[0;32m############################################################

ssdCaffe BEGIN

############################################################\033[0m' 
sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
sudo apt-get install --no-install-recommends libboost-all-dev
sudo apt-get install libgoogle-glog-dev
sudo apt-get install liblmdb-dev
sudo apt-get install libopenblas-dev
git clone -b ssd https://github.com/weiliu89/caffe.git ssdcaffe
cd ssdcaffe

git checkout 4817bf8b4200b35ada8ed0dc378dceaf38c539e4
cp Makefile.config.example Makefile.config
cp ~/Documents/Makefile ~/ssdcaffe/Makefile
cp ~/Documents/Makefile.config ~/ssdcaffe/Makefile.config
#cd ~
#sudo chmod -R 777 ssdcaffe/

# Adjust Makefile.config (for example, if using Anaconda Python, or if cuDNN is desired)
# cd ~/AD-EYE_Core/AD-EYE/ROS_Packages


# sudo apt-get install libgoogle-glog-dev
# sudo apt-get install liblmdb-dev
# sudo apt-get install libopenblas-dev



# ssdCaffe Continue
# Caffe: http://caffe.berkeleyvision.org/installation.html#compilation
# Source: https://github.com/BVLC/caffe/wiki/Commonly-encountered-build-issues

# Adjust Makefile.config (for example, if using Anaconda Python, or if cuDNN is desired)

#hash -r #reset the environment, equivelant to starting new terminal to run script
#source ~/.bashrc
echo "########################## SCRIPT 2 BEGIN #####################"

cd ~/ssdcaffe
echo "export LD_LIBRARY_PATH=/usr/local/cuda/lib64:/home/adeye/ssdcaffe/build/lib:\$LD_LIBRARY_PATH" >> ~/.bashrc
source ~/.bashrc
make all -j6
make test -j6
make && make distribute

 

# Install Autoware and AD EYE
echo -e '\033[0;32m############################################################

Autoware and AD EYE BEGIN

############################################################\033[0m' 
cd ~    # Please open a new Terminal or back to your user path
git clone https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core.git
cd AD-EYE_Core
git checkout dev

cd autoware.ai
./autoware.ai.repos.run
source ~/.bashrc
#cd ~
#sudo chmod -R 777 AD-EYE_Core/
#cd ~/AD-EYE_Core/autoware.ai

sudo apt-get update
# cd ~/AD-EYE_Core/autoware.ai
# sudo apt-get install -y python-catkin-pkg python-rosdep ros-$ROS_DISTRO-catkin gksu
sudo apt-get install -y python-catkin-pkg python-rosdep ros-kinetic-catkin gksu
sudo apt-get install -y python3-pip python3-colcon-common-extensions python3-setuptools python3-vcstool
pip3 install -U setuptools
#sudo rosdep fix-permissions
rosdep update
# rosdep install -y --from-paths src --ignore-src --rosdistro $ROS_DISTRO
rosdep install -y --from-paths src --ignore-src --rosdistro kinetic
#source ~/.bashrc


echo -e '\033[0;32m############################################################

Begin to install autoware

############################################################\033[0m' 
#sleep 2
#hash -r
#sleep 2
#hash -r
cd ../AD-EYE_Core/autoware.ai/
source ~/.bashrc
#sleep 2
AUTOWARE_COMPILE_WITH_CUDA=1 colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

echo -e '\033[0;32m############################################################

Autoware installation done!

############################################################\033[0m' 


echo "source $HOME/AD-EYE_Core/autoware.ai/install/setup.bash --extend" >> ~/.bashrc
source ~/.bashrc

cd ~/AD-EYE_Core
sudo apt-get install ros-kinetic-costmap-2d
sudo apt-get install ros-kinetic-navigation
sudo apt-get install ros-kinetic-grid-map
cd AD-EYE/ROS_Packages
catkin_make


source ~/.bashrc

#hash -r
#source ~/.bashrc

echo "########################## SCRIPT 3 BEGIN #####################"
cd ~
# cd ~/AD-EYE_Core/AD-EYE/ROS_Packages
echo "source $HOME/AD-EYE_Core/AD-EYE/ROS_Packages/devel/setup.bash --extend" >> ~/.bashrc
#exec bash
source ~/.bashrc


sudo apt install openssh-client
sudo apt install openssh-server


echo "export PATH=/usr/local/cuda-9.2/bin\${PATH:+:\${PATH}}$" >> ~/.bashrc
source ~/.bashrc

echo "export LD_LIBRARY_PATH=/usr/local/cuda-9.2/lib64\${LD_LIBRARY_PATH:+:\${LD_LIBRARY_PATH}}​" >> ~/.bashrc
source ~/.bashrc




echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/lib​" >> ~/.bashrc
source ~/.bashrc


echo -e '\033[0;32m#####

DONE

#####\033[0m' 

exec bash




