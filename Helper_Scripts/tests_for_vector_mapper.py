import roslaunch
import rospy
import pandas as pd 
import sys
import os
from roslaunch.config import load_config_default



#Command line input: python3 tests_for_vector_mapper.py world_name:=W01_Base_Map

##A function for reading launch_file and making a dictionary of arg". 
#Returning it as keys and values 
#@param roslaunch_file The list containing the str of the file path
def getArgs(roslaunch_file):
        loader = roslaunch.xmlloader.XmlLoader(resolve_anon=False)
        config = load_config_default(roslaunch_file, None, loader=loader, verbose=False, assign_machines=False)
        return loader.root_context.resolve_dict['arg']

##A function for reading point.csv file and returning its start and end point.
#@param csv_path The str of csv_path
#@param csv_file_name The str of csv name
def readCsvFile(csv_path, csv_file_name):

        list_of_points = pd.read_csv(csv_path + csv_file_name, delimiter=',', header=None, skip_blank_lines=True,float_precision=None)

        start_point = (list_of_points.loc[ [3],[4,5] ]) #[3]=row, [4,5]=coloumn represent Global Y, X
        end_point = (list_of_points.loc[ [22],[4,5] ])

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
        


if __name__ == "__main__":
        
        rospy.init_node('vector_map_loader', anonymous=True) #Initializing ROS Node given nodename. 
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        roslaunch_file = ["/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/launch/my_map.launch"]
        launch = roslaunch.parent.ROSLaunchParent(uuid, roslaunch_file)
        
        launch.start()

        args_dict = getArgs(roslaunch_file)
        csv_path = args_dict.get("VectorMap_Files_Folder")
        csv_file_name = "point.csv"  

        checkInputArgs(csv_path, csv_file_name)
        readCsvFile(csv_path, csv_file_name)
        
        rospy.sleep(3)
        # 3 seconds later
        launch.shutdown()   
