#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <queue>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/LaneArray.h>
#include <std_msgs/Bool.h>
#include <vector_map_msgs/PointArray.h>
#include <cmath>
#include <iostream>
#include <tf/transform_broadcaster.h>

/*
Example on how to run the program:

Terminal1 type: rosrun adeye goalSequencer
Terminal2 type: roslaunch adeye my_map.la world_name:=W01_Base_Map
Terminal3 type one of the below:
rostopic pub /adeye/goals geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x: 0.0, y: 0.0, z: 49.156}, orientation: {z: 0.416, w: 0.909}}}'
rostopic pub /adeye/goals geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x: 137.998049077445, y: 121.23713661199696, z: 49.156}, orientation: {z: 0.760, w: 0.650}}}'
rostopic pub /adeye/goalseometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x: 120.0, y: 130.0, z: 1.0}, orientation: {w: 1.0}}}'
rostopic pub /current_behavior geometry_msgs/TwistStamped "{header: {stamp: now, frame_id: "map"}, twist: {linear: {x: 1.0, y: 2.0, z: 3.0}, angular: {x: 1.0,y: 13.0,z: 1.0}}}"
*/

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
    ros::Subscriber sub_vector_map_;
    ros::Publisher pub_goal_;
    ros::Publisher pub_update_local_planner_;
    ros::Publisher pub_clear_goal_list_bool_;

    
    // ROS rate
    ros::Rate rate_;

    // Vehicle position
    float x_ego_;
    float y_ego_;

    // Autoware vectormap
    vector_map_msgs::PointArray vector_map_data_;

    // Goal queue
    std::queue <geometry_msgs::PoseStamped> goal_coordinates_;

    // Boolean value for the global planner, end state and the goals
    bool has_global_planner_and_goal_been_reset_ = false;
    bool should_update_global_planner_ = false;
    bool received_first_goal_ = false;
    bool received_vector_mapper_ = false;

    // Autoware behavior state status
    double autoware_behavior_state_;

    // Distance tolerance for duplicate goals
    const double GOAL_DISTANCE_TOLERANCE_ = 10; // [m]
    const double VMAP_DISTANCE_TOLERANCE_ = 5; // [m]

    // Orientation tolerance between goals or goal and vector map
    const double ORIENTAION_TOLERANCE_ = 30; // [degrees]

    // Vehicle State behaviour
    const double END_STATE_ = 13.0;
    const double FORWARD_STATE_ = 2.0;
    
    // Minimum goals in the goal coordinates queue for publishing next (upcoming) goals
    const int MINIMUM_GOALS_ = 2;

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
        // Store the first goal if the goal queue is empty and boolean for upcoming goal is false

        if (goal_coordinates_.empty() && received_vector_mapper_ && checkGoalValidity(msg -> pose.position.x, msg -> pose.position.y, msg -> pose.orientation) ) 
        {   
            // Store the first real-world map goal coordinates  
            goal_coordinates_.push(*msg);       

            ROS_INFO("The first goal has been received. Position:- x = %lf, y = %lf, z = %lf",
                goal_coordinates_.front().pose.position.x, goal_coordinates_.front().pose.position.y, goal_coordinates_.front().pose.position.z);
            
            // Boolean for receiving the first goal
            received_first_goal_ = true;
            
        }

        else if (received_vector_mapper_ == false)
        {
            ROS_INFO("No vector map received, please close the goal publisher and start vector map in another terminal by typing for example:");
            ROS_INFO("roslaunch adeye my_map.launch world_name:=W01_Base_Map");
        }

        else if (goal_coordinates_.empty() == false && checkGoalValidity(msg -> pose.position.x, msg -> pose.position.y, msg -> pose.orientation))
        {
            goal_coordinates_.push(*msg);

            // Print the new goal positions
            ROS_INFO("The next goal has been received. Position:- x = %lf, y = %lf, z = %lf",goal_coordinates_.back().pose.position.x, goal_coordinates_.back().pose.position.y, goal_coordinates_.back().pose.position.z );
        } 
        else
        {
            ROS_INFO("The received goal is not valid");
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
    void autowareGlobalPlanCallback(const autoware_msgs::LaneArray::ConstPtr &msg)
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
     * \brief Autoware vector map Callback : Called when the vector map is received.
     * \param msg The message contains the data points of the vector map. 
     * \details Stores the data point value from the vector map
     */ 
    void vectorMapCallback(const vector_map_msgs::PointArray::ConstPtr &msg)
    {   
        ROS_INFO("Recived vector mapper");
        received_vector_mapper_ = true;
        vector_map_data_ = *msg;
    }
    


    /*!
    * \brief Calculate the distance between two x and y points
    * \param x_1, x_2, y_1 and y_2 are points of the real world map
    */
    double getDistance(const double& x_one, const double& x_two, const double& y_one, const double& y_two)
    {
        return sqrt((x_two - x_one) * (x_two - x_one) + (y_two - y_one) * (y_two - y_one));
    }

    /*!
    * \brief Calculate the orientation between two x and y points and retrun it in degrees
    * \param x_1, x_2, y_1 and y_2 are points of the real world map
    */
    double getOrientation(const double& x_one, const double& x_two, const double& y_one, const double& y_two)
    {
        double angle = atan2(y_two-y_one, x_two-x_one);
        if (angle < 0)
        {
            angle += 2*M_PI;
        }
    return angle*(180.0/M_PI);
    }

    /*!
    * \brief Help function for the function checkGoalValidity
    * \param x, y is the position of the received goal. file_size_ is the number of lines in the point.csv file that contains vector map data.
    *        yaw_angle is the angle of the received goal  
    * \details Loop through the vector map to see if the received goal position is close or within the vector map
    */
    bool ifInVectorMapp(const double& x, const double& y, const int& file_size_, const double& yaw_angle)
    {
        for (unsigned int i = 0; i < file_size_; i++)
        {
            //Check if the goal is close or within the vector map
            if (getDistance(x, vector_map_data_.data[i].ly, y, vector_map_data_.data[i].bx) <= VMAP_DISTANCE_TOLERANCE_ ) 
            {
                //Calcluate the orientation of the vector map
                double vmap_orientation = getOrientation(vector_map_data_.data[i].ly, vector_map_data_.data[i+1].ly, vector_map_data_.data[i].bx, vector_map_data_.data[i+1].bx); 
                
                //Check if the difference between goal and vector map orientation is small enoguh. 
                if (yaw_angle-vmap_orientation < ORIENTAION_TOLERANCE_)
                {
                    return true;
                }
                /*Continue the for loop to see if there exist other points in the vector map 
                with small enough orientation difference with the received goal*/
                else
                {
                    continue;
                }
            }
        }
        ROS_INFO("Recieved goal is not within the vector map or goal orientation difference from the vector map is too large");
        return false;
    }

    /*!
     * \brief Boolean function that checks the validity of the received goal
     * \param x, y and goal_orientation are the are data provided by the goals
     * \details Check if the received goal exist in the vector map and their orientation difference 
     *          Also check the distance and orientation with the pervious stored goal.
     */
    bool checkGoalValidity(const double& x, const double& y, const geometry_msgs::Quaternion& goal_orientation)
    {
        //extra -1 since we need to calculate data point of i+1 in the loop
        int file_size_ = vector_map_data_.data.size() - 2; 

        //Transform quaternion to euler angles
        double yaw_angle = tf::getYaw(goal_orientation)*(180.0/M_PI);

        //Check goal validity for the first goal
        //If it is within or close to the vector map and if the orientation is similar.
        if (goal_coordinates_.empty())
        {
            
            return ifInVectorMapp(x, y, file_size_, yaw_angle);
            
        }
        //Check the goal validity when there exist more than one goal.
        else 
        {

            //Distance between two consecutive goals
            double goal_distance = getDistance(goal_coordinates_.back().pose.position.x, x, goal_coordinates_.back().pose.position.y, y); 
            //yaw angle of previous goal
            double previous_yaw_angle = tf::getYaw(goal_coordinates_.back().pose.orientation)*(180.0/M_PI); 

            //Checking the distance and orientation between two consequtive goals. 
            //They can be some degrees apart from each other even though they are close to each other. 
            if (goal_distance > GOAL_DISTANCE_TOLERANCE_ || yaw_angle - previous_yaw_angle > ORIENTAION_TOLERANCE_)
            {
                return ifInVectorMapp(x, y, file_size_, yaw_angle);
            }
            else
            {
                ROS_INFO("Distance or orientation between current goal and previous goal is not large enough");
            }

        }        
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
        sub_goal_coordinates_ = nh_.subscribe<geometry_msgs::PoseStamped>("/adeye/goals", 1, &GoalSequencer::storeGoalCoordinatesCallback, this);
        sub_position_ = nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &GoalSequencer::positionCallback, this);
        sub_autoware_state_ = nh_.subscribe<geometry_msgs::TwistStamped>("/current_behavior", 1, &GoalSequencer::behaviorStateCallback, this);
        sub_autoware_global_plan_ = nh_.subscribe<autoware_msgs::LaneArray>("/lane_waypoints_array", 1, &GoalSequencer::autowareGlobalPlanCallback, this);
        sub_vector_map_ = nh_.subscribe<vector_map_msgs::PointArray>("/vector_map_info/point", 1, &GoalSequencer::vectorMapCallback, this);
        pub_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
        pub_update_local_planner_ = nh_.advertise<std_msgs::Int32>("/adeye/update_local_planner", 1, true);
        pub_clear_goal_list_bool_= nh_.advertise<std_msgs::Bool>("/adeye/clear_first_goal", 1, true);
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
                
                ROS_INFO("The first goal has been published. Position:- x = %lf, y = %lf, z = %lf", goal_coordinates_.front().pose.position.x, goal_coordinates_.front().pose.position.y, goal_coordinates_.front().pose.position.z);

                // Bool value reset to true for sending upcoming goals in the main run loop.
                received_first_goal_ = false;
            }
            
            // Condition for next (upcoming) goals
            // Publish the next goal when the car enters in end state (end state = 13.0) and condition for removing the previous goal and setting up the next goal 
            if (autoware_behavior_state_ == END_STATE_ && !has_global_planner_and_goal_been_reset_ && goal_coordinates_.size() >= MINIMUM_GOALS_)
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

                ROS_INFO("The next goal has been published. Position:- x = %lf, y = %lf, z = %lf", goal_coordinates_.front().pose.position.x, goal_coordinates_.front().pose.position.y, goal_coordinates_.front().pose.position.z);

                // Update the global planner boolean
                should_update_global_planner_ = true;
                
                // Update the planner and goal boolean for end state
                has_global_planner_and_goal_been_reset_ = true;
            }
            else if (autoware_behavior_state_ == FORWARD_STATE_) // The planner and goal boolean is set to false after publishing the goal and planner (forward state = 2.0)
            {
                has_global_planner_and_goal_been_reset_ = false;
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