#!/bin/bash

export DISPLAY=:0
source $HOME/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/sh/tempbash
roslaunch adeye manager_simulation.launch test_automation:=true>/dev/null 2>&- & disown
roslaunch adeye ExperimentA.launch>/dev/null 2>&- & disown
roslaunch adeye ExperimentB.launch>/dev/null 2>&- & disown
sleep 5
echo "error" > file=sys.stderr
exit
