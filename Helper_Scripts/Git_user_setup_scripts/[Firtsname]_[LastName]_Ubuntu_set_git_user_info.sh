#!/bin/sh

#Write your name between the quotation marks
name=""

#Write your email between the quotation marks
email=""


if [ -n "$name" ] && [ -n "$email" ];
then
cd /home/adeye/AD-EYE_Core
git config --global user.name "$name"
git config --global user.email "$email"
git config --local user.name "$name"
git config --local user.email "$email"
cd /home/adeye/
echo "Your information has been updated"
else
echo "[WARNING] You didn't set your name or your email in the script, you won't be able to commit or push changes" 
fi




