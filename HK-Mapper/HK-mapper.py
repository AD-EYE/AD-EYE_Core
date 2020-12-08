#!/usr/bin/python

"""
    Filename: HK-mapper.py
    Authors: J Roing, A De Val, F Larsson, H Lind, A Phan, V Hanefors, M Svjatoha, J Jungaker, C Jensen
    Date last modified: 3 Dec 2020
    Version: 1.0
    License: GPLv3
    Copyright: (C)Copyright 2020 Mechatronics HK AD-EYE Team
    Python version: Python 2.7.12


    Description: Starts the mapping process with the sensor rig consisting of Velodyne VLP-16 and Xsens Mit-700.
    Other: VLP16 driver needs to be installed and the Velodyne VLP-16 needs to be connected. Configure the sensors before mapping.
    
    Usage: python HK-mapper.py -r True <--rosbag-dir> <"path to rosbag output"> <-rviz> <True> <-v> <True> <-x> <True> <-vc> <True>

    NOTE: Check that the correct USB port where IMU is connected is chmod.

    See the full specifications with
    python HK-mapper.py --help 
"""
# ========================================================================
# Imports
# ========================================================================
from __future__ import print_function 

import subprocess
import roslaunch
import rospy
import os
import argparse
import distutils.spawn
import shlex
import sys
import signal
import psutil
import time
import webbrowser
from datetime import datetime

# ========================================================================
# Global Variables
# ========================================================================
root_dir = os.path.dirname(os.path.abspath(__file__))                               #Path to root directory

velodyne_launch_path = os.path.join(root_dir, "src", "velodyne", 
                "velodyne_pointcloud", "launch", "VLP16_points.launch")             #Path to velodyne launch file


xsens_launch_path = os.path.join(root_dir, "src", "ethzasl_xsens_driver-master", 
                "launch", "xsens_driver.launch")                                    #Path to xsens drive launch file

# ========================================================================
# Helper Functions
# ========================================================================

def create_parser(): 
    """Create a parser object"""

    parser = argparse.ArgumentParser(description='Starts the mapping process with the sensor rig consisting of Velodyne VLP-16 and Xsens Mit-700.')
    parser.add_argument('-r', '--rosbag', type=bool, default=False, help="Run with rosbag <True|False>")
    parser.add_argument("--rosbag-dir", type=str, default=root_dir, help="Path to rosbag output")
    parser.add_argument("-rviz","--rviz", type=bool, default=False, help="Runs rviz <True|False>")
    parser.add_argument("-v","--velodyne", type=bool, default=False, help="Launch Velodyne <True|False>")
    parser.add_argument("-x","--xsens", type=bool, default=False, help="Launch Xsens <True|False>")
    parser.add_argument("-vc","--velodyne-config", type=bool, default=False, help="Launch Velodyne GUI <True|False>")
    parser.add_argument("-xc","--xsens-config", type=bool, default=False, help="Launch documentation for xsens_driver <True|False>")
    parser.add_argument("-p","--rosbag-play", type=bool, default=False, help="Play recorded rosbag <True|False>")
    parser.add_argument("--rosbag-file", type=str, help="Path to recorded rosbag")
    my_args = parser.parse_args()

    return my_args

def generate_rosbag_path(rosbag_dir): 
    """Geneate a path for the rosbag"""

    current_time = datetime.now()                                               #Get current time
    time_stamp=current_time.strftime("%d-%b-%Y_%H-%M-%S.%f")                    #Extract time into string
    rosbag_path = os.path.join(rosbag_dir, time_stamp)                          #Generate path for rosbag 
    
    return rosbag_path

def chmod_usb(): 
    """Give read and write permission on ttyUSB0 for Xsense driver"""

    try: 

        subprocess.call(["sudo", "chmod", "666", "/dev/ttyUSB0"])

        print("**************************************\n")
        print("Succesfully chmod 666 ttyUSB0 for Xsens driver")
        print("\n**************************************")
        

    except: 
        print("**************************************\n")
        print("Could not connect to Xsens to USB port")
        print("\n**************************************")


def force_kill(): 
    """Killing any active rosmaster before start"""  

    cmd = ["killall", "-9", "rosmaster"]
    subprocess.Popen(cmd)

def play_rosbag(path):
    """Play rosbag"""

    cmd = ["rosbag", "play", str(path)]
        
    subprocess.Popen(cmd)

    cmd = ["rosrun", "rviz", "rviz", "-f", "velodyne"]

    subprocess.Popen(cmd)

# ========================================================================
# Classes
# ========================================================================
class Roslaunch(): 

    def __init__(self, args): 
        """Initializer"""

        self.uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(self.uuid)
        self.launch = roslaunch.scriptapi.ROSLaunch() 
        self.launch_files = []
        self.args = args

    def set_launch_files(self, launch_files):
        """Set the launch files"""

        self.launch_files = launch_files
        self.launch.parent = roslaunch.parent.ROSLaunchParent(self.uuid, self.launch_files)

    def run_rviz(self): 
        """Set all nodes that should be launched"""

        rviz = roslaunch.core.Node("rviz", "rviz")
        self.launch.launch(rviz)

    def run_rosbag(self):
        """Record rosbag"""

        rosbag_path = generate_rosbag_path(self.args.rosbag_dir)

        cmd = ["rosbag", "record", "-a", "-O", str(rosbag_path), "--duration", "1800"]
        
        subprocess.Popen(cmd) 


    def start(self): 
        """Start the launch files"""

        self.launch.start()
        rospy.sleep(3)
        print("\n\n\n args.rviz = {0} \n\n\n".format(self.args.rviz))
        if self.args.rviz: 
            self.run_rviz()

        if self.args.rosbag: 
             self.run_rosbag()

        self.launch.spin()
    
    def stop(self): 
        self.launch.stop()

class Roscore(): 
    """roscore wrapped into a subprocess. 
    Singleton implementation prevents from creating more than one instance."""

    __initialized = False
    def __init__(self):
        if Roscore.__initialized:
            raise Exception("You can't create more than 1 instance of Roscore.")
        Roscore.__initialized = True
    def run(self):
        try:
            self.roscore_process = subprocess.Popen(['roscore'])
            #self.roscore_pid = self.roscore_process.pid  # pid of the roscore process (which has child processes)
        except OSError as e:
            sys.stderr.write('roscore could not be run')
            raise e
        
    def stop(self):
        subprocess.call(['killall', '-9', 'roscore'])

class Sensors():
    def __init__(self, args): 
        """Initializer"""
        self.launch_files = []
        self.args = args
    
    def velodyne_config(self):
        """Configure Velodyne"""
        webbrowser.open_new('http://192.168.1.201/')

    def xsens_config(self):
        """Configure Velodyne"""
        webbrowser.open_new('http://wiki.ros.org/xsens_driver')

    def choose_launch_files(self):
        """Choose sensors to launch"""
        if self.args.velodyne:
            self.launch_files.append(velodyne_launch_path)
            print("**************************************\n")
            print('Initiating Velodyne')
            print("\n**************************************")
        
        if self.args.xsens:
            self.launch_files.append(xsens_launch_path)
            print("**************************************\n")
            print('Initiating Xsens')
            print("\n**************************************")
    
        return self.launch_files

    def sensors_config(self):
        """Choose sensors to configurate launch"""
        if self.args.velodyne_config: 
            if self.args.velodyne:
                print("**************************************\n")
                print('Launching Velodyne GUI')
                print("\n**************************************")
                self.velodyne_config()

        if self.args.xsens_config:
            print("**************************************\n")
            print('Launch documentation for ROS Driver for XSens')
            print("\n**************************************")
            self.xsens_config() 

    def sensors_play(self):
        """Choose if the rosbag will be played"""
        if self.args.rosbag_play:
            print("**************************************\n")
            print('Play recorded rosbag')
            print("\n**************************************")
            play_rosbag(self.args.rosbag_file)

# ========================================================================
# Main function
# ========================================================================
if __name__ == "__main__":

    force_kill()                                        #Killing active rosmaster

    chmod_usb()                                         #Allow read and write permisson

    args = create_parser()                              #Create parser with user input
    sensors = Sensors(args)                             
    launch_files = sensors.choose_launch_files()        #Choose launch files
    sensors.sensors_config()                            #Configure sensors

    try: 
        roscore = Roscore()                             
        roscore.run()
        rospy.sleep(3)
        
        launcher = Roslaunch(args)

        launcher.set_launch_files(launch_files)         #Set launch_files
        launcher.start()                                #Start the recording 
        
    finally:
        launcher.stop()
        rospy.sleep(3)
        sensors.sensors_play()                          #Play the recording

        roscore.stop()




    







