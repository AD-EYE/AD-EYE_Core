#include <ros/ros.h>

#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include "autoware_msgs/Lane.h"
#include "autoware_msgs/LaneArray.h"

class TrajectoryVisualizer
{
  private:
    ros::NodeHandle nh_;
    ros::Publisher pub_trajectory_markers_;
    ros::Subscriber sub_trajectory_;

    /*!
     * \brief Creates a Marker based on x, y, z values and a marker id.
     * \param marker_id The id of the marker to be created.
     * \param x position of the marker to be created along x axis.
     * \param y position of the marker to be created along y axis.
     * \param z position of the marker to be created along z axis.
     */
    visualization_msgs::Marker createWaypointMarker(int marker_id, float x, float y, float z) const
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "/map";  // might be to be changed later if frame can be different than map
        marker.header.stamp = ros::Time();
        marker.id = marker_id;
        marker.type = visualization_msgs::Marker::SPHERE;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = x;
        marker.pose.position.y = y;
        marker.pose.position.z = z;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.4;
        marker.scale.y = 0.4;
        marker.scale.z = 0.4;
        marker.color.a = 1.0;
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        return (marker);
    }

    /*!
     * \brief Trajectory Callback: receives the trajectory that needs to be visualized.
     * \param trajectory The trajectory message.
     */
    void trajectoryCallback(const autoware_msgs::Lane::ConstPtr& trajectory)
    {
        int marker_id = 0;
        visualization_msgs::MarkerArray marker_array;

        for (auto waypoint : trajectory->waypoints)
        {
            marker_array.markers.push_back(createWaypointMarker(marker_id, waypoint.pose.pose.position.x,
                                                                waypoint.pose.pose.position.y,
                                                                waypoint.pose.pose.position.z));
            marker_id++;
        }
        pub_trajectory_markers_.publish(marker_array);
    }

    /*!
     * \brief Trajectories Callback: receives the trajectories that needs to be visualized.
     * \param trajectory The trajectories message.
     */
    void trajectoriesCallback(const autoware_msgs::LaneArray::ConstPtr& trajectories)
    {
        int marker_id = 0;
        visualization_msgs::MarkerArray marker_array;

        for (auto lane : trajectories->lanes)
        {
            for (auto waypoint : lane.waypoints)
            {
                marker_array.markers.push_back(createWaypointMarker(marker_id, waypoint.pose.pose.position.x,
                                                                    waypoint.pose.pose.position.y,
                                                                    waypoint.pose.pose.position.z));
                marker_id++;
            }
        }
        pub_trajectory_markers_.publish(marker_array);
    }

  public:
    /*!
     * \brief Constructor
     * \param nh ROS NodeHandle.
     * \param trajectory_topic The topic on which to find the trajectory/ies.
     */
    TrajectoryVisualizer(ros::NodeHandle nh, std::string trajectory_topic) : nh_(nh)
    {
        ros::master::V_TopicInfo master_topics;
        ros::master::getTopics(master_topics);
        std::string topic_data_type;
        for (auto topic_info : master_topics)
        {
            if (topic_info.name == trajectory_topic)
            {
                topic_data_type = topic_info.datatype;
                break;
            }
        }

        if (topic_data_type == "autoware_msgs/Lane")
            sub_trajectory_ = nh_.subscribe<autoware_msgs::Lane>(trajectory_topic, 100,
                                                                 &TrajectoryVisualizer::trajectoryCallback, this);
        else if (topic_data_type == "autoware_msgs/LaneArray")
            sub_trajectory_ = nh_.subscribe<autoware_msgs::LaneArray>(
                trajectory_topic, 100, &TrajectoryVisualizer::trajectoriesCallback, this);
        pub_trajectory_markers_ =
            nh_.advertise<visualization_msgs::MarkerArray>(trajectory_topic.append("_Rviz"), 1, true);
    }

    /*!
     * \brief Main loop
     */
    void run()
    {
        ros::Rate rate(20);
        while (nh_.ok())
        {
            ros::spinOnce();
            rate.sleep();
        }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "trajectory_visuaizer");
    ros::NodeHandle nh;
    //    std::string trajectory_topic = "/local_weighted_trajectories";
    std::string trajectory_topic = "/final_waypoints";
    TrajectoryVisualizer trajectory_visualizer(nh, trajectory_topic);
    trajectory_visualizer.run();
    return 0;
}