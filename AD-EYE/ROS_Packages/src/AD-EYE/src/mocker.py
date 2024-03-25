#!/usr/bin/env python

import rospy
from std_msgs.msg import UInt8, Float64, Bool, String
from geometry_msgs.msg import PoseArray, TwistStamped, Pose
from sensor_msgs.msg import NavSatFix
from visualization_msgs.msg import MarkerArray, Marker

class bounding_box:
    def __init__(self, point1, point2):

        # ensure that 1 is on the left, 2 is on the right
        if point1[0] < point2[0]:
            self.lat1 = point1[0]
            self.lat2 = point2[0]
        else:
            self.lat1 = point2[0]
            self.lat2 = point1[0]
        
        # ensure that 1 is on the bottom, 2 is on the top
        if point1[1] < point2[1]:
            self.long1 = point1[1]
            self.long2 = point2[1]
        else:
            self.long1 = point2[1]
            self.long2 = point1[1]
    
    def check_if_inside(self, latitude, longitude):
        if latitude < self.lat1:
            return False
        elif latitude > self.lat2:
            return False
        elif longitude < self.long1:
            return False
        elif longitude > self.long2:
            return False
        else:
            return True

class Mocker:
    def __init__(self):
        rospy.init_node("tecosa_mocker")
        self.rec_speed_publisher = rospy.Publisher("/suggested_speed", UInt8, queue_size=1)
        self.marker_publisher = rospy.Publisher("/objects_markers", MarkerArray, queue_size=1)
        self.warning_publisher = rospy.Publisher("/warning", String, queue_size=1)
        
        self.speed_zones = {
            bounding_box((59.35428925605726, 18.062568116840684),(59.352861872471244, 18.068072009804272)) : 15, # Exp. Nord
            bounding_box((59.352560,18.066822),(59.351220,18.070233)) : 30, # Brinellvagen
            bounding_box((59.350717,18.069385),(59.349820,18.070190)) : 20, # 
            bounding_box((59.349974682491286, 18.066240227535655),(59.34809162160392, 18.072613251875843)) : 10  # Intersection area
        }

        self.max_speed = 50

        self.mock_trajectory = [
            (300, -410),
            (305, -420),
            (310, -430),
            (315, -440),
            (320, -450),
            (325, -460),
            (330, -470),
            (335, -480),
            (340, -490),
            (345, -500)
        ]

        self.warning_zones = {
            bounding_box((59.349974682491286, 18.066240227535655),(59.34809162160392, 18.072613251875843)) : "Incoming Vehicle" # Intersection area
        }

        self.gps_subscriber = rospy.Subscriber("/fix", NavSatFix, self.gps_callback, queue_size=1)

    def gps_callback(self, gps_fix):
        in_zone = False
        for zone, speed in self.speed_zones.items():
            if zone.check_if_inside(gps_fix.latitude, gps_fix.longitude):
                in_zone = True
                self.rec_speed_publisher.publish(speed)
                break
        if in_zone == False:
            self.rec_speed_publisher.publish(self.max_speed)

        in_zone = False
        for zone, message in self.warning_zones.items():
            if zone.check_if_inside(gps_fix.latitude, gps_fix.longitude):
                in_zone = True
                self.warning_publisher.publish(message)
                break
        if in_zone == False:
            self.warning_publisher.publish("")
    
    def publish_marker(self, n):
        p = Pose()
        p.position.x = self.mock_trajectory[n][0]
        p.position.y = self.mock_trajectory[n][1]
        p.position.z = -2.22

        p.orientation.z = 0.2297529
        p.orientation.w = 0.973249

        marker_msg = Marker()
        marker_msg.header.frame_id= "world"
        marker_msg.type = Marker.CUBE
        marker_msg.action = Marker.ADD
        marker_msg.pose = p

        marker_msg.scale.x = 3
        marker_msg.scale.y = 3
        marker_msg.scale.z = 3

        marker_msg.color.r = 255
        marker_msg.color.g = 1
        marker_msg.color.b = 1
        marker_msg.color.a = 0.5

        marker_array_msg = MarkerArray()

        marker_array_msg.markers.append(marker_msg)

        self.marker_publisher.publish(marker_array_msg)

if __name__ == '__main__':
    node = Mocker()
    r = rospy.Rate(10)
    counter = 0
    dot_counter = 0
    while not rospy.is_shutdown():
        counter += 1
        if counter == 10:
            counter = 0
            if dot_counter < len(node.mock_trajectory):
                node.publish_marker(dot_counter)
                dot_counter += 1
            else:
                dot_counter = 0
                node.publish_marker(dot_counter)
        r.sleep()
