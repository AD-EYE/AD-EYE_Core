#! /usr/bin/env bash
set -e
# Parsing agruments
if [ -n "$1" ] # If argument folder given
then
    bagDir="$1"/ # Get the folder where rosbags are
    initDir=$(pwd) # Storing the initial working dir
    cd $bagDir
else
    bagDir="./" # assuming it is the current folder
fi

fixScript="/home/adeye/AD-EYE_Core/AD-EYE/TA/fix_bag_msg_def.py"

mkdir initialBags

echo -n "Fixing bags "

bagList=$(ls -tr *.bag)
nBag=$(echo $bagList | wc -w)
i=1

for bag in $bagList
do
    echo -ne "\rFixing bags $i/$nBag"
    mv $bag initialBags/
    $fixScript -l initialBags/$bag $bag > /dev/null
    ((i++))
done

echo " - Done"

if [ $bagDir == "./" ]; then
    cd $initDir # Going back to the initial working dir
fi
