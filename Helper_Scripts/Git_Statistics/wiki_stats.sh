#Extracting data from a git wiki repository
#!/bin/bash

#Identification of the user
echo "Enter your username : "
read USER
export USER
echo "Enter your token : "
read -s TOKEN
export TOKEN

#Working directory
export WORKING_PATH=~

#Cloning process for AD-EYE_Core.wiki
cd $WORKING_PATH
mkdir wiki_statistics
cd wiki_statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/wiki_statistics
spawn git clone https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core.wiki.git
expect "Username"
send $env(USER)\r
expect "Password"
send $env(TOKEN)\r
interact'

#Cloning process for AD-EYE_GUI.wiki
/usr/bin/expect -c'
cd $env(WORKING_PATH)/wiki_statistics
spawn git clone https://gits-15.sys.kth.se/AD-EYE/AD-EYE_GUI.wiki.git
expect "Username"
send $env(USER)\r
expect "Password"
send $env(TOKEN)\r
interact'


#Cloning process for AR_room.wiki
/usr/bin/expect -c'
cd $env(WORKING_PATH)/wiki_statistics
spawn git clone https://gits-15.sys.kth.se/AD-EYE/AR_room.wiki.git
expect "Username"
send $env(USER)\r
expect "Password"
send $env(TOKEN)\r
interact'

echo
#Extracting data from the AD-EYE_Core.wiki repository
echo "In AD-EYE_Core, there are : " $(find AD-EYE_Core.wiki/ -name '*.md' | wc -l) "wiki pages and" "$(($(find AD-EYE_Core.wiki/ -name '*.PNG' | wc -l)+$(find AD-EYE_Core.wiki/ -name '*.png' | wc -l)+$(find AD-EYE_Core.wiki/ -name '*.jpg' | wc -l)+$(find AD-EYE_Core.wiki/ -name '*.JPG' | wc -l)))" " pictures"

#Extracting data from the AD-EYE_GUI.wiki repository
echo "In AD-EYE_GUI, there are : " $(find AD-EYE_GUI.wiki/ -name '*.md' | wc -l) "wiki pages and" "$(($(find AD-EYE_GUI.wiki/ -name '*.PNG' | wc -l)+$(find AD-EYE_GUI.wiki/ -name '*.png' | wc -l)+$(find AD-EYE_GUI.wiki/ -name '*.jpg' | wc -l)+$(find AD-EYE_GUI.wiki/ -name '*.JPG' | wc -l)))" " pictures"

#Extracting data from the AR_room.wiki repository
echo "In AR_room, there are : " $(find AR_room.wiki/ -name '*.md' | wc -l) "wiki pages and" "$(($(find AR_room.wiki/ -name '*.PNG' | wc -l)+$(find AR_room.wiki/ -name '*.png' | wc -l)+$(find AR_room.wiki/ -name '*.jpg' | wc -l)+$(find AR_room.wiki/ -name '*.JPG' | wc -l)))" " pictures"

#Deleting the cloned folders
cd $WORKING_PATH
sudo rm -r -f wiki_statistics
