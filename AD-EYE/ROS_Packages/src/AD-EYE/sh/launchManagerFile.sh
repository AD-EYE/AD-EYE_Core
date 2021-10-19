#!/bin/bash

export DISPLAY=:0
source $HOME/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/sourceROSAndPackages.sh
roslaunch adeye manager_simulation.launch test_automation:=true>/dev/null 2>&- & disown