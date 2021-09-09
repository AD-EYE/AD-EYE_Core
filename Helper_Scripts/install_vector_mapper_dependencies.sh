#!/usr/bin/env bash

read -p "Do you want to install the Vector Mapper? (y/n)" answer

case $answer in 
    [Yy] )
    echo "Preparing to install dependencies...." ;;
     
    [Nn] )
    echo "Exiting"; exit 1;;
    *)
    echo "Answer with a y or n "; exit 1;;
esac

cd ~/AD-EYE_Core/Pex_Data_Extraction/pex2csv
pwd
git checkout dev
echo "Upgrading pip..."
pip3 install --upgrade pip
echo "Installing dependencies"
pip3 install -r requirements.txt
sudo apt-get install python3-tk