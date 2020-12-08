#!/usr/bin/env python
# Created by: HK-team HT2020 

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64
from geometry_msgs.msg import TwistStamped

udp_ip = "192.168.1.20" 	# ip of RCV
ip_nvidia = "192.168.1.200"	# ip of host
udp_port = 10001		# port of host
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((ip_nvidia, udp_port))
global pkg_nr
pkg_nr = 1	

# Init variables
linearVelocity = 0.0
angularVelocity = 0.0

# callback is a vallback function that sets the current linear and angular velocity 
def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data)
    global linearVelocity
    global angularVelocity
    
    linearVelocity = data.twist.linear.x
    angularVelocity = data.twist.angular.z

# send_rcv sends a udp message to the RCV consisting of the RCVs current angular and linear velocity
def send_rcv():
    rospy.init_node('send_rcv', anonymous=True)

    #rospy.Subscriber('TwistS', TwistStamped, callback)		#For following a Simulation Experiment
    rospy.Subscriber('twist_raw', TwistStamped, callback)	#Real world experiment
    rate = rospy.Rate(100) # 100hz frequency of sending UDP to RCV	

    while not rospy.is_shutdown():

	 data = struct.pack('Iff', pkg_nr, angularVelocity, linearVelocity)
         sock.sendto(data, (udp_ip, udp_port))
	 rate.sleep()

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
      try:
          send_rcv()
      except rospy.ROSInterruptException:
          pass



