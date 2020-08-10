#include <ros/ros.h>
#include <tf/transform_listener.h>
// #include <std_msgs/Float32MultiArray.h>
#include <pcl_ros/point_cloud.h>
#include <autoware_msgs/CloudClusterArray.h>
#include <geometry_msgs/PolygonStamped.h>
#include <jsk_recognition_msgs/PolygonArray.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

class SafetyChannelPerception {

    private:
        ros::NodeHandle &nh_;
        ros::Subscriber sub_Lidar_;
        ros::Publisher pub_PointCloud_;
        ros::Publisher pub_Polygons_;
        ros::Rate rate_;
        PointCloud point_cloud_;
        std::string polygon_frame_ = "SSMP_map";
        tf::TransformListener& tf_listener_;
        


        void ClusterCallback(const autoware_msgs::CloudClusterArray::ConstPtr& msg) {
            jsk_recognition_msgs::PolygonArray poly_array;
            for(auto cluster: msg->clusters)
            {
                poly_array.header.frame_id = cluster.convex_hull.header.frame_id;
                geometry_msgs::PolygonStamped poly_in_gridmap_frame;
                poly_in_gridmap_frame.header.frame_id = polygon_frame_;
                for(auto pt: cluster.convex_hull.polygon.points)
                {
                    geometry_msgs::PointStamped pt_stamped_sensor_frame, pt_stamped_gridmap_frame;
                    pt_stamped_sensor_frame.header.frame_id = cluster.convex_hull.header.frame_id;
                    pt_stamped_sensor_frame.point.x = pt.x;
                    pt_stamped_sensor_frame.point.y = pt.y;
                    pt_stamped_sensor_frame.point.z = pt.z;
                    try
                    {
                        tf_listener_.transformPoint(polygon_frame_, pt_stamped_sensor_frame, pt_stamped_gridmap_frame);
                    }
                    catch(tf::TransformException& ex)
                    {
                        ROS_ERROR("Received an exception trying to transform a point: %s", ex.what());
                    }
                    geometry_msgs::Point32 pt32__gridmap_frame;
                    pt32__gridmap_frame.x = pt_stamped_gridmap_frame.point.x;
                    pt32__gridmap_frame.y = pt_stamped_gridmap_frame.point.y;
                    pt32__gridmap_frame.z = pt_stamped_gridmap_frame.point.z;
                    poly_in_gridmap_frame.polygon.points.push_back(pt32__gridmap_frame);
                }
                poly_array.polygons.push_back(poly_in_gridmap_frame);
            }
            pub_Polygons_.publish(poly_array);
        }

    public:
        SafetyChannelPerception(ros::NodeHandle& nh, tf::TransformListener& listener): nh_(nh), rate_(10), tf_listener_(listener)
        {
            sub_Lidar_ = nh.subscribe<autoware_msgs::CloudClusterArray>("detection/lidar_detector/cloud_clusters", 1, &SafetyChannelPerception::ClusterCallback, this);

            pub_PointCloud_ = nh.advertise<PointCloud>("/points_filtered", 1, true);
            pub_Polygons_ = nh.advertise<jsk_recognition_msgs::PolygonArray>("detection/polygons", 1, true);

        }

        void run() {
            while (nh_.ok()) {
            ros::spinOnce();

            // publish stuff
            
            rate_.sleep();
        }
        }

};



int main(int argc, char** argv)
{
    ros::init(argc, argv, "SafetyChannelPerception");
    ros::NodeHandle nh;
    tf::TransformListener listener;
    SafetyChannelPerception scp = SafetyChannelPerception(nh,listener);
    scp.run();
}