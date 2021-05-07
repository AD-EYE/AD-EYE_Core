
#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <queue>
#include <vector>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/LaneArray.h>




/*!
* Initiate SequenceGoalNode class which stores all goals from the adeye goals, goal_map_node
* Store them as queue
* Publish the real world map goal coordinates one by one to auto-ware when the vehicle is in the vicinity of the goal position.
*/
class SequenceGoalNode
{
private:
    ros::NodeHandle &nh_;
    ros::Subscriber goal_coordinates_;
    ros::Subscriber sub_position_;
    ros::Subscriber autoware_state_;
    ros::Subscriber autoware_global_plan_;
    ros::Publisher pub_goal_;
    ros::Publisher update_local_planner_;
    

    // ROS rate
    ros::Rate rate_;

    // Goal position variable
    geometry_msgs::PoseStamped pose_stamped_;

    //Vehicle position
    float x_ego_;
    float y_ego_;

    // Real world coordinates
    // Positon coordinates
    double x_world_position_coordinate_ = 0.0, y_world_position_coordinate_ = 0.0, z_world_position_coordinate_ ;

    // Orientation coordinates
    double x_world_orientation_coordinate_, y_world_orientation_coordinate_, z_world_orientation_coordinate_, w_world_orientation_coordinate_;

    // Goal queue
    std::queue <std::pair <double, double> > goal_coordinates_xy_;

    // Bool value for the first goal, global planner and end state
    bool received_next_goal_ = false;
    bool hasPlannerAndGoalBeenReset_ = false;
    bool updateGlobalPlanner_ = false;
    
    // Autoware and vehicle state status
    std::vector<visualization_msgs::Marker> autoware_behaviour_state_;
    std::string vehicle_state_status_;
    
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
        // Received goal position coordinates
        x_world_position_coordinate_ = msg -> pose.position.x;
        y_world_position_coordinate_ = msg -> pose.position.y;
        z_world_position_coordinate_ = msg -> pose.position.z;

        x_world_orientation_coordinate_ = msg -> pose.orientation.x;
        y_world_orientation_coordinate_ = msg -> pose.orientation.y;
        z_world_orientation_coordinate_ = msg -> pose.orientation.z;
        w_world_orientation_coordinate_ = msg -> pose.orientation.w;

        if (!received_next_goal_) {
                    
            // Position coordinates
            pose_stamped_.header.frame_id = "world";
            pose_stamped_.pose.position.x = x_world_position_coordinate_;
            pose_stamped_.pose.position.y = y_world_position_coordinate_;
            pose_stamped_.pose.position.z = z_world_position_coordinate_;
        
            // Orientation coordinates
            pose_stamped_.pose.orientation.x = x_world_orientation_coordinate_;
            pose_stamped_.pose.orientation.y = y_world_orientation_coordinate_;
            pose_stamped_.pose.orientation.z = z_world_orientation_coordinate_;
            pose_stamped_.pose.orientation.w = w_world_orientation_coordinate_;

            ROS_INFO("The first goal position coordinates:- x = %lf, y = %lf, z = %lf",
                pose_stamped_.pose.position.x, pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

            // Publish and store the first real-world map goal coordinates  
            goal_coordinates_xy_.push(std::make_pair (x_world_position_coordinate_, y_world_position_coordinate_));       
            pub_goal_.publish(pose_stamped_);

            // Bool value reset to true for sending upcoming goals in the main run loop.
            received_next_goal_ = true;
            
        }

        // Store the goal position coordinates in the queue if the goal is not near as 10 m to the previous goal
        if (destinationDistance(goal_coordinates_xy_.back().first, x_world_position_coordinate_, goal_coordinates_xy_.back().second, y_world_position_coordinate_) > 10 )
        {
            goal_coordinates_xy_.push(std::make_pair (x_world_position_coordinate_, y_world_position_coordinate_));
        }
        
        // Print the new goal positions
        ROS_INFO("The new goal has been received:- x = %lf and y = %lf", goal_coordinates_xy_.back().first, goal_coordinates_xy_.back().second);   
    }
    
    /*!
     * \brief Store Autoware State Callback : Continuously called when the autoware behaviour state information has changed.
     * \param msg The message contains the autoware state status.
     * \details Stores the vehicle state status.
     */
    void autowareStateCallback(const visualization_msgs::MarkerArray::ConstPtr &msg)
    { 
        autoware_behaviour_state_ = msg -> markers;
        vehicle_state_status_ = autoware_behaviour_state_[0].text;
    }
    
    /*!
     * \brief Autoware global plan Callback : Called when the global plan from autoware has changed.
     * \param msg A smart pointer to the message from the topic.
     */
    void autowareGlobalPlanCallback(const autoware_msgs::LaneArrayConstPtr& msg)
    {
      if (updateGlobalPlanner_)
      {
          // Update the local planner for the next goal
            local_planner_.data = 1;
            update_local_planner_.publish(local_planner_);
            updateGlobalPlanner_ = false;
            ROS_INFO("Updates Local Planner!");
      }
    }

    /*!
     * \brief Calculate the distance between two x and y points
     * \param x_1, x_2, y_1 and y_2 are points of the real world map
     */
    double destinationDistance(double x_one, double x_two, double y_one, double y_two)
    {
        double distance = pow(pow(x_one - x_two, 2) + pow(y_one - y_two, 2), 0.5);
        return distance;
    }
    
public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    SequenceGoalNode(ros::NodeHandle &nh) : nh_(nh), rate_(20)
    {
        // Initialize node, publishers and subscribers
        goal_coordinates_ = nh.subscribe<geometry_msgs::PoseStamped>("/adeye/goals", 1, &SequenceGoalNode::storeGoalCoordinatesCallback, this);
        sub_position_ = nh.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &SequenceGoalNode::positionCallback, this);
        autoware_state_ = nh.subscribe<visualization_msgs::MarkerArray>("/behavior_state", 1, &SequenceGoalNode::autowareStateCallback, this);
        autoware_global_plan_ = nh.subscribe("/lane_waypoints_array", 1, &SequenceGoalNode::autowareGlobalPlanCallback, this);
        pub_goal_ = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
        update_local_planner_ = nh.advertise<std_msgs::Int32>("/adeye/update_local_planner", 1, true);
    }   

    void run() 
    {
        // Publish the coordinates of the next goal once the car is reached near as 30 m to the goal.
        while (nh_.ok())
        {
            ros::spinOnce();

            if (received_next_goal_)
            {
                // Calculate the destination distance
                double destination_distance = destinationDistance(goal_coordinates_xy_.front().first, x_ego_, goal_coordinates_xy_.front().second, y_ego_);
                ROS_INFO("Destination distance: %lf", destination_distance);
                
                // Publish the next goal when the car enters in end state
                if (vehicle_state_status_ == "(0)End")
                {
                    if (!hasPlannerAndGoalBeenReset_)
                    { 
                        // Remove the first goal
                        goal_coordinates_xy_.pop();
                    
                        // Position coordinates
                        pose_stamped_.header.frame_id = "world";
                        pose_stamped_.pose.position.x = goal_coordinates_xy_.front().first;
                        pose_stamped_.pose.position.y = goal_coordinates_xy_.front().second;
                        pose_stamped_.pose.position.z = z_world_position_coordinate_;
                    
                        // Orientation coordinates
                        pose_stamped_.pose.orientation.x = x_world_orientation_coordinate_;
                        pose_stamped_.pose.orientation.y = y_world_orientation_coordinate_;
                        pose_stamped_.pose.orientation.z = z_world_orientation_coordinate_;
                        pose_stamped_.pose.orientation.w = w_world_orientation_coordinate_;

                        ROS_INFO("The next goal coordinates:- x = %lf, y = %lf, z = %lf",
                            pose_stamped_.pose.position.x, pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

                        // Publish the real world map goal coordinates         
                        pub_goal_.publish(pose_stamped_);
                        
                        // Update the global planner boolean
                        updateGlobalPlanner_ = true;
                        
                        // Update the planner and goal boolean for end state
                        hasPlannerAndGoalBeenReset_ = true;
                    }
                    
                    // The planner and goal boolean is set to false after publishing the goal and planner
                    if (vehicle_state_status_ == "(0)Forward")
                    {
                        hasPlannerAndGoalBeenReset_ = false;
                    }
                }  
            }
            rate_.sleep();
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "SequenceGoalNode");
    ros::NodeHandle nh;
    SequenceGoalNode sequence_goal_node(nh);
    sequence_goal_node.run();
    return 0;
}