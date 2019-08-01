rosnode kill -a>/dev/null 2>&- & disown
killall -9 rosmaster>/dev/null 2>&- & disown

ps -aux | grep "ssh" 
pkill -f "ssh" #>/dev/null 2>&- disown
sleep 2
exit
