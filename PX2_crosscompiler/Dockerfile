
FROM ubuntu:xenial-20210804

RUN apt-get update && \
      apt-get -y install sudo


ADD ./nvidia/ /home/ubuntu/nvidia/
ADD ./driveworks-1.2 /usr/local/driveworks
ADD ./cuda-9.2 /usr/local/cuda

RUN sudo apt install g++-aarch64-linux-gnu -y
RUN sudo apt install gcc-aarch64-linux-gnu -y
RUN sudo apt install cmake -y
RUN sudo apt install vim -y
