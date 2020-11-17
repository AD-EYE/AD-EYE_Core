#!/usr/bin/env python
# license removed for brevity
# import roslib
import os
import rospy
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from geometry_msgs.msg import Point
from autoware_msgs.msg import DetectedObjectArray
from std_msgs.msg import Bool
import numpy as np
import tf
from enum import Enum
import subprocess
import time # to put timestamp in rosbags' names

Store = True

if Store == True :
    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')

MAX_DECCELERATION = -3 #m/s/s
PEDESTRIAN_END_POSITION = [236.628436713, -484.694323036]
ROSBAG_PARAMETERS = [0,0.5,0.1,0]
# ROSBAG_PARAMETERS = [7.74,40.0,0.9,20]


class ExperimentOutcomes(Enum):
    PEDESTRIAN_OUT_OF_ROAD = 1
    CAR_PASSED_THROUGH_PEDESTRIAN = 2
    CAR_STOPPED = 3


class ExperimentARecorder:
    ego_speeds = []
    collision_speed = 'N/A'
    collision = False
    pedestrian_position = PEDESTRIAN_END_POSITION
    ego_pose = [0,0,0]
    distances_ego_pedestrian = []
    distance_pedestiran_lane_center = 100
    number_detections = 0
    number_new_detections = 0
    pedestrian_passed = False
    pedistrian_detected = False

    


    def __init__(self):
        rospy.Subscriber("/gnss_pose", PoseStamped, self.egoPoseCallback)
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        rospy.Subscriber("/simulink/pedestrian_pose", Point, self.pedestrianPositionCallback)
        rospy.Subscriber("/detection/lidar_detector/objects", DetectedObjectArray, self.lidarObjectCallback)
        self.stop_pub = rospy.Publisher("/simulink/stop_experiment",Bool, queue_size = 1) # stop_publisher
        # self.vel_pub = rospy.Publisher("/expA/velocity",Point, queue_size = 1) # for visualization in rqt_plot since /current_velocity had issues with the plotting
        self.tf_listener = tf.TransformListener()

        if self.shouldRecordRosbag():
            ROSBAG_PATH = "/run" + str(time.time()) + ".bag" # ~ is added as a prefix, name of the bag
            TOPICS = "/TwistS /vehicle/odom /tf /filtered_points /camera_1/image_raw /dynamic_collision_points_rviz /local_trajectories_eval_rviz"
            ROSBAG_COMMAND = "rosbag record " + TOPICS + " -O ~" + ROSBAG_PATH +" __name:=rosbag_recorder" # command to start the rosbag
            
            subprocess.Popen(ROSBAG_COMMAND, shell=True, executable='/bin/bash')
            


    def egoPoseCallback(self, data):
        Px = data.pose.position.x
        Py = data.pose.position.y
        quaternion = (data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w)
        euler = tf.transformations.euler_from_quaternion(quaternion)
        self.ego_pose =  [Px, Py, euler[0]]
        if Store == True :
            self.checkExperimentEnd()

    def pedestrianPositionCallback(self, data):
        x = data.x
        y = data.y
        self.pedestrian_position = [x,y]

    def egoSpeedCallback(self, data):
        current_ego_speed = data.twist.linear.x
        self.ego_speeds.append(current_ego_speed)
        # self.vel_pub.publish(Point(current_ego_speed,current_ego_speed,current_ego_speed)) # for visualization in rqt_plot since /current_velocity had issues with the plotting

    def lidarObjectCallback(self, data):
        for object in data.objects:
            try:
                object_pose = self.tf_listener.transformPose('/world', object)
                if((object_pose.pose.position.x - PEDESTRIAN_END_POSITION[0])**2 + (object_pose.pose.position.y - PEDESTRIAN_END_POSITION[1])**2<16 and not self.pedestrian_passed):
                    print object_pose.pose.position.x
                    print object_pose.pose.position.y
                    self.number_detections += 1
                    if not self.pedistrian_detected:
                        self.number_new_detections += 1
                    self.pedistrian_detected = True
            except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
                continue
            



    # checks if we fullfil the conditions to stop the experiment
    def checkExperimentEnd(self):
        print rospy.get_rostime().secs
        print self.number_detections
        print self.number_new_detections
        if len(self.ego_speeds)>2 : # in order to have access to the previous speed 
            d = np.sqrt( (self.ego_pose[1]-self.pedestrian_position[1])**2 + (self.ego_pose[0]-self.pedestrian_position[0])**2 )
            self.distances_ego_pedestrian.append(d)
            if len(self.distances_ego_pedestrian)>2 and rospy.get_rostime().secs > 12 : #to make sure the experiment is not stopped at the begining due to noise
                if self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-3]<self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-2] : # if the distance is increasing, the pedestrian has been passed,
                                                                                                    # we don't compare distance_Ego_P[len(distance_Ego_P)-2] with d because they are equal when the car stops
                    
                    if self.collision == False : # if the collision didn't occurred
                        self.distance_pedestiran_lane_center = np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)
                        self.pedestrian_passed = True
                        self.computeAndStoreData(ExperimentOutcomes.PEDESTRIAN_OUT_OF_ROAD)

                    else:
                        if (self.ego_speeds[len(self.ego_speeds)-1]==0.0) and (self.ego_speeds[len(self.ego_speeds)-2]!=0.0): # and (self.ego_speeds[len(self.ego_speeds)-3]!=0.0): # if the car just stoped (to test it only once)
                            self.computeAndStoreData(ExperimentOutcomes.CAR_PASSED_THROUGH_PEDESTRIAN)
                else :
                    if d<2.5 : # if there is a collision
                        if self.collision == False : # we set the collision speed
                            self.collision = True
                            self.collision_speed = self.ego_speeds[len(self.ego_speeds)-1-1]
                            self.distance_pedestiran_lane_center = np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)
                            self.pedestrian_passed = True
                            if self.distance_pedestiran_lane_center < 0.001:
                                self.distance_pedestiran_lane_center = 0
                    if (self.ego_speeds[len(self.ego_speeds)-1]==0.0) and (self.ego_speeds[len(self.ego_speeds)-1-1]!=0.0): # if the car just stoped (to test it only once)
                        self.distance_pedestiran_lane_center = np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)
                        if self.distance_pedestiran_lane_center < 0.001:
                            self.distance_pedestiran_lane_center = 0
                        self.computeAndStoreData(ExperimentOutcomes.CAR_STOPPED)



    # procedure that processes and stores the data
    def computeAndStoreData(self, experiment_outcome):
        self.writeParameters()
        if experiment_outcome == ExperimentOutcomes.PEDESTRIAN_OUT_OF_ROAD:
            file.write("The pedestrian wasn't on the road when the car passed him --> no collision, no stop \n")
            file.close()
        elif experiment_outcome == ExperimentOutcomes.CAR_PASSED_THROUGH_PEDESTRIAN:
            collision = 'Yes'
            stop_distance = self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]
            estimated_stop_distance = self.collision_speed * self.collision_speed / 2 / MAX_DECCELERATION # if the car has continue braking it would have stopped at this distance
            self.writeData(collision, stop_distance, estimated_stop_distance)
        elif experiment_outcome == ExperimentOutcomes.CAR_STOPPED:
            collision = 'No'
            stop_distance = self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]
            self.writeData(collision, stop_distance, stop_distance)


        if self.shouldRecordRosbag():
            subprocess.Popen("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')
        self.stop_pub.publish(True) # stop_publisher



    def writeData(self, Collision, StopDistance, estimated_stop_distance):
        file.write("Collision, "+str(Collision)) # then we write all the data needed in ExperimentA.csv
        file.write(', ')
        file.write("Coll speed, "+str(self.collision_speed))
        file.write(', ')
        file.write("Stop dist, "+str(StopDistance))
        file.write(', ')
        file.write("Estimated stop dist, "+str(estimated_stop_distance))
        file.write(', ')
        file.write("Number of pedestrian detections, "+str(self.number_detections))
        file.write(', ')
        file.write("Number of new pedestrian detections, "+str(self.number_new_detections))
        file.write(', ')
        file.write("Dist pedestrian from lane center, "+str(self.distance_pedestiran_lane_center))
        file.write('\n')
        file.close()

        
        


    # writes the experiment parameters
    def writeParameters(self):
        max_velocity = 0
        if rospy.has_param("adeye/motion_planning/op_common_params/maxVelocity"):
            max_velocity = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
        file.write("Set speed, "+str(max_velocity)+" , ")
        rain_intensity = rospy.get_param("/simulink/rain_intensity")
        file.write("Set rain intensity, "+str(rain_intensity)+" , ")
        reflectivity = rospy.get_param("/simulink/reflectivity")
        file.write("Set reflectivity, "+str(reflectivity)+" , ")
        trigger_distance = 0
        if(rospy.has_param("/simulink/trigger_distance")):
            trigger_distance = rospy.get_param("/simulink/trigger_distance")
        file.write("Set trigger distance, "+str(trigger_distance)+" , ")

    def shouldRecordRosbag(self):
        max_velocity = 0
        if rospy.has_param("adeye/motion_planning/op_common_params/maxVelocity"):
            max_velocity = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
        rain_intensity = rospy.get_param("/simulink/rain_intensity")
        reflectivity = rospy.get_param("/simulink/reflectivity")
        trigger_distance = 0
        if(rospy.has_param("/simulink/trigger_distance")):
            trigger_distance = rospy.get_param("/simulink/trigger_distance")
        if (max_velocity == ROSBAG_PARAMETERS[0]) and (rain_intensity == ROSBAG_PARAMETERS[1]) and (reflectivity == ROSBAG_PARAMETERS[2]) and (trigger_distance == ROSBAG_PARAMETERS[3]):
            return True




#listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA_recorder')
    exp_A_recorder = ExperimentARecorder()
    rospy.spin()
