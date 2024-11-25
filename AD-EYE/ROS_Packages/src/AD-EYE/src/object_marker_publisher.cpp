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
    std_msgs::ColorRGBA label_color_ = parseColor({0, 0, 0, 1.0}); //black
    float label_height_ = 1.0;
    std::string markers_out_topic = "/test_label_markers";
    float marker_display_duration_ = 0.2;
    std::string ros_namespace_;
    
    enum Sensor{
        Fusion,
        Camera1,
        Camera2,
        Lidar_Radar
    };
    std_msgs::ColorRGBA sensor_colors_[4] = {
        parseColor({255, 0, 0, 1.0}), // Fusion color:red
        parseColor({0, 255, 0, 1.0}), // Camera1 color:green
        parseColor({0, 0, 255, 1.0}), // Camera2 color:blue
        parseColor({255, 255, 0, 1.0})  // Lidar_Radar color:yellow
    };

    /*!
    * \brief To extract label from autoware object, convert it into ROS Marker message 
    * \param in_object: the object from which label need to be extracted
   */
    visualization_msgs::Marker getLabelMarker( const autoware_msgs::DetectedObject &in_object)
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
        return label_marker;
    }

    /*!
    * \brief To extract location and pose from autoware object, convert it into ROS Marker message 
    * of type sphere 
    * \param in_object: the object for which a centroid shold be displayed
    * \param color: required color of the sphere
   */
    visualization_msgs::Marker getCentroidMarker(const autoware_msgs::DetectedObject &in_object, std_msgs::ColorRGBA color)
    {
        visualization_msgs::Marker centroid_marker;
        centroid_marker.lifetime = ros::Duration(marker_display_duration_);

        centroid_marker.header = in_object.header;
        centroid_marker.type = visualization_msgs::Marker::SPHERE;
        centroid_marker.action = visualization_msgs::Marker::ADD;
        centroid_marker.pose = in_object.pose;
        centroid_marker.ns = ros_namespace_ + "/centroid_markers";

        centroid_marker.scale.x = 1;
        centroid_marker.scale.y = 1;
        centroid_marker.scale.z = 1;
        centroid_marker.color = color;
        centroid_marker.id = marker_id_++;
        return centroid_marker;
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

    
    /*!
    * \brief checks if the detected object is relevant for visualization i.e whether
    * it is a car?person etc that the driver needs to lookout for. 
    * \param current_label label of the detected object
    * \return true if object is relevant false if not
   */
    bool isObjectRelevant(std::string current_label)
    {
        std::string relevant_labels [4] = {"car" , "pedestrian" , "truck/bus" ,
            "motorbike"};
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

    /*!
    * \brief It will process objects detected by a particular sensor
    * and publish labels and spheres for relevant objects onto  test_label_markers topic
    * color of spheres is determined by sensor_colors_ array 
    * \param in_objects array of objects detected by a particular sensor
    * \param sensor type of sensor
   */
    void publishSensorDetectedObjects(const autoware_msgs::DetectedObjectArray &in_objects, Sensor sensor)
    {
        
        visualization_msgs::MarkerArray markers;
        for (auto const &object: in_objects.objects)
        {
            if (isObjectValid(object))
            {   
                if(!object.label.empty() && isObjectRelevant(object.label))
                {
                    markers.markers.push_back(getLabelMarker(object));
                    markers.markers.push_back(getCentroidMarker(object, sensor_colors_[sensor]));
                }
            }
        }
        pub_markers_.publish(markers);
    }



    void detectedObjectsFusionCallback(const autoware_msgs::DetectedObjectArray &in_objects)
    {
       publishSensorDetectedObjects (in_objects, Fusion);
    }

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
    ObjectMarkerPublisher(ros::NodeHandle& nh): nh_(nh)
    {
        sub_detected_objects_ =
        nh_.subscribe("/fusion/objects", 1,
                           &ObjectMarkerPublisher::detectedObjectsFusionCallback, this);
        pub_markers_ = nh_.advertise<visualization_msgs::MarkerArray>(
                            markers_out_topic, 1);
        
        ros_namespace_ = ros::this_node::getNamespace();
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ObjectMarkerPublisher");
    ros::NodeHandle nh;
    ObjectMarkerPublisher omc(nh);
    ros::spin();
    return 0;
}

