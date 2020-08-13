"""
This file describes the FeatureControl class.
"""

from roslaunch import rlutil, parent, configure_logging
import rospy
import time

DEFAULT_WAIT_TIME = 0.1


class FeatureControl:

    """
    This is a class for controlling the starting and stopping of the features
    Attributes: 
        filepath            :   string for the file path to evaluate whether safe
        feature_name        :   string for the name of the feature in consideration        
        sleep_time_on_start :   
        sleep_time_on_stop

    Methods:

        start   :
        stop    :   
    
    """


    def __init__(self, filepath, feature_name, sleep_time_on_start=DEFAULT_WAIT_TIME,
                 sleep_time_on_stop=DEFAULT_WAIT_TIME):
        self.uuid = rlutil.get_or_generate_uuid(None, False)
        configure_logging(self.uuid)
        self.filepath = filepath
        self.Launch = parent.ROSLaunchParent(self.uuid, [filepath])
        self.FeatureName = feature_name
        self.sleep_time_on_start = sleep_time_on_start
        self.sleep_time_on_stop = sleep_time_on_stop

    def start(self):
        self.uuid = rlutil.get_or_generate_uuid(None, False)
        configure_logging(self.uuid)
        self.Launch = parent.ROSLaunchParent(self.uuid, [self.filepath])
        self.Launch.start()
        rospy.loginfo("%s: Started feature - %s", rospy.get_name(), self.FeatureName)
        time.sleep(self.sleep_time_on_start)

    def stop(self):
        self.Launch.shutdown()
        rospy.loginfo("%s: Stopped feature - %s", rospy.get_name(), self.FeatureName)
        time.sleep(self.sleep_time_on_stop)
