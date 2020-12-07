# Information regarding the RCV ROS package

In the following document you will find information regarding each node  that you will find in this ROS package. The purpose of this package is to integrate the Research Vehicle (RCV) on ITRL with the AD-EYE platform. The code that you will find here was made during the HK-project in mechatronics  2020. 

## Overview of the nodes 

- RCV 
		- README.md
		- package.xml 
		- CMakeLists.txt 
		- rcv_launcher.py
		- non_rcv_topics.py
		- rcv_current_velocity.py
		- rcv_gnss_pose.py
		- rcv_imu.py
		- rcv_info.py
		- rcv_odom.py
		- receive_rcv.py
		- send_rcv.py
		- set_goal.py
		- msg
	* Rcv_info.msg


###  package.xml 
The typical generated file when creating a ROS-package. The only thing that is modified in this file is that lines <exec_depend>message_runtime</exec_depend> and 
<build_depend>message_generation</build_depend>  have been un-commented. This is so that we can use our own message type. 

### CMakeLists.txt 
Typical generated CMakeList.txt file that is generated when creating a ROS-package. Only some minor modifications have been made to get the custom message to work properly. 

### rcv_launcher.py
The launcher file that launches all the nodes that in this package. 

Note that the rcv-launcher.py is dependent on a separate package for the VLP-16 velodyne lidar and that this package is re-mapped to publish on the topic ``points_raw`` that is used by the AD-EYE platform. 

### non_rcv_topics.py
This node deals with topics that is, as of now, independent of the RCV (meaning that they don't need to get information from the RCV udp handler) and sends static. 
