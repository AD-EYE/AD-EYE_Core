#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>

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
    cameraObjectListFuse(ros::NodeHandle &nh, std::string inputTopic1, std::string inputTopic2, std::string outputTopic) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub1 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic1, 1, &cameraObjectListFuse::msg1_callback, this);
        sub2 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic2, 1, &cameraObjectListFuse::msg2_callback, this);
        pub = nh_.advertise<autoware_msgs::DetectedObjectArray>(outputTopic, 1, true);
    }

    void msg1_callback(autoware_msgs::DetectedObjectArray msg)
    {
        msg1 = msg;

        // Identify the objects that have been detected by the camera_1
        for (size_t i = 0; i < msg1.objects.size(); i++) {
            if (msg1.objects.at(i).label!="unknown" && msg1.objects.at(i).label!="") {
                msg1.objects.at(i).user_defined_info.push_back("camera_1");
            }
        }

        msg1_flag = true;
    }

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

void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <input_topic_1> <input_topic_2> <output_topic>");
}

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
