rosnode kill -a>/dev/null 2>&- & disown
killall -9 rosmaster>/dev/null 2>&- & disown

roslaunch_pid=`pgrep -x roslaunch`

if [ -n "$roslaunch_pid" ]; then
    pkill -P $roslaunch_pid
fi

ps -aux | grep "ssh" 
pkill -f "ssh" #>/dev/null 2>&- disown
sleep 2
exit
