#include <camera_object_list_fuse.h>

CameraObjectListFuse::CameraObjectListFuse(ros::NodeHandle& nh, std::string input_topic_1, std::string input_topic_2,
                                           std::string output_topic)
  : nh_(nh)
{
    // Initialize the publishers and subscribers
    sub1_ =
        nh_.subscribe<autoware_msgs::DetectedObjectArray>(input_topic_1, 1, &CameraObjectListFuse::msg1Callback, this);
    sub2_ =
        nh_.subscribe<autoware_msgs::DetectedObjectArray>(input_topic_2, 1, &CameraObjectListFuse::msg2Callback, this);
    pub_ = nh_.advertise<autoware_msgs::DetectedObjectArray>(output_topic, 1, true);
}

void CameraObjectListFuse::msg1Callback(autoware_msgs::DetectedObjectArray msg)
{
    in_msg1_ = msg;

    // Identify the objects that have been detected by camera_1
    for (size_t i = 0; i < in_msg1_.objects.size(); i++)
    {
        if (in_msg1_.objects.at(i).label != "unknown" && in_msg1_.objects.at(i).label != "")
        {
            in_msg1_.objects.at(i).user_defined_info.push_back("camera_1");
        }
    }

    msg1_flag_ = true;
}

void CameraObjectListFuse::msg2Callback(autoware_msgs::DetectedObjectArray msg)
{
    in_msg2_ = msg;

    // Identify the objects that have been detected by the camera_2
    for (size_t i = 0; i < in_msg2_.objects.size(); i++)
    {
        if (in_msg2_.objects.at(i).label != "unknown" && in_msg2_.objects.at(i).label != "")
        {
            in_msg2_.objects.at(i).user_defined_info.push_back("camera_2");
        }
    }

    msg2_flag_ = true;
}

bool CameraObjectListFuse::isSameObject(autoware_msgs::DetectedObject msg1, autoware_msgs::DetectedObject msg2)
{
    return (msg1.pose.position.x == msg2.pose.position.x && msg1.pose.position.y == msg2.pose.position.y &&
            msg1.pose.position.z == msg2.pose.position.z);
}

autoware_msgs::DetectedObject CameraObjectListFuse::getMostRelevantObject(autoware_msgs::DetectedObject msg1,
                                                                          autoware_msgs::DetectedObject msg2)
{
    autoware_msgs::DetectedObject fused_msg;

    // empty messages
    if (msg1.label.empty() || msg2.label.empty())
    {
        fused_msg = msg1;
    }

    // either messages is empty
    if (!msg1.label.empty() && msg2.label.empty())
    {
        fused_msg = msg1;
    }
    if (msg1.label.empty() && !msg2.label.empty())
    {
        fused_msg = msg2;
    }

    // none messages are empty
    if (!msg1.label.empty() && !msg2.label.empty())
    {
        if (msg1.label == msg2.label)
        {
            fused_msg = msg1;
        }
        else
        {
            fused_msg = msg1;  // TODO - more elaborate selection
        }
    }

    return fused_msg;
}

void CameraObjectListFuse::fuse()
{
    fused_msg_ = in_msg1_;

    for (size_t i = 0; i < in_msg2_.objects.size(); i++)
    {
        bool object_from_fused_msg = false;
        for (size_t j = 0; j < fused_msg_.objects.size(); j++)
        {
            if (isSameObject(in_msg2_.objects.at(i), fused_msg_.objects.at(j)))
            {
                object_from_fused_msg = true;
                fused_msg_.objects.at(j) = getMostRelevantObject(fused_msg_.objects.at(j),in_msg2_.objects.at(i));
            }
        }
        if (!object_from_fused_msg)
        {
            fused_msg_.objects.push_back(in_msg2_.objects.at(i));
        }
    }
}

void CameraObjectListFuse::publish()
{
    pub_.publish(fused_msg_);
}

autoware_msgs::DetectedObjectArray CameraObjectListFuse::getFusedMessage()
{
    return fused_msg_;
}

void CameraObjectListFuse::run()
{
    ros::Rate rate(20);
    while (nh_.ok())
    {
        ros::spinOnce();
        if (msg1_flag_ || msg2_flag_)
        {
            publish();
        }
        rate.sleep();
    }
}

void usage(std::string bin_name)
{
    ROS_FATAL_STREAM("\n"
                     << "Usage : " << bin_name << " <input_topic_1> <input_topic_2> <output_topic>");
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string input_topic_1, input_topic_2, output_topic;
    input_topic_1 = argv[1];
    input_topic_2 = argv[2];
    output_topic = argv[3];

    ros::init(argc, argv, "CameraObjectListFuse");
    ros::NodeHandle nh;
    CameraObjectListFuse camera_object_fuser(nh, input_topic_1, input_topic_2, output_topic);
    camera_object_fuser.run();
    return 0;
}
