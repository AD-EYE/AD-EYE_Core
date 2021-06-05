#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <queue>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/LaneArray.h>
#include <std_msgs/Bool.h>


/*!
* Initiate SequenceGoalNode class which stores all goals from the adeye goals, goal_map_node
* Store them as queue
* Publish the real world map goal coordinates one by one to auto-ware when the vehicle is in the vicinity of the goal position.
*/
class GoalSequencer
{
private:
    ros::NodeHandle &nh_;
    ros::Subscriber sub_goal_coordinates_;
    ros::Subscriber sub_position_;
    ros::Subscriber sub_autoware_state_;
    ros::Subscriber sub_autoware_global_plan_;
    ros::Publisher pub_goal_;
    ros::Publisher pub_update_local_planner_;
    ros::Publisher pub_clear_goal_list_bool_;
    
    // ROS rate
    ros::Rate rate_;

    // Vehicle position
    float x_ego_;
    float y_ego_;

    // Goal queue
    std::queue <geometry_msgs::PoseStamped::ConstPtr > goal_coordinates_;

    // Boolean value for the global planner, end state and the goals
    bool has_global_planner_and_goal_been_reset_ = false;
    bool should_update_global_planner_ = false;
    bool received_first_goal_ = false;
    bool received_next_goal_ = false;
    
    // Autoware behavior state status
    double autoware_behavior_state_;

    // Distance tolerance for duplicate goals
    const double DISTANCE_TOLERANCE = 10; // [m]

    // Vehicle State behaviour
    const double END_STATE = 13.0;
    const double FORWARD_STATE_ = 2.0;

    /*!
     * \brief Position Callback : Continuously called when the vehicle position information has changed.
     * \param msg The message contains the vehicle position coordinates.
     * \details Stores the vehicle position coordinates information.
     */
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        // Received the vehicle position coordinates
        x_ego_ = msg -> pose.position.x;
        y_ego_ = msg -> pose.position.y;
    }

    /*!
     * \brief Store Goal Coordinates Callback : Called when the goal coordinates are received from the goal_map_node.
     * \param msg The message contains the goal position coordinates.
     * \details Stores the goal coordinates information as queue.
     */
    void storeGoalCoordinatesCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        // Store the first goal if the goal queue is empty
        if (goal_coordinates_.empty()) 
        {
            // Store the first real-world map goal coordinates  
            goal_coordinates_.push(msg);       

            ROS_INFO("The first goal has been received. Position:- x = %lf, y = %lf, z = %lf",
                goal_coordinates_.front() -> pose.position.x, goal_coordinates_.front() -> pose.position.y, goal_coordinates_.front() -> pose.position.z);
            
            // Boolean for receiving the first goal
            received_first_goal_ = true;
        }

        // Store the upcoming goal positions in the queue if the goal is not near as 10 m to the previous goal
        if (getDistance(goal_coordinates_.back()-> pose.position.x, msg -> pose.position.x, goal_coordinates_.back()-> pose.position.y, msg -> pose.position.y) > DISTANCE_TOLERANCE)
        {
            goal_coordinates_.push(msg);

            // Print the new goal positions
            ROS_INFO("The next goal has been received. Position:- x = %lf, y = %lf, z = %lf",goal_coordinates_.back()-> pose.position.x, goal_coordinates_.back()-> pose.position.y, goal_coordinates_.back() -> pose.position.z );   

            // Boolean for receiving the next goal
            received_next_goal_ = true;
        }    
    }
    
    /*!
     * \brief Behavior State Callback : Continuously called to show the vehicle behaviour state information.
     * \param msg The message contains the vehicle state status.
     * \details Stores the autoware behavior state status.
     */
    void behaviorStateCallback(const geometry_msgs::TwistStamped::ConstPtr &msg)
    { 
        // Autoware behavior state (2.0 = Forward state and 13.0 = End state)
        autoware_behavior_state_ =  msg -> twist.angular.y;
    }
    
    /*!
     * \brief Autoware global plan Callback : Called when the global plan from autoware has changed.
     * \param msg A smart pointer to the message from the topic.
     */
    void autowareGlobalPlanCallback(const autoware_msgs::LaneArrayConstPtr& msg)
    {
        // Local planner value
        std_msgs::Int32 local_planner;

        if (should_update_global_planner_)
        {
            // Update the local planner for the next goal
            local_planner.data = 1;
            pub_update_local_planner_.publish(local_planner);
            should_update_global_planner_ = false;
            ROS_INFO("Updated Local Planner!");
        }
    }

    /*!
      * \brief Calculate the distance between two x and y points
      * \param x_1, x_2, y_1 and y_2 are points of the real world map
      */
     double getDistance(double x_one, double x_two, double y_one, double y_two)
     {
         return pow(pow(x_one - x_two, 2) + pow(y_one - y_two, 2), 0.5);
     }
    
public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    GoalSequencer(ros::NodeHandle &nh) : nh_(nh), rate_(20)
    {
        // Initialize node, publishers and subscribers
        sub_goal_coordinates_ = nh.subscribe<geometry_msgs::PoseStamped>("/adeye/goals", 1, &GoalSequencer::storeGoalCoordinatesCallback, this);
        sub_position_ = nh.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &GoalSequencer::positionCallback, this);
        sub_autoware_state_ = nh.subscribe<geometry_msgs::TwistStamped>("/current_behavior", 1, &GoalSequencer::behaviorStateCallback, this);
        sub_autoware_global_plan_ = nh.subscribe("/lane_waypoints_array", 1, &GoalSequencer::autowareGlobalPlanCallback, this);
        pub_goal_ = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
        pub_update_local_planner_ = nh.advertise<std_msgs::Int32>("/adeye/update_local_planner", 1, true);
        pub_clear_goal_list_bool_= nh.advertise<std_msgs::Bool>("/adeye/clear_goal_list", 1, true);
    }   

    void run() 
    {
        // Publish the coordinates of the next goal once the car enters in the end state.
        while (nh_.ok())
        {
            ros::spinOnce();
            
            // Condition for the first goal
            if (received_first_goal_) 
            {      
                // Publish the first goal 
                pub_goal_.publish(goal_coordinates_.front());
                
                ROS_INFO("The first goal has been published. Position:- x = %lf, y = %lf, z = %lf", goal_coordinates_.front() -> pose.position.x, goal_coordinates_.front() -> pose.position.y, goal_coordinates_.front() -> pose.position.z);

                // Bool value reset to true for sending upcoming goals in the main run loop.
                received_first_goal_ = false;
            }
            
            // Condition for next (upcoming) goals
            if (received_next_goal_)
            { 
                // Publish the next goal when the car enters in end state (end state = 13.0)
                if (autoware_behavior_state_ == END_STATE)
                {
                    // Condition for removing the previous goal and setting up the next goal
                    if (!has_global_planner_and_goal_been_reset_ && received_next_goal_)
                    { 
                        // Boolean for clearing the goal list in autoware op_global_planner
                        std_msgs::Bool clear_goal_list;
                        
                        // Publish true value to clear the goal list in autoware
                        clear_goal_list.data = true;
                        pub_clear_goal_list_bool_.publish(clear_goal_list);

                        // Remove the previous goal
                        goal_coordinates_.pop();
                    
                        // Publish the real world map goal coordinates         
                        pub_goal_.publish(goal_coordinates_.front());

                        ROS_INFO("The next goal has been published. Position:- x = %lf, y = %lf, z = %lf", goal_coordinates_.front() -> pose.position.x, goal_coordinates_.front() -> pose.position.y, goal_coordinates_.front() -> pose.position.z);

                        // Update the global planner boolean
                        should_update_global_planner_ = true;
                        
                        // Update the planner and goal boolean for end state
                        has_global_planner_and_goal_been_reset_ = true;
                    }
                }

                // The planner and goal boolean is set to false after publishing the goal and planner (forward state = 2.0)
                if (autoware_behavior_state_ == FORWARD_STATE_) 
                {
                    has_global_planner_and_goal_been_reset_ = false;
                }
            }
            rate_.sleep();
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "GoalSequencer");
    ros::NodeHandle nh;
    GoalSequencer sequence_goal_node(nh);
    sequence_goal_node.run();
    return 0;
}