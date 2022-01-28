#!/usr/bin/env python

import os
import rospy
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from geometry_msgs.msg import Point
from autoware_msgs.msg import DetectedObjectArray
from std_msgs.msg import Bool
from std_msgs.msg import UInt64
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
file = open('/home/adeye/Experiment_Results/Experiment_moving_wall.csv','a')



class ExperimentARecorder:
    first_nb_points_recorded = False
    first_nb_points = 0
    total_nb_points = 0
    nb_points_callbacks = 0
    non_hit_points = []
    invalidated_points = []


    def __init__(self):
        self.start_time = self.getCurrentTimeSring()
        # rospy.Subscriber("/simulink/pedestrian_pose", Point, self.pedestrianPositionCallback)
        rospy.Subscriber("/points_raw_float32", Float32MultiArray, self.pointCloudCallback)
        rospy.Subscriber("/non_hit_points", UInt64, self.nonHitPointsCallback)
        rospy.Subscriber("/points_invalidated_rain_model", UInt64, self.invalidatedPointsCallback)
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

        if(self.shouldStopExperiment()):
            self.writeParameters()
            self.writeData()
            self.stop_pub.publish(True) # stop_publisher




    def nonHitPointsCallback(self, data):
        self.non_hit_points.append(int(data.data))
    def invalidatedPointsCallback(self, data):
        self.invalidated_points.append(int(data.data))
        print(len(self.invalidated_points))
 
    def shouldStopExperiment(self):
        print("checking time: " + str(rospy.Time.now().to_sec()))
        return (rospy.Time.now().to_sec() >= 10)


    def writeData(self):
        file.write("Nb of valid point cloud points at first iteration, "+str(self.first_nb_points))
        file.write(', ')
        file.write("Average nb of valid point cloud points, "+str(self.total_nb_points/float(self.nb_points_callbacks)))
        file.write(', ')
        # file.write("total nb ofcloud points, "+str(self.total_nb_points))
        # file.write(', ')

        nb_divisions = 10
        slice_size = 200 / nb_divisions
        for i in range(nb_divisions):
            start_index = i*slice_size
            end_index = (i+1)*slice_size
            file.write("slice " + str(i) + ": average nb of non hit points, " + str(sum(self.non_hit_points[start_index:end_index]) / float(slice_size)))
            file.write(', ')
        for i in range(nb_divisions):
            start_index = i*slice_size
            end_index = (i+1)*slice_size
            file.write("slice " + str(i) + ": average nb of hit points ivalidated by rain, " + str(sum(self.invalidated_points[start_index:end_index]) / float(slice_size)))
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
        rain_intensity = rospy.get_param("/simulink/rain_intensity")
        file.write("Set rain intensity, "+str(rain_intensity)+" , ")
        reflectivity = rospy.get_param("/simulink/reflectivity")
        file.write("Set reflectivity, "+str(reflectivity)+" , ")




#listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA_recorder')
    exp_A_recorder = ExperimentARecorder()
    rospy.spin()
