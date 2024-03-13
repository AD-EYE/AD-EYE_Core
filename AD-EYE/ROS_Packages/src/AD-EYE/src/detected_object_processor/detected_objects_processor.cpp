#include <ros/ros.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/ColorRGBA.h>
#include <tf/transform_listener.h>


class DetectedObjectsProcessor
{
    private:
        ros::NodeHandle nh_;
        ros::Publisher pub_objects_;
        ros::Subscriber sub_objects_;
        tf::TransformListener listener;

        std::string in_topic_ = "/sensor_detected_objects";
        std::string out_topic_ = "/objects_markers";
        float marker_display_duration_ = 0.1;
        std::string world_frame_ = "/world";
        std::string sensor_frame_ = "/external_sensor_tf";
        int id_ = 0;

        std_msgs::ColorRGBA parseColor(const std::vector<double> in_color)
        {
            std_msgs::ColorRGBA color;
            float r,g,b,a;
            if (in_color.size() == 4) //r,g,b,a
            {
                color.r = in_color[0]/255.f;
                color.g = in_color[1]/255.f;
                color.b = in_color[2]/255.f;
                color.a = in_color[3];
            }
            return color;
        }

        visualization_msgs::Marker getMarker(geometry_msgs::PoseStamped pose_msg)
        {
            visualization_msgs::Marker marker;

            marker.lifetime = ros::Duration(marker_display_duration_);
            marker.id = id_++;
            marker.header.frame_id= "world";
            marker.header.stamp = ros::Time::now();
            marker.type = visualization_msgs::Marker::SPHERE;
            marker.action = visualization_msgs::Marker::ADD;
            marker.ns = "/detected_object_markers";
            marker.pose = pose_msg.pose;
            marker.scale.x = 3;
            marker.scale.y = 3;
            marker.scale.z = 3;
            marker.color = parseColor({255, 0, 0, 1.0}); // color:red
            return marker;
        }

        void sensorObjectsCallback(const geometry_msgs::PoseArray::ConstPtr& msg_ptr)
        {
            geometry_msgs::PoseArray msg = *msg_ptr;
            visualization_msgs::MarkerArray markers_msg;
            geometry_msgs::PoseStamped sensor_pose, world_pose;
            sensor_pose.header = msg.header;

            for(geometry_msgs::Pose pose: msg.poses)
            {
                try
                {
                    sensor_pose.pose = pose; 
                    listener.transformPose("world", sensor_pose, world_pose);
                }
                catch(tf::TransformException& ex)
                {
                    ROS_ERROR("Received an exception trying to transform a pose from sensor frame to world: %s", ex.what());
                }
                visualization_msgs::Marker marker = getMarker(world_pose);
                markers_msg.markers.push_back(marker);
            }
            pub_objects_.publish(markers_msg);
        }

    public:
        DetectedObjectsProcessor(ros::NodeHandle& nh): nh_(nh)
        {
            pub_objects_ = nh_.advertise<visualization_msgs::MarkerArray>(
                                out_topic_, 1);
            sub_objects_ = nh_.subscribe<geometry_msgs::PoseArray>(in_topic_, 1,
                        &DetectedObjectsProcessor::sensorObjectsCallback, this);
        }

};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "DetectedObjectsProcessor");
    ros::NodeHandle nh;
    DetectedObjectsProcessor dop(nh);
    ros::spin();
    return 0;
}