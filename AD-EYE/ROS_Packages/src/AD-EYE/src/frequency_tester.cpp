#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <rosgraph_msgs/Clock.h>

// to measure time
#include <sys/time.h>



class TwistSender {
    public:
    int counter = 0;

    TwistSender(ros::NodeHandle &nh) {
        ros::Time::waitForValid();
        std::cout << "time is valid" << std::endl;
        ros::Rate rate(10);
        rate.reset();
        while(ros::ok())
        {
            std::cout << rate.cycleTime().toSec() << std::endl;
            std::cout << rate.expectedCycleTime().toSec() << std::endl;
            std::cout << rate.sleep() << std::endl;
            counter++;
            // rate.reset();
            std::cout << "counter: " << counter << std::endl;
            std::cout << "time: " << ros::Time::now().toSec() << std::endl;
        }
    }

};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "TwistSender");
    ros::NodeHandle nh;
    TwistSender scp = TwistSender(nh);
}