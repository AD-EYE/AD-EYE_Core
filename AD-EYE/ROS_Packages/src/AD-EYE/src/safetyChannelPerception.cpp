#include <ros/ros.h>
// #include <std_msgs/Float32MultiArray.h>
#include <pcl_ros/point_cloud.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

class SafetyChannelPerception {

    private:
        ros::NodeHandle &nh_;
        ros::Subscriber sub_Lidar_;
        ros::Publisher pub_PointCloud_;
        ros::Rate rate_;
        PointCloud point_cloud_;

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

    public:
        SafetyChannelPerception(ros::NodeHandle& nh): nh_(nh), rate_(10)
        {
            sub_Lidar_ = nh.subscribe<PointCloud>("/points_raw", 1, &SafetyChannelPerception::Lidar_callback, this);
            pub_PointCloud_ = nh.advertise<PointCloud>("/points_filtered", 1, true);

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