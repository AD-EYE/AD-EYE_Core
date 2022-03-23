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
    msg1_ = msg;

    // Identify the objects that have been detected by camera_1
    for (size_t i = 0; i < msg1_.objects.size(); i++)
    {
        if (msg1_.objects.at(i).label != "unknown" && msg1_.objects.at(i).label != "")
        {
            msg1_.objects.at(i).user_defined_info.push_back("camera_1");
        }
    }

    msg1_flag_ = true;
}

void CameraObjectListFuse::msg2Callback(autoware_msgs::DetectedObjectArray msg)
{
    msg2_ = msg;

    // Identify the objects that have been detected by the camera_2
    for (size_t i = 0; i < msg2_.objects.size(); i++)
    {
        if (msg2_.objects.at(i).label != "unknown" && msg2_.objects.at(i).label != "")
        {
            msg2_.objects.at(i).user_defined_info.push_back("camera_2");
        }
    }

    msg2_flag_ = true;
}

void CameraObjectListFuse::fuse()
{
    msg3_ = msg1_;
    // std::cout << "Size of msg1_: " << msg1_.objects.size() << '\n';
    // std::cout << "Size of msg2_: " << msg2_.objects.size() << '\n';

    for (size_t i = 0; i < msg2_.objects.size(); i++)
    {
        if (msg2_.objects.at(i).label != "unknown")
        {
            for (size_t j = 0; j < msg3_.objects.size(); j++)
            {
                if (msg3_.objects.at(j).user_defined_info.size() > 0 &&
                    msg2_.objects.at(i).user_defined_info.size() > 0)
                {
                    if (msg3_.objects.at(j).user_defined_info.at(0) == msg2_.objects.at(i).user_defined_info.at(0))
                    {
                        msg3_.objects.at(j) = msg2_.objects.at(i);
                        // std::cout << "label: " << msg2_.objects.at(i).label << '\n';
                    }
                }
            }
        }
    }
}

void CameraObjectListFuse::publish()
{
    pub_.publish(msg3_);
}

autoware_msgs::DetectedObjectArray CameraObjectListFuse::getFusedMessage()
{
    return msg3_;
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
