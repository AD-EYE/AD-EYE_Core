#Identification of the user
#!/bin/bash
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

#Extracting data from the AD-EYE_Core.wiki repository
cd AD-EYE_Core.wiki
echo "In AD-EYE_Core, there are : "
ls *.md |wc -l
echo "wiki pages and"
cd Images
find . -type f | wc -l
echo " pictures"

#Extracting data from the AD-EYE_GUI.wiki repository
cd $WORKING_PATH
cd wiki_statistics/AD-EYE_GUI.wiki
mkdir Images
echo "In AD-EYE_GUI, there are : "
ls *.md |wc -l
echo "wiki pages and"
cd Images
find . -type f | wc -l
echo " pictures"

#Extracting data from the AR_room.wiki repository
cd $WORKING_PATH
cd wiki_statistics/AR_room.wiki
mkdir Images
echo "In AR_room, there are : "
ls *.md |wc -l
echo "wiki pages and"
cd Images
find . -type f | wc -l
echo " pictures"