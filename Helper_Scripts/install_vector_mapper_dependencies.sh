#!/usr/bin/env bash
#This bash script installs the python dependencies required for installing vector mapper

# Ask whether we need to install vector mapper
read -p "Do you want to install the Vector Mapper? (y/n)" answer


case $answer in 
    [Yy] )
    echo "Preparing to install dependencies...." ;;
     
    [Nn] )
    echo "Exiting"; exit 1;;
    *)
    echo "Answer with a y or n "; exit 1;;
esac

# Go to the location where the requirements.txt file is and check if it exists
cd ~/AD-EYE_Core/Pex_Data_Extraction/pex2csv

echo "Checking whether the file requirements.txt exists in your system ...."
if [ -f requirements.txt ] 
then
    echo "This file exists in this system"
fi

git checkout feature/install_vector_mapper_dependencies

# Upgrade pip
echo "Upgrading pip..."
pip3 install --upgrade pip

#Installing dependencies
echo "Installing dependencies"
pip3 install -r vector_mapper_dependencies.txt
sudo apt-get install python3-tk
