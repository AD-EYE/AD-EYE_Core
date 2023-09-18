#!/bin/bash

sudo ip link set up can0 type can bitrate 500000
sudo ip link set up can2 type can bitrate 500000 dbitrate 2000000 fd on fd-non-iso on
sudo ip link set up can3 type can bitrate 500000 dbitrate 2000000 fd on fd-non-iso on
