#!/bin/bash
find -type f -iname "*" -exec chmod +x {} \;
sudo apt-get update
sudo apt-get install -y expect

sudo sed -i -e "\$a export LD_LIBRARY_PATH=/usr/local/cuda/lib64:/home/adeye/ssdcaffe/build/lib:\$LD_LIBRARY_PATH" /etc/bash.bashrc

sudo sed -i -e "\$a export PATH=/usr/local/cuda-9.2/bin\${PATH:+:\${PATH}}" /etc/bash.bashrc

sudo sed -i -e "\$a export LD_LIBRARY_PATH=/usr/local/cuda-9.2/lib64\${LD_LIBRARY_PATH:+:\${LD_LIBRARY_PATH}}" /etc/bash.bashrc

sudo sed -i -e "\$a export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/lib​" /etc/bash.bashrc
