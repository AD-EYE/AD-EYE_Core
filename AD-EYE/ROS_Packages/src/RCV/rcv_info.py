#!/usr/bin/env python

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64MultiArray, Byte
from RCV.msg import Rcv_info

udp_ip = "192.168.1.200" #Nvidia
udp_port = 10000
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((udp_ip, udp_port))

def rcv_info():

	# Initialize publisher 
	pub = rospy.Publisher('rcv_info', Rcv_info, queue_size=100)

	rospy.init_node('rcv_info_publisher', anonymous=True)
	rate = rospy.Rate(100) # 100hz
	myInfo = Rcv_info()
	
	while not rospy.is_shutdown():
		print("-----------------------")
		data_rec, add = sock.recvfrom(128)
		print("Data received")
		data_rec = struct.unpack('fffffffffffff',data_rec)
	
		# Set message parameters
		myInfo.auto_mode = data_rec[0]
		myInfo.quat_w = data_rec[1]
		myInfo.quat_x = data_rec[2]
		myInfo.quat_y = data_rec[3]
		myInfo.quat_z = data_rec[4]
		myInfo.yaw_rate = data_rec[5]
		myInfo.a_x = data_rec[6]
		myInfo.a_z = data_rec[7]
		myInfo.lin_vel = data_rec[8]
		myInfo.lat = data_rec[9]
		myInfo.lon = data_rec[10]
		myInfo.odom_x = data_rec[11]
		myInfo.odom_y = data_rec[12]

		# Publish topic
		pub.publish(myInfo)
		
		print("data published")
		print("-----------------------")
		rate.sleep()

if __name__ == '__main__':
      try:
          rcv_info()
      except rospy.ROSInterruptException:
          pass





