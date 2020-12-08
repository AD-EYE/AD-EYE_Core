#!/usr/bin/env python
# Created by: HK-team HT2020 

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64
from nav_msgs.msg import Odometry 
from geometry_msgs.msg import Quaternion, Vector3, Point, Twist
from RCV.msg import Rcv_info


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

# createQuaternion creates a ROS Quaternion type and returns it
def createQuaternion(quat_x, quat_y, quat_z, quat_w): 
	printMsg = "Creating Quaternion from: ({0}, {1}, {2}, {3})".format(str(quat_x), str(quat_y), str(quat_z), str(quat_w))
	print(printMsg) 
	
	# NOTE: Maybe normalization needs to be done
	# Creating Quaternion object to be returned  
	q = Quaternion
	q.x = quat_x
	q.y = quat_y
	q.z = quat_z
	q.w = quat_w
	return q

# createVector3 creates a ROS Vector3 type and returns it 
def createVector3(x, y, z, unit): 
	printMsg = "Creating Vector3 with unit {0} from: ({1}, {2}, {3})".format(str(unit), str(x), str(y), str(z))
	print(printMsg) 

	# Create Vector3 object to be returned 
	myVector3 = Vector3()
	myVector3.x = x #Roll 
	myVector3.y = y #Pitch 
	myVector3.z = z #Yaw
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
		
# createPoint creates a ROS Point type and returns it
def createPoint(x, y, unitType): 
	printMsg = "Creating Point with {0} from: (x = {1}, y = {2})".format(str(unitType), str(x), str(y))
	print(printMsg) 

	# Create Vector3 object to be returned 
	myPoint = Point()
	myPoint.x = x
	myPoint.y = y
	myPoint.z = 0.0
	return myPoint 

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

# rcv_odom creates a publisher that publish the odometry position of the RCV
def rcv_odom():

	# Initialize publisher 
	pub = rospy.Publisher('vehicle/odom', Odometry, queue_size=100)
	rospy.init_node('rcv_odom', anonymous=True)
	rate = rospy.Rate(100) # 100hz
	
	# Create object
	myOdom = Odometry() 

	# Set intial sequence
	seq = 0

	while not rospy.is_shutdown():

		print("-----------------------")
		rospy.Subscriber('rcv_info', Rcv_info, get_data)
		print("Data received")


		# Create Imu object to be published
		myOdom.header.seq = seq
		myOdom.header.stamp = rospy.Time.now() 	
		myOdom.header.frame_id = 'base_link'	#TODO: Check this. NOTE: Not sure that this is the right frame. Thinking that ndt_match should set base_link as child 
		myOdom.child_frame_id = 'base_link' 	#TODO: Check this. NOTE: Not sure that this is the right frame. Thinking that ndt_match should set base_link as child 
		myOdom.pose.pose.orientation = createQuaternion(quat_x = quat_x, quat_y = quat_y, quat_z = quat_z, quat_w = quat_w) 
		myOdom.pose.pose.position = createPoint(unitType = "Odometry point", x = odom_x, y = odom_y)
		myOdom.twist.twist = createTwist(linX = lin_vel, linY = 0.0, linZ = 0.0, angX = 0.0, angY = 0.0, angZ = yaw_rate)

		pub.publish(myOdom)
		
		# Iterate seq  
		seq = seq + 1
		
		print("data published")
		print("-----------------------")
		rate.sleep()

if __name__ == '__main__':
      try:
          rcv_odom()
      except rospy.ROSInterruptException:
          pass





