#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/ColorRGBA.h>

class DetectedObjectsPublisher
{
    private:
        ros::NodeHandle nh_;
        ros::Publisher pub_markers_;
        std::string ros_namespace_;

        std::string markers_out_topic = "/objects_markers";
        float marker_display_duration_ = 0.2;

        /*!
        * \brief function to create color of type ROS  std_msgs::ColorRGBA from RGBA values
        * \param in_color vector of size 4  containing RGBA values of color 
        */
        static std_msgs::ColorRGBA parseColor(const std::vector<double> in_color)
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
    public:
        DetectedObjectsPublisher(ros::NodeHandle& nh): nh_(nh)
        {
            pub_markers_ = nh_.advertise<visualization_msgs::MarkerArray>(
                                markers_out_topic, 1);
            ros_namespace_ = ros::this_node::getNamespace();
        }
        void run()
        {
            visualization_msgs::Marker marker;

            marker.lifetime = ros::Duration(marker_display_duration_);
            marker.header.frame_id= "world";
            marker.header.stamp = ros::Time::now();
            marker.type = visualization_msgs::Marker::CUBE;
            marker.action = visualization_msgs::Marker::ADD;
            marker.ns = ros_namespace_ + "/detected_object_markers";

            marker.pose.position.x = 84.59;
            marker.pose.position.y = 175.01;
            marker.pose.position.z = -2.22;
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 0.0;
            marker.scale.x = 3;
            marker.scale.y = 3;
            marker.scale.z = 3;
            marker.color = parseColor({255, 0, 0, 1.0}); // color:red
            
            ros::Rate loop_rate(20);
            int count = 0;
            float markerx;
            while (ros::ok())
            {

                visualization_msgs::MarkerArray markers;
                markerx = marker.pose.position.x;
                if (count%10 == 0)
                {
                    if(markerx > 200)
                        markerx = 84.59;
                    markerx += 10;
                }
                    
                marker.pose.position.x = markerx;
                markers.markers.push_back(marker);
                pub_markers_.publish(markers);

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