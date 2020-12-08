#!/usr/bin/env python
# Created by: HK-team HT2020 

import rospy
import socket
import time
import sys
import struct

from std_msgs.msg import Float64
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Quaternion, Vector3
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
	# NOTE: Maybe normalization needs to be done
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

def rcv_imu():

	# Initialize publisher 
	pub = rospy.Publisher('imu_raw', Imu, queue_size=100)

	rospy.init_node('rcv_imu', anonymous=True)
	rate = rospy.Rate(100) # 100hz
	
	# Create Imu object
	myImu = Imu() 

	# Set intial sequence
	seq = 0

	while not rospy.is_shutdown():
		print("-----------------------")
		rospy.Subscriber('rcv_info', Rcv_info, get_data)
		print("Data received")

		# Set Imu object to be published
		myImu.header.seq = seq
		myImu.header.stamp = rospy.Time.now() 
		myImu.header.frame_id = 'velodyne'
		myImu.orientation = createQuaternion(quat_x, quat_y, quat_z, quat_w) 
		myImu.angular_velocity = createVector3(0.0, 0.0, yaw_rate, "rad/s")
		myImu.linear_acceleration = createVector3(a_x, 0.0, a_z,"m/s")
		pub.publish(myImu)
		
		# Iterate seq  
		seq = seq + 1

		print("data published")
		print("-----------------------")
		rate.sleep()

if __name__ == '__main__':
      try:
          rcv_imu()
      except rospy.ROSInterruptException:
          pass





