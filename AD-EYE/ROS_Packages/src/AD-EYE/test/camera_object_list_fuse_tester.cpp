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

void testTwoEmptyMsgs(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;

    autoware_msgs::DetectedObjectArray in_msgs2;

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.size() == 0);
}

void testOneEmptyMsg(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.size() == 1);
}

void testNoMsgCameraTopicTwo(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    in_msgs1.objects.push_back(msg1);

    fuser.msg1Callback(in_msgs1);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.size() == 1);
}

void testOverlapMerging(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.size() == 1);
}

void testOverlapMsgOneWithLabel(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    msg1.label = "Pedestrian";
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(0).label == "Pedestrian");
}

void testOverlapMsgTwoWithLabel(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    msg2.label = "Pedestrian";
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(0).label == "Pedestrian");
}

void testOverlapTwoMsgWithoutLabel(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(0).label.empty());
    assert(fused_msg.objects.size() == 1);
}

void testOverlapMsgsWithSameLabel(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    msg1.label = "Pedestrian";
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    msg2.label = "Pedestrian";
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(0).label == "Pedestrian");
}

void testOverlapMsgsWithoutSameLabel(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    msg1.pose.position.x = 5;
    msg1.label = "Pedestrian";
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    msg2.label = "Dog";
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(0).label == "Pedestrian");
}

void testOverlapMsgOneWithThreeObjects(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    // first object
    msg1.pose.position.x = 5;
    msg1.pose.position.y = -5;
    msg1.pose.position.z = 5;
    msg1.label = "Pedestrian";
    in_msgs1.objects.push_back(msg1);
    // second object
    msg1.pose.position.x = 5;
    msg1.pose.position.y = 5;
    msg1.pose.position.z = 5;
    msg1.label = "Dog";
    in_msgs1.objects.push_back(msg1);
    // third object
    msg1.pose.position.x = 5;
    msg1.pose.position.y = 2.5;
    msg1.pose.position.z = 5;
    msg1.label = "Bicycle";
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    msg2.pose.position.x = 5;
    msg2.pose.position.y = 5;
    msg2.pose.position.z = 5;
    msg2.label = "Dog";
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(1).label == "Dog");
}

void testOverlapMsgsWithMoreObjects(ros::NodeHandle nh)
{
    CameraObjectListFuse fuser(nh, "dummy_1", "dummy_2", "dummy_3");
    
    autoware_msgs::DetectedObjectArray in_msgs1;
    autoware_msgs::DetectedObject msg1;
    // first object
    msg1.pose.position.x = 5;
    msg1.pose.position.y = -5;
    msg1.pose.position.z = 5;
    msg1.label = "Pedestrian";
    in_msgs1.objects.push_back(msg1);
    // second object
    msg1.pose.position.x = 5;
    msg1.pose.position.y = 5;
    msg1.pose.position.z = 5;
    msg1.label = "Dog";
    in_msgs1.objects.push_back(msg1);
    // third object
    msg1.pose.position.x = 5;
    msg1.pose.position.y = 2.5;
    msg1.pose.position.z = 5;
    msg1.label = "Bicycle";
    in_msgs1.objects.push_back(msg1);

    autoware_msgs::DetectedObjectArray in_msgs2;
    autoware_msgs::DetectedObject msg2;
    // first object
    msg2.pose.position.x = 5;
    msg2.pose.position.y = 5;
    msg2.pose.position.z = 5;
    msg2.label = "Dog";
    in_msgs2.objects.push_back(msg2);
    // second object
    msg2.pose.position.x = 5;
    msg2.pose.position.y = -5;
    msg2.pose.position.z = 5;
    msg2.label = "Pedestrian";
    in_msgs2.objects.push_back(msg2);
    // third object
    msg2.pose.position.x = 5;
    msg2.pose.position.y = 2.5;
    msg2.pose.position.z = 5;
    msg2.label = "Bicycle";
    in_msgs2.objects.push_back(msg2);
    // fourth object
    msg2.pose.position.x = 5;
    msg2.pose.position.y = -2.5;
    msg2.pose.position.z = 5;
    msg2.label = "Car";
    in_msgs2.objects.push_back(msg2);

    fuser.msg1Callback(in_msgs1);
    fuser.msg2Callback(in_msgs2);

    autoware_msgs::DetectedObjectArray fused_msg;
    fuser.fuse();
    fused_msg = fuser.getFusedMessage();

    assert(fused_msg.objects.at(0).label == "Pedestrian");
    assert(fused_msg.objects.at(1).label == "Dog");
    assert(fused_msg.objects.at(2).label == "Bicycle");
    assert(fused_msg.objects.at(3).label == "Car");
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "TesterNode");
    ros::NodeHandle nh;
    testNonOverlapMerging(nh);
    testTwoEmptyMsgs(nh);
    testOneEmptyMsg(nh);
    testNoMsgCameraTopicTwo(nh);
    testOverlapMsgOneWithLabel(nh);
    testOverlapMsgTwoWithLabel(nh);
    testOverlapTwoMsgWithoutLabel(nh);
    testOverlapMsgsWithSameLabel(nh);
    testOverlapMsgsWithoutSameLabel(nh);
    testOverlapMsgOneWithThreeObjects(nh);
    testOverlapMsgsWithMoreObjects(nh);
    std::cout << "All tests passed (the error messages above, if any, are printed by the different modules to indicate "
                 "faults that they have detected which were set up for these tests)"
              << std::endl;
}