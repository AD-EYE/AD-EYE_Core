#!/bin/bash


echo "To setup your user name and email, please specify a valid path to your git repository."
echo "The git folder /home/adeye/AD-EYE_Core will be used by default"


echo



while true 
do

	read -p "Please enter a path or press 'enter' : " My_Path

	if [ "$My_Path" = "" ]
	then
		My_Path=/home/adeye/AD-EYE_Core
	fi

	cd $My_Path
	
	echo
	echo "The current user's name is $(git config --local user.name)"
	echo "The current user's email is $(git config --local user.email)"
	echo

	read -p "Give your user name : " Name
	read -p "Give your user email : " Email
	echo
	echo "You will use the following :"
	echo $Name
	echo $Email
	echo

	read -p "Do you want to continue ? (y/n)" yn
	if [ $yn = "y" ]
	then
		git config --local user.name "$Name"
		git config --local user.email "$Email"
		git config --global user.name "$Name"
		git config --global user.email "$Email"
		echo "The name and email have been changed"
		exit
	fi

done
cd /home/adeye/
