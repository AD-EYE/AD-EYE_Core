#!/usr/bin/env python
# Created by: HK-team HT2020 

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64
from geometry_msgs.msg import Vector3, Twist, TwistStamped
from RCV.msg import Rcv_info #Import custom message 

# Intialize each variable that is recived from the RCV
auto_mode = 0.0		# Auto_mode from 
quat_w = 0.0		# Quaternion w
quat_x = 0.0		# Quaternion x
quat_y = 0.0		# Quaternion y
quat_z = 0.0		# Quaternion z
yaw_rate = 0.0		# Yaw rate
a_x = 0.0		# Acceleration x
a_z= 0.0		# Acceleration z
lin_vel = 0.0 		# Linear velocity
lat = 0.0		# Latitude (gnss)
lon = 0.0		# Longitude (gnss)
odom_x = 0.0		# odometry x
odom_y = 0.0		# odometry y

# createVector3 creates a ROS Vector3 type and returns it 
def createVector3(x, y, z, unit): 
	printMsg = "Creating Vector3 with unit {0} from: ({1}, {2}, {3})".format(str(unit), str(x), str(y), str(z))
	print(printMsg) 

	# Create Vector3 object to be returned 
	myVector3 = Vector3()
	myVector3.x = x  
	myVector3.y = y  
	myVector3.z = z 
	return myVector3 

# createTwist creates a ROS Twist type and returns it
def createTwist(linX, linY, linZ, angX, angY, angZ): 
	printMsg = "Creating Twist from: (linX = {0}, linY = {1}, linZ = {2}, angX = {3}, angY = {4}, angZ = {5})".format(str(linX), str(linY), str(linZ), str(angX), str(angY), str(angZ))
	print(printMsg) 

	# Create twist object to be returned 
	myTwist = Twist() 
	myTwist.linear = createVector3(unit = "m/s", x=linX, y=linY, z=linZ)
	myTwist.angular = createVector3(unit = "rad/s", x=angX, y=angY, z=angZ)
	return myTwist

# get_data callback function to get data from rcv_info and set this data 
def get_data(rcv_info):

	global auto_mode
	global quat_w 
	global quat_x 
	global quat_y 
	global quat_z 
	global yaw_rate 
	global a_x 
	global a_z
	global lin_vel 
	global lat 
	global lon 
	global odom_x 
	global odom_y
	
	auto_mode = rcv_info.auto_mode
	quat_w = rcv_info.quat_w
	quat_x = rcv_info.quat_x
	quat_y = rcv_info.quat_y
	quat_z = rcv_info.quat_z
	yaw_rate = rcv_info.yaw_rate
	a_x = rcv_info.a_x
	a_z = rcv_info.a_z
	lin_vel = rcv_info.lin_vel
	lat = rcv_info.lat
	lon = rcv_info.lon
	odom_x = rcv_info.odom_x
	odom_y = rcv_info.odom_y


# rcv_current_velocity creates a publisher that publish the current linear and angular velocity of the RCV
def rcv_current_velocity():

	# Initialize publisher 
	pub = rospy.Publisher('current_velocity', TwistStamped, queue_size=100)
	rospy.init_node('current_velocity', anonymous=True)
	rate = rospy.Rate(100) # Rate of the RCV 
	
	# Create TwistStamped object
	myTwistStamped = TwistStamped() 

	# Set intial sequence
	seq = 0

	while not rospy.is_shutdown():
		print("-----------------------")
		rospy.Subscriber('rcv_info', Rcv_info, get_data)
		print("Data received")

		# Set twist stamped object to be published
		myTwistStamped.header.seq = seq
		myTwistStamped.header.stamp = rospy.Time.now() 
		myTwistStamped.header.frame_id = 'velodyne'
		myTwistStamped.twist = createTwist(linX = lin_vel, linY = 0.0, linZ = 0.0, angX = 0.0, angY = 0.0, angZ = yaw_rate) 
		pub.publish(myTwistStamped)
		
		# Iterate seq  
		seq = seq + 1
		

		print("data published")
		print("-----------------------")
		rate.sleep()

if __name__ == '__main__':
      try:
          rcv_current_velocity()
      except rospy.ROSInterruptException:
          pass





