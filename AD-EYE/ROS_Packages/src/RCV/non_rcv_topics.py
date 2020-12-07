#!/usr/bin/env python

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Bool, Int32

def non_rcv_topics():
    	rospy.init_node('non_rcv_topics_node', anonymous=True)
     	rate = rospy.Rate(100) # 100hz
	
	pub1 = rospy.Publisher('initial_checks', Bool, queue_size=10)
	pub2 = rospy.Publisher('activation_request', Bool, queue_size=10)
	pub3 = rospy.Publisher('fault', Bool, queue_size=10)
	pub4 = rospy.Publisher('switchCommand', Int32, queue_size=10)
	
	while not rospy.is_shutdown():
		pub1.publish(1)
		pub2.publish(1)
		pub3.publish(0)
		pub4.publish(1)
		rate.sleep()
    
if __name__ == '__main__':
      try:
          non_rcv_topics()
      except rospy.ROSInterruptException:
          pass
