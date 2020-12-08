#!/usr/bin/env python
# Created by: HK-team HT2020 


import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Bool, Int32

# non_rcv_topics publishes topics that is idependent of the RCV but needed to get the AD-EYE 
# platform to run properly. Each node here is publishes a hard coded boolean. 
def non_rcv_topics():
	
	#Init ros node non_rcv_topics_node
    	rospy.init_node('non_rcv_topics_node', anonymous=True)
     	rate = rospy.Rate(100) # Rate of the RCV 
	

	# Init publisher
	pub1 = rospy.Publisher('initial_checks', Bool, queue_size=10)
	pub2 = rospy.Publisher('activation_request', Bool, queue_size=10)
	pub3 = rospy.Publisher('fault', Bool, queue_size=10)
	pub4 = rospy.Publisher('switchCommand', Int32, queue_size=10)
	
	# Publish topics
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
