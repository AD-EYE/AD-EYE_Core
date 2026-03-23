#!/usr/bin/env python

import math
import rospy
import subprocess
import argparse
import os
import sys
import glob
import roslaunch
import time

from datetime import datetime
from autoware_config_msgs.msg import ConfigNDTMapping
from autoware_config_msgs.msg import ConfigApproximateNDTMapping
from sensor_msgs.msg import Imu, PointCloud2
from geometry_msgs.msg import PoseStamped


class RoscoreWrapper():
    """Roscore wrapped into a subprocess, to help start and stop the rosmaster process.
    Singleton implementation prevents creating more than one instance."""

    __initialized = False

    def __init__(self):
        if RoscoreWrapper.__initialized:
            raise Exception("You can't create more than one instance of roscore.")
        RoscoreWrapper.__initialized = True

    def start(self):
        try:
            self.roscore_process = subprocess.Popen(['roscore'])
        except OSError as e:
            sys.stderr.write('roscore could not be started!')
            raise e

    def stop(self):
        subprocess.call(['killall', '-9', 'roscore'])


class ProcessManager():
    """Starts the different ROS nodes required for the mapping."""

    def __init__(self, filepath: str, output_path: str, start_rviz: bool):
        """Initializer"""
        self.input_filepath = filepath
        self.output_filename =  self.generate_PCD_path(filepath, output_path)
        print(self.output_filename)
        self.start_rviz = start_rviz

        self.uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(self.uuid)
        self.launch = roslaunch.scriptapi.ROSLaunch()
        self.launch_files = []
        self.FNULL = open(os.devnull, 'w')


    def generate_PCD_path(self, filepath: str, output_path: str):
        """Geneate a timestamp for the PCD."""
        output_filename = os.path.basename(os.path.abspath(filepath)).split(".bag")[0] + ".pcd"
        output_filename = os.path.join(output_path, output_filename)
        output_filename = "'{0}'".format(output_filename)
        return output_filename

    def transform_imu(self):
        print("Transforming imu")
        rospy.init_node('imu_transformer')
        #msg = rospy.wait_for_message("/os_cloud_node/imu", Imu) #This will create a new subscription to the topic, receive one message, then unsubscribe.

        rolls = []
        pitches = []
        yaws = []
        p_xs = []
        p_ys = []
        p_zs = []

        for i in range(10):
            msg = rospy.wait_for_message("/ndt_pose", PoseStamped)
            q_x = msg.pose.orientation.x
            q_y = msg.pose.orientation.y
            q_z = msg.pose.orientation.z
            q_w = msg.pose.orientation.w
            p_x = msg.pose.position.x
            p_y = msg.pose.position.y
            p_z = msg.pose.position.z


            roll = math.atan2(2*q_w*q_x + 2*q_y*q_z, 1 - 2*q_x**2 - 2*q_y**2)
            pitch = math.asin(2*q_w*q_y - 2*q_z*q_x)
            yaw = math.atan2(2*q_w*q_z + 2*q_x*q_y, 1 - 2*q_y**2 - 2*q_z**2)

            p_xs.append(p_x)
            p_ys.append(p_y)
            p_zs.append(p_z)
            rolls.append(roll)
            pitches.append(pitch)
            yaws.append(yaw)


        p_x = sum(p_xs) / float(len(p_xs))
        p_y = sum(p_ys) / float(len(p_ys))
        p_z = sum(p_zs) / float(len(p_zs))
        roll = sum(rolls) / float(len(rolls))
        pitch = sum(pitches) / float(len(pitches))
        yaw = sum(yaws) / float(len(yaws))


        print("Calc roll: ", roll)
        print("Calc pitch: ", pitch)
        print("Calc yaw: ", yaw)

        print("Starting position x: ", p_x)
        print("Starting position y: ", p_y)
        print("Starting position z: ", p_z)

        #set parameter to server
        rospy.set_param('tf_x', p_x)
        rospy.set_param('tf_y', p_y)
        rospy.set_param('tf_z', p_z)
        rospy.set_param('tf_roll', roll)
        rospy.set_param('tf_pitch', pitch)
        rospy.set_param('tf_yaw', yaw)
        cmd = ['roslaunch', 'runtime_manager', 'setup_tf.launch', 'x:='+str(p_x), 'y:='+str(p_y), 'z:='+str(p_z), str(yaw), str(pitch), str(roll), 'frame_id:=/base_link', 'child_frame_id:=/velodyne', 'period_in_ms:=10']
        self.tf_process = subprocess.Popen(cmd, stdout=self.FNULL, stderr=self.FNULL) #TODO: Output stderr


    def play_rosbag(self):
        """Play rosbag."""
        print("Playing rosbag...")
        cmd = ["rosrun", "topic_tools", "relay", "/os_cloud_node/points", "/points_raw"]
        self.relay_process = subprocess.Popen(cmd)
        rosbag_path = self.input_filepath
        rospy.set_param('use_sim_time', 'true')
        cmd = ["rosbag", "play", str(rosbag_path)]
        self.rosbag_process = subprocess.Popen(cmd, stdout=self.FNULL, stderr=self.FNULL)

    def start_ndt_matching(self):

        settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 1.0, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 1.0, min_scan_range: 1.5, max_scan_range: 75.0, min_add_scan_shift: 2.0}"

        cmd = ["rostopic", "pub", "/config/ndt_mapping", "autoware_config_msgs/ConfigNDTMapping", settings]
        self.topic_pub_process = subprocess.Popen(cmd)

        rospy.set_param("ndt_matching/method_type", "2")
        rospy.set_param("ndt_matching/use_gnss", "1")
        rospy.set_param("ndt_matching/use_odom", False)
        rospy.set_param("ndt_matching/use_imu", "1")
        rospy.set_param("ndt_matching/imu_upside_down", False)
        rospy.set_param("ndt_matching/imu_topic", "/imu/data")
        rospy.set_param("ndt_matching/queue_size", "1")
        rospy.set_param("ndt_matching/offset", "linear")
        rospy.set_param("ndt_matching/get_height", True)
        rospy.set_param("ndt_matching/use_local_transform", False)
        rospy.set_param("ndt_matching/sync", False)
        rospy.set_param("ndt_matching/use_scan_stamp", True)

        quer = roslaunch.core.Node('lidar_localizer', 'queue_counter')
        self.launch.launch(quer)
        print("starting ndt in a separate terminal")
        self.ndt_matching_process = subprocess.Popen(['xterm', '-e', 'rosrun lidar_localizer ndt_matching'])

    def start_ndt_mapping(self):
        print("Starting ndt mapping")

        print("If the rosbag is big, it is recomended to edit ndt_mapping code to disable the publishing of the map. This will allow to generate maps that are bigger than 1GB.")

        settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 1.0, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 1.0, min_scan_range: 1.5, max_scan_range: 75.0, min_add_scan_shift: 2.0}"

        cmd = ["rostopic", "pub", "/config/ndt_mapping", "autoware_config_msgs/ConfigNDTMapping", settings]
        self.topic_pub_process = subprocess.Popen(cmd)

        rospy.set_param("/ndt_mapping/imu_topic", "/imu/data")
        rospy.set_param("/ndt_mapping/imu_upside_down", True)
        rospy.set_param("/ndt_mapping/incremental_voxel_update", True)
        rospy.set_param("/ndt_mapping/method_type", False)
        rospy.set_param("/ndt_mapping/use_imu", True)
        rospy.set_param("/ndt_mapping/use_odom", False)

        quer = roslaunch.core.Node('lidar_localizer', 'queue_counter')
        self.launch.launch(quer)
        print("starting ndt in a separate terminal")
        self.ndt_mapping_process = subprocess.Popen(['xterm', '-e', 'rosrun lidar_localizer ndt_mapping'])


    def run_rviz(self):
        """Set all nodes that should be launched"""
        self.rviz_process = subprocess.Popen(["rosrun", "rviz", "rviz", "-d" , "/home/adeye/AD-EYE_Core/Helper_Scripts/Mapping/mapping_config.rviz"])


    def start(self):
        """Start the launch files"""

        output = "{{header: {{seq: 1, stamp: {{secs: 0, nsecs: 0}}, frame_id: ''}}, filename: {0}, filter_res: 0.0}}".format(self.output_filename)

        self.launch.start()

        self.play_rosbag()

        self.transform_imu()

        self.start_ndt_mapping()

        if self.start_rviz:
            self.run_rviz()

        # the mapping process is finished when no new message is published on the topic /ndt_map
        i = 0
        try:
            while True: # while we receive message mapping is not done
                self.launch.spin_once()
                rospy.wait_for_message("/current_pose", PoseStamped, timeout=5) # if this function times out, it throws an exception
                i = i+1
                if i%100 == 0:
                    print("Waiting for the mapping to be finished...", end="\r")
        except: # when no message has been published, the exception leads here
            print("                                         ", end="\r")
            print("Saving the map as a pcd file: " + output)
            topic_output_pub_process = subprocess.Popen(["rostopic", "pub", "-1" ,"/config/ndt_mapping_output", "autoware_config_msgs/ConfigNDTMappingOutput", output])
            time.sleep(30)
            topic_output_pub_process.terminate()
        finally:
            self.launch.stop()
            # deleting unnecessary files generated by ndt_mapping
            files_to_delete = glob.glob('ndt_mapping*.csv')
            for file in files_to_delete:
                try:
                    os.remove(file)
                except:
                    print("Error while deleting file : ", filePath)
            self.tf_process.terminate()
            self.relay_process.terminate()
            self.rosbag_process.terminate()
            self.ndt_mapping_process.terminate()
            self.topic_pub_process.terminate()
            if self.start_rviz:
                self.rviz_process.terminate()


def create_parser():
    """Create a parser object."""
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input", type=str, required=True, help="Path to input file(s)")
    parser.add_argument("-o", "--output", type=str, required=True, help="Path to PCD output dir")
    parser.add_argument("--rviz", action="store_true", help="Open Rviz flag")
    my_args = parser.parse_args()
    return my_args


def force_kill_ros():
    """"Force-kill all currently running ROS processes."""
    print('Attempting to kill all ROS processes...')
    subprocess.call(["rosnode", "kill", "-a"])
    time.sleep(1)
    subprocess.call(["killall", "-9", "rosmaster"])


def mapping_wrapper(input_path: str, output_path: str, start_rviz: bool = False):
    """Main functionality wrapper."""

    print("Converting rosbags to PCD + \n")
    print("Input path: " + input_path)
    print("Output path: " + output_path)
    print("Start Rviz: " + str(start_rviz) + "\n")

    if not os.path.exists(input_path):
        raise OSError("Input file/directory does not exist.")

    if input_path.endswith(".bag"):
            input_directory = os.path.split(input_path)[0]
            files = [os.path.split(input_path)[1]]
    else:
        input_directory = input_path
        files = []
        for filename in os.listdir(input_directory):
            if filename.endswith(".bag"):
                    files.append(filename)

    print("Directory: " + input_directory)
    print("Files to convert: ", end="")
    print(files, end="\n\n")

    force_kill_ros()
    roscore_wrapper = RoscoreWrapper()

    i = 0
    file_count = str(len(files))
    for filename in files:
        i += 1
        counter = str(i) + "/" + file_count
        print("Starting process rosbag -> pcd with file " + counter + ": " + filename)

        filepath = os.path.join(input_directory, filename)
        args=""
        roscore_wrapper.start()
        process_manager = ProcessManager(filepath=filepath, output_path=output_path, start_rviz=start_rviz)
        process_manager.start()
        roscore_wrapper.stop()

    force_kill_ros()


if __name__ == "__main__":

    args = create_parser()
    mapping_wrapper(input_path=args.input, output_path=args.output, start_rviz=args.rviz)
