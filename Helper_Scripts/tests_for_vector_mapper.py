import roslaunch
import rospy
import pandas as pd 
import sys
from roslaunch.core import RLException



#Command line input: python3 tests_for_vector_mapper.py world_name:=W01_Base_Map point.csv


#Input: launch file path
#Make a dictionary from arg"
#Return: Dictionary of key and values 
def get_args(roslaunch_file):
        loader = roslaunch.xmlloader.XmlLoader(resolve_anon=False)
        config = load_config_default(roslaunch_file, None, loader=loader, verbose=False, assign_machines=False)
        return loader.root_context.resolve_dict['arg']

def read_csv_file(csv_path, csv_file_name):
        list_of_points = pd.read_csv(csv_path + csv_file_name, delimiter=',', header=None, skip_blank_lines=True,float_precision=None)

        """     Point.csv
                self.B = 0.0        # Latitude
                self.L = 0.0        # Longitude
                self.H = z       # Altitude
                self.Ly = x         # Global Y, values are swapped for Autoware, does not work swapping the lines
                self.Bx = y         # Global X
                self.ReF = 7
                self.MCODE1 = 0
                self.MCODE2 = 0
                self.MCODE3 = 0

        Ignores blank line. start with index 0, so 4th line is read when writing 3.
        (list_of_points.loc[ [3],[4,5] ] ) gives in the following format:

                4           5
        3  84.041486  138.819932 
        """
         

        start_point = (list_of_points.loc[ [3],[4,5] ])
        end_point = (list_of_points.loc[ [22],[4,5] ])

        print(start_point)
        print(end_point) 

def check_input_args():
        try:
        
            args = rospy.myargv(argv=sys.argv) #pass arguments to ros
            return args
        #if len(args) != 2: #Check proper length. this python file path + name of the file to open
        #except IndexError as error:
        except RLException as e:

        #except rospy.ROSInterruptException:
            error_message = """ ERROR: No file name provided. 
            Example of input: python3 test_launch_file.py world_name:=W01_Base_Map point.csv"""
            print(error_message)
        #    sys.exit(1)
        
            print(str(e), file=sys.stderr)
            sys.exit(1)
if __name__ == "__main__":
        
        rospy.init_node('vector_map_loader', anonymous=True) #Initializing ROS Node given nodename. 
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        roslaunch_file = ["/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/launch/my_map.launch"]
        launch = roslaunch.parent.ROSLaunchParent(uuid, roslaunch_file)
        
        launch.start()
        args = check_input_args()
        
        
        args_dict = get_args(roslaunch_file)
        csv_path = args_dict.get("VectorMap_Files_Folder")
   
        #/home/adeye/AD-EYE_Core/AD-EYE/Experiments/W01_Base_Map/Vector_Map_Files/point.csv
        csv_file_name = args[1]  
        read_csv_file(csv_path, csv_file_name)
                 
        
        rospy.sleep(3)
        # 3 seconds later
        launch.shutdown()   


