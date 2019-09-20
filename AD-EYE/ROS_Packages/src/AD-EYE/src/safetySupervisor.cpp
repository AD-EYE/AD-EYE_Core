#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>
#include <autoware_msgs/Lane.h>

//using namespace grid_map;


class safetySupervisor
{
private:
    // constants
    bool SAFE = 0;
    bool UNSAFE = 1;
    //Critical area
    const float car_length = 5;
    const float car_width = 2;
    const grid_map::Length critAreaSize; //(4 * car_length, 2 * car_width +1);
    const float pi = 3.141592654;

    // node, publishers and subscribers
    ros::NodeHandle nh_;
    ros::Publisher pubSwitch;
    ros::Subscriber subGnss;
    ros::Subscriber subGridmap;
    ros::Subscriber subAutowareTrajectory;

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

    safetySupervisor(ros::NodeHandle nh) : critAreaSize(4 * car_length, 2 * car_width +1)
    {
        // Initialize the node, publishers and subscribers
        nh_ = nh;

        pubSwitch = nh_.advertise<std_msgs::Int32>("/switchCommand", 1, true);

        subGnss = nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &safetySupervisor::gnss_callback, this);
        subGridmap = nh_.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &safetySupervisor::gridmap_callback, this);
        subAutowareTrajectory = nh_.subscribe<autoware_msgs::Lane>("/final_waypoints", 1, &safetySupervisor::autowareTrajectory_callback, this);

        // Initialize the variables
        state = SAFE;

        // Initialize the flags
        gnss_flag = 0;
        gridmap_flag = 0;
        //rate(float 20);

    }

    void gnss_callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        geometry_msgs::PoseStamped gnss = *msg;
        pose = gnss.pose;
        gnss_flag = 1;
    }

    void gridmap_callback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        grid_map::GridMapRosConverter::fromMessage(*msg, gridmap);
        //gridmap = *msg;
        gridmap_flag = 1;
    }

    void autowareTrajectory_callback(const autoware_msgs::Lane::ConstPtr& msg)
    {
        autowareTrajectory = *msg;
        //for (int i = 0; i < autowareTrajectory.waypoints.size(); i++)
        //{
        //  ROS_INFO("%f", autowareTrajectory.waypoints[0].pose.pose.position.x);
        //}
        autowareTrajectory_flag = 1;
    }

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

    void publish()
    {
        msg.data = state;
        pubSwitch.publish(msg);
    }


    void evaluate()
    {
        //Is the center of the car inside the road
        state = SAFE;
        float current_lane_id = gridmap.atPosition("Lanes", grid_map::Position(pose.position.x, pose.position.y));
        //ROS_INFO("%f", current_lane_id);
        if (current_lane_id == 0) {
            state = UNSAFE;
            return;
        }

        //Is there a dynamic object in the critical area
        const float x = pose.position.x;    //Center is currently in the fron of the car
        const float y = pose.position.y;
        const float a = pose.orientation.z;
        const grid_map::Position critAreaCenter(x + car_length*cos(a*pi)/2, y + car_length*sin(a*pi)/2);
        bool isOk;
        grid_map::SubmapGeometry critArea(gridmap, critAreaCenter, critAreaSize, isOk);
        if(!isOk) {
            ROS_ERROR("Getting Submap from Gridmap failed");
            return;
        }
        for(grid_map::SubmapIterator areaIt(critArea) ; !areaIt.isPastEnd() ; ++areaIt) {
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
    safetySupervisor sS(nh);
    sS.run();
    return 0;
}
