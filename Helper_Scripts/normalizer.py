import roslaunch
import rospy
import pandas as pd 
import sys
import os
from roslaunch.config import load_config_default
from numpy.random import randint
from numpy.random import seed
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import PoseWithCovarianceStamped
from autoware_msgs.msg import LaneArray
from tf.transformations import quaternion_from_euler
import numpy as np

#Command line input: python3 tests_for_vector_mapper.py world_name:=W01_Base_Map

##A function for reading launch_file and making a dictionary of arg". 
#Returning it as keys and values 
#@param roslaunch_file The list containing the str of the file path
def getArgs(roslaunch_file):
        loader = roslaunch.xmlloader.XmlLoader(resolve_anon=False)
        config = load_config_default(roslaunch_file, None, loader=loader, verbose=False, assign_machines=False)
        return loader.root_context.resolve_dict['arg']

##A function that calls for random postion
#@param Integer file_rows length.
#return random start, end row value
def randomPosition(file_rows):
        seed(1)

        random_start_row = randint(0, file_rows) #random values from 0 to file_rows.
        random_end_row = randint(0, file_rows)
        return random_start_row, random_end_row

def normalizer(coord_array):
        norm = np.linalg.norm(coord_array)
        normal_array = coord_array/norm
        return normal_array


##A function for reading point.csv file and returning its start and end point.
#@param csv_path The str of csv_path
#@param csv_file_name The str of csv name
def readCsvFile(csv_path, csv_file_name):

        list_of_points = pd.read_csv(csv_path + csv_file_name, delimiter=',', header=None, skip_blank_lines=True,float_precision=None)
        
        file_rows = len(list_of_points)-1
        
        #position_rows = randomPosition(file_rows)
        position_rows = [3, 22]
        #Check if their distance if too close. If it is, call for new random position again.
        #while abs(position_rows[0] - position_rows[1]) <= 10:
                #position_rows = randomPosition(file_rows)
        
        #start_point = (list_of_points.loc[ [position_rows[0]],[4,5] ]) #[3]=row, [4,5]=coloumn represent Global Y, X
        #end_point = (list_of_points.loc[ [position_rows[1]],[4,5] ])
        
        start_point = (list_of_points.loc[ [position_rows[0]],[4,5] ])
        end_point = (list_of_points.loc[ [position_rows[1]],[4,5] ])

        """

        norm_start_point = normalizer( [ start_point.loc[position_rows[0] , 4], start_point.loc[position_rows[0] , 5] ])
        start_point.loc[ [position_rows[0]],[4,5] ] = norm_start_point[0], norm_start_point[1]

        norm_end_point = normalizer( [ end_point.loc[position_rows[1] , 4], end_point.loc[position_rows[1] , 5] ])
        end_point.loc[ [position_rows[1]],[4,5] ] = norm_end_point[0], norm_end_point[1]
        """
        print(start_point)
        print(end_point) 




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
        
def callback(data):
        data.id = "W01_Base_Map"
        rospy.loginfo("I heard " + data.id)


##Main function that initizalize node and corresponding launch file.
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
        readCsvFile(csv_path, csv_file_name)
        
        
        pub_goal = rospy.Publisher("/move_base_simple/goal", PoseStamped, queue_size = 1)
        pub_init_pose = rospy.Publisher("/initialpose", PoseWithCovarianceStamped, queue_size = 1)
        sub_global_plan = rospy.Subscriber("/lane_waypoints_array", LaneArray, callback, queue_size=1)

        """
        self.B = 0.0        # Latitude
        self.L = 0.0        # Longitude
        self.H = z          # Altitude
        self.Ly = x         # Global Y, values are swapped for Autoware, does not work swapping the lines
        self.Bx = y         # Global X
        self.ReF = 7
        self.MCODE1 = 0
        self.MCODE2 = 0
        self.MCODE3 = 0

        """
        q_start = quaternion_from_euler( 138.819932, 84.041486, 0.0)
        q_goal = quaternion_from_euler(151.706019, 96.517499, 0.0)
        print(q_start)  
        goal_msg = PoseStamped()
        goal_msg.header.stamp = rospy.get_rostime()
        goal_msg.header.frame_id = "W01_Base_Map"
        goal_msg.pose.position.x = 138.819932
        goal_msg.pose.position.y = 84.041486
        goal_msg.pose.position.z = 0.0

        goal_msg.pose.orientation.w = q_start[3]
        goal_msg.pose.orientation.x = q_start[0]      
        goal_msg.pose.orientation.y = q_start[1]
        goal_msg.pose.orientation.z = q_start[2]

        initpose_msg = PoseWithCovarianceStamped()
        initpose_msg.header.stamp = rospy.get_rostime()
        initpose_msg.header.frame_id = "W01_Base_Map"
        initpose_msg.pose.pose.position.x = 151.706019 
        initpose_msg.pose.pose.position.y = 96.517499
        initpose_msg.pose.pose.position.z = 0.0
        
        initpose_msg.pose.pose.orientation.w = q_goal[3]
        initpose_msg.pose.pose.orientation.x = q_goal[0]
        initpose_msg.pose.pose.orientation.y = q_goal[1]
        initpose_msg.pose.pose.orientation.z = q_goal[2]

        print(LaneArray())
        print(goal_msg)
        #print(goal_msg)
        #print(initpose_msg)

        

        rate = rospy.Rate(3)
        while not rospy.is_shutdown():
                pub_goal.publish(goal_msg)
                pub_init_pose.publish(initpose_msg)
                rate.sleep()

        try:
            launch.spin()
        finally:
            # After Ctrl+C, stop all nodes from running
            launch.shutdown()

if __name__ == "__main__":
        main()

          


