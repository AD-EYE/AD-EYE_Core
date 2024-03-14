#include <ros/ros.h>
#include<geometry_msgs/PoseArray.h>
#include<geometry_msgs/Pose.h>

class DetectedObjectsPublisher
{
    private:
        ros::NodeHandle nh_;
        ros::Publisher pub_objects_;

        std::string out_topic = "/sensor_detected_objects";

    public:
        DetectedObjectsPublisher(ros::NodeHandle& nh): nh_(nh)
        {
            pub_objects_ = nh_.advertise<geometry_msgs::PoseArray>(
                                out_topic, 1);
        }

        geometry_msgs::Pose getPose(float x, float y)
        {
            geometry_msgs::Pose pose;
            pose.position.x = x;
            pose.position.y = y;
            pose.position.z = 2.0;
            pose.orientation.x = 0.0;
            pose.orientation.y = 0.0;
            pose.orientation.z = 0.0;
            pose.orientation.w = 1.0;
            return pose;
        }
        void run()
        {
            geometry_msgs::Pose pose1, pose2;
            // // start of intersection pose
            // pose1 = getPose(15.0, 0.0);
            // pose2 = getPose(-25, 5);
            // // end of intersection pose

            // start of building camera pose
            pose1 = getPose(15.0, 0.0);
            pose2 = getPose(-2, 15);
            // end of building camera pose

            ros::Rate loop_rate(10);
            int count = 0;
            while (ros::ok())
            {
                geometry_msgs::PoseArray poses;
                poses.header.frame_id = "external_sensor_tf";
                if (count%5 == 0)
                {
                    if(pose1.position.x > 30)
                        pose1.position.x = 15.0;
                    pose1.position.x += 5;
                }
                poses.poses.push_back(pose1);
                poses.poses.push_back(pose2);
                pub_objects_.publish(poses);

                ros::spinOnce();

                loop_rate.sleep();
                ++count;
            }

        }

};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "DetectedObjectsPublisher");
    ros::NodeHandle nh;
    DetectedObjectsPublisher dop(nh);
    dop.run();
    return 0;
}