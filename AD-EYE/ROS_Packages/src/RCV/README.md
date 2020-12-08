# Information regarding the RCV ROS package

In the following document you will find information regarding each node that you will find in this ROS package. The purpose of this package is to integrate the Research Vehicle (RCV) on ITRL with the AD-EYE platform. The code that you will find here was made during the HK-project in mechatronics 2020. 

## Overview of package structure 

```
RCV 
│
└─── msg
│   │   Rcv_info.msg
│   
│   CMakeLists.txt
│   README.md
│   non_rcv_topics.py
│   package.xml
│   rcv_current_velocity.py
│   rcv_gnss_pose.py
│   rcv_imu.py
│   rcv_get.py
│   rcv_launcher.launch
│   rcv_odom.py
│   rcv_send.py
│   set_goal.py
```

### Rcv_info.msg
Defines out own message type, ``Rcv_info``, which is used with the topic ``rcv_info``.

### CMakeLists.txt 
Typical generated CMakeList.txt file that is generated when creating a ROS-package. Only some minor modifications have been made to get the custom message to work properly. 

### non_rcv_topics.py
This node deals with topics that is, as of now, independent of the RCV (meaning that they don't need to get information from the RCV udp handler) and sends static. 

###  package.xml 
The typical generated file when creating a ROS-package. The only thing that is modified in this file is that lines <exec_depend>message_runtime</exec_depend> and 
<build_depend>message_generation</build_depend>  have been un-commented. This is so that we can use our own message type. 

### rcv_current_velocity.py
Initiates node ``current_velocity``, subscribes to ``rcv_info`` and creates linear and angular twist-values of the RCV's current values. The twist-values are published to topic ``current_velocity``.

### rcv_gnss_pose.py
Initiates node ``rcv_gnss_pose``, subscribes to ``rcv_info`` and calculates x and y position on the map. The gnss-pose is published to topic ``gnss_pose``. 

Note that this node is currently not launched, since it is not finished,  instead ``2D Pose Estimate`` in Rviz is currently used.

### rcv_imu.py
Initiates node ``rcv_imu``, subscribes to ``rcv_info`` and publishes the quaternion position, linear acceleration and angular velocity to topic ``imu_raw``.

### rcv_get.py
Initiates node ``rcv_info_publisher``, creates udp socket at specified port number and binds the Nvidia Drive PX2's ip adress to it. The udp-data data is received from the RCV and the udp-data is unpacked as floats and published to topic ``rcv_info``. 

Note that the RCV has to send the udp messages to the correct ip adress and port of the Nvidia Drive PX2, which is specified in the RCV Simulink file.

### rcv_launcher.py
The launcher file that launches all the nodes that in this package. 

Note that the rcv-launcher.py is dependent on a separate package for the VLP-16 velodyne lidar and that this package is re-mapped to publish on the topic ``points_raw`` that is used by the AD-EYE platform.

### rcv_odom.py
Initiates node ``rcv_odom``, subscribes to ``rcv_info`` and publishes the quaternion position, odometry position and twist-values to topic ``vehicle/odom``.

Note that the RCV Simulink file has to be rebuilt to reset the odometry position to 0. This should be solved in the RCV Simulink file.

### rcv_send.py 
Initiates node ``send_rcv``, subscribes to ``twist_raw`` and creates udp socket at specified port number and binds the Nvidia Drive PX2's ip adress to it. Twist values are packed as binary data and sent through udp to the RCV's ip adress and port. 

Note that the ip adresses of the RCV and Nvidia Drive PX2, as well as port, are definied in both this script and in the RCV Simulink file. The portnumber in rcv_info.py and send_rcv.py have to be two different ports.

### set_goal.py
Initiates node ``set_goal`` and publishes goal position to topic ``move_base_simple/goal``.

Note that this node is currently not launched, since it is not finished, instead ``2D Nav Goal`` in Rviz is currently used.

### RCV Simulink file
Set sockets for udp connection ip adresses and ports: Ethernet UDP Setup-block.

Recieve upd-data (angular velocity and linear velocity) from PX2: Input -> ChairRefSignals1.
To choose socket and change what data is being received: Input -> ChairRefSignals1 -> UDP_receiver -> Ethernet UDP Receive (Change message size and socket number), DSDecode32 (change data types to receive).

Send udp-data data to PX2, quaternion calculation and odometry calculation: Output -> UDP_Out.
To choose socket and change what data is being sent: Output -> UDP_Out -> Ethernet UDP Transmit (Change message size and socket number), DSEncode32 (change data types to send).

