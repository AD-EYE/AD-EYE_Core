rosnode kill -a>/dev/null 2>&- & disown
killall -9 rosmaster>/dev/null 2>&- & disown

# Killing all processes launched by all roslaunch
for pid in $(pgrep -x roslaunch)
do
    pkill -P $pid
done

ps -aux | grep "ssh"
pkill -f "ssh" #>/dev/null 2>&- disown
sleep 2
exit
