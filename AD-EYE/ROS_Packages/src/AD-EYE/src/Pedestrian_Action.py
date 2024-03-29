#!/usr/bin/env python

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


if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
    os.mkdir('/home/adeye/Experiment_Results/')
file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')


MAX_DECCELERATION = -3 #m/s/s
PEDESTRIAN_END_POSITION = [236.628436713, -484.694323036]
ROSBAG_PARAMETERS = [7.74,40.0,0.9,20]
CAR_FRONT_LENGTH = 3.75 # from the back wheels to the front of the chassis
PEDESTRIAN_WIDTH = 0.3

##Creates the ExperimentOutcomes enumeration
#
#Child class of the Enum class.
#This enumeration has the 3 values PEDESTRIAN_OUT_OF_ROAD, CAR_PASSED_THROUGH_PEDESTRIAN, and CAR_STOPPED.
class ExperimentOutcomes(Enum):
    PEDESTRIAN_OUT_OF_ROAD = 1
    CAR_PASSED_THROUGH_PEDESTRIAN = 2
    CAR_STOPPED = 3

##A class to run an record the experiment A.
#The ego vehicle starts far from the pedestrian and accelerates until it reaches the established maximum speed.
#Once the ego vehicle is at a distance lesser or equal to the trigger distance from the pedestrian, 
#he moves from the side of the road to the center of the lane on which the ego vehicle is driving.
#We study in this experiment the influence of rain on the lidar by storing
#in files the distance from the ego vehicle to the pedestrian when the experiment stops and the reason why.
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
    rosbag_started = False
    experiment_started = False

    

    ##The constructor
    #
    #@param self The object pointer
    def __init__(self):
        rospy.Subscriber("/gnss_pose", PoseStamped, self.egoPoseCallback)
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        rospy.Subscriber("/simulink/pedestrian_pose", Point, self.pedestrianPositionCallback)
        rospy.Subscriber("/detection/lidar_detector/objects", DetectedObjectArray, self.lidarObjectCallback)
        self.stop_pub = rospy.Publisher("/simulink/stop_experiment",Bool, queue_size = 1) # stop_publisher
        # self.vel_pub = rospy.Publisher("/expA/velocity",Point, queue_size = 1) # for visualization in rqt_plot since /current_velocity had issues with the plotting
        self.tf_listener = tf.TransformListener()

        
            

    ##A method to update the position of the ego vehicle from /gnss_pose.
    #@param self The object pointer
    #@param data A Posestamped message
    def egoPoseCallback(self, data):
        Px = data.pose.position.x
        Py = data.pose.position.y
        quaternion = (data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w)
        euler = tf.transformations.euler_from_quaternion(quaternion)
        self.ego_pose =  [Px, Py, euler[0]]
            
    ##A method to update the pedestrian position from /simulink/pedestrian_pose.
    #@param self The object pointer
    #@param data Point message 
    def pedestrianPositionCallback(self, data):
        x = data.x
        y = data.y
        self.pedestrian_position = [x,y]

    ##A method to update the speed of the ego vehicle from /current_velocity, and to start the experiment if it's not already done.
    #@param self The object pointer
    #@param data TwistStamped message 
    def egoSpeedCallback(self, data):
        current_ego_speed = data.twist.linear.x
        if current_ego_speed != 0 and not self.experiment_started:
            self.experiment_started = True
            self.startRosbag()
            self.writeParameters()
            self.checkExperimentEnd()
        if self.experiment_started:
            self.ego_speeds.append(current_ego_speed)
            self.checkCollision()
            self.checkExperimentEnd()
        # self.vel_pub.publish(Point(current_ego_speed,current_ego_speed,current_ego_speed)) # for visualization in rqt_plot since /current_velocity had issues with the plotting

    ##A method to count the number of detections by the lidar, and check if a pedestrian is detected.
    #@param self The object pointer
    #@param data DetectedObjectArray message 
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
            

    ##A method that check if the experiment has ended and stores the correct experiment outcome.
    #@param self The object pointer
    def checkExperimentEnd(self):
        print rospy.get_rostime().secs
        if self.experiment_started and self.ego_speeds[len(self.ego_speeds)-1]==0.0 and rospy.get_rostime().secs>12:
            if not self.collision and not self.pedestrian_passed:
                self.distance_pedestiran_lane_center = np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)
                if self.distance_pedestiran_lane_center < 0.001:
                    self.distance_pedestiran_lane_center = 0
                self.computeAndStoreData(ExperimentOutcomes.CAR_STOPPED)
            elif not self.collision and self.pedestrian_passed:
                self.distance_pedestiran_lane_center = np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)
                self.pedestrian_passed = True
                self.computeAndStoreData(ExperimentOutcomes.PEDESTRIAN_OUT_OF_ROAD)
            elif self.collision and self.pedestrian_passed:
                self.computeAndStoreData(ExperimentOutcomes.CAR_PASSED_THROUGH_PEDESTRIAN)
            else: #this possibility of having collided whihout passing the pedestrian end position should never appear
                file.write("A collision occured without passing the pedestrian. This should not happen.\n")
                file.close()


    ##A method to check for a collision between the ego vehicle and the pedestrian.
    #@param self The object pointer
    def checkCollision(self):
        d = np.sqrt( (self.ego_pose[1]-self.pedestrian_position[1])**2 + (self.ego_pose[0]-self.pedestrian_position[0])**2 )
        self.distances_ego_pedestrian.append(d)
        if d < CAR_FRONT_LENGTH + PEDESTRIAN_WIDTH : # if there is a collision
            if self.collision == False : # we set the collision speed
                self.collision = True
                self.collision_speed = self.ego_speeds[len(self.ego_speeds)-2]
                self.distance_pedestiran_lane_center = np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)
                self.pedestrian_passed = True
                if self.distance_pedestiran_lane_center < 0.001:
                    self.distance_pedestiran_lane_center = 0

        # this is in case the pedestrian is out of the road when the car passes. we want pedestrian_passed to be True while collision is false
        d = np.sqrt( (self.ego_pose[1]-PEDESTRIAN_END_POSITION[1])**2 + (self.ego_pose[0]-PEDESTRIAN_END_POSITION[0])**2 )
        if d < CAR_FRONT_LENGTH + PEDESTRIAN_WIDTH : # the car has passed the end position
            self.pedestrian_passed = True


    ##A method that processes and stores the data.
    #The experimment outcome and the distance between the ego vehicle and the pedestrian are stored in a file 
    #@param self The object pointer
    #@param experiment_outcome An ExperimentOutcomes object explaining how or what the experiment stoped
    def computeAndStoreData(self, experiment_outcome):
        if experiment_outcome == ExperimentOutcomes.PEDESTRIAN_OUT_OF_ROAD:
            file.write("The pedestrian wasn't on the road when the car passed him --> no collision, no stop)" + ", "
                + str(self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-4]) + ", "
                + str(self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-3]) + ", "
                + str(self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-2]) + ", "
                + str(self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]) )

            file.write(', ')
            file.write("Dist pedestrian from lane center, "+str(self.distance_pedestiran_lane_center))
            file.write('\n')
            file.close()
        elif experiment_outcome == ExperimentOutcomes.CAR_PASSED_THROUGH_PEDESTRIAN:
            collision = 'Yes'
            stop_distance = - self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]
            estimated_stop_distance = self.collision_speed * self.collision_speed / 2 / MAX_DECCELERATION # if the car has continue braking it would have stopped at this distance
            self.writeData(collision, stop_distance, estimated_stop_distance)
        elif experiment_outcome == ExperimentOutcomes.CAR_STOPPED:
            collision = 'No'
            stop_distance = self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]
            self.writeData(collision, stop_distance, stop_distance)
        if self.shouldRecordRosbag(): # in any cases if a rosbag was recorded it must me stopped
            subprocess.Popen("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')
        self.stop_pub.publish(True) # stop_publisher


    ##A method that write in the ExperimentA.csv file the experiment's results.
    #@param self The object pointer
    #@param Collision A string taking the value "Yes" or "No"
    #@param StopDistance A float indicating the distance to the pedestrian when the car stopped
    #@param estimated_stop_distance A float indicating the estimated distance to the pedestrian when the car stopped
    def writeData(self, Collision, StopDistance, estimated_stop_distance):
        file.write("Maximum speed reached, "+str(max(self.ego_speeds)))
        file.write(', ')
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

        
    ##A method that write in the ExperimentA.csv file the experiment's parameters.
    #@param self The object pointer
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


    ##A method to check if the experiment's results should be stored in a .bag file.
    #This is done by checking that the maximum velocity, the rain intensity,
    #the reflectivity, and the trigger distance match the ROSBAG parameters
    #@param self The object pointer
    def shouldRecordRosbag(self):
        max_velocity = 0
        if rospy.has_param("adeye/motion_planning/op_common_params/maxVelocity"):
            max_velocity = float(rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity"))
        rain_intensity = rospy.get_param("/simulink/rain_intensity")
        reflectivity = rospy.get_param("/simulink/reflectivity")
        trigger_distance = 0
        if(rospy.has_param("/simulink/trigger_distance")):
            trigger_distance = rospy.get_param("/simulink/trigger_distance")
        if (max_velocity == ROSBAG_PARAMETERS[0]) and (rain_intensity == ROSBAG_PARAMETERS[1]) and (reflectivity == ROSBAG_PARAMETERS[2]) and (trigger_distance == ROSBAG_PARAMETERS[3]):
            return True
        else:
            return False


    ##A method to start storing the experiment results in a bag file.
    #@param self The object pointer
    def startRosbag(self):
        if self.shouldRecordRosbag() and not self.rosbag_started:
            ROSBAG_PATH = "/Experiment_Results/run" + str(time.time()) + ".bag" # ~ is added as a prefix, name of the bag
            TOPICS = "/TwistS /vehicle/odom /tf /filtered_points /camera_1/image_raw /dynamic_collision_points_rviz /local_trajectories_eval_rviz"
            ROSBAG_COMMAND = "rosbag record " + TOPICS + " -O ~" + ROSBAG_PATH +" __name:=rosbag_recorder" # command to start the rosbag
            self.rosbag_started = True
            subprocess.Popen(ROSBAG_COMMAND, shell=True, executable='/bin/bash')




#listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA_recorder')
    exp_A_recorder = ExperimentARecorder()
    rospy.spin()
