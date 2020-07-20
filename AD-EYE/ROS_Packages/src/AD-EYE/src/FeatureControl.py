from roslaunch import rlutil, parent, configure_logging
import rospy
import time

DEFAULT_WAIT_TIME = 0.1


class FeatureControl:

    """ 
    This is a class for controlling the starting/stopping of the feature
      
    Attributes: 

        uuid                :   str
        filepath            :   str
            The path of the file   
        Launch              :   
            Uses roslaunch to launch the parent file
        feature_name        :
        sleep_time_on_start :   float
        sleep_time_on_stop  :   float
        

    Methods:

        start()
            Starts the feature 

        stop()
            Stops the running feature
        
    
    """

    def __init__(self, filepath, feature_name, sleep_time_on_start=DEFAULT_WAIT_TIME,
                 sleep_time_on_stop=DEFAULT_WAIT_TIME):
        
        """         
        Parameters: 

            filepath            :   str
                The path of the file   
            feature_name        :
            
            sleep_time_on_start :   float

            sleep_time_on_stop  :   float
                    
        """
        
        self.uuid = rlutil.get_or_generate_uuid(None, False)
        configure_logging(self.uuid)
        self.filepath = filepath
        self.Launch = parent.ROSLaunchParent(self.uuid, [filepath])
        self.FeatureName = feature_name
        self.sleep_time_on_start = sleep_time_on_start
        self.sleep_time_on_stop = sleep_time_on_stop

    def start(self):

        """      
        Starts the feature that have been requested by the user   

        Parameters
        ----------
        Raises
        ------
        """

        self.uuid = rlutil.get_or_generate_uuid(None, False)
        configure_logging(self.uuid)
        self.Launch = parent.ROSLaunchParent(self.uuid, [self.filepath])
        self.Launch.start()
        rospy.loginfo("%s: Started feature - %s", rospy.get_name(), self.FeatureName)
        time.sleep(self.sleep_time_on_start)

    def stop(self):
        """      
        Stops the feature that have been requested by the user   

        Parameters
        ----------
        Raises
        ------
        """
        self.Launch.shutdown()
        rospy.loginfo("%s: Stopped feature - %s", rospy.get_name(), self.FeatureName)
        time.sleep(self.sleep_time_on_stop)
