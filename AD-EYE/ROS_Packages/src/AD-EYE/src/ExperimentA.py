#!/usr/bin/env python

import os
import rospy
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from geometry_msgs.msg import Point
from autoware_msgs.msg import DetectedObjectArray
from std_msgs.msg import Bool
from std_msgs.msg import Float32MultiArray
import numpy as np
import tf
from enum import Enum
import subprocess
import time # to put timestamp in rosbags' names
import socket # to get pc name
import time
from jsk_rviz_plugins.msg import OverlayText

if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
    os.mkdir('/home/adeye/Experiment_Results/')
file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')

MAX_DECCELERATION = -4 #m/s/s
PEDESTRIAN_END_POSITION = [236.628436713, -484.694323036]
ROSBAG_PARAMETERS = [7.74,40.0,0.9,20]
CAR_FRONT_LENGTH = 3.75 # from the back wheels to the front of the chassis
PEDESTRIAN_WIDTH = 0.3


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
    number_new_tracking = 0
    pedestrian_passed = False
    pedestrian_detected = False
    pedestrian_detected_previous_iteration = False
    pedestrian_tracked = False
    pedestrian_tracked_previous_iteration = False
    rosbag_started = False
    experiment_started = False
    last_dist_between_centers = 100000
    center_passed = False

    pedistrian_first_detection_done = False
    distance_first_detection = 0
    distance_pedestiran_lane_center_first_detection = 0

    first_nb_points_recorded = False
    first_nb_points = 0
    total_nb_points = 0
    nb_points_callbacks = 0

    exception_frame_transform = False


    def __init__(self):
        self.start_time = self.getCurrentTimeSring()
        rospy.Subscriber("/gnss_pose", PoseStamped, self.egoPoseCallback)
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        rospy.Subscriber("/simulink/pedestrian_pose", Point, self.pedestrianPositionCallback)
        rospy.Subscriber("/detection/lidar_detector/objects", DetectedObjectArray, self.lidarObjectCallback)
        rospy.Subscriber("/detection/lidar_tracker/objects", DetectedObjectArray, self.lidarTrackerObjectCallback)
        rospy.Subscriber("/points_raw_float32", Float32MultiArray, self.pointCloudCallback)
        self.stop_pub = rospy.Publisher("/simulink/stop_experiment",Bool, queue_size = 1) # stop_publisher
        self.text_overlay_pub = rospy.Publisher("/text_overlay",OverlayText, queue_size = 1)
        # self.vel_pub = rospy.Publisher("/expA/velocity",Point, queue_size = 1) # for visualization in rqt_plot since /current_velocity had issues with the plotting
        self.tf_listener = tf.TransformListener()

    def getCurrentTimeSring(self):
        t = time.localtime()
        current_time = time.strftime("%H:%M:%S", t)
        return str(current_time)

    def isCloseToZero(self, value):
        return abs(value) < 0.1

    def countNonZerosPoints(self, points):
        count = 0
        for point_index in range(len(points)/4):
            if not (self.isCloseToZero(points[point_index]) and self.isCloseToZero(points[point_index + 1]) and self.isCloseToZero(points[point_index + 2])):
                count += 1
        return count

    def pointCloudCallback(self, data):
        self.nb_points_callbacks += 1
        nb_valid_points = self.countNonZerosPoints(data.data)
        self.total_nb_points += nb_valid_points
        if not self.first_nb_points_recorded:
            self.first_nb_points_recorded = True
            self.first_nb_points = nb_valid_points


    def egoPoseCallback(self, data):
        Px = data.pose.position.x
        Py = data.pose.position.y
        quaternion = (data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w)
        euler = tf.transformations.euler_from_quaternion(quaternion)
        self.ego_pose =  [Px, Py, euler[0]]
            

    def pedestrianPositionCallback(self, data):
        x = data.x
        y = data.y
        self.pedestrian_position = [x,y]

    def egoSpeedCallback(self, data):
        current_ego_speed = data.twist.linear.x
        if current_ego_speed > 0.3 and not self.experiment_started:
            self.experiment_started = True
            self.startRosbag()
            self.writeParameters()
            self.checkExperimentEnd()
        if self.experiment_started:
            self.ego_speeds.append(current_ego_speed)
            self.computeDistance()
            self.checkCollision()
            self.checkExperimentEnd()
        # self.vel_pub.publish(Point(current_ego_speed,current_ego_speed,current_ego_speed)) # for visualization in rqt_plot since /current_velocity had issues with the plotting

    def lidarObjectCallback(self, data):
        for object in data.objects:
            try:
                object_pose = self.tf_listener.transformPose('/world', object)
                if((object_pose.pose.position.x - PEDESTRIAN_END_POSITION[0])**2 + (object_pose.pose.position.y - PEDESTRIAN_END_POSITION[1])**2<16):
                    print object_pose.pose.position.x
                    print object_pose.pose.position.y
                    self.number_detections += 1
                    if not self.pedistrian_first_detection_done:
                        self.pedistrian_first_detection_done = True
                        self.distance_first_detection = self.getCurrentDistance()
                        self.distance_pedestiran_lane_center_first_detection = self.getCurrentDistancePedestrianToLaneCenter()
                    self.pedestrian_detected = True
            except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
                self.exception_frame_transform = True
                continue
        if not self.pedestrian_detected_previous_iteration and self.pedestrian_detected:
                self.number_new_detections += 1
        self.pedestrian_detected_previous_iteration = self.pedestrian_detected
        self.pedestrian_detected = False
        self.publishDetectionsOverlay()
        

    def publishDetectionsOverlay(self):
        text = OverlayText()
        text.left = 20
        text.top = 20
        text.width = 800
        text.height = 400
        text.fg_color.a = 1.0
        text.fg_color.r = 1.0
        text.fg_color.g = 1.0
        text.text_size = 26
        text.font = "Liberation Mono"
        text.text = "Number of detections: " + str(self.number_detections) + "\n" + "Nb new detections:... " + str(self.number_new_detections) + "\n" + "Nb new trackings:.... " + str(self.number_new_tracking) + "\n" 
        self.text_overlay_pub.publish(text)


    def lidarTrackerObjectCallback(self, data):
        for object in data.objects:
            try:
                object_pose = self.tf_listener.transformPose('/world', object)
                if((object_pose.pose.position.x - PEDESTRIAN_END_POSITION[0])**2 + (object_pose.pose.position.y - PEDESTRIAN_END_POSITION[1])**2<16):
                    print("got lidar tracker")
                    self.pedestrian_tracked = True
            except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
                self.exception_frame_transform = True
                continue
        if not self.pedestrian_tracked_previous_iteration and self.pedestrian_tracked:
                self.number_new_tracking += 1
        self.pedestrian_tracked_previous_iteration = self.pedestrian_tracked
        self.pedestrian_tracked = False
            
    def shouldStopExperiment(self):
        return (self.experiment_started and abs(self.ego_speeds[len(self.ego_speeds)-1])<=0.1 and self.distances_ego_pedestrian[-1] < 200)

    def checkExperimentEnd(self):
        print rospy.get_rostime().secs
        if self.shouldStopExperiment():
            if not self.collision and not self.pedestrian_passed:
                self.distance_pedestiran_lane_center = self.getCurrentDistancePedestrianToLaneCenter()
                if self.distance_pedestiran_lane_center < 0.001:
                    self.distance_pedestiran_lane_center = 0
                self.computeAndStoreData(ExperimentOutcomes.CAR_STOPPED)
            elif not self.collision and self.pedestrian_passed:
                self.distance_pedestiran_lane_center = self.getCurrentDistancePedestrianToLaneCenter()
                self.pedestrian_passed = True
                self.computeAndStoreData(ExperimentOutcomes.PEDESTRIAN_OUT_OF_ROAD)
            elif self.collision and self.pedestrian_passed:
                self.computeAndStoreData(ExperimentOutcomes.CAR_PASSED_THROUGH_PEDESTRIAN)
            else: #this possibility of having collided whihout passing the pedestrian end position should never appear
                file.write("A collision occured without passing the pedestrian. This should not happen.\n")
                file.close()
            self.stop_pub.publish(True) # stop_publisher

    def getCurrentDistancePedestrianToLaneCenter(self):
        return np.sqrt((self.pedestrian_position[0]-PEDESTRIAN_END_POSITION[0])**2+(self.pedestrian_position[1]-PEDESTRIAN_END_POSITION[1])**2)

    def getCurrentDistance(self):
        return np.sqrt( (self.ego_pose[1]-self.pedestrian_position[1])**2 + (self.ego_pose[0]-self.pedestrian_position[0])**2 )

    def computeDistance(self):
        d = self.getCurrentDistance()
        if(d > self.last_dist_between_centers and d < 4):
            self.center_passed = True
        offset_distance = CAR_FRONT_LENGTH + PEDESTRIAN_WIDTH
        if(self.center_passed):
            self.distances_ego_pedestrian.append(-d - offset_distance)
        else:
            self.distances_ego_pedestrian.append(d - offset_distance)
        self.last_dist_between_centers = d

    def checkCollision(self):
        # here we check for collision between the car and the pedestrian
        d = self.getCurrentDistance()
        # self.distances_ego_pedestrian.append(d)
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



    # procedure that processes and stores the data
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
            stop_distance = self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]
            estimated_stop_distance = self.collision_speed * self.collision_speed / 2 / MAX_DECCELERATION # if the car has continue braking it would have stopped at this distance
            self.writeData(collision, stop_distance, estimated_stop_distance)
        elif experiment_outcome == ExperimentOutcomes.CAR_STOPPED:
            collision = 'No'
            stop_distance = self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-1]
            self.writeData(collision, stop_distance, stop_distance)
        if self.shouldRecordRosbag(): # in any cases if a rosbag was recorded it must me stopped
            subprocess.Popen("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')
        



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
        file.write("Number of new pedestrian tracking, "+str(self.number_new_tracking))
        file.write(', ')
        file.write("Distance ego to pedestrian at first detection, "+str(self.distance_first_detection))
        file.write(', ')
        file.write("Distance pedestrian to lane center at first detection, "+str(self.distance_pedestiran_lane_center_first_detection))
        file.write(', ')
        file.write("Dist pedestrian from lane center st end of experiment, "+str(self.distance_pedestiran_lane_center))
        file.write(', ')
        file.write("Nb of valid point cloud points at first iteration, "+str(self.first_nb_points))
        file.write(', ')
        file.write("Average nb of valid point cloud points, "+str(self.total_nb_points/float(self.nb_points_callbacks)))
        file.write(', ')
        file.write("Center passed, "+str(self.center_passed))
        file.write(', ')
        file.write("Exception in frame transformation, "+str(self.exception_frame_transform))
        file.write(', ')
        file.write("Computer name, "+socket.gethostname())
        file.write(', ')
        file.write("Start time, "+str(self.start_time))
        file.write(', ')
        file.write("End time, "+str(self.getCurrentTimeSring()))
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
