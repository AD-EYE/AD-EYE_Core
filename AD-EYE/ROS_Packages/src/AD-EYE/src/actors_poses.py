#! /usr/bin/env python
import rospy
import roslib
import tf
import math

from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class ActorsPosesPublisher():
    
    def __init__(self):
        self.actors_pose_array_pub = rospy.Publisher('/actors_poses', PoseArray, queue_size=1)
        
        self.publishPoses()

    def addPosesToArray(self, Px, Py, pose_increment_value, actors_pose_array,actor_initial_pose):
        other_actors_pose = Pose()
        other_actors_pose.position.x = Px - self.actor_initial_pose.position.x + self.pose_increment_value
        other_actors_pose.position.y = Py - self.actor_initial_pose.position.y + self.pose_increment_value
        other_actors_pose.position.z = 0.0 
        other_actors_pose.orientation.x = 0.0
        other_actors_pose.orientation.y = 0.0
        other_actors_pose.orientation.z = 0.0 
        other_actors_pose.orientation.w = 1.0

        self.actors_pose_array.poses.append(Pose(other_actors_pose.position, other_actors_pose.orientation))

    def publishPoses(self):
        counter = 0

        self.actor_initial_pose =Pose()
        self.actor_initial_pose.position.x = 58.0
        self.actor_initial_pose.position.y = 168.0

        while not rospy.is_shutdown() and counter < 30:
            self.pose_increment_value = 5 * counter

            self.actors_pose_array = PoseArray()

            self.actors_pose_array.header.seq = 1 
            self.actors_pose_array.header.stamp = rospy.Time.now() 
            self.actors_pose_array.header.frame_id = "map"

            self.addPosesToArray(55.0, 176.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose) 
            self.addPosesToArray(60.0, 181.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose) 
            self.addPosesToArray(70.0, 186.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(75.0, 191.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(80.0, 196.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(85.0, 201.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(90.0, 205.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(100.0, 215.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(120.0, 230.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)
            self.addPosesToArray(130.0, 240.0, self.pose_increment_value, self.actors_pose_array, self.actor_initial_pose)

            rate = rospy.Rate(1)
            self.actors_pose_array_pub.publish(self.actors_pose_array)
            rospy.loginfo(self.actors_pose_array)
            rate.sleep()
            counter = counter + 1

if __name__=="__main__":
    rospy.init_node('actors_poses')
    
    ActorsPosesPublisher()
    rospy.spin()
    
   
    


