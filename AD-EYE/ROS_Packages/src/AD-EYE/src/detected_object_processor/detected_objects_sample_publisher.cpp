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
        void run()
        {
            geometry_msgs::Pose pose;
            pose.position.x = 10.0;
            pose.position.y = 4.0;
            pose.position.z = 2.0;
            pose.orientation.x = 0.0;
            pose.orientation.y = 0.0;
            pose.orientation.z = 0.0;
            pose.orientation.w = 1.0;

            ros::Rate loop_rate(10);
            int count = 0;
            while (ros::ok())
            {

                geometry_msgs::PoseArray poses;
                poses.header.frame_id = "external_sensor_tf";
                if (count%10 == 0)
                {
                    if(pose.position.x > 100)
                        pose.position.x = 10.0;
                    pose.position.x += 10;
                }
                poses.poses.push_back(pose);
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