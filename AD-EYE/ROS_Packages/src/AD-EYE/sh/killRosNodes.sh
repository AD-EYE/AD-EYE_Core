rosnode kill -a
killall -9 rosmaster

roslaunch_pid=`pgrep -x roslaunch`

if [ -n "$roslaunch_pid" ]; then
    pkill -P $roslaunch_pid
fi

sleep 5
exit

