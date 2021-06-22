#!/bin/sh

#Write your name between the quotation marks
name=""

#Write your email between the quotation marks
email=""

cd /home/adeye/AD-EYE_Core
git config --global user.name "$name"
git config --global user.email "$email"
git config --local user.name "$name"
git config --local user.email "$email"
cd /home/adeye/
