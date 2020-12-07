#!/usr/bin/env python

import rospy
import socket
import time
import sys
import struct
import utm 
import numpy as np

from geometry_msgs.msg import Quaternion, Point, PoseStamped
from RCV.msg import Rcv_info

'''

topic: gnss_pose

msg: geometry_msgs/Pose

geometry_msgs/Point position
  float64 x
  float64 y
  float64 z
geometry_msgs/Quaternion orientation
  float64 x
  float64 y
  float64 z
  float64 w

'''
# x = 333 791.67728
# y = 
# x = 333 791.67728

auto_mode = 0.0
quat_w = 0.0
quat_x = 0.0
quat_y = 0.0
quat_z = 0.0
yaw_rate = 0.0
a_x = 0.0
a_z= 0.0
lin_vel = 0.0
lat = 0.0
lon = 0.0
maplat = 0.0
maplon = 0.0
odom_x = 0.0
odom_y = 0.0


def createQuaternion(quat_x, quat_y, quat_z, quat_w): 
	printMsg = "Creating Quaternion from: ({0}, {1}, {2}, {3})".format(str(quat_x), str(quat_y), str(quat_z), str(quat_w))
	#print(printMsg) 
	
	# NOTE: Maybe normalization needs to be done
	# Creating Quaternion object to be returned  
	q = Quaternion()
	const = np.sqrt(quat_x*quat_x + quat_y*quat_y + quat_z*quat_z + quat_w*quat_w)
	q.x = quat_x#/const
	q.y = quat_y#/const
	q.z = quat_z#/const
	q.w = quat_w#/const

	return q


def createPoint(lat, lon): 
	#printMsg = "Creating Point with {0} from: ({1}, {2})".format(str(unitType), str(lat), str(lon))
	#print(printMsg) 
	u = utm.from_latlon(lat, lon)
	print(u[0])
	print(u[1])
	#umap = utm.from_latlon(maplat, maplon) 
	# Create Vector3 object to be returned 
	myPoint = Point()
	#myPoint.x = 59.327792
	#myPoint.y = 18.077771
	#myPoint.x = 59.306509
	#myPoint.y = 18.095710
	myPoint.x = 0.0 # u[0] #- umap[0]  
	myPoint.y = 0.0 #u[1] #- umap[1]
	myPoint.z = 0.0
	return myPoint 


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
	global maplat	
	global maplon	
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
	#lat = 59.34648		#Mock for car
	#lon = 18.07243		#Mock for car
	#lat2 = 59.34648		#Mock for car
	#lon2 = 18.07243		#Mock for car
	#maplat = 59.306509	#Depends on what map
	#maplon = 18.095710	#Depends on what map
	odom_x = rcv_info.odom_x
	odom_y = rcv_info.odom_y

def rcv_gnss_pose():
	
	
	# Initialize publisher 
	rospy.init_node('rcv_gnss_pose', anonymous=True)
	pub = rospy.Publisher('gnss_pose', PoseStamped, queue_size=100)
	rate = rospy.Rate(10) # 100hz
	
	myPose = PoseStamped()
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
		#myPoint = Point()
		myPoint = createPoint(lat, lon)
		#myPoint.x = -1.76180434227 #change to UTM 
		#myPoint.y = 0.756325662136
		myPoint.z = 0.0		
		myPose.pose.position = myPoint #createPoint(lat, lon)
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





