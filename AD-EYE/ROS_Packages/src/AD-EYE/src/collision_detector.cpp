#include <ros/ros.h>
#include <ros/this_node.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Bool.h>

#include <cpp_utils/pose_datatypes.h>

#include <std_msgs/ColorRGBA.h>  //Used for ego footprint visualization

/*!
  \brief A node that detect collision with other objects using the SSMP_gridMap
  \details Output a message when collision occurs and also output the car position and speed.\n
  Currently it only supports collision detection for dynamic objects and only print the speed of the car.
  \todo
    - Get the car footprint dimensions from a message (not hardcoded values)
    - Static Object collision
    - For dynamic object : Output both speed of the car and the object.
                                And calculate the collision speed.
 */
class CollisionDetector
{
  private:
    // node, publishers and subscribers
    ros::NodeHandle& nh_;
    ros::Subscriber sub_footprint_;
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_velocity_;
    ros::Subscriber sub_gridmap_;
    ros::Publisher pub_collision_;

    // ros::Publisher pubArea;  //Used for ego footprint visualization

    // Ego footprint
    const float car_length_ = 5;  // These values should be calculated or taken from a
    const float car_width_ = 2;   // msg, not hardcoded.

    const float cog_offset_ = 1.69;  // Offset between the gnss ego_pose_ and the center of the car
    grid_map::Polygon ego_footprint_;

    // variables
    geometry_msgs::Pose ego_pose_;
    geometry_msgs::TwistStamped ego_velocity_;
    bool gnss_flag_;
    bool gridmap_flag_;
    grid_map::GridMap gridmap_;  //({"StaticObjects", "DrivableAreas", "DynamicObjects", "Lanes"});
    //! Used to determine the type of the collision
    enum class CollisionType
    {
        None,
        staticObject,
        dynamicObject
    };

  public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    CollisionDetector(ros::NodeHandle& nh) : nh_(nh)
    {
        // Initialize the node, publishers and subscribers
        // pubArea = nh_.advertise<visualization_msgs::Marker>("/collision_ego_footprint", 1, true);  //Used for ego
        // footprint visualization
        pub_collision_ = nh_.advertise<std_msgs::Bool>("/collision", 10);
        sub_gnss_ =
            nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &CollisionDetector::gnssCallback, this);
        sub_velocity_ = nh_.subscribe<geometry_msgs::TwistStamped>("/current_velocity", 10,
                                                                   &CollisionDetector::velocityCallback, this);

        sub_gridmap_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1,
                                                             &CollisionDetector::gridmapCallback, this);

        // Initialize the flags
        gnss_flag_ = false;
        gridmap_flag_ = false;
    }

    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& gnss)
    {
        ego_pose_ = gnss->pose;
        gnss_flag_ = true;
    }

    void velocityCallback(const geometry_msgs::TwistStamped::ConstPtr& vel)
    {
        ego_velocity_ = *vel;
    }

    /*!
     * \brief Gridmap Callback : Called when the gridmap_ information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the gridmap_ information.
     */
    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        grid_map::GridMapRosConverter::fromMessage(*msg, gridmap_);
        gridmap_flag_ = true;
    }

    /*!
     * \brief Check for collision using the SSMP_gridMap
     * \param gridmap The gridMap to look in
     * \param pose The position of the car
     * \return A CollisionType enum member, regarding the type of collision (None if no collision)
     */
    CollisionType checkCollision(const grid_map::GridMap& gridmap, const geometry_msgs::Pose& pose)
    {
        const float x = pose.position.x;
        const float y = pose.position.y;
        const float a = cpp_utils::extract_yaw(pose.orientation);

        const grid_map::Position center(x + cog_offset_ * cos(a) / 2, y + cog_offset_ * sin(a) / 2);

        ego_footprint_.removeVertices();
        const grid_map::Position point1(center.x() + (cos(a) * car_length_ - sin(a) * car_width_) / 2,
                                        center.y() + (sin(a) * car_length_ + cos(a) * car_width_) / 2);
        const grid_map::Position point2(point1.x() + sin(a) * car_width_, point1.y() - cos(a) * car_width_);
        const grid_map::Position point3(point2.x() - cos(a) * car_length_, point2.y() - sin(a) * car_length_);
        const grid_map::Position point4(point1.x() - cos(a) * car_length_, point1.y() - sin(a) * car_length_);

        ego_footprint_.addVertex(point1);
        ego_footprint_.addVertex(point2);
        ego_footprint_.addVertex(point3);
        ego_footprint_.addVertex(point4);

        /*visualization_msgs::Marker ca_visu;  //Used for ego footprint visualization
        std_msgs::ColorRGBA color;
        color.r = 1.0;
        color.a = 1.0;
        grid_map::PolygonRosConverter::toLineMarker(ego_footprint_, color, 0.2, 0.5, ca_visu);
        ca_visu.header.frame_id = gridmap_.getFrameId();
        ca_visu.header.stamp.fromNSec(gridmap_.getTimestamp());
        pubArea.publish(ca_visu); */

        for (grid_map::PolygonIterator areaIt(gridmap, ego_footprint_); !areaIt.isPastEnd(); ++areaIt)
        {
            if (gridmap.at("DynamicObjects", *areaIt) > 0)
            {  // If there is something inside the area
                return CollisionType::dynamicObject;
            }
        }

        return CollisionType::None;
    }

    /*!
     * \brief The main loop of the Node
     * \details Basically checks for topics updates, then evaluate
     * the situation and triggers (or not) the safety switch depending of
     * the situation evaluation.
     */
    void run()
    {
        CollisionType collision = CollisionType::None;
        std_msgs::Bool collision_state;
        ros::Rate rate(20);
        ROS_INFO("Collision detector started !");
        while (nh_.ok())
        {
            collision_state.data = false;
            ros::spinOnce();

            if (gridmap_flag_ && gnss_flag_)
            {
                // Collision detection
                collision = checkCollision(gridmap_, ego_pose_);
                if (collision != CollisionType::None)
                {
                    std::stringstream msg;
                    std::string type;
                    if (collision == CollisionType::dynamicObject)
                    {
                        type = "Static";
                    }
                    else if (collision == CollisionType::staticObject)
                    {
                        type = "Dynamic";
                    }
                    msg << "Collision detected ! [" << type << " Object]\n";
                    msg << "Position (x,y) = (" << ego_pose_.position.x << ", " << ego_pose_.position.y << ")\n";
                    msg << "Car Velocity   = " << ego_velocity_.twist.linear.x;

                    ROS_WARN_STREAM_THROTTLE(1, msg.str());
                    collision_state.data = true;
                }
            }
            pub_collision_.publish(collision_state);

            rate.sleep();
        }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "CollisionDetector");
    ros::NodeHandle nh;
    CollisionDetector CollisionDetector(nh);
    CollisionDetector.run();
    return 0;
}
