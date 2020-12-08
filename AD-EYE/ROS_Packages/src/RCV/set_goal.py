#!/usr/bin/env python
# Created by: HK-team HT2020 

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64
from geometry_msgs.msg import PoseStamped

# set_goal sets the goal on the map
def set_goal():

	# Initialize publisher 
	pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=100)
	rospy.init_node('set_goal', anonymous=True)
	rate = rospy.Rate(100) # 100hz
	
	# Init PoseStamped type 
	myGoal = PoseStamped()

	# Set intial sequence
	seq = 0

	while not rospy.is_shutdown():
		print("-----------------------")

		# Set Imu object to be published
		myGoal.header.seq = seq
		myGoal.header.stamp = rospy.Time.now() 
		myGoal.header.frame_id = 'velodyne'
		
		myGoal.pose.position.x = 1.0
		myGoal.pose.position.y = 2.0
		myGoal.pose.position.z = 3.0

		myGoal.pose.orientation.x = 0.0
		myGoal.pose.orientation.y = 0.0
		myGoal.pose.orientation.z = 0.0
		myGoal.pose.orientation.w = 1.0

		
		# Publish myGoal
		pub.publish(myGoal)
		
		# Iterate seq  
		seq = seq + 1
		
		print("data published")
		print("-----------------------")
		rate.sleep()

if __name__ == '__main__':
      try:
          set_goal()
      except rospy.ROSInterruptException:
          pass





