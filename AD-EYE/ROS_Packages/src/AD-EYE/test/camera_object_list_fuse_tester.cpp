#include <iostream>
#include <ros/ros.h>

#include "camera_object_list_fuse.h"
#include <autoware_msgs/DetectedObjectArray.h>

void testNonOverlapMerging(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = -5;
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.size() == 2);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "TesterNode");
    ros::NodeHandle nh;
    testNonOverlapMerging(nh);
    std::cout << "All tests passed (the error messages above, if any, are printed by the different modules to indicate "
                 "faults that they have detected which were set up for these tests)"
              << std::endl;
}