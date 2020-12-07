#!/usr/bin/env python

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64

udp_ip = "192.168.1.150" #Nvidia
#udp_ip = "127.0.0.1" #intern ip
udp_port = 10001
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((udp_ip, udp_port))

def receive_rcv():
     pub = rospy.Publisher('rcv_fdb', Float64, queue_size=10)
     rospy.init_node('receive_rcv', anonymous=True)
     rate = rospy.Rate(100) # 100hz
     while not rospy.is_shutdown():
	  data, add = sock.recvfrom(128)
	  print("datan kom fram")
	  data = struct.unpack('????',data)		#Decide what variables AD-EYE system wants
	  print("data received", data[3])
	
          pub.publish(data[3])
	  print("data published")
          rate.sleep()

if __name__ == '__main__':
      try:
          receive_rcv()
      except rospy.ROSInterruptException:
          pass
