#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>
#include <autoware_msgs/Lane.h>

#include <cpp_utils/pose_datatypes.h>

#include <visualization_msgs/Marker.h> //Used for critical area visualization
#include <std_msgs/ColorRGBA.h>        //Used for critical area visualization

//using namespace grid_map;

/*!
 * \brief The Safety Supervisor supervise the automated driving.
 * \details His goal is to trigger the switch that decides if the vehicle
 * listen to the DDT given by the nominal chanel or by the safety channel.
 */
class SafetySupervisor
{
private:
    // node, publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pubSwitch;
    ros::Subscriber subGnss;
    ros::Subscriber subGridmap;
    ros::Subscriber subAutowareTrajectory;

    //ros::Publisher pubArea;  //Used for critical area visualization

    // constants
    bool SAFE = 0;
    bool UNSAFE = 1;
    //Critical area
    const float car_length = 5;
    const float car_width = 2;
    const float critArea_length = 2.5 * car_length; //Size of the critical Area
    const float critArea_width = car_width * 1.6;
    grid_map::Polygon critArea;
    const float pi = 3.141592654;

    // variables
    geometry_msgs::Pose pose;
    bool state;
    bool gnss_flag;
    bool gridmap_flag;
    bool autowareTrajectory_flag;
    std_msgs::Int32 msg;
    //grid_map_msgs::GridMap gridmap;
    grid_map::GridMap gridmap; //({"StaticObjects", "DrivableAreas", "DynamicObjects", "Lanes"});
    autoware_msgs::Lane autowareTrajectory;

public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    SafetySupervisor(ros::NodeHandle &nh) : nh_(nh)
    {
        // Initialize the node, publishers and subscribers
        pubSwitch = nh_.advertise<std_msgs::Int32>("/switchCommand", 1, true);

        subGnss = nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &SafetySupervisor::gnss_callback, this);
        subGridmap = nh_.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &SafetySupervisor::gridmap_callback, this);
        subAutowareTrajectory = nh_.subscribe<autoware_msgs::Lane>("/final_waypoints", 1, &SafetySupervisor::autowareTrajectory_callback, this);

        //pubArea = nh_.advertise<visualization_msgs::Marker>("/critArea", 1, true);  //Used for critical area visualization

        // Initialize the variables
        state = SAFE;

        // Initialize the flags
        gnss_flag = 0;
        gridmap_flag = 0;
        //rate(float 20);

    }

    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnss_callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        geometry_msgs::PoseStamped gnss = *msg;
        pose = gnss.pose;
        gnss_flag = 1;
    }

    /*!
     * \brief Gridmap Callback : Called when the gridmap information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the gridmap information.
     */
    void gridmap_callback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        grid_map::GridMapRosConverter::fromMessage(*msg, gridmap);
        //gridmap = *msg;
        gridmap_flag = 1;
    }

    /*!
     * \brief Autoware trajectory Callback : Called when the autoware trajectory information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the autoware trajectory information.
     */
    void autowareTrajectory_callback(const autoware_msgs::Lane::ConstPtr& msg)
    {
        autowareTrajectory = *msg;
        //for (int i = 0; i < autowareTrajectory.waypoints.size(); i++)
        //{
        //  ROS_INFO("%f", autowareTrajectory.waypoints[0].pose.pose.position.x);
        //}
        autowareTrajectory_flag = 1;
    }

    /*!
     * \brief The main loop of the Node
     * \details Basically checks for topics updates, then evaluate
     * the situation and triggers (or not) the safety switch depending of
     * the situation evaluation.
     */
    void run()
    {
        ros::Rate rate(20);
        while(nh_.ok())
        {
            ros::spinOnce();
            if(gnss_flag == 1 && gridmap_flag == 1)
            {
                evaluate();
                publish();
            }
            rate.sleep();
            //ROS_INFO("Current state: %d", state);
        }
    }

    /*!
     * \brief It is in this function that the switch
     * is trigerred or not.
     */
    void publish()
    {
        msg.data = state;
        pubSwitch.publish(msg);
    }

    /*!
     * \brief The function where the situation is evaluated.
     * \details The situation is evaluated and the state of the vehicle is
     * declared safe or unsafe.
     */
    void evaluate()
    {
        //Is the center of the car inside the road
        state = SAFE;
        float current_lane_id = gridmap.atPosition("Lanes", grid_map::Position(pose.position.x, pose.position.y));
        //ROS_INFO("Lane ID : %f", current_lane_id);
        if (current_lane_id == 0) {
            ROS_WARN_THROTTLE(1, "The center of the car is not inside the road");
            state = UNSAFE;
            return;
        }

        //Is there a dynamic object in the critical area
        const float x = pose.position.x;    //Center is currently in the fron of the car
        const float y = pose.position.y;
        const float a = cpp_utils::extract_yaw(pose.orientation);// * pi;
        const grid_map::Position center(x + car_length * cos(a)/2, y + car_length * sin(a)/2);

        critArea.removeVertices();
        const grid_map::Position point1(center.x() + (cos(a) * critArea_length - sin(a) * critArea_width)/2,
                                        center.y() + (sin(a) * critArea_length + cos(a) * critArea_width)/2);
        const grid_map::Position point2(point1.x() + sin(a) * critArea_width, point1.y() - cos(a) * critArea_width);
        const grid_map::Position point3(point2.x() - cos(a) * critArea_length, point2.y() - sin(a) * critArea_length);
        const grid_map::Position point4(point1.x() - cos(a) * critArea_length, point1.y() - sin(a) * critArea_length);
        /*critArea.addVertex(grid_map::Position(center.x() + (cos(a) * critArea_length - sin(a) * critArea_width)/2,
                                        center.y() + (sin(a) * critArea_length + cos(a) * critArea_width)/2));
        critArea.addVertex(grid_map::Position(critArea.getVertex(0).x() + sin(a) * critArea_width,
                    critArea.getVertex(0).y() + cos(a) * critArea_width));
        critArea.addVertex(grid_map::Position(critArea.getVertex(1).x() - cos(a) * critArea_length,
                    critArea.getVertex(1).y() - sin(a) * critArea_length));
        critArea.addVertex(grid_map::Position(critArea.getVertex(0).x() - cos(a) * critArea_length,
                    critArea.getVertex(0).y() - sin(a) * critArea_length));*/
        critArea.addVertex(point1);
        critArea.addVertex(point2);
        critArea.addVertex(point3);
        critArea.addVertex(point4);

        /*visualization_msgs::Marker ca_visu;  //Used for critical area visualization
        std_msgs::ColorRGBA color;
        color.r = 1.0;
        color.a = 1.0;
        grid_map::PolygonRosConverter::toLineMarker(critArea, color, 0.2, 0.5, ca_visu);
        ca_visu.header.frame_id = gridmap.getFrameId();
        ca_visu.header.stamp.fromNSec(gridmap.getTimestamp());
        pubArea.publish(ca_visu);*/

        for(grid_map::PolygonIterator areaIt(gridmap, critArea) ; !areaIt.isPastEnd() ; ++areaIt) {
            if(gridmap.at("DynamicObjects", *areaIt) > 0) { //If there is something inside the area
                ROS_WARN_THROTTLE(1, "There is a dynamic object in the critical Area !");
                state = UNSAFE;
                return;
            }
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "safetySupervisor");
    ros::NodeHandle nh;
    SafetySupervisor safetySupervisor(nh);
    safetySupervisor.run();
    return 0;
}
