#include <ros/ros.h>
#include <ros/master.h>
#include <ros/this_node.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Bool.h>

#include <cpp_utils/pose_datatypes.h>

#include <visualization_msgs/Marker.h> //Used for ego footprint visualization
#include <std_msgs/ColorRGBA.h>        //Used for ego footprint visualization

/*!
  \brief A node that detect collision with other objects using the SSMP_gridMap
  \details Output a message when collision occurs and also output the car position and speed.
  Currently it only supports collision detection for dynamic objects and only print the speed of the car.
  TODO:
    - Get the car footprint dimensions from a message (not hardcoded values)
    - Static Object collision
    - For dynamic object : Output both speed of the car and the object.
                                And calculate the collision speed.
 */
class CollisionDetector
{
private:
    // node, publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Subscriber subFootprint;
    ros::Subscriber subGnss;
    ros::Subscriber subVelocity;
    ros::Subscriber subGridmap;
    ros::Publisher pubCollision;

    //ros::Publisher pubArea;  //Used for ego footprint visualization

    //Ego footprint
    const float car_length = 5; // These values should be calculated or taken from a
    const float car_width = 2;  // msg, not hardcoded.

    const float cog_offset = 1.69; // Offset between the gnss pose and the center of the car
    grid_map::Polygon egoFootprint;

    // variables
    geometry_msgs::Pose pose;
    geometry_msgs::TwistStamped velocity;
    bool gnss_flag;
    bool gridmap_flag;
    grid_map::GridMap gridmap; //({"StaticObjects", "DrivableAreas", "DynamicObjects", "Lanes"});
    //! Used to determine the type of the collision
    enum class collisionType {None, staticObject, dynamicObject};


public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    CollisionDetector(ros::NodeHandle &nh) : nh_(nh)
    {
        // Initialize the node, publishers and subscribers
        //pubArea = nh_.advertise<visualization_msgs::Marker>("/collision_ego_footprint", 1, true);  //Used for ego footprint visualization
        pubCollision = nh_.advertise<std_msgs::Bool>("/collision", 10);
        subGnss = nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &CollisionDetector::gnss_callback, this);
        subVelocity = nh_.subscribe<geometry_msgs::TwistStamped>("/current_velocity", 10, &CollisionDetector::velocity_callback, this);

        subGridmap = nh_.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &CollisionDetector::gridmap_callback, this);

        // Initialize the flags
        gnss_flag = 0;
        gridmap_flag = 0;

    }

    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnss_callback(const geometry_msgs::PoseStamped::ConstPtr& gnss)
    {
        pose = gnss->pose;
        gnss_flag = true;
    }

    void velocity_callback(const geometry_msgs::TwistStamped::ConstPtr& vel) {
        velocity = *vel;
    }

    /*!
     * \brief Gridmap Callback : Called when the gridmap information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the gridmap information.
     */
    void gridmap_callback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        grid_map::GridMapRosConverter::fromMessage(*msg, gridmap);
        gridmap_flag = true;
    }


    /*!
     * \brief Check for collision using the SSMP_gridMap
     * \param gridmap The gridMap to look in
     * \param pose The position of the car
     * \return A collisionType enum member, regarding the type of collision (None if no collision)
     */
    collisionType checkCollision(const grid_map::GridMap& gridmap, const geometry_msgs::Pose& pose)
    {
        const float x = pose.position.x;
        const float y = pose.position.y;
        const float a = cpp_utils::extract_yaw(pose.orientation);

        const grid_map::Position center(x + cog_offset * cos(a)/2, y + cog_offset * sin(a)/2);

        egoFootprint.removeVertices();
        const grid_map::Position point1(center.x() + (cos(a) * car_length - sin(a) * car_width)/2,
                                        center.y() + (sin(a) * car_length + cos(a) * car_width)/2);
        const grid_map::Position point2(point1.x() + sin(a) * car_width, point1.y() - cos(a) * car_width);
        const grid_map::Position point3(point2.x() - cos(a) * car_length, point2.y() - sin(a) * car_length);
        const grid_map::Position point4(point1.x() - cos(a) * car_length, point1.y() - sin(a) * car_length);

        egoFootprint.addVertex(point1);
        egoFootprint.addVertex(point2);
        egoFootprint.addVertex(point3);
        egoFootprint.addVertex(point4);

        /*visualization_msgs::Marker ca_visu;  //Used for ego footprint visualization
        std_msgs::ColorRGBA color;
        color.r = 1.0;
        color.a = 1.0;
        grid_map::PolygonRosConverter::toLineMarker(egoFootprint, color, 0.2, 0.5, ca_visu);
        ca_visu.header.frame_id = gridmap.getFrameId();
        ca_visu.header.stamp.fromNSec(gridmap.getTimestamp());
        pubArea.publish(ca_visu); */

        for(grid_map::PolygonIterator areaIt(gridmap, egoFootprint) ; !areaIt.isPastEnd() ; ++areaIt) {
            if(gridmap.at("DynamicObjects", *areaIt) > 0) { //If there is something inside the area
                return collisionType::dynamicObject;
            }
        }

        return collisionType::None;
    }


    /*!
     * \brief The main loop of the Node
     * \details Basically checks for topics updates, then evaluate
     * the situation and triggers (or not) the safety switch depending of
     * the situation evaluation.
     */
    void run()
    {
        collisionType collision = collisionType::None;
        std_msgs::Bool collisionState;
        ros::Rate rate(20);
        ROS_INFO("Collision detector started !");
        while(nh_.ok())
        {
            collisionState.data = false;
            ros::spinOnce();

            if(gridmap_flag && gnss_flag)
            {
                // Collision detection
                collision = checkCollision(gridmap, pose);
                if(collision != collisionType::None) {
                    std::stringstream msg;
                    std::string type;
                    if(collision == collisionType::dynamicObject) {
                        type = "Static";
                    } else if (collision == collisionType::staticObject) {
                        type = "Dynamic";
                    }
                    msg << "Collision detected ! [" << type << " Object]\n";
                    msg << "Position (x,y) = (" << pose.position.x << ", " << pose.position.y << ")\n";
                    msg << "Car Velocity   = " << velocity.twist.linear.x;

                    ROS_WARN_STREAM_THROTTLE(1, msg.str());
                    collisionState.data = true;
                }
            }
            pubCollision.publish(collisionState);

            rate.sleep();
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "CollisionDetector");
    ros::NodeHandle nh;
    CollisionDetector CollisionDetector(nh);
    CollisionDetector.run();
    return 0;
}
