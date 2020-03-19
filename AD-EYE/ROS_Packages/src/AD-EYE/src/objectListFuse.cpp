#include <ros/ros.h>
#include <ros/master.h>
#include <ros/this_node.h>

#include <autoware_msgs/DetectedObjectArray.h>

class objectListFuse
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
    objectListFuse(ros::NodeHandle &nh, std::string inputTopic1, std::string inputTopic2, std::string outputTopic) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub1 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic1, 1, &objectListFuse::msg1_callback, this);
        sub2 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic2, 1, &objectListFuse::msg2_callback, this);
        pub = nh_.advertise<autoware_msgs::DetectedObjectArray>(outputTopic, 1, true);
    }

    void msg1_callback(autoware_msgs::DetectedObjectArray msg)
    {
        msg1 = msg;
        msg1_flag = true;
    }

    void msg2_callback(autoware_msgs::DetectedObjectArray msg)
    {
        msg2 = msg;
        msg2_flag = true;
    }

    void publish()
    {
        msg3 = msg1;
        for (size_t i = 0; i < msg2.objects.size(); i++) {
          msg3.objects.push_back(msg2.objects.at(i));
        }
        pub.publish(msg3);
    }

    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          if (msg1_flag == true && msg2_flag == true) {
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

    ros::init(argc, argv, "objectListFuse");
    ros::NodeHandle nh;
    objectListFuse oLF(nh, inputTopic1, inputTopic2, outputTopic);
    oLF.run();
    return 0;
}
