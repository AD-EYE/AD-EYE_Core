#Example command line input: python3 tests_for_vector_mapper.py world_name:=W01_Base_Map
import roslaunch
import rospy
import sys
import os
import math
import time
import pandas as pd 
import numpy as np
from roslaunch.config import load_config_default
from numpy.random import randint
from numpy.random import seed
from pyquaternion import Quaternion
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import PoseWithCovarianceStamped
from autoware_msgs.msg import LaneArray
from visualization_msgs.msg import Marker
from visualization_msgs.msg import MarkerArray
import random

##A class that receive data from the subscriber
class Receiver:
        ##The constructor
        #@param self The object pointer
        #@param received_path Boolean that changes to True when the global plan is found
        def __init__(self, received_path = False):
                self.received_path = received_path
        
        ##Global plan callback : called when the global plan is found.
        #@param self The object pointer
        #@param data that contain data info of LaneArray
        def callback(self, data):
                if data.lanes[0].waypoints[0].lane_id != '':
                        rospy.loginfo("Path found!")
                        self.received_path = True
                else:
                        rospy.loginfo("No path found!")


##A function for reading launch_file and making a dictionary of arg 
#Returning it as keys and values 
#@param roslaunch_file The list containing the str of the file path
def getArgs(roslaunch_file):
        loader = roslaunch.xmlloader.XmlLoader(resolve_anon=False)
        config = load_config_default(roslaunch_file, None, loader=loader, verbose=False, assign_machines=False)
        return loader.root_context.resolve_dict['arg']

##A function that calls for random postion
#@param Integer file_rows length.
#return random start, end row value
def randomPosition(csv_path,csv_file_name):
        #seed(1)
        list_of_points = pd.read_csv(csv_path + csv_file_name, delimiter=',', header=None, skip_blank_lines=True,float_precision=None)
        file_rows = len(list_of_points)-2 #total file rows is len(list_of_points)-1. 
                                          #But subtract a extra 1 to make sure that we don't exceed the file rows for the computation of orientation.
        random_start_row = random.randint(0, file_rows) #random values from 0 to file_rows.
        random_end_row = random.randint(0, file_rows)
        return random_start_row, random_end_row


##A function for reading point.csv file and returning its start and end point.
#@param csv_path The str of csv_path
#@param csv_file_name The str of csv name
def readCsvFile(csv_path, csv_file_name, position_rows):

        list_of_points = pd.read_csv(csv_path + csv_file_name, delimiter=',', header=None, skip_blank_lines=True,float_precision=None)
        
        start_point = (list_of_points.loc[ [position_rows[0]],[4,5] ]) #[3]=row, [4,5]=coloumn represent Global Y, X
        end_point = (list_of_points.loc[ [position_rows[1]],[4,5] ])

        start_point_array = [ start_point.loc[position_rows[0] , 4], start_point.loc[position_rows[0] , 5] ]
        end_point_array = [ end_point.loc[position_rows[1] , 4], end_point.loc[position_rows[1] , 5] ]
        #print(start_point)
        #print(end_point)
        return start_point_array, end_point_array

##A function for checking the user input is correct.
#By cheking world_name, if name exist, or if any input is given.
#@param csv_path The str of csv_path
#@param csv_file_name The str of csv name
def checkInputArgs(csv_path, csv_file_name):
        example_input = "Example of input: python3 tests_for_vector_mapper.py world_name:=W01_Base_Map"

        try:
            
            sys.argv[1] #Check if we have one input. If not, goes to "except IndexError as error"
            myargv = rospy.myargv(argv=sys.argv)
            path_name = csv_path + csv_file_name
            if not os.path.isfile(path_name):
                print("Error: Not a valid world name.")
                print(example_input)
                sys.exit(1)
                raise rospy.exceptions.ROSInitException('exit')
            
            #Check proper length. this python file path and ignore name of the world
            if len(myargv) != 1:
                print("Error: Too many input.")
                print(example_input)
            
        
        except IndexError:
            print("Please specify a world name. Right now world_name:=W01_Base_Map is used.")
            print(example_input)


##A function that calculates the orientaion of initial and goal position through yaw angle formula
#@param start_point_array List that contains x, y coordinate. 
#@param end_point_array List that contains x, y coordinate. 
#return yaw angle.
def calcOrientation(start_point_array, end_point_array):
        initial_x = start_point_array[1]
        initial_y = start_point_array[0]
        end_x = end_point_array[1]
        end_y = end_point_array[0]
        angle = math.atan2(end_y-initial_y, end_x-initial_x) 
        if angle >= 0:
                while angle > 2*math.pi:
                        angle -= 2 * math.pi
                return angle
        else:
                return (angle + 2 * math.pi)

##A function that caluclates the quaternion given a consecutive start and goal position.
#@param start_point_array List that contains x, y coordinate. 
#@param end_point_array List that contains x, y coordinate. 
#return quaternion coordinates for start and goal position.
def getQuaternion(start_point_array, end_point_array, positions_array2):
        start_point_array2 = positions_array2[0]
        end_point_array2 = positions_array2[1]
        yaw_angle_init = calcOrientation(start_point_array, start_point_array2)
        yaw_angle_goal = calcOrientation(end_point_array, end_point_array2)
        #print("yaw angle init: " + str(math.degrees(yaw_angle_init)))
        #print("yaw angle goal: " + str(math.degrees(yaw_angle_goal)))
        quaternion_init = Quaternion(axis=[0, 0, 1], angle = yaw_angle_init) 
        quaternion_goal = Quaternion(axis=[0, 0, 1], angle = yaw_angle_goal)
        return quaternion_init, quaternion_goal

##A function that sets the start position for publishing 
#@param start_point_array List that contains x, y coordinate. 
#@param quaternion_init List that contains w, x, y, z of quaternion coordinate for start position.
#return position information for publishing.
def startPosition(start_point_array, quaternion_init):
        initpose_msg = PoseWithCovarianceStamped()
        initpose_msg.header.stamp = rospy.get_rostime()
        initpose_msg.header.frame_id = "/map" #str(sys.argv[1]) str(sys.argv[1])
        initpose_msg.pose.pose.position.x = start_point_array[1]
        initpose_msg.pose.pose.position.y = start_point_array[0]
        initpose_msg.pose.pose.orientation.w = quaternion_init[0]
        initpose_msg.pose.pose.orientation.x = quaternion_init[1]
        initpose_msg.pose.pose.orientation.y = quaternion_init[2]
        initpose_msg.pose.pose.orientation.z = quaternion_init[3]
        return initpose_msg

##A function that sets the goal position for publishing 
#@param end_point_array List that contains x, y coordinate.
#@param quaternion_goal List that contains w, x, y, z of quaternion coordinate for goal position.
#return position information for publishing.
def goalPosition(end_point_array, quaternion_goal):
        goal_msg = PoseStamped()
        goal_msg.header.stamp = rospy.get_rostime()
        goal_msg.header.frame_id = "/map" #str(sys.argv[1])
        goal_msg.pose.position.x = end_point_array[1]
        goal_msg.pose.position.y = end_point_array[0]
        goal_msg.pose.orientation.w = quaternion_goal[0]
        goal_msg.pose.orientation.x = quaternion_goal[1]
        goal_msg.pose.orientation.y = quaternion_goal[2]
        goal_msg.pose.orientation.z = quaternion_goal[3]
        return goal_msg

##A function that marks the published start and goal position on Rviz
#@param start_point_array List that contains x, y coordinate. 
#@param quaternion_init List that contains w, x, y, z of quaternion coordinate for start position.
#@param end_point_array List that contains x, y coordinate.
#@param quaternion_goal List that contains w, x, y, z of quaternion coordinate for goal position.
#return marker information for publishing.
def marker(start_point_array, end_point_array, quaternion_init, quaternion_goal):
        marker_array = MarkerArray()
        marker_init = Marker()
        marker_init.header.frame_id = "/map"
        marker_init.header.stamp = rospy.Time.now()
        # set shape, Arrow: 0; Cube: 1 ; Sphere: 2 ; Cylinder: 3
        marker_init.type = 0
        marker_init.id = 0
        marker_init.action = marker_init.ADD
        # Set the scale of the marker_init
        marker_init.scale.x = 0.5 
        marker_init.scale.y = 0.5
        marker_init.scale.z = 0.5
        # Set the color
        marker_init.color.r = 1.0
        marker_init.color.g = 0.0
        marker_init.color.b = 0.0
        marker_init.color.a = 1.0
        marker_init.pose.position.x = start_point_array[1]
        marker_init.pose.position.y = start_point_array[0]
        marker_init.pose.orientation.x = quaternion_init[1]
        marker_init.pose.orientation.y = quaternion_init[2]
        marker_init.pose.orientation.z = quaternion_init[3]
        marker_init.pose.orientation.w = quaternion_init[0]

        marker_goal = Marker()
        marker_goal.header.frame_id = "/map"
        marker_goal.header.stamp = rospy.Time.now()
        # set shape, Arrow: 0; Cube: 1 ; Sphere: 2 ; Cylinder: 3
        marker_goal.type = 0
        marker_goal.id = 1
        marker_goal.action = marker_goal.ADD
        # Set the scale of the marker_init
        marker_goal.scale.x = 0.5
        marker_goal.scale.y = 0.5
        marker_goal.scale.z = 0.5
        # Set the color
        marker_goal.color.r = 1.0
        marker_goal.color.g = 0.0
        marker_goal.color.b = 0.0
        marker_goal.color.a = 1.0
        marker_goal.pose.position.x = end_point_array[1]
        marker_goal.pose.position.y = end_point_array[0]
        marker_goal.pose.orientation.x = quaternion_goal[1]
        marker_goal.pose.orientation.y = quaternion_goal[2]
        marker_goal.pose.orientation.z = quaternion_goal[3]
        marker_goal.pose.orientation.w = quaternion_goal[0]

        marker_array.markers.append(marker_init)
        marker_array.markers.append(marker_goal)
        return marker_array


##Main function that initizalize node and corresponding launch file.
#Publishes some msg to the global planner.
def main():
        rospy.init_node('vector_map_tester', anonymous=True) #Initializing ROS Node given nodename. 
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        roslaunch_file = "/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/launch/my_map.launch"
        roslaunch_file2 ="/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/launch/my_mission_planning.launch"
        launch = roslaunch.parent.ROSLaunchParent(uuid, [roslaunch_file, roslaunch_file2])

        launch.start()

        args_dict = getArgs([roslaunch_file])
        csv_path = args_dict.get("VectorMap_Files_Folder") #Get the key value which is a path.
        csv_file_name = "point.csv"  

        checkInputArgs(csv_path, csv_file_name)
        #Do while loop. Checks that the distance between start position and goal position is larger than 2.5 meters.
        position_rows = randomPosition(csv_path, csv_file_name)
        positions_array = readCsvFile(csv_path, csv_file_name, position_rows)
        start_point_array = positions_array[0]
        end_point_array = positions_array[1]
        dist_goal_init = math.hypot(end_point_array[0] - start_point_array[0], end_point_array[1] - start_point_array[1])
        #print("Distance = " + str(dist_goal_init))
        while dist_goal_init <= 2.5:
                position_rows = randomPosition(csv_path, csv_file_name)
                positions_array = readCsvFile(csv_path, csv_file_name, position_rows)
                start_point_array = positions_array[0]
                end_point_array = positions_array[1]
                dist_goal_init = math.hypot(end_point_array[0] - start_point_array[0], end_point_array[1] - start_point_array[1])                

        position_rows2 = [position_rows[0] + 1, position_rows[1] + 1]
        positions_array2 = readCsvFile(csv_path, csv_file_name, position_rows2)

        quaternion_init, quaternion_goal = getQuaternion(start_point_array, end_point_array, positions_array2)


        receiver = Receiver()

        pub_goal = rospy.Publisher("/adeye/goals", PoseStamped, queue_size = 1)
        pub_init_pose = rospy.Publisher("/initialpose", PoseWithCovarianceStamped, queue_size = 1)
        pub_marker_array = rospy.Publisher("/visualization_marker_array", MarkerArray, queue_size = 1)
        sub_global_plan = rospy.Subscriber("/lane_waypoints_array", LaneArray, receiver.callback, queue_size = 1)

        initpose_msg = startPosition(start_point_array, quaternion_init)
        goal_msg = goalPosition(end_point_array, quaternion_goal)
        marker_array = marker(start_point_array, end_point_array, quaternion_init, quaternion_goal)

        rate = rospy.Rate(1)
        while not rospy.is_shutdown():
                pub_init_pose.publish(initpose_msg)
                pub_marker_array.publish(marker_array)
                pub_goal.publish(goal_msg)
                rate.sleep()
                if receiver.received_path == True:
                        break
        rospy.sleep(1)
        launch.shutdown()  

if __name__ == "__main__":
        main()

          


