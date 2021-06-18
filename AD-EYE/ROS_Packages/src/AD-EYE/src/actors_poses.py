#! /usr/bin/env python
import rospy
import roslib
import tf
import math
from std_msgs.msg import Int64
from adeye_msgs.msg import categorized_poses
from adeye_msgs.msg import categorized_pose
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class ActorsPosesPublisher():
    
    def __init__(self):
        self.actors_pose_array_pub_= rospy.Publisher('/actors_poses', categorized_poses, queue_size=1)
        self.publishPoses()

    def getPoseArray(self,Px,Py,pose_increment_value,number_of_actors,actor_category) :
        actors_pose_array = categorized_poses()
        actor_initial_pose =Pose()
        actor_initial_pose.position.x = 2000
        actor_initial_pose.position.y = 2000
         
        for i in range(0,number_of_actors):
            actors_pose = categorized_pose()
            actors_pose.category = actor_category
            actors_pose.pose.position.x = Px - actor_initial_pose.position.x + pose_increment_value 
            actors_pose.pose.position.y = Py - actor_initial_pose.position.y + pose_increment_value 
            actors_pose.pose.position.z = 0
            actors_pose.pose.orientation.x = 0
            actors_pose.pose.orientation.y = 0
            actors_pose.pose.orientation.z = 0 
            actors_pose.pose.orientation.w = 1
            actors_pose.header.seq = 1 
            actors_pose.header.stamp = rospy.Time.now() 
            actors_pose.header.frame_id = "map"

            actors_pose_array.poses.append(actors_pose)
            Px = Px + 2
            Py = Py + 2
        return(actors_pose_array)

    def publishPoses(self):
        
        counter = 0
        while not rospy.is_shutdown() and counter < 50:
            pose_increment_value = 3 * counter
            
            
            array_of_pedestrian_poses = self.getPoseArray(54,168,pose_increment_value, 20,1 )
            array_of_car_poses = self.getPoseArray(96,171,pose_increment_value, 20, 2 )
            array_of_cycle_poses = self.getPoseArray(63,171,pose_increment_value, 10, 3 )
            array_of_motorcycle_poses = self.getPoseArray(208,171,pose_increment_value, 5, 4 )
            
            actors_pose_array = categorized_poses()

            actors_pose_array.poses.extend(
                 array_of_pedestrian_poses.poses + array_of_car_poses.poses 
                + array_of_cycle_poses.poses + array_of_motorcycle_poses.poses)
          
            print(len(actors_pose_array.poses))
            print(counter)

            rate = rospy.Rate(1)
            self.actors_pose_array_pub_.publish(actors_pose_array)
            rate.sleep()
            counter = counter + 1
            

if __name__=="__main__":
    rospy.init_node('actors_poses')
    ActorsPosesPublisher()
    