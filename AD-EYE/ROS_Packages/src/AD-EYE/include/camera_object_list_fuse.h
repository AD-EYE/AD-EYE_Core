#ifndef CAMERA_OBJECT_LIST_FUSE_H
#define CAMERA_OBJECT_LIST_FUSE_H

#include <ros/ros.h>
#include <autoware_msgs/DetectedObjectArray.h>

/*!
 * \brief A node that list the objects detected by the camera 1 and 2, and publish it
 * \details Publish a list of all the objects detected by the camera 1 and the camera 2.
 * The purpuse is to fuse the objects detected by the two cameras in one message.
 */
class CameraObjectListFuse
{
  private:
    // Node, publishers and subscribers
    ros::NodeHandle& nh_;

    ros::Subscriber sub1_;
    ros::Subscriber sub2_;

    ros::Publisher pub_;

    autoware_msgs::DetectedObjectArray in_msg1_;
    autoware_msgs::DetectedObjectArray in_msg2_;
    autoware_msgs::DetectedObjectArray fused_msg_;

    bool msg1_flag_ = false;
    bool msg2_flag_ = false;

    bool isSameObject(autoware_msgs::DetectedObject msg1, autoware_msgs::DetectedObject msg2);
    autoware_msgs::DetectedObject getMostRelevantObject(autoware_msgs::DetectedObject msg1, autoware_msgs::DetectedObject msg2);

  public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param input_topic_1 Name of the topic that connect the camera 1
     * \param input_topic_2 Name of the topic that connect the camera 2
     * \param output_topic Name of the topic where the output list will be published
     * \details Initialize the node and its components such as publishers and subscribers. It call msg1Callback and
     * msg2Callback
     */
    CameraObjectListFuse(ros::NodeHandle& nh, std::string input_topic_1, std::string input_topic_2,
                         std::string output_topic);

    /*!
     * \brief Callback call in the constructor
     * \param msg Contain the list of object detected by camera 1
     * \details Identify the objects that have been detected by camera 1
     */
    void msg1Callback(autoware_msgs::DetectedObjectArray msg);

    /*!
     * \brief Callback call in the constructor
     * \param msg Contain the list of object detected by camera 2
     * \details Identify the objects that have been detected by camera 2
     */
    void msg2Callback(autoware_msgs::DetectedObjectArray msg);

    /*!
     * \brief Fuses the last messages from both topics
     */
    void fuse();

    /*!
     * \brief Returns the fused message
     */
    autoware_msgs::DetectedObjectArray getFusedMessage();

    /*!
     * \brief Publish the last fused message
     * \details Publish the list of all the object detected by camera 1 and 2 to outputTopic.
     */
    void publish();

    /*!
     * \brief The main loop of the Node
     */
    void run();
};

/*!
* \brief Exception
* \details Exception raise if names of topics weren't given
*/
void usage(std::string bin_name);

#endif  // CAMERA_OBJECT_LIST_FUSE_H