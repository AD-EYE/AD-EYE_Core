#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <queue>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/LaneArray.h>
#include <std_msgs/Bool.h>
#include <rosbag/recorder.h>


/*!
* Initiate SequenceGoalNode class which stores all goals from the adeye goals, goal_map_node
* Store them as queue
* Publish the real world map goal coordinates one by one to auto-ware when the vehicle is in the vicinity of the goal position.
*/
class rosbags
{
private:
    ros::NodeHandle &nh_;
    
    // ROS rate
    ros::Rate rate_;

    void recording()
    {
        rosbag::RecorderOptions options;
        options.prefix = "/home/adeye/rosbags/demorecord.bag";
        std::vector<std::string> topics(1); ;
        topics[0] = "/move_base_simple/goal";
        options.topics = topics;
        rosbag::Recorder recorder(options);
        recorder.run();
    }
    
public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    rosbags(ros::NodeHandle &nh) : nh_(nh), rate_(20)
    {
        recording();
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rosbagsRolling");
    ros::NodeHandle nh;
    rosbags ros_rolling(nh);
    return 0;
}