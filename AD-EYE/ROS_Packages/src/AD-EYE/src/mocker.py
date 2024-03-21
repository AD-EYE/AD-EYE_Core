#!/usr/bin/env python

import rospy
from std_msgs.msg import UInt8, Float64, Bool
from geometry_msgs.msg import PoseArray, TwistStamped
from sensor_msgs.msg import NavSatFix

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
        self.ext_publisher = rospy.Publisher("/sensor_detected_objects", PoseArray, queue_size=1)
        self.rec_speed_publisher = rospy.Publisher("/suggested_speed", UInt8, queue_size=1)
        
        self.gps_subscriber = rospy.Subscriber("/fix", NavSatFix, self.gps_callback, queue_size=1)

        self.speed_zones = {
            bounding_box((59.353074,18.063190),(59.353522,18.066228)) : 15, # Exp. Nord
            bounding_box((59.352560,18.066822),(59.351220,18.070233)) : 30, # Brinellvagen
            bounding_box((59.350717,18.069385),(59.349820,18.070190)) : 20, # 
            bounding_box((59.349974682491286, 18.066240227535655),(59.34809162160392, 18.072613251875843)) : 10  # Intersection area
        }

        self.max_speed = 50

    def external_objects_callback(self, external_objects):
        self.ext_publisher.publish(external_objects)

    def gps_callback(self, gps_fix):
        for zone, speed in self.speed_zones.items():
            if zone.check_if_inside(gps_fix.latitude, gps_fix.longitude):
                self.rec_speed_publisher.publish(speed)
                break
        self.rec_speed_publisher.publish(self.max_speed)

if __name__ == '__main__':
    node = Mocker()
    rospy.spin()