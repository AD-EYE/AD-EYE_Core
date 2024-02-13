#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <autoware_msgs/DetectedObject.h>
#include <std_msgs/ColorRGBA.h>
#include <autoware_msgs/DetectedObjectArray.h>

class ObjectMarkerPublisher
{
private:
    ros::NodeHandle nh_;
    ros::Rate rate_=ros::Rate(20);
    ros::Subscriber sub_detected_objects_;
    ros::Publisher pub_markers_;
    int marker_id_ = 0;
    std_msgs::ColorRGBA label_color_;
    // std_msgs::ColorRGBA centroid_color_;
    float label_height_ = 1.0;
    std::string markers_out_topic = "/test_label_markers";
    float marker_display_duration_ = 0.2;
    visualization_msgs::MarkerArray label_markers_;
    visualization_msgs::MarkerArray centroid_markers_;
    std::string ros_namespace_;

    void addLabelMarker( const autoware_msgs::DetectedObject &in_object)
    {
        visualization_msgs::Marker label_marker;
        label_marker.lifetime = ros::Duration(marker_display_duration_);
        label_marker.header = in_object.header;
        label_marker.ns = ros_namespace_ + "/label_markers";
        label_marker.action = visualization_msgs::Marker::ADD;
        label_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        label_marker.scale.x = 1.5;
        label_marker.scale.y = 1.5;
        label_marker.scale.z = 1.5;

        label_marker.color = label_color_;

        label_marker.id = marker_id_++;
        label_marker.text = in_object.label; //Object Class if available
        label_marker.pose.position.x = in_object.pose.position.x;
        label_marker.pose.position.y = in_object.pose.position.y;
        label_marker.pose.position.z = label_height_;
        label_marker.scale.z = 1.0;

        label_markers_.markers.push_back(label_marker);
    }

    void addCentroidMarker(const autoware_msgs::DetectedObject &in_object)
    {
        visualization_msgs::Marker centroid_marker;
        centroid_marker.lifetime = ros::Duration(marker_display_duration_);

        centroid_marker.header = in_object.header;
        centroid_marker.type = visualization_msgs::Marker::SPHERE;
        centroid_marker.action = visualization_msgs::Marker::ADD;
        centroid_marker.pose = in_object.pose;
        centroid_marker.ns = ros_namespace_ + "/centroid_markers";

        centroid_marker.scale.x = 0.5;
        centroid_marker.scale.y = 0.5;
        centroid_marker.scale.z = 0.5;

        if (in_object.color.a == 0)
        {
            centroid_marker.color = label_color_;
        }
        else
        {
            centroid_marker.color = in_object.color;
        }
        centroid_marker.id = marker_id_++;
        centroid_markers_.markers.push_back(centroid_marker);
    }

    bool isObjectValid(const autoware_msgs::DetectedObject &in_object)
    {
        if (!in_object.valid ||
            std::isnan(in_object.pose.orientation.x) ||
            std::isnan(in_object.pose.orientation.y) ||
            std::isnan(in_object.pose.orientation.z) ||
            std::isnan(in_object.pose.orientation.w) ||
            std::isnan(in_object.pose.position.x) ||
            std::isnan(in_object.pose.position.y) ||
            std::isnan(in_object.pose.position.z) ||
            (in_object.pose.position.x == 0.) ||
            (in_object.pose.position.y == 0.) ||
            (in_object.dimensions.x <= 0.) ||
            (in_object.dimensions.y <= 0.) ||
            (in_object.dimensions.z <= 0.)
            )
        {
            return false;
        }
        return true;
    }//end isObjectValid

    bool isObjectRelevant(std::string current_label)
    {
        std::string relevant_labels [5] = {"car" , "person", 
                                        "bicycle", "bus",
                                        "truck"};
        bool is_relevant = false;
        for (std::string label : relevant_labels)
        {
            if (label == current_label){
                is_relevant = true;
                break;
            }
        }
        return is_relevant;
    }



    void detectedObjectsCallback(const autoware_msgs::DetectedObjectArray &in_objects)
    {
        label_markers_.markers.clear();
        centroid_markers_.markers.clear();
        for (auto const &object: in_objects.objects)
        {
            if (isObjectValid(object))
            {
                
                if(!object.label.empty() && isObjectRelevant(object.label))
                {

                    addLabelMarker(object);
                    addCentroidMarker(object);
                }
            }
        }
        pub_markers_.publish(label_markers_);
        pub_markers_.publish(centroid_markers_);
    }


public:
    ObjectMarkerPublisher(ros::NodeHandle& nh): nh_(nh)
    {
        sub_detected_objects_ =
        nh_.subscribe("/fusion/objects", 1,
                           &ObjectMarkerPublisher::detectedObjectsCallback, this);
        pub_markers_ = nh_.advertise<visualization_msgs::MarkerArray>(
                            markers_out_topic, 1);
        label_color_.r = 255;
        label_color_.g = 0;
        label_color_.b = 0;
        label_color_.a = 1.0;
        ros_namespace_ = ros::this_node::getNamespace();
    }

    void run()
    {
        while (nh_.ok())
            {
                ros::Time rostime = ros::Time::now();
                ros::spinOnce();
                rate_.sleep();
            }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ObjectMarkerPublisher");
    ros::NodeHandle nh;
    ObjectMarkerPublisher omc(nh);
    omc.run();
    return 0;
}

