from roslaunch import rlutil, parent, configure_logging
import rospy
import time

##@var DEFAULT_WAIT_TIME
DEFAULT_WAIT_TIME = 0.1

##A class to write in a log the behavior of a feature and its parents'
class FeatureControl:


    ##The constructor
    #
    #@param self The object pointer
    #@param filepath String indicating the path to the studied feature
    #@param feature_name String indicating the name of the studied feature
    #@param sleep_time_on_start Float which default value is #DEFAULT_WAIT_TIME
    #@param sleep_time_on_stop Float which default value is #DEFAULT_WAIT_TIME
    def __init__(self, filepath, feature_name, sleep_time_on_start=DEFAULT_WAIT_TIME,
                 sleep_time_on_stop=DEFAULT_WAIT_TIME):
        self.uuid = rlutil.get_or_generate_uuid(None, False)
        configure_logging(self.uuid)
        self.filepath = filepath
        self.Launch = parent.ROSLaunchParent(self.uuid, [filepath])
        self.FeatureName = feature_name
        self.sleep_time_on_start = sleep_time_on_start
        self.sleep_time_on_stop = sleep_time_on_stop


    ##A method to start the feature and its parents, and write the status of the name of the feature and of nodes in a log.
    #@param self The object pointer
    def start(self):
        if self.filepath != "":
            self.uuid = rlutil.get_or_generate_uuid(None, False)
            configure_logging(self.uuid)
            self.Launch = parent.ROSLaunchParent(self.uuid, [self.filepath])
            self.Launch.start()
            rospy.loginfo("%s: Started feature - %s", rospy.get_name(), self.FeatureName)
            time.sleep(self.sleep_time_on_start)

    ##A method to stop the feature and its parents, and write the status of the name of the feature and of nodes in a log.
    #@param self The object pointer
    def stop(self):
        if self.filepath != "":
            self.Launch.shutdown()
            rospy.loginfo("%s: Stopped feature - %s", rospy.get_name(), self.FeatureName)
            time.sleep(self.sleep_time_on_stop)
