#!/usr/bin/env python
import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64
from geometry_msgs.msg import TwistStamped

udp_ip = "192.168.1.20" #RCV
#udp_ip = "127.0.0.1"	#internal ip
ip_nvidia = "192.168.1.200"
udp_port = 10001
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((ip_nvidia, udp_port))
global pkg_nr
pkg_nr = 1	

linearVelocity = 0.0
angularVelocity = 0.0

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data)
    global linearVelocity
    global angularVelocity
    
    linearVelocity = 0.1*data.twist.linear.x
    angularVelocity = data.twist.angular.z

def send_rcv():
    rospy.init_node('send_rcv', anonymous=True)

    #rospy.Subscriber('TwistS', TwistStamped, callback)		#For following a Simulation Experiment
    rospy.Subscriber('twist_raw', TwistStamped, callback)	#Real world experiment
    
    rate = rospy.Rate(100) # 100hz frequency of sending UDP to RCV	
    while not rospy.is_shutdown():

	 data = struct.pack('Ifff', pkg_nr, angularVelocity, linearVelocity, 1.0)
         sock.sendto(data, (udp_ip, udp_port))
	 rate.sleep()

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
      try:
          send_rcv()
      except rospy.ROSInterruptException:
          pass



