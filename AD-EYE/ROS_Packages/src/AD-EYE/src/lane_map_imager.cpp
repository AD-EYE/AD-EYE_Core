#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/PoseStamped.h>
#include <cmath>

using namespace grid_map;

/*!
* Initiate LaneMapImager class which extracts "Lane" Layer from Grid Map
* Convert it into ROS image
* Publish real world map goal coordinates from ROS image through pixels coordinates
*/
class LaneMapImager
{
  private:
    ros::NodeHandle& nh_;
    ros::Subscriber map_extractor_;
    ros::Subscriber goal_pixels_;
    ros::Publisher pub_extract_image_;
    ros::Publisher pub_goal_position_;

    // ROS Rate
    ros::Rate rate_;

    // Grid Map
    GridMap grid_map_;
    double resolution_{};
    Position length_;
    Position position_;

    // ROS Image
    sensor_msgs::Image image_;

    // Goal Position Variable
    geometry_msgs::PoseStamped pose_stamped_;

    // Real World Coordinates //
    // Position Coordinates  //
    double x_position_world_coordinate_{}, y_position_world_coordinate_{}, z_position_world_coordinate_ = 0.0;
    // Orientation Coordinates, harcoded for now //
    double w_orientation_world_coordinate_ = 0.707, x_orientation_world_coordinate_ = 0.0,
           y_orientation_world_coordinate_ = 0.0, z_orientation_world_coordinate_ = 0.707;

    // Pixels Coordinates //
    double x_pixels_coordinate_{}, y_pixels_coordinate_{};

    // GridMap Coordinates //
    double x_gridmap_coordinate_{}, y_gridmap_coordinate_{};

    // Image Condition
    bool created_image_ = false;

    /*!
     * \brief GridMap Extractor Callback : Called when the grid map information has been received.
     * \param msg Message contains the grid map information.
     * \details Convert "Lanes" layer from the grid map information to
     * ROS sensor image, and also calculate map resolution and origin.
     */
    void gridMapExtractorCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        // Convert received message back to gridMap
        GridMapRosConverter::fromMessage(*msg, grid_map_);

        // Creates an image message from a grid map layer
        created_image_ = GridMapRosConverter::toImage(grid_map_, "Lanes", sensor_msgs::image_encodings::RGB8, image_);

        if (created_image_)
        {
            ROS_INFO("Sucessfully created an image");
        }
        else
        {
            ROS_WARN("The image creation is failed");
        }

        // Get Resolution and Origin
        resolution_ = grid_map_.getResolution();
        length_ = grid_map_.getLength();
        position_ = grid_map_.getPosition();

        ROS_INFO("Resolution = %f, X-Grid Length = %f and Y-Grid Length = %f", resolution_, length_.x(), length_.y());
    }

    /*!
     * \brief Goal Pixels Coordinates Callback : Called when the goal pixels coordinates are received from GUI by user.
     * \param msg Message contains the pixel coordinates.
     * \details Stores the pixels coordinates information, and
     * calculate the real world map goal coordinates.
     */
    void goalPixelsCoordinatesCallback(const std_msgs::Int16MultiArray::ConstPtr& msg)
    {
        // The image in GUI is rotated by 90 degree. For that, the pixels coordinates are rotated based on the x-y axis.
        x_pixels_coordinate_ = -msg->data.at(1);
        y_pixels_coordinate_ = -msg->data.at(0);

        // Take pixels coordinates and convert to gridmap coordinates and then change the gridmap origin side same as to
        // Real World Map
        x_gridmap_coordinate_ = length_.x() + (x_pixels_coordinate_ * resolution_);
        y_gridmap_coordinate_ = length_.y() + (y_pixels_coordinate_ * resolution_);

        // Convert pixels coordinates to the real world map goal coordinates
        double offset_x = position_.x() - (0.5 * length_.x());
        double offset_y = position_.y() - (0.5 * length_.y());
        x_position_world_coordinate_ = offset_x + x_gridmap_coordinate_;
        y_position_world_coordinate_ = offset_y + y_gridmap_coordinate_;

        // Position coordinates
        // Rounded values are used in order to reach at the exact position on the map.
        pose_stamped_.header.frame_id = "world";
        pose_stamped_.pose.position.x = round(x_position_world_coordinate_);
        pose_stamped_.pose.position.y = round(y_position_world_coordinate_);
        pose_stamped_.pose.position.z = z_position_world_coordinate_;

        // Orientation coordinates
        pose_stamped_.pose.orientation.x = x_orientation_world_coordinate_;
        pose_stamped_.pose.orientation.y = y_orientation_world_coordinate_;
        pose_stamped_.pose.orientation.z = z_orientation_world_coordinate_;
        pose_stamped_.pose.orientation.w = w_orientation_world_coordinate_;

        ROS_INFO("The real world map position coordinates:- x = %lf, y = %lf, z = %lf", pose_stamped_.pose.position.x,
                 pose_stamped_.pose.position.y, pose_stamped_.pose.position.z);

        // Publish the Real World Map Goal Coordinates
        pub_goal_position_.publish(pose_stamped_);
    }

  public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    explicit LaneMapImager(ros::NodeHandle& nh) : nh_(nh), rate_(20)
    {
        // Initialize node, publishers and subscribers
        map_extractor_ = nh.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1,
                                                              &LaneMapImager::gridMapExtractorCallback, this);
        pub_extract_image_ = nh.advertise<sensor_msgs::Image>("/lane_layer_image", 1, true);
        goal_pixels_ = nh.subscribe<std_msgs::Int16MultiArray>("/gui/goal_pixels", 1,
                                                               &LaneMapImager::goalPixelsCoordinatesCallback, this);
        pub_goal_position_ = nh.advertise<geometry_msgs::PoseStamped>("/adeye/goals", 1, true);
    }
    /*!
     * \brief The main function of the Node. Contains the main loop.
     * \brief Basically, publish the ROS image and update it when grid map position is changed.
     */
    void run()
    {
        double i = 0;
        // Publish the ROS Sensor Image through /lane_layer_image topic
        while (nh_.ok())
        {
            ros::spinOnce();
            // Publish the image after receiving the grid map data
            // Then publish the image only after changing the grid map position
            if (i != position_.x() && created_image_)
            {
                pub_extract_image_.publish(image_);
                ROS_INFO("Publishing Image");
                i = position_.x();
            }
            rate_.sleep();
        }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "LaneMapImager");
    ros::NodeHandle nh;
    LaneMapImager goal_map_node(nh);
    goal_map_node.run();
    return 0;
}