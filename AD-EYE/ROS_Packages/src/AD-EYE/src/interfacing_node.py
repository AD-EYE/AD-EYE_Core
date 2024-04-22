#!/usr/bin/env python
import rospy
from std_msgs.msg import UInt8, Bool, Float32, String
from geometry_msgs.msg import PoseArray, TwistStamped, Point
from sensor_msgs.msg import NavSatFix

class InterfaceNode:
    def __init__(self):
        rospy.init_node("interfacing_node")

        # threshold values for displaying warning message based on distance and time-to-collision
        self.distance_threshold = 25
        self.ttc_threshold = 5

        # warning message to be published
        self.warning_message = "Incoming vehicle!"

        # time of the last time a warning was published
        self.last_warning = rospy.Time.now()
        self.incoming_warning = False

        self.ext_publisher = rospy.Publisher("/sensor_detected_objects", PoseArray, queue_size=1)
        self.rec_speed_publisher = rospy.Publisher("/suggested_speed", UInt8, queue_size=1)
        self.gps_publisher = rospy.Publisher("/tecosa/car_location", NavSatFix, queue_size=1)
        self.car_speed_publisher = rospy.Publisher("/tecosa/car_speed", Float32, queue_size=1)
        self.warning_publisher = rospy.Publisher("/warning", String, queue_size=1)
        
        self.ext_subscriber = rospy.Subscriber("/EdgeDetection", PoseArray, self.external_objects_callback, queue_size=1)
        self.risk_subscriber = rospy.Subscriber("/EdgeRisk", Point, self.risk_callback, queue_size=1)
        self.gps_subscriber = rospy.Subscriber("/fix", NavSatFix, self.gps_callback, queue_size=1)
        self.car_speed_subscriber = rospy.Subscriber("/estimated_vel_kmph", Float32, self.car_velocity_callback, queue_size=1)

    def external_objects_callback(self, external_objects):
        self.ext_publisher.publish(external_objects)

    def risk_callback(self, risk_metrics):
        obstacle_distance = risk_metrics.x
        time_to_collision = risk_metrics.y
        recommended_speed = int(risk_metrics.z)

        if (obstacle_distance < self.distance_threshold) or (time_to_collision < self.ttc_threshold):
            self.warning_publisher.publish(self.warning_message)
            self.last_warning = rospy.Time.now()
            self.incoming_warning = True
        else:
            self.warning_publisher.publish("")
            self.incoming_warning = False

        self.rec_speed_publisher.publish(recommended_speed)


    def gps_callback(self, gps_fix):
        self.gps_publisher.publish(gps_fix)

    # car velocity in km/h
    def car_velocity_callback(self, velocity):
        self.car_speed_publisher.publish(velocity)

if __name__ == '__main__':
    node = InterfaceNode()
    r = rospy.Rate(10)
    while not rospy.is_shutdown():
        if (rospy.Time.now() > node.last_warning + rospy.Duration(5)) and node.incoming_warning:
            node.warning_publisher.publish("")
            node.incoming_warning = False
        r.sleep()
