#! /usr/bin/env python
import rospy
import roslib
import tf
import math
from std_msgs.msg import Int32
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class pedestrianPose ():
    
    def __init__(self,pose_List):

        self.poseList = pose_List
        
        self.pedestrian_pose_array_pub = rospy.Publisher('/pedestrian_pose', PoseArray, queue_size=1)
    
        pedestrian_pose_array= PoseArray()

        for newPose in self.poseList:
            pedestrian_pose_array.poses.append(Pose(newPose.pose.position, newPose.pose.orientation)) 
        rate = rospy.Rate(1)
        self.pedestrian_pose_array_pub.publish(pedestrian_pose_array)
        rospy.loginfo(pedestrian_pose_array)
        rate.sleep()

def createPose(Px, Py, internal_Counter):
    human_pose = PoseStamped()
    human_pose.pose.position.x = Px + internal_Counter
    human_pose.pose.position.y = Py + internal_Counter
    human_pose.pose.position.z = 0.0 
    human_pose.pose.orientation.x = 0.0
    human_pose.pose.orientation.y = 0.0
    human_pose.pose.orientation.z = 0.0 
    human_pose.pose.orientation.w = 1.0

    human_pose.header.seq = 1 
    human_pose.header.stamp = rospy.Time.now() 
    human_pose.header.frame_id = "map" 
    return human_pose 

if __name__=="__main__":
    rospy.init_node('pedestrian_pose')
    print ("pedestrianpose")
    counter = 0
    while counter < 50 :
        internal_Counter = 5 * counter
        pose_List = []
        pose_List.append( createPose(55.0, 176.0, internal_Counter) )
        pose_List.append( createPose(100.0, 231.0, internal_Counter) )
        pose_List.append( createPose(105.0, 236.0, internal_Counter) )
        pose_List.append( createPose(110.0, 241.0, internal_Counter) )
        pose_List.append( createPose(115.0, 246.0, internal_Counter) )
        pose_List.append( createPose(120.0, 251.0, internal_Counter) )
        counter = counter + 1
        pedestrianPose(pose_List)
        rospy.spin()
    
   
    


