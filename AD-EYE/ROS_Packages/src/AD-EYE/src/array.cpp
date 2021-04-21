#include "ros/ros.h"
#include "std_msgs/Int16MultiArray.h"
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <geometry_msgs/PoseStamped.h>
 


using namespace grid_map;
// Initiate GridMapExtractor class which extracs "Lane" Layer from Grid Map.
class GridMapExtractor 
{

private:
    ros::NodeHandle& nh_;
    ros::Subscriber map_extractor_;
    ros::Subscriber goal_pixels_;
    ros::Publisher pub_extract_image_;
    ros::Publisher goal_position_;

    ros::Rate rate_;
    
    // Map
    GridMap grid_map_;
    
    // Image
    sensor_msgs::Image image_;
    
    // Goal Position Variable
    geometry_msgs::PoseStamped poseStamped;
    
    //Variables
    float rostime_;
    float frequency_ = 20; // this value should be alligned with the frequency value used in the GridMapCreator_node
    double x=249.0, y=136.0, z=0.0, W=0.707, X=0.0, Y=0.0,Z=0.707;
    
    
    void goalcoordinatescallback(const std_msgs::Int16MultiArray::ConstPtr& msg)
    {
         ROS_INFO("I heard: [%d],[%d]", msg->data.at(0),msg->data.at(1));
    }
    
    void mapExtractorCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        
        // Convert received message back to gridMap
        GridMapRosConverter::fromMessage(*msg, grid_map_); 

        // Creates an image message from a grid map layer
        bool create_image_ = GridMapRosConverter::toImage(grid_map_, "Lanes", sensor_msgs::image_encodings::RGB8, image_);

        ROS_INFO("Sucessfully create an image : %s", create_image_?"true":"false");
    }

    

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
public:
    GridMapExtractor(ros::NodeHandle &nh) : nh_(nh), rate_(1)
    {
        // Initialize node, publishers and subscribers
        goal_pixels_ = nh.subscribe<std_msgs::Int16MultiArray>("/goal_pixels", 1,	&GridMapExtractor::goalcoordinatescallback, 	this);
        map_extractor_ = nh.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &GridMapExtractor::mapExtractorCallback, this);
        pub_extract_image_ = nh.advertise<sensor_msgs::Image>("/lane_layer_image", 1, true);
        goal_position_ = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);

        
        // Set the goal position //
        poseStamped.header.seq = 1;
        poseStamped.header.frame_id = "world";
        poseStamped.pose.position.x = x;
        poseStamped.pose.position.y = y;
        poseStamped.pose.position.z = z;

        poseStamped.pose.orientation.x = X;
        poseStamped.pose.orientation.y = Y;
        poseStamped.pose.orientation.z = Z;
        poseStamped.pose.orientation.w = W;

        ROS_INFO("poseStamped orientation: %lf, %lf, %lf",
    		poseStamped.pose.position.x,poseStamped.pose.position.y,poseStamped.pose.position.z);

        goal_position_.publish(poseStamped);


         while (nh_.ok()) 
        {
            rostime_ = ros::Time::now().toSec();
            pub_extract_image_.publish(image_);
            ROS_INFO("Publishing Image");

            //Time control
            rostime_ = ros::Time::now().toSec() - rostime_;
            if(rostime_ > 1/frequency_){
                ROS_WARN("Flatening Node : Frequency is not met!");
            }

            ros::spinOnce();
            rate_.sleep();
        }
    }
};

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "Array_sub");
    ros::NodeHandle nh;
    GridMapExtractor exc(nh);
    ros::spin();
    return 0;
}