#include "ros/ros.h"
#include "std_msgs/Int16MultiArray.h"
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <cpp_utils/pose_datatypes.h>

using namespace grid_map;

/*!
     * Initiate GridMapExtractor class which extracs "Lane" Layer from Grid Map
     * Convert it into Image
     * Publish Real World Map goal coordiantes from Image through Pixels coordinates
     */
class GridMapExtractor
{

private:
    ros::NodeHandle &nh_;
    ros::Subscriber map_extractor_;
    ros::Subscriber goal_pixels_;
    ros::Publisher pub_extract_image_;
    ros::Publisher goal_position_;
    ros::Subscriber sub_position_ego_;

    ros::Rate rate_;
    

    //Car informations
    float x_ego_ = 0;
    float y_ego_ = 0;
    float yaw_ego_ = 0;

    // Grid Map
    GridMap grid_map_;
    double resolution_;
    Position origin_;

    // ROS Image
    sensor_msgs::Image image_;

    // Goal Position Variable
    geometry_msgs::PoseStamped pose_stamped_;

    //ROS Variables
    float rostime_;
    float frequency_ = 20; // this value should be alligned with the frequency value used in the GridMapCreator_node

    // Real World Coordinates //
    // Positon Coordinates  //
    double x_world_coordinate_, y_world_coordinate_, z_world_coordinate_ = 0.0;
    // Orientation Coordinates //
    double W_world_coordinate_ = 0.707, X_world_coordinate_ = 0.0, Y_world_coordinate_ = 0.0, Z_world_coordinate_ = 0.707;

    // Pixels Coordinates //
    double x_pixels_coordinate_, y_pixels_coordinate_;

    
    /*!
     * \brief GridMap Extractor Callback : Called when the grid map information has received.
     * \param msg The GridMap information to the message from the topic.
     * \details Convert "Lanes" layer from the GridMap information given by the GridMapCreator, to
     * ROS Sensor Image and also calculate Resolution and Origin.
     */
    void mapExtractorCallback(const grid_map_msgs::GridMap::ConstPtr &msg)
    {

        // Convert received message back to gridMap
        GridMapRosConverter::fromMessage(*msg, grid_map_);

        // Creates an image message from a grid map layer
        bool create_image = GridMapRosConverter::toImage(grid_map_, "Lanes", sensor_msgs::image_encodings::RGB8, image_);

        ROS_INFO("Sucessfully create an image : %s", create_image_ ? "true" : "false");

        // Get Resolution and Origin
        resolution_ = grid_map_.getResolution();
        origin_ = grid_map_.getLength() ;

        ROS_INFO("Resolution %f , X-Grid Position %f and Y-Grid Position %f", resolution_, origin_.x(), origin_.y());

        
    }
    
    /*!
     * \brief Goal Pixels Coordinates Callback : Called when the goal pixels coordinates received from Image by USER.
     * \param msg The Pixels Coordinates to the message from the topic.
     * \details Stores the Pixels Coordinates information given by the GUI and USER, then
     * calculate and Publish the Real World Map Goal Coordinates.
     */
    void goalPixlesCoordinatesCallback(const std_msgs::Int16MultiArray::ConstPtr &msg)
    {
        ROS_INFO("I heard Pixles Coordinates: [%d],[%d]", msg->data.at(0), msg->data.at(1));
        x_pixels_coordinate_ = msg->data.at(0);
        y_pixels_coordinate_ = msg->data.at(1);

        // Convert Pixes Coordinates to Real World Map Goal Coordinates
        x_world_coordinate_ = origin_.x() + x_pixels_coordinate_ * resolution_;
        y_world_coordinate_ = origin_.y() + y_pixels_coordinate_ * resolution_;

        
        // Position Coordinates
        pose_stamped_.header.frame_id = "world";
        pose_stamped_.pose.position.x = x_world_coordinate_;
        pose_stamped_.pose.position.y = y_world_coordinate_;
        pose_stamped_.pose.position.z = z_world_coordinate_;
        
        // Orientation Coordinates
        pose_stamped_.pose.orientation.x = X_world_coordinate_;
        pose_stamped_.pose.orientation.y = Y_world_coordinate_;
        pose_stamped_.pose.orientation.z = Z_world_coordinate_;
        pose_stamped_.pose.orientation.w = W_world_coordinate_;

        ROS_INFO("poseStamped orientation: %lf, %lf, %lf",
                 pose_stamped_.pose.position.x, pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

        // Publish the Real World Map Goal Coordinates         
        goal_position_.publish(pose_stamped_);

    }

    void positionEgoCallback(const nav_msgs::Odometry::ConstPtr& msg) 
    {
        x_ego_ = msg->pose.pose.position.x;
        y_ego_ = msg->pose.pose.position.y;
        yaw_ego_ = cpp_utils::extract_yaw(msg->pose.pose.orientation);

        ROS_INFO("x = %f and y = %f",x_ego_,y_ego_);
    }

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
public:
    GridMapExtractor(ros::NodeHandle &nh) : nh_(nh), rate_(1)
    {
        //ros::SubscriberStatusCallback connect_cb    = boost::bind(&GridMapExtractor::goalPixlesCoordinatesCallback, this);
        // Initialize node, publishers and subscribers
        map_extractor_ = nh.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &GridMapExtractor::mapExtractorCallback, this);
        pub_extract_image_ = nh.advertise<sensor_msgs::Image>("/lane_layer_image", 1, true);
        goal_pixels_ = nh.subscribe<std_msgs::Int16MultiArray>("//gui/goal_pixels", 1, &GridMapExtractor::goalPixlesCoordinatesCallback, this);
        goal_position_ = nh.advertise<geometry_msgs::PoseStamped>("/real_map_goal_coordinates", 1, true); //move_base_simple/goal
        sub_position_ego_ = nh.subscribe<nav_msgs::Odometry>("/vehicle/odom", 100, &GridMapExtractor::positionEgoCallback, this);

        frequency_ = 20;
        rate_ = ros::Rate(frequency_);
        
        // publish Image
        // Publish the ROS Sensor Image through /lane_layer_image topic
        while (nh_.ok())
        {
            ros::spinOnce();
            rostime_ = ros::Time::now().toSec();
            pub_extract_image_.publish(image_);
            ROS_INFO("Publishing Image");

            //Time control
            rostime_ = ros::Time::now().toSec() - rostime_;
            if (rostime_ > 1 / frequency_)
            {
                ROS_WARN("Flatening Node : Frequency is not met!");
            }

            rate_.sleep();
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "GridMapExtractor");
    ros::NodeHandle nh;
    GridMapExtractor exc(nh);
    return 0;
}