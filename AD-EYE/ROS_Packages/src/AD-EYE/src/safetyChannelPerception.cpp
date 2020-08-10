#include <ros/ros.h>
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

        void Lidar_callback(const PointCloud::ConstPtr& msg) {
            printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
            // printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
            // BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points)
            const pcl::PointXYZ& pt = (msg->points).front();
            printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);
            point_cloud_.empty();
            point_cloud_.header.frame_id = msg->header.frame_id;
            for(auto& pt: msg->points)
            {
                if(pt.z>0.1)
                    point_cloud_.push_back(pt);
            }
            pub_PointCloud_.publish(point_cloud_);
        }

        void ClusterCallback(const autoware_msgs::CloudClusterArray::ConstPtr& msg) {
            jsk_recognition_msgs::PolygonArray poly_array;
            for(auto cluster: msg->clusters)
            {
                poly_array.header.frame_id = cluster.convex_hull.header.frame_id;
                poly_array.polygons.push_back(cluster.convex_hull);
            }
            printf ("publishing a polygon");
            pub_Polygons_.publish(poly_array);
        }

    public:
        SafetyChannelPerception(ros::NodeHandle& nh): nh_(nh), rate_(10)
        {
            // sub_Lidar_ = nh.subscribe<PointCloud>("/points_raw", 1, &SafetyChannelPerception::Lidar_callback, this);
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
    SafetyChannelPerception scp = SafetyChannelPerception(nh);
    scp.run();
}