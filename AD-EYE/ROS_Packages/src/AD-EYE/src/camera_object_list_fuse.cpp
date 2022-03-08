#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>

/*!
 * \brief A node that list the objects detected by the camera 1 and 2, and publish it
 * \details Publish a list of all the objects detected by the camera 1 and the camera 2. 
 * The purpuse is to fuse the objects detected by the two cameras in one message.
 */
class cameraObjectListFuse
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber sub1;
    ros::Subscriber sub2;

    ros::Publisher pub;

    autoware_msgs::DetectedObjectArray msg1;
    autoware_msgs::DetectedObjectArray msg2;
    autoware_msgs::DetectedObjectArray msg3;

    bool msg1_flag = false;
    bool msg2_flag = false;

public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param inputTopic1 Name of the topic that connect the camera 1
     * \param inputTopic2 Name of the topic that connect the camera 2
     * \param outputTopic Name of the topic where the output list will be published
     * \details Initialize the node and its components such as publishers and subscribers. It call msg1_callback and msg2_callback
     */
    cameraObjectListFuse(ros::NodeHandle &nh, std::string inputTopic1, std::string inputTopic2, std::string outputTopic) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub1 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic1, 1, &cameraObjectListFuse::msg1_callback, this);
        sub2 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic2, 1, &cameraObjectListFuse::msg2_callback, this);
        pub = nh_.advertise<autoware_msgs::DetectedObjectArray>(outputTopic, 1, true);
    }

    /*!
     * \brief Callback call in the constructeur
     * \param msg Contain the list of object detected by camera 1
     * \details Identify the objects that have been detected by camera 1
     */
    void msg1_callback(autoware_msgs::DetectedObjectArray msg)
    {
        msg1 = msg;

        // Identify the objects that have been detected by camera_1
        for (size_t i = 0; i < msg1.objects.size(); i++) {
            if (msg1.objects.at(i).label!="unknown" && msg1.objects.at(i).label!="") {
                msg1.objects.at(i).user_defined_info.push_back("camera_1");
            }
        }

        msg1_flag = true;
    }

    /*!
     * \brief Callback call in the constructeur
     * \param msg Contain the list of object detected by camera 2
     * \details Identify the objects that have been detected by camera 2
     */
    void msg2_callback(autoware_msgs::DetectedObjectArray msg)
    {
        msg2 = msg;

        // Identify the objects that have been detected by the camera_2
        for (size_t i = 0; i < msg2.objects.size(); i++) {
            if (msg2.objects.at(i).label!="unknown" && msg2.objects.at(i).label!="") {
                msg2.objects.at(i).user_defined_info.push_back("camera_2");
            }
        }

        msg2_flag = true;
    }

    /*!
     * \brief Publish all the object detected
     * \details Publish the list of all the object detected by camera 1 and 2 to outputTopic.
     */
    void publish()
    {

        msg3 = msg1;
        bool objectAssigned = false;
        // std::cout << "Size of msg1: " << msg1.objects.size() << '\n';
        // std::cout << "Size of msg2: " << msg2.objects.size() << '\n';



        for (size_t i = 0; i < msg2.objects.size(); i++) {
            if (msg2.objects.at(i).label!="unknown") {
                for (size_t j = 0; j < msg3.objects.size(); j++) {
                    if (msg3.objects.at(j).user_defined_info.size() > 0 && msg2.objects.at(i).user_defined_info.size() > 0) {
                        if (msg3.objects.at(j).user_defined_info.at(0) == msg2.objects.at(i).user_defined_info.at(0)) {
                            msg3.objects.at(j) = msg2.objects.at(i);
                            // std::cout << "label: " << msg2.objects.at(i).label << '\n';
                        }
                    }
                }
            }
        }
     pub.publish(msg3);
    }

    /*!
     * \brief The main loop of the Node
     */
    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          if (msg1_flag == true || msg2_flag == true) {
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
void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <input_topic_1> <input_topic_2> <output_topic>");
}

/*!
* \brief Main function
* \details In the argument of the command line, it needs inoutTopic1 which contains the camera1, then inputTopic2 which contains the camera2, then outputTopic
*/
int main(int argc, char** argv)
{
    if (argc < 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string inputTopic1, inputTopic2, outputTopic;
    inputTopic1 = argv[1];
    inputTopic2 = argv[2];
    outputTopic = argv[3];

    ros::init(argc, argv, "cameraObjectListFuse");
    ros::NodeHandle nh;
    cameraObjectListFuse cOLF(nh, inputTopic1, inputTopic2, outputTopic);
    cOLF.run();
    return 0;
}
