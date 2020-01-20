rosnode kill -a
killall -9 rosmaster

# Killing all processes launched by all roslaunch
for pid in $(pgrep -x roslaunch)
do
    pkill -P $pid
done

sleep 5
exit

