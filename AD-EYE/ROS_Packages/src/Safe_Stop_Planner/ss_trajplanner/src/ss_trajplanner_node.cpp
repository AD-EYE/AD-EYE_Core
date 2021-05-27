// ros includes
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include <rcv_common_msgs/trajectory_reference.h>
#include <rcv_common_msgs/current_traj_info.h>
#include <rcv_common_msgs/amount_trajs.h>
#include <rcv_common_msgs/SSMP_control.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <planner_utils/costmap_cloner.h>
#include <cpp_utils/pose_datatypes.h>
#include <cpp_utils/vector_ops.h>
#include <ss_trajplanner/trajectory_set_handler.h>
#include <visualization_msgs/MarkerArray.h>

#define WHITE 1
#define GREEN 30
#define YELLOW 50
#define RED 99

#define OBSTRUCTED_VALUE 100
#define OBSTRUCTED_THRESHOLD 90

class SafeStopTrajectoryPlanner
{
public:

  // only load trajectories with a v_init close to real velocity
  int getSubsetIndex(float v_ego,std::vector<float> v_init_vector){
    float min_v_diff = 100;
    int index_of_min_v_diff = 0;
    for(size_t i=0; i<v_init_vector.size();i++){
      float v_diff = std::fabs(v_ego-v_init_vector.at(i));
      if(v_diff<min_v_diff){
        min_v_diff = v_diff;
        index_of_min_v_diff = i;//-1; // select the subset with v_init smaller then v_ego
      }
      if(index_of_min_v_diff<0){   // check for when i = 0
        index_of_min_v_diff=0;
      }
    }
    return index_of_min_v_diff;
  }

  // callback for velocity and position as received from prescan
  void odom_callback(const nav_msgs::Odometry::ConstPtr& msg){
    nav_msgs::Odometry odom = *msg;
    v_ego = odom.twist.twist.linear.x;
    x_ego = odom.pose.pose.position.x;
    y_ego = odom.pose.pose.position.y;
    yaw_ego = cpp_utils::extract_yaw(odom.pose.pose.orientation);
  }

  // callback which control what the safety planner needs to be doing
  void SSMP_control_callback(rcv_common_msgs::SSMP_control::ConstPtr const & msg ){
      if(msg->SSMP_control == 2 && traj_out.t.size() == 0) {
          ROS_WARN("SSMP Trajectory is empty so the SSMP control message will be ignored");
      }
      else {
          ROS_WARN("Received SSMP control msg");
          SSMP_control = msg->SSMP_control;
      }
  }

  // constructor
  SafeStopTrajectoryPlanner(ros::NodeHandle nh) {
    nh_ = nh;
    // keep dt at 0.1 as the trajectories are spaced apart 0.1 seconds, messing with this number means the trajectories don't make sense anymore
    float dt = 0.1;
    ros::Rate loop_rate(1/dt);
    // counter used to send the correct velocity at the correct time
    int counter = 0;

    // handle params
    ros::NodeHandle p_nh("~");
    std::string cm_base  = p_nh.param("costmap_base_topic",std::string("/costmap_base"));
    std::string trajectory_set_filename = p_nh.param<std::string>("trajectory_set_filename","");

    // pubs & subs
    traj_pub_ = nh.advertise<rcv_common_msgs::current_traj_info>("/safe_stop_traj",1);
    traj_vis_pub_ = nh.advertise<visualization_msgs::MarkerArray>("safe_stop_traj_vis",1);
    entire_traj_pub_ = nh.advertise<rcv_common_msgs::trajectory_reference>("/entire_traj",1);
    amount_trajs_pub_ = nh.advertise<rcv_common_msgs::amount_trajs>("/trajs_categorized",1);
    endposes_vis_pub_ = nh.advertise<visualization_msgs::MarkerArray>("safe_stop_endposes_vis",1);
    odom_sub_ = nh.subscribe<nav_msgs::Odometry>("/vehicle/odom",1, &SafeStopTrajectoryPlanner::odom_callback,this);
    SSMP_control_sub_  = nh.subscribe<rcv_common_msgs::SSMP_control>("/SSMP_control",1,&SafeStopTrajectoryPlanner::SSMP_control_callback,this);

    // basically puts the safety planner on hold until both prescan as well as the gridmap are completely loaded, without this, problems will arise
     ros::Duration(2).sleep();


    // loads in the occupancy map
    col_checker = planner_utils::get_collision_checker_from_topic("SSMP_base_link", cm_base, 5, "raw_data");
    ROS_INFO_STREAM("Finished loading safety planner");

    tf::TransformListener tf_listener;

    // load trajectory set
    TrajectorySetHandler traj_set_handler;
    traj_set_handler.load_trajectory_set(trajectory_set_filename, trajSet, v_init_vector);
    traj_set_handler.check_traj_set(trajSet, v_init_vector);

    // initialize traj vars to 0
    traj_set_handler.setTrajToZero(traj);
    traj_set_handler.setTrajToZero(mincost_traj);
    traj_set_handler.setTrajToZero(traj_out_last);
    traj_set_handler.setTrajToZero(traj_out);


    // while running
    try{
      visualization_msgs::MarkerArray endposes_vis_msg;
      while (ros::ok())
      {
        ros::spinOnce();

        col_checker->prepare();       // re-initailize collision checker

        // selection of subset
        int index_of_subset = getSubsetIndex(v_ego,v_init_vector);
        std::vector<TrajectorySetHandler::trajectory> trajSubSet = trajSet.at(index_of_subset);

        // loop through subset
        double min_cost = DBL_MAX;
        int index_of_mincost_traj;
        int green_trajs = 0;
        int yellow_trajs = 0;
        int red_trajs = 0;

        // the set of trajectories only needs to be checked as long as the safety planner is not activated
        if(SSMP_control == 1){
          endposes_vis_msg.markers.clear(); // clears out the last set of endopses markers
          counter = 0; //To reset the waypoint index after switch back to Nominal Channel
          for(size_t i=0; i<trajSubSet.size(); i++){
            traj = trajSubSet.at(i);

            // collision check candidate trajectory
            int val = 0;
            int val_endpose = 0;
            bool isendpose = true;
            for (size_t j=traj.t.size()-1; j>0; j--){
              // set up pose to be checked
              geometry_msgs::PoseStamped pose_st;
              pose_st.pose.position.x = x_ego + traj.X.at(j)*cos(yaw_ego) - traj.Y.at(j)*sin(yaw_ego);
              pose_st.pose.position.y = y_ego + traj.X.at(j)*sin(yaw_ego) + traj.Y.at(j)*cos(yaw_ego);
              tf::Quaternion tf_q = cpp_utils::get_tf_quat(traj.psi.at(j) + yaw_ego);
              tf::quaternionTFToMsg(tf_q,pose_st.pose.orientation);

              // do collision check
              val = (int)round(col_checker->max_val_for_footprint(pose_st));
              if (val >= OBSTRUCTED_THRESHOLD){
                val_endpose = val;
                break; // no reason to continue checking if one pose collides
              }

              // if endpose, store pose and val for cost function evaluation
              if(isendpose){
                isendpose = false;
                val_endpose = val;


                visualization_msgs::Marker end_pose_marker;
                end_pose_marker.header.frame_id = "SSMP_base_link";
                end_pose_marker.header.stamp = ros::Time::now();
                end_pose_marker.id = endposes_vis_msg.markers.size();
                end_pose_marker.type = visualization_msgs::Marker::CUBE;
                end_pose_marker.scale.x = 2.00; // todo: grab from footprint
                end_pose_marker.scale.y = 1.5;
                end_pose_marker.scale.z = 0.1;
                end_pose_marker.color.a = 0.5;
                end_pose_marker.color.r = (float) val_endpose / 100.0f;
                end_pose_marker.color.g = 0.5;
                end_pose_marker.color.b = 0.0;
                end_pose_marker.pose.position.x = traj.X.at(j);
                end_pose_marker.pose.position.y = traj.Y.at(j);
                end_pose_marker.pose.position.z = 0.0;
                end_pose_marker.pose.orientation = tf::createQuaternionMsgFromYaw(traj.psi.at(j));
                endposes_vis_msg.markers.push_back(end_pose_marker);
              }
            }

            // evaluate S(O(x(t)))
            int endpose_cost = val_endpose;
            // int endpose_cost = 0;
            if(val_endpose <= GREEN){           // yellow - in lane
              // endpose_cost = 2;
              green_trajs++;
            } else if(val_endpose <= YELLOW){    // green - safe area
              // endpose_cost = 1;
              yellow_trajs++;
            } else {     // red - unsafe area
              // endpose_cost = 3;
              red_trajs++;
            }

            // evaluate cost function
            // double cost = traj.timeUntilStopped/traj.t.back() + endpose_cost;
            double cost = endpose_cost;
            if(cost < min_cost){
              min_cost = cost;
              index_of_mincost_traj = i;
            }
          }

          // to clear old markers we will publish invisible markers with same id
          for(size_t i=endposes_vis_msg.markers.size(); i<1000; i++){
              visualization_msgs::Marker marker;
              marker.header.frame_id = "SSMP_base_link";
              marker.header.stamp = ros::Time();
              marker.id = i;
              marker.type = visualization_msgs::Marker::DELETE;
              marker.pose.position.x = 1;
              marker.pose.position.y = 1;
              marker.pose.position.z = 1;
              marker.pose.orientation.w = 1.0;
              marker.scale.x = 1;
              marker.scale.y = 0.1;
              marker.scale.z = 0.1;
              marker.color.a = 0.0; // Don't forget to set the alpha!
              marker.color.r = 0.0;
              marker.color.g = 1.0;
              marker.color.b = 0.0;
              endposes_vis_msg.markers.push_back(marker);
          }

          // choose traj with lowest cost
          mincost_traj = trajSubSet.at(index_of_mincost_traj);
          ROS_INFO("Chosen mincost trajectory = %f, cost: %f", mincost_traj.ID, min_cost);
          ROS_INFO("Endposition: (%f, %f)", x_ego+mincost_traj.X.at(99)*cos(yaw_ego)-mincost_traj.Y.at(99)*sin(yaw_ego),y_ego+mincost_traj.X.at(99)*sin(yaw_ego)+mincost_traj.Y.at(99)*cos(yaw_ego));

          // compensate for discretization of input velocity
          double v_diff = v_ego - mincost_traj.v_x.at(0);
          size_t Ntraj = mincost_traj.t.size();
          for(size_t i = 0; i<Ntraj;i++){
            mincost_traj.v_x.at(i) = mincost_traj.v_x.at(i) + v_diff*((double)(Ntraj-i))/((double)Ntraj);
          }

          traj_out = mincost_traj;
        }
        // when switched is flicked, stop calculating new trajs and instead keep current traj and go through it
        else if(SSMP_control == 2){
          traj_out = traj_out_last;
          cpp_utils::add_scalar_to_vector(traj_out.t,-dt);
          counter++;
          // if counter over traj size, traj is done, goto finish leads to somewhere outside this loop, effectively killing this node
          if(counter >= traj_out.t.size()-1){
            ROS_INFO("Real endposition: (%f, %f)", x_ego, y_ego);
//            goto finish;
            ROS_WARN("Resetting SSMP");
            SSMP_control = 1;
          }
        }
        traj_out_last = traj_out;

        // since angular velocity is not present in the traj, it needs to be calculated by hand
        std::vector<double> angvel;
        angvel.push_back(0);
        for(size_t i = 1; i < traj_out.t.size(); i++){
          angvel.push_back(0);
          angvel.at(i) = (traj_out.psi.at(i)-traj_out.psi.at(i-1))/(traj_out.t.at(i)-traj_out.t.at(i-1));
        }

        // create msgs with only current part of traj
        rcv_common_msgs::current_traj_info traj_msg;
        traj_msg.header.stamp = ros::Time::now();
        traj_msg.header.frame_id = "SSMP_base_link";
        traj_msg.t = traj_out.t.at(counter);
        traj_msg.x = traj_out.X.at(counter);
        traj_msg.y = traj_out.Y.at(counter);
        traj_msg.v_lin = traj_out.v_x.at(counter);
        traj_msg.v_ang = angvel.at(counter);

        // create msgs with the complete traj
        rcv_common_msgs::trajectory_reference entire_traj_msg;
        entire_traj_msg.header.stamp = ros::Time::now();
        entire_traj_msg.header.frame_id = "SSMP_base_link";
        entire_traj_msg.t = traj_out.t;
        entire_traj_msg.x = traj_out.X;
        entire_traj_msg.y = traj_out.Y;
        entire_traj_msg.v = traj_out.v_x;
        entire_traj_msg.yaw = traj_out.psi;
        entire_traj_msg.length = (int)traj_out.t.size();

        visualization_msgs::MarkerArray traj_vis_msg;
        traj_vis_msg.markers.clear(); // clear before adding new nodes
        for(int i=0; i<(int)traj_out.t.size(); i++){ // TODO no need to visualize all 100 traj pts
          visualization_msgs::Marker marker;
          marker.header.frame_id = "SSMP_base_link";
          marker.header.stamp = ros::Time::now();
          marker.id = i;
          marker.type = visualization_msgs::Marker::CUBE;
          marker.scale.x = 0.05;
          marker.scale.y = 0.05;
          marker.scale.z = entire_traj_msg.v.at(i)*0.2; // height proportional to v
          marker.pose.position.x = entire_traj_msg.x.at(i);
          marker.pose.position.y = entire_traj_msg.y.at(i);
          marker.pose.position.z = marker.scale.z/2; // offset
          marker.color.a = 1.0;
          marker.color.r = 1.0;
          marker.color.g = 0.5;
          marker.color.b = 0.0;
          traj_vis_msg.markers.push_back(marker);
        }

        // Create msgs containing the amount of red, yellow, and green trajectories
        rcv_common_msgs::amount_trajs trajcategory;
        trajcategory.header.stamp = ros::Time::now();
        trajcategory.green_trajs = green_trajs;
        trajcategory.yellow_trajs = yellow_trajs;
        trajcategory.red_trajs = red_trajs;

        // publish msgs
        traj_pub_.publish(traj_msg);
        if(SSMP_control == 1)
        {
            traj_vis_pub_.publish(traj_vis_msg);
            endposes_vis_pub_.publish(endposes_vis_msg);
        }
        entire_traj_pub_.publish(entire_traj_msg);
        // if(green_trajs+yellow_trajs+red_trajs != 0){
        //   amount_trajs_pub_.publish(trajcategory);
        // }
        amount_trajs_pub_.publish(trajcategory);

        loop_rate.sleep();
      }

      finish:
      ROS_INFO("Finished");

    } catch (const std::out_of_range& oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
    ros::Duration(5).sleep(); // to have time to read the exception message
  }

private:
  // node publishers and subscribers
  ros::NodeHandle nh_;
  ros::Publisher traj_pub_;
  ros::Publisher entire_traj_pub_;
  ros::Publisher amount_trajs_pub_;
  ros::Publisher traj_vis_pub_;
  ros::Publisher safe_stop_trajectory_planner_status_pub_;
  ros::Publisher endposes_vis_pub_;
  ros::Subscriber occ_grid_sub_;
  ros::Subscriber odom_sub_;
  ros::Subscriber SSMP_control_sub_;

  // struct for trajset and vector for init velocities of the respective subsets
  std::vector<float> v_init_vector;
  TrajectorySetHandler::trajectory traj;
  TrajectorySetHandler::trajectory mincost_traj;
  TrajectorySetHandler::trajectory traj_out_last;
  TrajectorySetHandler::trajectory traj_out;
  std::vector<std::vector<TrajectorySetHandler::trajectory>> trajSet;

  // pointer to col_checker object
  planner_utils::TwoDCollisionCheckerI * col_checker;

  // ego state
  float v_ego;
  float x_ego;
  float y_ego;
  float yaw_ego;
  int SSMP_control = 1;
};


int main(int argc, char **argv)
{
  // init node
  ros::init(argc, argv, "ss_trajplanner");
  ros::NodeHandle nh;
  SafeStopTrajectoryPlanner sstp(nh);
  return 0;
}
