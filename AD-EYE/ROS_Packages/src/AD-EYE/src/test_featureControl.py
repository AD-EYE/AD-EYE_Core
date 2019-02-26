from unittest import TestCase
import time
from FeatureControl import FeatureControl

SECS = 1
filepath = "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/launch/switch.launch"


class TestFeatureControl(TestCase):
    def test_start(self):
        test_feature = FeatureControl(filepath, "test_node", SECS, SECS)
        original_launch = test_feature.Launch
        test_feature.start()
        time.sleep(SECS)
        test_feature.stop()
        time.sleep(SECS)
        test_feature.start()
        new_launch = test_feature.Launch
        self.assertNotEqual(original_launch, new_launch)

    def test_stop(self):
        self.fail()
