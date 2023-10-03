#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <queue>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/LaneArray.h>
#include <std_msgs/Bool.h>
#include <vector_map_msgs/PointArray.h>
#include <cmath>
#include <iostream>
#include <tf/transform_broadcaster.h>
#include <stdlib.h>
#include <tuple>
/*
Example on how to run the program:

Terminal1 type: catkin_make, then: rosrun adeye goalSequencer
Terminal2 type: roslaunch adeye my_map.launch world_name:=W01_Base_Map, or: roslaunch adeye my_map.launch
Terminal3 type one of the below:
rostopic pub /adeye/goals geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x: 0.0,
y: 0.0, z: 49.156}, orientation: {z: 0.416, w: 0.909}}}'
rostopic pub /adeye/goals geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x:
137.998049077445, y: 121.23713661199696, z: 49.156}, orientation: {z: 0.760, w: 0.650}}}'
rostopic pub /adeye/goals geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x:
140.82, y: 62.27, z: 49.156}, orientation: {z: 0, w: 1}}}'
rostopic pub /adeye/goals geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x:
418.84, y: 164.26}, orientation: {z: 0.0, w: 1}}}'

Case when goals is 4.4m apart from each other but 180 degrees heading difference:
rostopic pub /adeye/goals geometry_msgs/seStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x:
101.27694427859949, y: 222.26434883547188}, orientation: {z: 0.0, w: 1}}}'
rostopic pub /adeye/goals geometry_msgs/seStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x:
98.57472205637728, y: 225.76434883547188}, orientation: {z: 1.0, w: 0.0}}}'

rostopic pub /current_behavior geometry_msgs/TwistStamped "{header: {stamp: now, frame_id: "map"}, twist: {linear: {x:
1.0, y: 2.0, z: 3.0}, angular: {x: 1.0,y: 13.0,z: 1.0}}}"
*/

/*!
* Initiate SequenceGoalNode class which stores all goals from the adeye goals, goal_map_node
* Store them as queue
* Publish the real world map goal coordinates one by one to auto-ware when the vehicle is in the vicinity of the goal
* position.
*/
class GoalSequencer
{
  private:
    ros::NodeHandle& nh_;
    ros::Subscriber sub_goal_coordinates_;
    ros::Subscriber sub_position_;
    ros::Subscriber sub_autoware_state_;
    ros::Subscriber sub_vector_map_;
    ros::Publisher pub_goal_;
    ros::Publisher pub_overwrite_goal_;
    ros::Publisher pub_update_local_planner_;

    // ROS rate
    ros::Rate rate_;

    // Vehicle position
    float x_ego_;
    float y_ego_;

    // Autoware vectormap
    vector_map_msgs::PointArray vector_map_data_;

    // Goal queue
    std::queue<geometry_msgs::PoseStamped> goal_coordinates_;

    // Boolean value for the global planner, end state and the goals
    bool has_global_planner_and_goal_been_reset_ = false;
    bool should_update_global_planner_ = false;
    bool first_goal_sent_ = false;
    bool received_vector_mapper_ = false;

    int file_size_;
    // Autoware behavior state status
    double autoware_behavior_state_;

    // Distance tolerance for duplicate goals
    const double GOAL_DISTANCE_TOLERANCE_ = 10;  // [m]
    const double VMAP_DISTANCE_TOLERANCE_ = 5;   // [m]

    // Orientation tolerance between goals or goal and vector map
    const double ORIENTAION_TOLERANCE_ = 30;  // [degrees]

    // Vehicle State behaviour
    const double END_STATE_ = 13.0;
    const double FORWARD_STATE_ = 2.0;

    // Minimum goals in the goal coordinates queue for publishing next (upcoming) goals
    const int MINIMUM_GOALS_ = 2;

    /*!
     * \brief Position Callback : Continuously called when the vehicle position information has changed.
     * \param msg The message contains the vehicle position coordinates.
     * \details Stores the vehicle position coordinates information.
     */
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        // Received the vehicle position coordinates
        x_ego_ = msg->pose.position.x;
        y_ego_ = msg->pose.position.y;
    }

    /*!
     * \brief Store Goal Coordinates Callback : Called when the goal coordinates are received from the goal_map_node.
     * \param msg The message contains the goal position coordinates.
     * \details Stores the goal coordinates information as queue.
     */
    void storeGoalCoordinatesCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        if (!received_vector_mapper_)
        {
            ROS_INFO(
                "No vector map received, please close the goal publisher and start vector map in another terminal by "
                "typing for example:");
            ROS_INFO("roslaunch adeye my_map.launch world_name:=W01_Base_Map");
        }
        // Stores the goal if it is valid
        else if (isGoalValid(msg->pose.position.x, msg->pose.position.y, msg->pose.position.z, msg->pose.orientation))
        {
            // Print the new goal positions
            ROS_INFO("The next goal has position:- x = %lf, y = %lf, z = %lf", msg->pose.position.x,
                     msg->pose.position.y, msg->pose.position.z);
            // Store the real-world map goal coordinates
            goal_coordinates_.push(*msg);
        }
        else
        {
            ROS_INFO("The received goal is not valid");
        }
    }

    /*!
     * \brief Behavior State Callback : Continuously called to show the vehicle behaviour state information.
     * \param msg The message contains the vehicle state status.
     * \details Stores the autoware behavior state status.
     */
    void behaviorStateCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)
    {
        // Autoware behavior state (2.0 = Forward state and 13.0 = End state)
        autoware_behavior_state_ = msg->twist.angular.y;
    }

    /*!
     * \brief Autoware vector map Callback : Called when the vector map is received.
     * \param msg The message contains the data points of the vector map.
     * \details Stores the data point value from the vector map
     */
    void vectorMapCallback(const vector_map_msgs::PointArray::ConstPtr& msg)
    {
        ROS_INFO("Recived vector mapper");
        received_vector_mapper_ = true;
        vector_map_data_ = *msg;
        // extra -1 since we need to calculate data point of i+1 in the loop
        file_size_ = vector_map_data_.data.size() - 2;
    }

    /*!
    * \brief Calculate the distance between two x and y points
    * \param x_1, x_2, y_1 and y_2 are points of the real world map
    */
    double getDistance(const double& x_one, const double& x_two, const double& y_one, const double& y_two)
    {
        return sqrt((x_two - x_one) * (x_two - x_one) + (y_two - y_one) * (y_two - y_one));
    }

    /*!
    * \brief Calculate the orientation between two x and y points and retrun it in degrees
    * \param x_1, x_2, y_1 and y_2 are points of the real world map
    */
    double getOrientation(const double& x_one, const double& x_two, const double& y_one, const double& y_two)
    {
        double angle = atan2(y_two - y_one, x_two - x_one);
        std::cout << "angle: " << angle << std::endl;
        /*
        if (angle < 0)
        {
            angle += 2 * M_PI;
        }
        */
        return angle * (180.0 / M_PI);
    }

    /*!
    * \brief Finds the closest distance to a VM point
    * \param x, y is the position of the received goal
    * \details Loop through each point of the vector map and calculate its distance to x, y
    *          When the shortest distance is found, we return the distance and index to the closest VM point
    */
    std::tuple<double, int> findClosestVMDistance(const double& x, const double& y)
    {
        // initialize it as max value.
        double closest_vm_distance = std::numeric_limits<double>::max();
        double vm_distance;
        int index;
        for (unsigned int i = 0; i < file_size_; i++)
        {
            vm_distance = getDistance(x, vector_map_data_.data[i].ly, y, vector_map_data_.data[i].bx);

            // Update the point and distance until we find the shortest distance-
            if (vm_distance < closest_vm_distance)
            {
                closest_vm_distance = vm_distance;
                index = i;
            }
        }
        return std::make_tuple(closest_vm_distance, index);
    }

    /*!
    * \brief Finds the orientation of a certain VM point given the index.
    * \param i, is the index to the desired VM point.
    */
    double findOrientationOfVM(const int& i)
    {
        double vmap_orientation = getOrientation(vector_map_data_.data[i].ly, vector_map_data_.data[i + 1].ly,
                                                 vector_map_data_.data[i].bx, vector_map_data_.data[i + 1].bx);
        return vmap_orientation;
    }

    /*!
    * \brief Check if the goal is close to the VM
    * \param distance is the distance between goal and VM
    */
    bool isPointCloseToVM(const double& distance)
    {
        if (distance <= VMAP_DISTANCE_TOLERANCE_)
        {
            return true;
        }
        else
        {
            ROS_INFO("Recieved goal is not within the vector map");
            return false;
        }
    }

    /*!
    * \brief Check if the difference of VM orientation and yaw angle is small enough
    * \param vmap_orientation is the orientation of the VM point
    * \param yaw_angle is the orientation of the goal
    */
    bool isPointAlignedWithVM(const int& vmap_orientation, const double& yaw_angle)
    {
        // Check if the difference between goal and vector map orientation is small enough.
        if (abs(yaw_angle - vmap_orientation) < ORIENTAION_TOLERANCE_)
        {
            return true;
        }
        else
        {
            ROS_INFO("Recieved orientation difference from the vector map is too large");
            return false;
        }
    }

    /*!
     * \brief Boolean function that checks if the goal is valid with respect to the vector mapper
     * \param x, y are the data provided by the goals
     * \param yaw_angle is the orientation of the goal
     * \details Gets the closest distance to a point of the vector mapper and correponding index of that point.
     * Using the disance and index, it check if the received goal exist in the vector map with small enough orientation
     * difference
     */
    bool isGoalValidAccordingToVM(const double& x, const double& y, const double& yaw_angle)
    {
        double closest_vm_distance;
        int index;
        // Get the closest distance to a point of VM and corresponding index of that point.
        std::tie(closest_vm_distance, index) = findClosestVMDistance(x, y);

        // Get the orientation of the closest point of the VM
        double vmap_orientation = findOrientationOfVM(index);
        std::cout << "vmap_orientation: " << vmap_orientation << std::endl;
        //double yaw_angle_positive = yaw_angle < 0 ? yaw_angle + 360 : yaw_angle;

        // Check goal validity for the first goal by checking if the goal is close enough to the VM with large
        // orientation.
        if (isPointCloseToVM(closest_vm_distance) && isPointAlignedWithVM(vmap_orientation, yaw_angle))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /*!
    * \brief Checking the distance and orientation between two consequtive goals
    * \param distance_between_goals is the distance between two consequtive goals
    * \param angle_between_goals_headings is the orientation between two consequtive goals
    */

    bool areGoalsDifferentEnough(const double& x, const double& y, const double& yaw_angle)
    {
        // Distance between two consecutive goals
        double distance_between_goals =
            getDistance(goal_coordinates_.back().pose.position.x, x, goal_coordinates_.back().pose.position.y, y);

        // yaw angle of previous goal
        double previous_yaw_angle = tf::getYaw(goal_coordinates_.back().pose.orientation) * (180.0 / M_PI);

        double angle_between_goals_headings = abs(yaw_angle - previous_yaw_angle);

        // Goals can be some degrees apart from each other even though they are close to each other.
        if (distance_between_goals > GOAL_DISTANCE_TOLERANCE_ || angle_between_goals_headings > ORIENTAION_TOLERANCE_)
        {
            return true;
        }
        else
        {
            ROS_INFO("Distance or orientation between current goal and previous goal is not large enough");
            return false;
        }
    }

    /*!
     * \brief Boolean function that checks the validity of the received goal
     * \param x, y,z and goal_orientation are the data provided by the goals
     * \details Check if the received goal exist in the vector map and their orientation difference
     *          Also check the distance and orientation with the pervious stored goal.
     */
    bool isGoalValid(const double& x, const double& y, const double& z,
                     const geometry_msgs::Quaternion& goal_orientation)
    {
        bool is_goal_valid;

        // Transform quaternion to euler angles
        double yaw_angle = tf::getYaw(goal_orientation) * (180.0 / M_PI);
        std::cout << "yaw_angle: " << yaw_angle << std::endl;

        // find the cloest point and its distance and orientation.
        is_goal_valid = isGoalValidAccordingToVM(x, y, yaw_angle);

        // If the received goal is the first goal
        if (!goal_coordinates_.empty())
        {
            is_goal_valid = is_goal_valid && areGoalsDifferentEnough(x, y, yaw_angle);
        }

        return is_goal_valid;
    }

  public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    GoalSequencer(ros::NodeHandle& nh) : nh_(nh), rate_(20)
    {
        // Initialize node, publishers and subscribers
        sub_goal_coordinates_ = nh_.subscribe<geometry_msgs::PoseStamped>(
            "/adeye/goals", 1, &GoalSequencer::storeGoalCoordinatesCallback, this);
        sub_position_ =
            nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &GoalSequencer::positionCallback, this);
        sub_autoware_state_ = nh_.subscribe<geometry_msgs::TwistStamped>("/current_behavior", 1,
                                                                         &GoalSequencer::behaviorStateCallback, this);
        sub_vector_map_ = nh_.subscribe<vector_map_msgs::PointArray>("/vector_map_info/point", 1,
                                                                     &GoalSequencer::vectorMapCallback, this);
        pub_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);
        pub_overwrite_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("/adeye/overwriteGoal", 1, true);
        pub_update_local_planner_ = nh_.advertise<std_msgs::Int32>("/adeye/update_local_planner", 1, true);
    }

    void run()
    {
        // Publish the coordinates of the next goal once the car enters in the end state.
        while (nh_.ok())
        {
            ros::spinOnce();

            // Condition for the first goal
            if (!first_goal_sent_ && !goal_coordinates_.empty())
            {
                // Publish the first goal
                pub_goal_.publish(goal_coordinates_.front());

                ROS_INFO("The first goal has been published. Position:- x = %lf, y = %lf, z = %lf",
                         goal_coordinates_.front().pose.position.x, goal_coordinates_.front().pose.position.y,
                         goal_coordinates_.front().pose.position.z);

                // Bool value reset to true for sending upcoming goals in the main run loop.
                first_goal_sent_ = true;
            }

            // Condition for next (upcoming) goals
            // Publish the next goal when the car enters in end state (end state = 13.0) and condition for removing the
            // previous goal and setting up the next goal
            if (autoware_behavior_state_ == END_STATE_ && !has_global_planner_and_goal_been_reset_ &&
                goal_coordinates_.size() >= MINIMUM_GOALS_)
            {
                // Remove the previous goal
                goal_coordinates_.pop();

                // Publish the real world map goal coordinates
                pub_overwrite_goal_.publish(goal_coordinates_.front());

                ROS_INFO("The next goal has been published. Position:- x = %lf, y = %lf, z = %lf",
                         goal_coordinates_.front().pose.position.x, goal_coordinates_.front().pose.position.y,
                         goal_coordinates_.front().pose.position.z);

                std_msgs::Int32 local_planner;

                local_planner.data = 1;
                pub_update_local_planner_.publish(local_planner);
                ROS_INFO("Updated Local Planner!");

                // Update the planner and goal boolean for end state
                has_global_planner_and_goal_been_reset_ = true;
            }
            else if (autoware_behavior_state_ == FORWARD_STATE_)  // The planner and goal boolean is set to false after
                                                                  // publishing the goal and planner (forward state =
                                                                  // 2.0)
            {
                has_global_planner_and_goal_been_reset_ = false;
            }
            rate_.sleep();
        }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "GoalSequencer");
    ros::NodeHandle nh;
    GoalSequencer sequence_goal_node(nh);
    sequence_goal_node.run();
    return 0;
}