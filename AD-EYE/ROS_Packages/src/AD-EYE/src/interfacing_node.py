#!/usr/bin/env python
import rospy
from std_msgs.msg import UInt8, Bool, Float32
from geometry_msgs.msg import PoseArray, TwistStamped
from sensor_msgs.msg import NavSatFix

class InterfaceNode:
    def __init__(self):
        rospy.init_node("interfacing_node")
        self.ext_publisher = rospy.Publisher("/sensor_detected_objects", PoseArray, queue_size=1)
        self.rec_speed_publisher = rospy.Publisher("/suggested_speed", UInt8, queue_size=1)
        self.gps_publisher = rospy.Publisher("/tecosa/car_location", NavSatFix, queue_size=1)
        self.car_speed_publisher = rospy.Publisher("/tecosa/car_speed", Float32, queue_size=1)
        self.warning_publisher = rospy.Publisher("/warning", Bool, queue_size=1)
        
        self.ext_subscriber = rospy.Subscriber("/tecosa/external_detections", PoseArray, self.external_objects_callback, queue_size=1)
        self.rec_speed_subscriber = rospy.Subscriber("/tecosa/recommended_speed", UInt8, self.recommended_speed_callback, queue_size=1)
        self.gps_subscriber = rospy.Subscriber("/fix", NavSatFix, self.gps_callback, queue_size=1)
        self.car_speed_subscriber = rospy.Subscriber("/estimated_vel_kmph", Float32, self.car_velocity_callback, queue_size=1)
        self.warning_subscriber = rospy.Subscriber("/tecosa/warning", Bool, self.warning_callback, queue_size=1)

    def external_objects_callback(self, external_objects):
        self.ext_publisher.publish(external_objects)

    # recommended speed in km/h
    def recommended_speed_callback(self, recommended_speed):
        self.rec_speed_publisher.publish(recommended_speed)

    def gps_callback(self, gps_fix):
        self.gps_publisher.publish(gps_fix)

    # car velocity in km/h
    def car_velocity_callback(self, velocity):
        self.car_speed_publisher.publish(velocity)

    def warning_callback(self, is_warning):
        self.warning_publisher.publish(is_warning)

if __name__ == '__main__':
    node = InterfaceNode()
    rospy.spin()