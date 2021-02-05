#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "pcl_ros/transforms.h"
#include "tf/transform_listener.h"


class PointCloudFrameChanger {

    private:

        ros::Publisher pub_;
        ros::Subscriber sub_;
        tf::TransformListener tf_listener_;

        void pointcloud_transform_callback(sensor_msgs::PointCloud2 cloud_in)
        {
            sensor_msgs::PointCloud2 cloud_out_transformed;
            try {
                tf_listener_.waitForTransform("/base_link", "/world", ros::Time(0),
                                            ros::Duration(3.0));
                pcl_ros::transformPointCloud("/world", cloud_in,
                                            cloud_out_transformed, tf_listener_);
            }
            catch(tf::TransformException &ex) {
                ROS_ERROR("%s",ex.what());
            }
            pub_.publish(cloud_out_transformed);
        }

    public:

        PointCloudFrameChanger(ros::NodeHandle nh) {
            sub_ = nh.subscribe("/points_raw", 10, &PointCloudFrameChanger::pointcloud_transform_callback, this);
            pub_ = nh.advertise<sensor_msgs::PointCloud2> ("/points_world_frame", 1);
        }

        void run() {
            ros::spin();
        }

};



int main(int argc, char **argv)
{
  ros::init(argc, argv, "Point_cloud_frame_changer");
  ros::NodeHandle nh;
  PointCloudFrameChanger point_cloud_framme_changer(nh);
  point_cloud_framme_changer.run();

  return 0;
}
