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
    ros::Subscriber sub_goal_coordinates_;
    
    // Goal queue
    std::queue <geometry_msgs::PoseStamped::ConstPtr > goal_coordinates_;

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

    void storeGoalCoordinatesCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        goal_coordinates_.push(msg); 
    }
    
public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    rosbags(ros::NodeHandle &nh) : nh_(nh), rate_(20)
    {
        
        sub_goal_coordinates_ = nh_.subscribe<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, &rosbags::storeGoalCoordinatesCallback, this);
        //recording();
        system("rosrun rosbag_snapshot snapshot -d 30 /clock /aye/goals /move_base_simple/goal")
    }

    void run()
    {
        while (nh_.ok())
        {
            ros::spinOnce();
            if(goal_coordinates_.size() > 2)
            {
                system("rosrun rosbag_snapshot snapshot -t");
            }
            rate_.sleep();
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rosbagsRolling");
    ros::NodeHandle nh;
    rosbags ros_rolling(nh);
    ros_rolling.run();
    return 0;
}