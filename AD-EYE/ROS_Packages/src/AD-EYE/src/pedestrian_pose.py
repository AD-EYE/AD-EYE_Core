#! /usr/bin/env python
import rospy
import roslib
import tf
import math
from std_msgs.msg import Int32
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class pedestrianPose ():
    
    def __init__(self):
        self.egopose_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPoseCallback)
        self.goal_pub = rospy.Publisher('/pedestrian_pose', PoseStamped, queue_size=1)
    
    def gnssPoseCallback(self,egopose):
        pedestrianpose = PoseStamped()
        pose_tolerance = Int32()
        pose_tolerance.data = 20
       
        
        pedestrianpose.pose.position.x = egopose.pose.position.x + pose_tolerance.data
        pedestrianpose.pose.position.y = egopose.pose.position.y + pose_tolerance.data

        pedestrianpose.pose.position.z = egopose.pose.position.z

        pedestrianpose.pose.orientation.x = egopose.pose.orientation.x
        pedestrianpose.pose.orientation.y = egopose.pose.orientation.y
        pedestrianpose.pose.orientation.z = egopose.pose.orientation.z
        pedestrianpose.pose.orientation.w = egopose.pose.orientation.w

        pedestrianpose.header.seq = 1 
        pedestrianpose.header.stamp = rospy.Time.now() 
        pedestrianpose.header.frame_id = "map"
        
        rate = rospy.Rate(1)
        
        self.goal_pub.publish(pedestrianpose)
        rospy.loginfo(pedestrianpose)
        rate.sleep()
  

if __name__=="__main__":
    rospy.init_node('pedestrian_pose')
    print ("pedestrianpose")
    pedestrianPose()
    rospy.spin()
    
   
    


