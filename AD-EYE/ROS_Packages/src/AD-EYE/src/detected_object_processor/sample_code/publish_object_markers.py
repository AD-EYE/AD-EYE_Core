#!/usr/bin/env python

import rospy
from visualization_msgs.msg import Marker
from visualization_msgs.msg import MarkerArray
from geometry_msgs.msg import Pose
import sys

def parseColor(marker_msg, rgba_list):
    marker_msg.color.r = rgba_list[0]
    marker_msg.color.g = rgba_list[1]
    marker_msg.color.b = rgba_list[2]
    marker_msg.color.a = rgba_list[3]

p = Pose()
p.position.x = 84.599590301513672
p.position.y = 171.27021789550781
p.position.z = -2.22
p.orientation.x = 0.0
p.orientation.y = 0.0
p.orientation.z = 0.0
p.orientation.w = 0.0

marker_msg = Marker()
marker_array_msg = MarkerArray()
marker_msg.header.frame_id= "world"
marker_msg.type = Marker.CUBE
marker_msg.action = Marker.ADD
marker_msg.ns = "/detected_object_markers"
marker_msg.pose = p

marker_msg.scale.x = 3
marker_msg.scale.y = 3
marker_msg.scale.z = 3

parseColor(marker_msg , [255, 0, 0, 0.5]) #red color



marker_array_msg.markers.append(marker_msg)

if __name__ == '__main__':
    rospy.init_node('test_box_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher('/objects_markers', MarkerArray, queue_size=1)
    counter = 0
    while not rospy.is_shutdown():
        markerx = marker_array_msg.markers[0].pose.position.x
        if counter%10 == 0:
            if(markerx > 200):
                markerx = 84.59
            markerx += 10
        marker_array_msg.markers[0].pose.position.x = markerx
        pub.publish(marker_array_msg)
        counter +=1
        rate.sleep()