#!/usr/bin/env python

import socket
import time

i = 0
TCP_IP = '10.42.0.28' # 10.42.0.28 => Tegra A and 10.42.0.29 => Tegra B. Use the one intedned to communicate with, i.e the one that runs the TegraCommunicationTestServer.py.
TCP_PORT = 11311 # default port for the ROS master
BUFFER_SIZE = 1024
MESSAGE = "Hello Server {}".format(i)

# set up connection and start communicate
while True: 
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   
    s.connect((TCP_IP, TCP_PORT))
    s.send(MESSAGE.encode('utf-8'))
    data = s.recv(BUFFER_SIZE).decode()
    s.close()

    print ("Reply: {}".format(data))
    i = i + 1
    MESSAGE = "Hello Server {}".format(i)

    time.sleep(1.0)