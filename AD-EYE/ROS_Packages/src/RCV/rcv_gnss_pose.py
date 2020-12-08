#!/usr/bin/env python
# Created by: HK-team HT2020 
# FIXME: This node does not work properly. AD-EYE can not read the published message as 
# 	 a point. Not sure why. The quick fix for this was to use PoseEstimation in Rviz
#	 to set the intial gnss estimation. The node have been disabled in the launch file right now.

import rospy
import socket
import time
import sys
import struct
import utm 
import numpy as np

from geometry_msgs.msg import Quaternion, Point, PoseStamped
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
	
	# Creating Quaternion object to be returned 
	# TODO: Maybe normalization needs to be done. See comments below
	q = Quaternion()
	const = np.sqrt(quat_x*quat_x + quat_y*quat_y + quat_z*quat_z + quat_w*quat_w)
	q.x = quat_x #/const
	q.y = quat_y #/const
	q.z = quat_z #/const
	q.w = quat_w #/const

	return q

# createPoint creates a ROS Point type and returns it
def createPoint(lat, lon): 
	#printMsg = "Creating Point with {0} from: ({1}, {2})".format(str(unitType), str(lat), str(lon))
	#print(printMsg) 
	u = utm.from_latlon(lat, lon) #Returns a vector with x and y cordinates 
	
	# print(u[0])
	# print(u[1])
	# Create Point object to be returned 
	myPoint = Point()
	myPoint.x = u[0] # TODO: Needs to have an offset relative our maps intial gnss pose
	myPoint.y = u[1] # TODO: Needs to have an offset relative our maps intial gnss pose
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
	quat_w = 0.0
	quat_x = 0.0
	quat_y = 0.0
	quat_z = 0.0
	yaw_rate = rcv_info.yaw_rate
	a_x = rcv_info.a_x
	a_z = rcv_info.a_z
	lin_vel = rcv_info.lin_vel
	lat = rcv_info.lat
	lon = rcv_info.lon
	odom_x = rcv_info.odom_x
	odom_y = rcv_info.odom_y

# rcv_gnss_pose creates a publisher that publish the gnss position the RCV 
def rcv_gnss_pose():
	
	# Initialize publisher 
	rospy.init_node('rcv_gnss_pose', anonymous=True)
	pub = rospy.Publisher('gnss_pose', PoseStamped, queue_size=100)
	rate = rospy.Rate(100) # FIXME: This does not work with 100Hz we think. Not sure why
	
	# Create PoseStamped object
	myPose = PoseStamped()
	
	# Set intial sequence
	seq = 0 

	while not rospy.is_shutdown():
		print("-----------------------")
		rospy.Subscriber('rcv_info', Rcv_info, get_data)
		print("Data received")

		# Create gnss object to be published
		myPose.header.stamp = rospy.Time.now()
		myPose.header.frame_id = "base_link"
		myPose.header.seq = seq
		myPose.pose.orientation = createQuaternion(quat_x, quat_y, quat_z, quat_w) 	
		myPose.pose.position = createPoint(lat, lon)
		pub.publish(myPose)
		
		print("Data published")
		print("-----------------------")
		print(myPose)
		seq = seq + 1
		rate.sleep()


if __name__ == '__main__':
      try:
          rcv_gnss_pose()
      except rospy.ROSInterruptException:
          pass





