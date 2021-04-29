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
#include <cmath>



    /*!
     * Initiate GoalMapNode class which extracs "Lane" Layer from Grid Map
     * Convert it into ROS Image
     * Publish Real World Map goal coordiantes from ROS Image through Pixels coordinates
     */
class SequenceGoalNode
{

private:
    ros::NodeHandle &nh_;
    ros::Subscriber goal_coordinates_;
    ros::Subscriber sub_position_;
    ros::Publisher pub_goal_;

    // ROS Rate
    ros::Rate rate_;

    // Goal Position Variable
    geometry_msgs::PoseStamped pose_stamped_;

    // variables
    //Position
    float x_ego_;
    float y_ego_;

    //ROS Variables
    float rostime_;
    float frequency_ = 20; // this value should be alligned with the frequency value used in the GridMapCreator_node
    double sequence;

    // Real World Coordinates //
    // Positon Coordinates  //
    double x_world_coordinate_ = 0.0, y_world_coordinate_ = 0.0;

    // Goal Vector
    std::vector <double> sequence_goal_vector_x_;
    std::vector <double> sequence_goal_vector_y_;
    
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        // Received Goal Position Coordinates
        x_ego_ = msg -> pose.position.x;
        y_ego_ = msg -> pose.position.y;

    }
    /*!
     * \brief Store Goal Coordinates Callback : Called when the goal coordinates received from Image by USER.
     * \param msg The Goal Coordinates to the message from the topic.
     * \details Stores the Goal Coordinates information in the Vector, then
     * calculate and Publish the Real World Map Goal Coordinates.
     */
    void storeGoalCoordinatesCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        // Received Goal Position Coordinates
        x_world_coordinate_ = msg -> pose.position.x;
        y_world_coordinate_ = msg -> pose.position.y;
        sequence = msg -> header.seq;

        
        // Print the Goal Position Coordinates
        ROS_INFO("poseStamped x: %lf and y: %lf", x_world_coordinate_, y_world_coordinate_);

        // Store the Goal Position Coordinates into Vector
        sequence_goal_vector_x_.push_back(x_world_coordinate_);
        sequence_goal_vector_y_.push_back(y_world_coordinate_);

        // Print the Goal Positions Vector
        for (int i = 0; i < sequence_goal_vector_x_.size(); i++) 
        {
            ROS_INFO("The Goal Vector-x is %lf", sequence_goal_vector_x_[i]);
            ROS_INFO("The Goal Vector-y is %lf", sequence_goal_vector_y_[i]);
        } 
        

    }
    

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
public:
    SequenceGoalNode(ros::NodeHandle &nh) : nh_(nh), rate_(1)
    {
        // Initialize node, publishers and subscribers
        goal_coordinates_ = nh.subscribe<geometry_msgs::PoseStamped>("/goal", 1, &SequenceGoalNode::storeGoalCoordinatesCallback, this);
        sub_position_ = nh.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &SequenceGoalNode::positionCallback, this);
        pub_goal_ = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
    

        frequency_ = 20;
        rate_ = ros::Rate(frequency_);
        
        // publish Goals
        // Publish the Goals through /simple/goal topic
        while (nh_.ok())
        {
            ros::spinOnce();
            // Position Coordinates

            if (!sequence_goal_vector_x_.empty())
            {   
                
                if (sequence >=1)
                {
                    double distance = pow(pow(sequence_goal_vector_x_[0]- x_ego_,2) + pow(sequence_goal_vector_y_[0] - y_ego_,2),0.5);
                    ROS_INFO("Distance: %lf", distance);

                    if (distance <= 150)
                    {
                        ROS_INFO("The next goal-x is %lf",sequence_goal_vector_x_[0]);
                        // Position Coordinates
                        pose_stamped_.header.frame_id = "world2";
                        pose_stamped_.pose.position.x = round(sequence_goal_vector_x_[0]);
                        pose_stamped_.pose.position.y = round(sequence_goal_vector_y_[0]);
                        pose_stamped_.pose.position.z = 0.0;
                    
                        // Orientation Coordinates
                        pose_stamped_.pose.orientation.x = 0;
                        pose_stamped_.pose.orientation.y = 0;
                        pose_stamped_.pose.orientation.z = 0.707;
                        pose_stamped_.pose.orientation.w = 0.707;

                        ROS_INFO("poseStamped orientation: %lf, %lf, %lf",
                            pose_stamped_.pose.position.x, pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

                        // Publish the Real World Map Goal Coordinates         
                        pub_goal_.publish(pose_stamped_);
                        sequence_goal_vector_x_.erase (sequence_goal_vector_x_.begin());
                        sequence_goal_vector_y_.erase (sequence_goal_vector_y_.begin());
                    }

                    
                }else if (sequence == 0)
                {
                    ROS_INFO("The first goal-x is %lf",sequence_goal_vector_x_[0]);
                    // Position Coordinates
                    pose_stamped_.header.frame_id = "world2";
                    pose_stamped_.pose.position.x = round(sequence_goal_vector_x_[0]);
                    pose_stamped_.pose.position.y = round(sequence_goal_vector_y_[0]);
                    pose_stamped_.pose.position.z = 0.0;
                
                    // Orientation Coordinates
                    pose_stamped_.pose.orientation.x = 0;
                    pose_stamped_.pose.orientation.y = 0;
                    pose_stamped_.pose.orientation.z = 0.707;
                    pose_stamped_.pose.orientation.w = 0.707;

                    ROS_INFO("poseStamped orientation: %lf, %lf, %lf",
                        pose_stamped_.pose.position.x, pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

                    // Publish the Real World Map Goal Coordinates         
                    pub_goal_.publish(pose_stamped_);
                    sequence_goal_vector_x_.erase (sequence_goal_vector_x_.begin());
                    sequence_goal_vector_y_.erase (sequence_goal_vector_y_.begin());
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
    SequenceGoalNode exc(nh);
    ros::spin();
    return 0;
}