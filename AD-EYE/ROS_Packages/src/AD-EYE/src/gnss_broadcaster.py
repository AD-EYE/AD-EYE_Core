#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Pose, PoseStamped, PoseWithCovarianceStamped
from geometry_msgs.msg import PoseStamped
from sensor_msgs.msg import NavSatFix
from math import cos, radians, sqrt, isnan
import tf


## This class gets the position of the car from the GNSS sensor as a NavSatFix message (longitude / latitude),
## converts it to a PoseStamped message (x, y coordinates) and tranfers it to the topic /gnss_pose.
## The Equirectangular projection is used, and therefore needs the long / lat coordinates of the map's origin
## and a standard parallel to center the projection (for example the center of KTH campus)

## A class to get the position of the car as a Pose message from simulink and
## to tranfer it to the topic /gnss_pose as a PoseStamped message.
class GnssBroadcaster:

    ##The constructor
    #@param self The object pointer
    def __init__(self, standard_parallel, map_origin):
        self.standard_parallel = standard_parallel
        self.map_origin = map_origin
        self.pose = PoseStamped()

        self.gnss_sub = rospy.Subscriber('/gnss_pose_simulink', PoseStamped, self.gnssSimulinkCallback)
        # self.gnss_sub = rospy.Subscriber('/fix', NavSatFix, self.gnssCallback)
        self.gnss_pub = rospy.Publisher('/gnss_pose', PoseStamped, queue_size=1)
        self.initialpose_pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped, queue_size=1)

        self.publish_initial_pose = True

    ##A Method to publish the position of the ego car as a PoseStamped message to the /gnss_pose topic.
    #@param self The object pointer
    #@param msg A Pose message received from /gnss_pose_simulink
    def gnssSimulinkCallback(self, msg):
        self.gnss_pub.publish(msg)

    def gnssCallback(self, fix):
        # Do not spread false coordinates
        if isnan(fix.latitude) or isnan(fix.longitude):
            return
        x_p, y_p = self.world_to_map_transform(self.standard_parallel, self.map_origin[0], self.map_origin[1], fix.longitude, fix.latitude)
        # print('Coords : (' + str(x_p) + " " + str(y_p) + "), Distance to the maps origin : " + str(sqrt(x_p**2 + y_p**2)) + 'm')

        self.pose.header.frame_id = "map"
        self.pose.header.stamp = rospy.Time.now()
        self.pose.pose.position.x = x_p #+ 60
        self.pose.pose.position.y = y_p #+ 50
        self.pose.pose.position.z = fix.altitude - 72
        quaternion = tf.transformations.quaternion_from_euler(0, 0, 0)
        self.pose.pose.orientation.x = quaternion[0]
        self.pose.pose.orientation.y = quaternion[1]
        self.pose.pose.orientation.z = quaternion[2]
        self.pose.pose.orientation.w = quaternion[3]
        self.gnss_pub.publish(self.pose)

        if self.publish_initial_pose:
            self.publish_initial_pose = False
            self.initialpose_pub.publish(self.startPosition(self.pose))

    # Equirectangular projection
    # phi_c : standard parallel, 0 : origin of the map, P : point to convert.
    # returns (x_p, y_p) : the coordinates on the map
    def world_to_map_transform(self, phi_c, lambda_0, phi_0, lambda_p, phi_p):
        #Earth radius [m]
        R = 6.371E6
        return (R * radians((lambda_p - lambda_0)) * cos(radians(phi_c)), R * radians((phi_p - phi_0)))

    def startPosition(self, pose_msg):
        initpose_msg = PoseWithCovarianceStamped()
        initpose_msg.header.stamp = rospy.get_rostime()
        initpose_msg.header.frame_id = "/map"
        initpose_msg.pose.pose.position.x = pose_msg.pose.position.x
        initpose_msg.pose.pose.position.y = pose_msg.pose.position.y
        initpose_msg.pose.pose.orientation.w = pose_msg.pose.orientation.w
        initpose_msg.pose.pose.orientation.x = pose_msg.pose.orientation.x
        initpose_msg.pose.pose.orientation.y = pose_msg.pose.orientation.y
        initpose_msg.pose.pose.orientation.z = pose_msg.pose.orientation.z
        return initpose_msg

if __name__ == '__main__':
    rospy.init_node('GNSS_broadcaster')
    standard_parallel = float(rospy.get_param('~standard_parallel'))
    map_origin = [float(x) for x in rospy.get_param('~map_origin').split(' ')]
    GnssBroadcaster(standard_parallel, map_origin)

    rospy.spin()
