#! /usr/bin/env python
import rospy
import roslib
import tf
import math
from numpy import arange
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class ActorsPosesPublisher():
    
    def __init__(self):
        self.actors_pose_array_pub = rospy.Publisher('/actors_poses', PoseArray, queue_size=1)
        
        self.publishPoses()

    def getPoseArray(self,poses,pose_increment_value) :

        actors_pose_array = PoseArray()
        actor_initial_pose =Pose()
        actor_initial_pose.position.x = 110.95
        actor_initial_pose.position.y = 600.05

        for i in poses:
            actors_pose = Pose()
            actors_pose.position.x = i[0] - actor_initial_pose.position.x + pose_increment_value
            actors_pose.position.y = i[1]- actor_initial_pose.position.y + pose_increment_value
            actors_pose.position.z = i[2]
            actors_pose.orientation.x = i[3]
            actors_pose.orientation.y = i[4]
            actors_pose.orientation.z = i[5] 
            actors_pose.orientation.w = i[6]
            actors_pose_array.header.seq = 1 
            actors_pose_array.header.stamp = rospy.Time.now() 
            actors_pose_array.header.frame_id = "map"

            actors_pose_array.poses.append(Pose(actors_pose.position, actors_pose.orientation))
        return(actors_pose_array)

    def publishPoses(self):

        pedestrianPoses = [[32.081,218.77,0.0,0.0,0.0,0.0,1.0],[43.21,229.17,0.0,0.0,0.0,0.0,1.0],[92.9,262.365,0.0,0.0,0.0,0.0,1.0],[97.94,251,0.0,0.0,0.0,0.0,1.0],[100.43,229.02,0.0,0.0,0.0,0.0,1.0],
        [151.3,230.45,0.0,0.0,0.0,0.0,1.0],[156.64,168.78,0.0,0.0,0.0,0.0,1.0],[118.48,217.84,0.0,0.0,0.0,0.0,1.0],[12.36,198.04,0.0,0.0,0.0,0.0,1.0],[201.59,229.5,0.0,0.0,0.0,0.0,1.0],
        [206.23,218,0.0,0.0,0.0,0.0,1.0],[227.02,215.53,0.0,0.0,0.0,0.0,1.0],[273.24,179.9,0.0,0.0,0.0,0.0,1.0],[361.8,180.26,0.0,0.0,0.0,0.0,1.0],[344.88,230.15,0.0,0.0,0.0,0.0,1.0],
        [442.694,229.71,0.0,0.0,0.0,0.0,1.0],[447.89,217.09,0.0,0.0,0.0,0.0,1.0],[417.90,156.1,0.0,0.0,0.0,0.0,1.0],[335.01,107.07,0.0,0.0,0.0,0.0,1.0],[250.04,118.45,0.0,0.0,0.0,0.0,1.0]]
        
        carPoses = [[34.73,222.02,0.0,0.0,0.0,0.0,1.0],[249.4,222.4,0.0,0.0,0.0,0.0,1.0],[249.78,171.26,0.0,0.0,0.0,0.0,1.0],[294.97,161.05,0.0,0.0,0.0,0.0,1.0],[414.4,171.44,0.0,0.0,0.0,0.0,1.0],
        [450.65,222.73,0.0,0.0,0.0,0.0,1.0],[97.47,255.17,0.0,0.0,1.0,0.0,0.0],[472.55,225.39,0.0,0.0,1.0,0.0,0.0],[435.425,174.53,0.0,0.0,1.0,0.0,0.0],[298.25,174.29,0.0,0.0,1.0,0.0,0.0],
        [265.09,225.84,0.0,0.0,1.0,0.0,0.0],[118.13,257.61,0.0,0.0,1.0,0.0,0.0],[109.6,225.69,0.0,0.0,1.0,0.0,0.0],[53.317,225.31,0.0,0.0,1.0,0.0,0.0],[74.83,251.61,0.0,0.0,1.0,0.0,0.0],
        [137.52,194.75,0.0,0.0,1.0,0.0,0.0],[138.0,143.57,0.0,0.0,1.0,0.0,0.0],[223,226,0.0,0.0,1.0,0.0,0.0],[257,170,0.0,0.0,0.0,0.0,1.0],[21.83,224.01,0.0,0.0,1.0,0.0,0.0]]

        cyclePoses =[[39.73,227.02,0.0,0.0,0.0,0.0,1.0],[254.4,227.4,0.0,0.0,0.0,0.0,1.0],[254.78,176.26,0.0,0.0,0.0,0.0,1.0],[299.97,166.05,0.0,0.0,0.0,0.0,1.0],[419.4,176.44,0.0,0.0,0.0,0.0,1.0],
        [455.65,227.73,0.0,0.0,0.0,0.0,1.0],[102.47,260.17,0.0,0.0,1.0,0.0,0.0],[477.55,230.39,0.0,0.0,1.0,0.0,0.0],[440.425,179.53,0.0,0.0,1.0,0.0,0.0],[303.25,179.29,0.0,0.0,1.0,0.0,0.0]]

        motorcyclePoses = [[37.081,223.77,0.0,0.0,0.0,0.0,1.0],[55.0,176.0,0.0,0.0,0.0,0.0,1.0],[97.9,267.365,0.0,0.0,0.0,0.0,1.0],[102.94,256,0.0,0.0,0.0,0.0,1.0],[105.43,234.02,0.0,0.0,0.0,0.0,1.0]]
        
        counter = 0
        while not rospy.is_shutdown() and counter < 50:
            pose_increment_value = 5 * counter
            
            carPosesArray = self.getPoseArray(carPoses,pose_increment_value)
            pedestrianPosesArray = self.getPoseArray(pedestrianPoses,pose_increment_value)
            cyclePosesArray = self.getPoseArray(cyclePoses,pose_increment_value)
            motorcyclePosesArray = self.getPoseArray(motorcyclePoses,pose_increment_value)
            
            actors_pose_array = PoseArray()

            actors_pose_array.poses.extend(
                carPosesArray.poses + pedestrianPosesArray.poses
                + cyclePosesArray.poses + motorcyclePosesArray.poses)
          
            print(len(actors_pose_array.poses))
            print(counter)

            rate = rospy.Rate(1)
            self.actors_pose_array_pub.publish(actors_pose_array)
            
            rate.sleep()
            counter = counter + 1

if __name__=="__main__":
    rospy.init_node('actors_poses')
    
    ActorsPosesPublisher()
    