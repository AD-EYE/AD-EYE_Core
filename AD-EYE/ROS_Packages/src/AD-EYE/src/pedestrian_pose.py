#! /usr/bin/env python
import rospy
import roslib
import tf
import math

from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class pedestrianPose ():
    
    def __init__(self,pedestrian_pose_array):
        self.pedestrian_pose_array_pub = rospy.Publisher('/pedestrian_pose', PoseArray, queue_size=1)
    
        self.pedestrian_pose_array = pedestrian_pose_array
        rate = rospy.Rate(1)
        self.pedestrian_pose_array_pub.publish(self.pedestrian_pose_array)
        rospy.loginfo(self.pedestrian_pose_array)
        rate.sleep()

def addPoseToArray(Px, Py, pose_increment_value, pedestrian_pose_array):
    human_pose = Pose()
    human_pose.position.x = Px + pose_increment_value
    human_pose.position.y = Py + pose_increment_value
    human_pose.position.z = 0.0 
    human_pose.orientation.x = 0.0
    human_pose.orientation.y = 0.0
    human_pose.orientation.z = 0.0 
    human_pose.orientation.w = 1.0

    #human_pose.header.seq = 1 
    #human_pose.header.stamp = rospy.Time.now() 
    #human_pose.header.frame_id = "map" 

    pedestrian_pose_array.poses.append(Pose(human_pose.position, human_pose.orientation))

if __name__=="__main__":
    rospy.init_node('pedestrian_pose')
    
    counter = 0
    while counter < 10 :
        pose_increment_value = 5 * counter
        pedestrian_pose_array = PoseArray()
        #pedestrian_pose_array.header.seq = 1 
        #pedestrian_pose_array.header.stamp = rospy.Time.now() 
        #pedestrian_pose_array.header.frame_id = "map"
        addPoseToArray(55.0, 176.0, pose_increment_value, pedestrian_pose_array) 
        addPoseToArray(100.0, 181.0, pose_increment_value, pedestrian_pose_array) 
        addPoseToArray(105.0, 186.0, pose_increment_value, pedestrian_pose_array)
        addPoseToArray(110.0, 191.0, pose_increment_value, pedestrian_pose_array)
        addPoseToArray(115.0, 196.0, pose_increment_value, pedestrian_pose_array)
        addPoseToArray(120.0, 201.0, pose_increment_value, pedestrian_pose_array)
        counter = counter + 1
        pedestrianPose(pedestrian_pose_array)
        rospy.spin()
    
   
    


