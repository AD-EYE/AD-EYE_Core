#!/usr/bin/env python  
import roslib
import rospy
import tf
import sys
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

##A class to link the world frame to the sensor frame
class SensorBroadcaster:

    ##The constructor
    #
    #@param self the object pointer
    #@param world_frame The map frame
    #@param sensor_frame The base_link frame
    def __init__(self, world_frame, sensor_frame):
        
        self.br = tf.TransformBroadcaster()
        self.world_frame = world_frame
        self.sensor_frame = sensor_frame

    def run(self):

        # define camera position in world frame
        pose = Pose()
        
        # # intersection position start
        # pose.position.x = 345
        # pose.position.y = -470
        # # intersection position end
        
        # building camera position start
        pose.position.x = 100
        pose.position.y = -15
        # building camera position end

        pose.position.z = 5
        pose.orientation.x = 0.0
        pose.orientation.y = 0.0
        pose.orientation.z = 0.0
        pose.orientation.w = 1.0
        rate = rospy.Rate(10.0)
        while not rospy.is_shutdown():
            self.sendTransform(pose)
            rate.sleep()

    ##A method to send the data to the transform broadcaster.
    #@param self the object pointer
    #@param data A PoseStamped message
    def sendTransform(self, pose):
        self.br.sendTransform((pose.position.x, pose.position.y, pose.position.z),
                         (pose.orientation.x, pose.orientation.y,pose.orientation.z, pose.orientation.w),
                         rospy.Time.now(),
                         self.sensor_frame,
                         self.world_frame)


if __name__ == '__main__':
    node_name = "sensor_frame_broadcaster"
    world_frame = "world"
    sensor_frame = "external_sensor_tf"
    rospy.init_node(node_name)
    broadcaster =SensorBroadcaster(world_frame, sensor_frame)
    broadcaster.run()
    rospy.spin()
