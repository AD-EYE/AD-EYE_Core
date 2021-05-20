#! /usr/bin/env python
import rospy
import roslib
import tf
import math

from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class PedestrianPosesPublisher():
    
    def __init__(self):
        self.pedestrian_pose_array_pub = rospy.Publisher('/pedestrian_pose', PoseArray, queue_size=1)
        
        self.publishPoses()

    def addPosesToArray(self, Px, Py, pose_increment_value, pedestrian_pose_array):
        human_pose = Pose()
        human_pose.position.x = Px + self.pose_increment_value
        human_pose.position.y = Py + self.pose_increment_value
        human_pose.position.z = 0.0 
        human_pose.orientation.x = 0.0
        human_pose.orientation.y = 0.0
        human_pose.orientation.z = 0.0 
        human_pose.orientation.w = 1.0

        self.pedestrian_pose_array.poses.append(Pose(human_pose.position, human_pose.orientation))

    def publishPoses(self):
        counter = 0
        while not rospy.is_shutdown() and counter < 10:
            self.pose_increment_value = 5 * counter
            self.pedestrian_pose_array = PoseArray()

            self.pedestrian_pose_array.header.seq = 1 
            self.pedestrian_pose_array.header.stamp = rospy.Time.now() 
            self.pedestrian_pose_array.header.frame_id = "map"

            self.addPosesToArray(55.0, 176.0, self.pose_increment_value, self.pedestrian_pose_array) 
            self.addPosesToArray(100.0, 181.0, self.pose_increment_value, self.pedestrian_pose_array) 
            self.addPosesToArray(105.0, 186.0, self.pose_increment_value, self.pedestrian_pose_array)
            self.addPosesToArray(110.0, 191.0, self.pose_increment_value, self.pedestrian_pose_array)
            self.addPosesToArray(115.0, 196.0, self.pose_increment_value, self.pedestrian_pose_array)
            self.addPosesToArray(120.0, 201.0, self.pose_increment_value, self.pedestrian_pose_array)
            
            rate = rospy.Rate(1)
            self.pedestrian_pose_array_pub.publish(self.pedestrian_pose_array)
            rospy.loginfo(self.pedestrian_pose_array)
            rate.sleep()
            counter = counter + 1

if __name__=="__main__":
    rospy.init_node('pedestrian_pose')
    
    PedestrianPosesPublisher()
    rospy.spin()
    
   
    


