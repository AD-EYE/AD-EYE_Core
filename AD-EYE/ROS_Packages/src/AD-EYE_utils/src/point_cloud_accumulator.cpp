#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "pcl_conversions/pcl_conversions.h"


class PointCloudAccumulator {

    private:

        pcl::PCLPointCloud2 accumulated_cloud_;
        ros::Subscriber sub_;
        ros::Publisher pub_;
        bool accumulation_started_ = true;

        void pointsCallback(const sensor_msgs::PointCloud2& input_cloud)
        {
            if(accumulation_started_) {

                // Convert point cloud message to PCL type
                pcl::PCLPointCloud2 input_cloud_pcl;
                pcl_conversions::toPCL(input_cloud, input_cloud_pcl);

                // Merge with the accumulated point cloud
                pcl::concatenatePointCloud(accumulated_cloud_, input_cloud_pcl, accumulated_cloud_);

                // Convert PCL type to ROS message
                sensor_msgs::PointCloud2 accumulated_cloud_message;
                pcl_conversions::fromPCL(accumulated_cloud_, accumulated_cloud_message);

                // Publish accumulated cloud message 
                pub_.publish(accumulated_cloud_message);
            }
        }


    public:

        PointCloudAccumulator(ros::NodeHandle nh) {
            std::string pt_cloud_topic = "/points_world_frame";
            std::string pt_cloud_acc_topic = "/points_accumulated";
            sub_ = nh.subscribe(pt_cloud_topic, 10, &PointCloudAccumulator::pointsCallback, this);
            pub_ = nh.advertise<sensor_msgs::PointCloud2> (pt_cloud_acc_topic, 1);
        }

        void run() {
            ros::spin();
        }

};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "point_cloud_accumulator");
  ros::NodeHandle nh;
  PointCloudAccumulator point_cloud_accumulator(nh);
  point_cloud_accumulator.run();
  return 0;
}
