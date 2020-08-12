#!/bin/bash


source ~/.bashrc

rosnode kill rosbag_recorder # try to "gently" kill rosbag


FILE0=$1".active" # .bag.active file path
FILE1=$1 # .bag file path
STARTTIME=$(date +%s) # for the timeout, after which rosbag is forcedly killed and data removed

echo "Previous state was Engaged, should the data be saved? [y/N]): "
read answer

if [ "$answer" != "${answer#[Yy]}" ] ;then
    echo Rosbag save: $FILE1
else
    while [  -f "$FILE0" ] && [ $(($(date +%s)-STARTTIME)) -lt 3 ]; do # wait for rosbag process to finish cleanly (.active to be removed) with a timeout
	sleep 0.1
    done

    until [  -f "$FILE1" ] || [ $(($(date +%s)-STARTTIME)) -gt 3 ]; do # wait for rosbag process to finish cleanly (.bag to be written) with a timeout
	sleep 0.1
    done

    killall rosbag > /dev/null 2>&1 # in case rosnode kill failed the rosbag is killed here
    shred -u $FILE0 > /dev/null 2>&1 #remove the .active file in case rosbag did not terminate cleanly
    shred -u $FILE1 > /dev/null 2>&1 #remove the .bag file
    echo "Data was deleted" 
fi


echo "Press enter to exit"
read answer
pids=`ps -o ppid=$$` # find parent processes
for pid in $pids
do
    if [ $pid != $$ ] # kill the parent process that has a different id to this one, it will close the terminal window (note: exit would not work here because of the Python call)
    then
         kill $pid
    fi
done


