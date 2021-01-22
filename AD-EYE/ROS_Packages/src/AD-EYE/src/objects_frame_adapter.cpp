#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
//#include <geometry_msgs/PolygonStamped.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

class objectsFrameAdapter
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber subObjects;

    ros::Publisher pubObjects;


    std::string target_frame;

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener;


    void detectedObjects_callback(autoware_msgs::DetectedObjectArray msg)
    {
        geometry_msgs::PoseStamped poseStampedIn;
        geometry_msgs::PoseStamped poseStampedOut;
        geometry_msgs::PointStamped pointStampedIn;
        geometry_msgs::PointStamped pointStampedOut;

        for (size_t i = 0; i < msg.objects.size(); i++) {
            msg.header.frame_id = target_frame;

            try{
                msg.objects.at(i).space_frame = target_frame;

                poseStampedIn.header = msg.objects.at(i).header;
                poseStampedIn.pose = msg.objects.at(i).pose;
                //std::cout << "Frame in: " << poseStampedIn.header.frame_id << '\n';
                tfBuffer.transform(poseStampedIn, poseStampedOut, target_frame, ros::Duration(0));
                msg.objects.at(i).header = poseStampedOut.header;
                msg.objects.at(i).pose = poseStampedOut.pose;
                //std::cout << "Frame out: " << poseStampedOut.header.frame_id << '\n';


                for (size_t j = 0; j < msg.objects.at(i).convex_hull.polygon.points.size(); j++) {
                    pointStampedIn.point.x = msg.objects.at(i).convex_hull.polygon.points[j].x;
                    pointStampedIn.point.y = msg.objects.at(i).convex_hull.polygon.points[j].y;
                    pointStampedIn.point.z = msg.objects.at(i).convex_hull.polygon.points[j].z;
                    pointStampedIn.header = msg.objects.at(i).convex_hull.header;
                    tfBuffer.transform(pointStampedIn, pointStampedOut, target_frame, ros::Duration(0));
                    msg.objects.at(i).convex_hull.polygon.points[j].x = pointStampedOut.point.x;
                    msg.objects.at(i).convex_hull.polygon.points[j].y = pointStampedOut.point.y;
                    msg.objects.at(i).convex_hull.polygon.points[j].z = pointStampedOut.point.z;
                }
                msg.objects.at(i).convex_hull.header.frame_id = target_frame;

            }
            catch (tf2::TransformException &ex) {
                ROS_WARN("%s",ex.what());
                ros::Duration(1.0).sleep();
                continue;
            }

        }

        pubObjects.publish(msg);
    }

public:
    objectsFrameAdapter(ros::NodeHandle &nh, std::string inputTopic, std::string outputTopic, std::string targetFrame) : nh_(nh), tfListener(tfBuffer)
    {
        target_frame = targetFrame;
        subObjects = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic, 1, &objectsFrameAdapter::detectedObjects_callback, this);
        pubObjects = nh_.advertise<autoware_msgs::DetectedObjectArray>(outputTopic, 1, true);
    }

    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          rate.sleep();
      }
    }
};

void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <input_topic> <output_topic> <target_frame>");
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string inputTopic, outputTopic, targetFrame;
    inputTopic = argv[1];
    outputTopic = argv[2];
    targetFrame = argv[3];

    // Initialize node
    ros::init(argc, argv, "objectsFrameAdapter");
    ros::NodeHandle nh;
    objectsFrameAdapter oFA(nh, inputTopic, outputTopic, targetFrame);
    oFA.run();
    return 0;
}
