
#include <ros/ros.h>
#include <vector>
#include <std_msgs/Int16MultiArray.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Int32.h>
#include <cmath>



/*!
* Initiate SequenceGoalNode class which stores all goals from the adeye goals, goal_map_node
* Store them into the vector
* Publish the real world map goal coordiantes one by one to autoware when the vehicle is viccinity of the goal position
*/
class SequenceGoalNode
{
private:
    ros::NodeHandle &nh_;
    ros::Subscriber goal_coordinates_;
    ros::Subscriber sub_position_;
    ros::Publisher pub_goal_;
    ros::Publisher update_local_planner_;

    // ROS rate
    ros::Rate rate_;

    // Goal position variable
    geometry_msgs::PoseStamped pose_stamped_;

    //Vehicle position
    float x_ego_;
    float y_ego_;

    //Goal sequence variables
    double sequence_;

    // Real world coordinates
    // Positon coordinates
    double x_world_position_coordinate_ = 0.0, y_world_position_coordinate_ = 0.0, z_world_position_coordinate_ ;

    // Orientation coordinates
    double x_world_orientation_coordinate_, y_world_orientation_coordinate_, z_world_orientation_coordinate_, w_world_orientation_coordinate_;

    // Goal vector
    std::vector <double> sequence_goal_vector_x_;
    std::vector <double> sequence_goal_vector_y_;
    std::vector <double> sequence_goal_number_;

    // Local planner
    std_msgs::Int32 local_planner_;
    
    /*!
     * \brief Position Callback : Continously called to watch the vehicle position in the map.
     * \param msg Message contain the vehicle position coordinates.
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
     * \param msg Message contain the goal position coordinates.
     * \details Stores the goal coordinates information in the vector.
     */
    void storeGoalCoordinatesCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        // Received goal position coordinates and sequence number
        x_world_position_coordinate_ = msg -> pose.position.x;
        y_world_position_coordinate_ = msg -> pose.position.y;
        z_world_position_coordinate_ = msg -> pose.position.z;

        x_world_orientation_coordinate_ = msg -> pose.orientation.x;
        y_world_orientation_coordinate_ = msg -> pose.orientation.y;
        z_world_orientation_coordinate_ = msg -> pose.orientation.z;
        w_world_orientation_coordinate_ = msg -> pose.orientation.w;

        sequence_ = msg -> header.seq;

        // Store the goal position coordinates into the vector
        sequence_goal_vector_x_.push_back(x_world_position_coordinate_);
        sequence_goal_vector_y_.push_back(y_world_position_coordinate_);
        sequence_goal_number_.push_back(sequence_);

        // Print the goal positions vector
        for (int i = 0; i < sequence_goal_vector_x_.size(); i++) 
        {
            ROS_INFO("The Goal Vector-x is %lf", sequence_goal_vector_x_[i]);
            ROS_INFO("The Goal Vector-y is %lf", sequence_goal_vector_y_[i]);
        }     
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
        goal_coordinates_ = nh.subscribe<geometry_msgs::PoseStamped>("/goal", 1, &SequenceGoalNode::storeGoalCoordinatesCallback, this);
        sub_position_ = nh.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &SequenceGoalNode::positionCallback, this);
        pub_goal_ = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
        update_local_planner_ = nh.advertise<std_msgs::Int32>("/adeye/updateLocalPlanner", 1, true);

    }   

    void run() 
    {
        // Publish the goals coordinates
        while (nh_.ok())
        {
            ros::spinOnce();

            if (!sequence_goal_vector_x_.empty())
            {   
                if (sequence_goal_number_[0] >= 0 )
                {
                    ROS_INFO("The next goal-x = %lf, y = %lf",sequence_goal_vector_x_[0], sequence_goal_vector_y_[0]);
                    
                    // Position coordinates
                    pose_stamped_.header.frame_id = "world";
                    pose_stamped_.pose.position.x = round(sequence_goal_vector_x_[0]);
                    pose_stamped_.pose.position.y = round(sequence_goal_vector_y_[0]);
                    pose_stamped_.pose.position.z = z_world_position_coordinate_;
                
                    // Orientation coordinates
                    pose_stamped_.pose.orientation.x = x_world_orientation_coordinate_;
                    pose_stamped_.pose.orientation.y = y_world_orientation_coordinate_;
                    pose_stamped_.pose.orientation.z = z_world_orientation_coordinate_;
                    pose_stamped_.pose.orientation.w = w_world_orientation_coordinate_;

                    ROS_INFO("The real world map position goal coordinates:- x = %lf, y = %lf, z = %lf",
                        pose_stamped_.pose.position.x, pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

                    // Publish the real world map goal coordinates         
                    pub_goal_.publish(pose_stamped_);

                    // Update the local planner for the next goal
                    if (sequence_goal_number_[0] >= 1) {
                        local_planner_.data = 1;
                        update_local_planner_.publish(local_planner_);
                    }

                    while(nh_.ok()) {
                        // Calculate toal distance from the vehicle position to goal
                        double distance = pow(pow(sequence_goal_vector_x_[0]- x_ego_,2) + pow(sequence_goal_vector_y_[0] - y_ego_,2),0.5);
                        ROS_INFO("Destination distance: %lf", distance);
                        ros::spinOnce();
                        rate_.sleep();
                        
                        // Wait until the vehicle is near to the goal position (30 meters), and then publish the next goal and update the local planner.
                        if (distance <= 30){
                            break;
                        }
                    }

                    // Erase the previous goal coordinates
                    sequence_goal_vector_x_.erase (sequence_goal_vector_x_.begin());
                    sequence_goal_vector_y_.erase (sequence_goal_vector_y_.begin());
                    sequence_goal_number_.erase(sequence_goal_number_.begin());
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