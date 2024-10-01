#!/bin/bash

BAGS=$@

LAST_BAG=${BAGS##* }
ALL_OTHER_BAGS=${BAGS% *}

for bag in $ALL_OTHER_BAGS
do
    echo Playing: $bag
    nohup rosbag play -q $bag 1>/dev/null 2>&1 &
done

# Run the last one in foreground to be able to abort
# the script (and all rosbag plays) with CTRL-C
echo Playing: $LAST_BAG
rosbag play -q $LAST_BAG 1>/dev/null 2>&1

