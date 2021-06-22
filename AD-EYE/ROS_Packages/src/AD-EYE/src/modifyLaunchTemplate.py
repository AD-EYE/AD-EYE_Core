#!/usr/bin/env python
#make changes in launch file according to name of the node (/adeye/area/node/variable) before running this node
#import roslib
import rospy
import rospkg
import re #support for 'REgular expression'
import sys #SYStem- specific parameters and functions
import os #Operating System
from std_msgs.msg import String
rospack = rospkg.RosPack()

# Basic folder locations
ADEYE_PACKAGE_LOCATION = rospack.get_path('adeye')+"/"
TEMPLATE_LAUNCH_FILES_LOCATION = "template_launch_files/"
MODIFIED_LAUNCH_FILES_LOCATION = "modified_launch_files/"

# Full path to folder
TEMPLATE_LAUNCH_FILES_FULL_PATH = ("%s%s" % (ADEYE_PACKAGE_LOCATION, TEMPLATE_LAUNCH_FILES_LOCATION))
MODIFIED_LAUNCH_FILES_FULL_PATH = ("%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION))

#Parent name of ros parameters and map.launch file
PARENT_NAME = "/adeye"
POINTCLOUD_DIRECTORY1 = "/home/adeye/AD-EYE_Core/AD-EYE/Experiments/"
POINTCLOUD_DIRECTORY2 = "/Pointcloud_Files/"
AREA_MAP = "config"
NODE_MAP = "manager"
VARIABLE_MAP = "WorldName"
SPECIAL_PARAMETER_MAP = str(PARENT_NAME + "/map/points_map_loader/args")


##Fills in the launch files templates from TEMPLATE_LAUNCH_FILES_FULL_PATH replacing the placeholder by the values on the ROS parameter server. 
##The modified tamplates are saved in MODIFIED_LAUNCH_FILES_FULL_PATH
def listener():

    if not os.path.exists(MODIFIED_LAUNCH_FILES_FULL_PATH):
        os.makedirs(MODIFIED_LAUNCH_FILES_FULL_PATH)

    for filename in os.listdir(MODIFIED_LAUNCH_FILES_FULL_PATH):
        os.remove(MODIFIED_LAUNCH_FILES_FULL_PATH + filename)

    for filename in os.listdir(TEMPLATE_LAUNCH_FILES_FULL_PATH): #all the files in launch file template directory
        if filename.endswith(".launch"):
            file = open(TEMPLATE_LAUNCH_FILES_FULL_PATH + filename, 'r') #opening a file to read (here, opens launch file template)('r' represents read only))
            template = file.read() #reads the file

            areas = rospy.get_param(PARENT_NAME) #get all the child namespaces (area) under parent "/adeye"
            for area in areas: #for every area in /adeye
                nodes = rospy.get_param(PARENT_NAME + "/" + area) #get all the child namespaces (node) under parent "/adeye/area"
                for node in nodes: #for every node in "/adeye/area"
                    variables = rospy.get_param(PARENT_NAME + "/" + area + "/" + node) #get all the child namespaces (variable) under parent "/adeye/area/node"
                    for variable in variables: #for every variable in "/adeye/area/node"
                        values = rospy.get_param(PARENT_NAME + "/" + area + "/" + node + "/" + variable) #getting only the value corresponding to each variable i.e. "/adeye/area/node/variable"
                        name = str(PARENT_NAME + "/" + area + "/" + node + "/" + variable) #converting variable "name" to string
                        template = template.replace(name, values)
            file.close() #close the file

            with open(MODIFIED_LAUNCH_FILES_FULL_PATH + filename, 'w+') as file: #opening new file in directory2('w' represents read&write and '+' implies it will create the file if non-existent)
                file.write(template)

    return()


if __name__ == '__main__':
     rospy.init_node('listener', anonymous = True) #initializing listener node
     listener()
