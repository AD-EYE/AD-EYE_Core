#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>

/*!
 * \brief A node that list the objects detected by the camera 1 and 2, and publish it
 * \details Publish a list of all the objects detected by the camera 1 and the camera 2.
 * The purpuse is to fuse the objects detected by the two cameras in one message.
 */
class CameraObjectListFuse
{
  private:
    // Node, publishers and subscribers
    ros::NodeHandle& nh_;

    ros::Subscriber sub1_;
    ros::Subscriber sub2_;

    ros::Publisher pub_;

    autoware_msgs::DetectedObjectArray msg1_;
    autoware_msgs::DetectedObjectArray msg2_;
    autoware_msgs::DetectedObjectArray msg3_;

    bool msg1_flag_ = false;
    bool msg2_flag_ = false;

  public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param input_topic_1 Name of the topic that connect the camera 1
     * \param input_topic_2 Name of the topic that connect the camera 2
     * \param output_topic Name of the topic where the output list will be published
     * \details Initialize the node and its components such as publishers and subscribers. It call msg1Callback and
     * msg2Callback
     */
    CameraObjectListFuse(ros::NodeHandle& nh, std::string input_topic_1,
                         std::string output_topic)
      : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub1_ = nh_.subscribe<autoware_msgs::DetectedObjectArray>(input_topic_1, 1, &CameraObjectListFuse::msg1Callback,
                                                                  this);
    /*         sub2_ = nh_.subscribe<autoware_msgs::DetectedObjectArray>(input_topic_2, 1, &CameraObjectListFuse::msg2Callback,
                                                                  this); */
        pub_ = nh_.advertise<autoware_msgs::DetectedObjectArray>(output_topic, 1, true);
    }

    /*!
     * \brief Callback call in the constructor
     * \param msg Contain the list of object detected by camera 1
     * \details Identify the objects that have been detected by camera 1
     */
    void msg1Callback(autoware_msgs::DetectedObjectArray msg)
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

    /*!
     * \brief Callback call in the constructor
     * \param msg Contain the list of object detected by camera 2
     * \details Identify the objects that have been detected by camera 2
     */
    /*     void msg2Callback(autoware_msgs::DetectedObjectArray msg)
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
    }*/

    /*!
     * \brief Publish all the object detected
     * \details Publish the list of all the object detected by camera 1 and 2 to outputTopic.
     */
    void publish()
    {
        msg3_ = msg1_;
        // std::cout << "Size of msg1_: " << msg1_.objects.size() << '\n';
        // std::cout << "Size of msg2_: " << msg2_.objects.size() << '\n';
    /* 
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
        } */
        pub_.publish(msg3_);
    }

    /*!
     * \brief The main loop of the Node
     */
    void run()
    {
        ros::Rate rate(20);
        while (nh_.ok())
        {
            ros::spinOnce();
            if (msg1_flag_)
            {
                publish();
            }
            rate.sleep();
        }
    }
};

/*!
* \brief Exception
* \details Exception raise if names of topics weren't given
*/
void usage(std::string bin_name)
{
    ROS_FATAL_STREAM("\n"
                     << "Usage : " << bin_name << " <input_topic_1> <input_topic_2> <output_topic>");
}

/*!
* \brief Main function
* \details In the argument of the command line, it needs inoutTopic1 which contains the camera1, then inputTopic2 which
* contains the camera2, then outputTopic
*/
int main(int argc, char** argv)
{
    if (argc < 4)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string input_topic_1,  output_topic;
    input_topic_1 = argv[1];
    output_topic = argv[3];

    ros::init(argc, argv, "CameraObjectListFuse");
    ros::NodeHandle nh;
    CameraObjectListFuse camera_object_fuser(nh, input_topic_1, output_topic);
    camera_object_fuser.run();
    return 0;
}
