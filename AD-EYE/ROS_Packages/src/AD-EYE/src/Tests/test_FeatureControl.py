#!/usr/bin/env python
from unittest import TestCase
from FeatureControl import FeatureControl
import rospkg
import rosnode

Node_to_check = '/controlSwitch'

SECS = 0.1
rospack = rospkg.RosPack()
filepath = rospack.get_path('adeye')+"/launch/switch.launch"

##A class to check the creation and behavior of the launch file and if the nodes are running
class TestFeatureControl(TestCase):

    ##Method test_start_1
    #
    # Test to ensure a new Launch file is created each time start() is called, to avoid bugs where rllaunch fails due
    # an incorrect launch configuration.
    # Test checks that the object used to start a launch has changed.
    #@param self the object pointer
    def test_start_1(self):
        test_feature = FeatureControl(filepath, "test_node", SECS, SECS)
        original_launch = test_feature.Launch
        test_feature.start()
        test_feature.stop()
        test_feature.start()
        new_launch = test_feature.Launch
        self.assertNotEqual(original_launch, new_launch)
        test_feature.stop()

    ##Method test_start_2
    #
    # Test to ensure that the start() function actually starts a node.
    # Test kills nodes that could be running with the same name, then starts roslaunch
    # and checks that the intended node is running as rosnode.get_node_names()
    # only returns nodes that are currently running
    #@param self the object pointer
    def test_start_2(self):
        test_feature = FeatureControl(filepath, "test_node", SECS, SECS)
        rosnode.kill_nodes(Node_to_check)
        test_feature.start()

        X = rosnode.get_node_names()
        test_feature.stop()
        if Node_to_check in X:
            pass
        else:
            self.fail()


    ##Method test_stop_1
    #
    #Test to ensure that the Launch file is stopped once the function stop() executes
    #The launch file is considered to have been killed when the node it had started is no longer running
    #@param self the object pointer
    def test_stop_1(self):
        test_feature = FeatureControl(filepath, "test_node", SECS, SECS)
        test_feature.start()
        test_feature.stop()
        with self.assertRaises(Exception):
            X = rosnode.get_node_names()


if __name__ == '__main__':
    # Ros unit testing framework is used to run all tests and save in .xml format
    import rosunit

    rosunit.unitrun('adeye', 'Feature_control_test_results', TestFeatureControl)
