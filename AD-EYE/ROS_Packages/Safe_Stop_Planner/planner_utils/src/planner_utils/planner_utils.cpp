#include "planner_utils/planner_utils.hpp"
#include <cpp_utils/interp.h>
#include <cpp_utils/path_ops.h>

#include <tf/LinearMath/Quaternion.h>
#include <tf/transform_datatypes.h>
#include <visualization_msgs/Marker.h>

namespace planner_utils {

//Utitlity functions, for cutting and stitching together paths

std::vector<double> get_path_s(std::vector<geometry_msgs::PoseStamped> const & input_path) {
  std::vector<double> path_s = {0.0};
  for(size_t i=1; i<input_path.size(); ++i) {
    geometry_msgs::PoseStamped const & pose      = input_path.at(i);
    geometry_msgs::PoseStamped const & pose_prev = input_path.at(i-1);
    double dx = pose.pose.position.x - pose_prev.pose.position.x;
    double dy = pose.pose.position.y - pose_prev.pose.position.y;
    path_s.push_back(path_s.back()+sqrt(dx*dx+dy*dy));
  }
  return path_s;
}

geometry_msgs::PoseStamped interp_pose(double s_prev, double s_next, double s_intrp,
                                       geometry_msgs::PoseStamped const & prev_pose,
                                       geometry_msgs::PoseStamped const & next_pose) {
  double t = (s_intrp-s_prev)/(s_next-s_prev);
  assert(t>=0.0);
  assert(t<=1.0);

  tf::Stamped<tf::Pose> prev, next;
  tf::poseStampedMsgToTF(prev_pose,prev);
  tf::poseStampedMsgToTF(next_pose,next);

  tf::Vector3 prev_v = prev.getOrigin();
  tf::Vector3 next_v = next.getOrigin();

  tf::Vector3 interped_v    = prev_v + (next_v-prev_v)*t;
  tf::Quaternion interped_q = prev.getRotation().slerp(next.getRotation(),t);

  //we have to be really carefull of z values!
  //if(next_v.z() < 0 ) //always let the direction be the same as next
  interped_v.setZ(next_v.z());

  //copy to get metadata right
  geometry_msgs::PoseStamped interped_pose = prev_pose;
  interped_pose.pose.position.x = interped_v.x();
  interped_pose.pose.position.y = interped_v.y();
  interped_pose.pose.position.z = interped_v.z();
  interped_pose.pose.orientation.x = interped_q.x();
  interped_pose.pose.orientation.y = interped_q.y();
  interped_pose.pose.orientation.z = interped_q.z();
  interped_pose.pose.orientation.w = interped_q.w();

  return interped_pose;
}

std::vector<geometry_msgs::PoseStamped> remove_before(std::vector<geometry_msgs::PoseStamped> const & path,
                                                      double s_begin,
                                                      bool do_interp) {
  std::vector<double> path_s = get_path_s(path);

  //it points to first point larger than s_begin
  auto it = std::upper_bound(path_s.begin(),path_s.end(),s_begin);

  std::vector<geometry_msgs::PoseStamped> to_keep;

  if(it == path_s.end()) {

    //there is no point larger than s_end
    throw std::runtime_error("s_begin is larger than s[-1]!");

  } else if(it==path_s.begin()) {
    //the first point is larger than s_begin
    ROS_WARN("There are no points to remove");
    return path;
  } else {
    to_keep = std::vector<geometry_msgs::PoseStamped>(path.begin()+(it-path_s.begin()),path.end());
  }

  if(do_interp) {

    //then we need to interpolate a point between it-1 and it
    size_t prev_i = it - path_s.begin() -1;
    size_t next_i = it - path_s.begin();

    //figure out "t"
    double s_prev = *(it-1);
    double s_next = *it;

    assert(s_next >= s_prev);

    to_keep.insert(to_keep.begin(),
                   interp_pose(s_prev,s_next,s_begin,path.at(prev_i),path.at(next_i)));
  }
  return to_keep;
}


std::vector<geometry_msgs::PoseStamped> remove_after(std::vector<geometry_msgs::PoseStamped> const & path,
                                                     double s_end,
                                                     bool do_interp) {
  std::vector<double> path_s = get_path_s(path);

  //find point before s_end

  //it points to first point larger than s_end
  auto it = std::upper_bound(path_s.begin(),path_s.end(),s_end);

  std::vector<geometry_msgs::PoseStamped> to_keep;

  if(it == path_s.end()) {
    //there is no point larger than s_end
    ROS_WARN("There are no points to remove");
    return path;
  } else if(it==path_s.begin()) {
    //the first point is larger than s_end
    throw std::runtime_error("s_end is smaller than zero!");
  } else {
    to_keep = std::vector<geometry_msgs::PoseStamped>(path.begin(),path.begin()+(it-path_s.begin()));
  }

  if(do_interp) {
    //then we need to interpolate a point between it-1 and it
    size_t prev_i = it - path_s.begin() -1;
    size_t next_i = it - path_s.begin();

    double s_prev = *(it-1);
    double s_next = *it;

    to_keep.push_back(interp_pose(s_prev,s_next,s_end,path.at(prev_i),path.at(next_i)));
  }
  return to_keep;
}

PathFixer::PathFixer()
{
  fixed_pose_publisher_ = node_handle_.advertise<visualization_msgs::Marker>("fixed_pose",1);
  path_point_pub_ = node_handle_.advertise<visualization_msgs::Marker>("path_fixer_path_points",1);
}

bool PathFixer::initialized() const {
  return state_ != NO_PATH;
}

void PathFixer::reset_state(const geometry_msgs::PoseStamped &start_pose) {
  ROS_INFO("Reset path_fixer");
  fixed_pose_ = start_pose;
  fixed_pose_.pose.position.z = 0.0;

  state_ = NO_PATH;
  s_start_ = 0.0;
  s_total_ = 0.0;
}

geometry_msgs::PoseStamped PathFixer::get_start_pose(const geometry_msgs::PoseStamped& start_input)  {

  if(!initialized()) {
    reset_state(start_input);
  }

  //store current pose
  current_pose_ = start_input;

  //visualize this for debugging
  visualization_msgs::Marker fixed_pose_marker;
  fixed_pose_marker.header.stamp = ros::Time::now();
  fixed_pose_marker.header.frame_id = start_input.header.frame_id;
  fixed_pose_marker.ns = "fixed_pose_marker";
  fixed_pose_marker.id = fixed_path_id_++;
  fixed_pose_marker.pose = fixed_pose_.pose;
  //fixed_pose_marker.pose.position.z = fixed_path_id_*0.4;
  fixed_pose_marker.type = visualization_msgs::Marker::SPHERE;
  fixed_pose_marker.scale.x = fixed_pose_marker.scale.y = fixed_pose_marker.scale.z = 0.125;
  fixed_pose_marker.color.a = 1.0;
  fixed_pose_marker.color.r = 1.0;
  fixed_pose_marker.color.g = fixed_pose_marker.color.b = 0.0;

  fixed_pose_publisher_.publish(fixed_pose_marker);

  //  if(fixed_path_id_ > 4) {
  //    throw std::runtime_error("YO");
  //  }
  return fixed_pose_;
}

void PathFixer::publish_current_path_points(std::vector<geometry_msgs::PoseStamped> const & path_to_pub,
                                            double r,double g, double b, double lat_offset) {
  visualization_msgs::Marker m;
  m.header.stamp = ros::Time::now();
  m.header.frame_id = current_pose_.header.frame_id;
  m.ns = "path_fixer_path_points";
  m.id = fixed_path_id_ + (int)(1000*lat_offset);
  m.pose.position.x = m.pose.position.y = 0.0;
  m.pose.position.z = fixed_path_id_*0.4;
  m.pose.orientation.x = m.pose.orientation.y = m.pose.orientation.z = 0.0;
  m.pose.orientation.w = 1.0;
  m.type = visualization_msgs::Marker::SPHERE_LIST;

  m.points.resize(path_to_pub.size());
  for(size_t i=0; i<path_to_pub.size(); ++i) {
    geometry_msgs::PoseStamped const & pose = path_to_pub.at(i);
    m.points.at(i) = pose.pose.position;
    //add lateral offset
    tf::Stamped<tf::Pose> tf_p;
    poseStampedMsgToTF(pose,tf_p);
    double useless_pitch, useless_roll, yaw;
    tf_p.getBasis().getEulerYPR(yaw, useless_pitch, useless_roll);

    m.points.at(i).x += lat_offset*cos(yaw+M_PI/2);
    m.points.at(i).y += lat_offset*sin(yaw+M_PI/2);
  }
  m.scale.x = m.scale.y = m.scale.z = 0.075;
  m.color.a = 1.0;
  m.color.r = r;
  m.color.g = g;
  m.color.b = b;

  path_point_pub_.publish(m);

}

std::vector<geometry_msgs::PoseStamped> PathFixer::update_path(const std::vector<geometry_msgs::PoseStamped> &path,
                                                               bool estimate_theta) {


  auto get_interp_data = []( std::vector<double> & path_x,
      std::vector<double> & path_y,
      std::vector<double> & path_z,
      std::vector<double> & path_s,
      std::vector<tf::Quaternion> & path_th,
      const std::vector<geometry_msgs::PoseStamped> &path,
      bool estimate_theta) -> void {

    size_t N = path.size();
    path_x.clear();
    path_y.clear();
    path_th.clear();
    path_x.reserve(N);
    path_y.reserve(N);
    path_z.reserve(N);
    path_th.reserve(N);

    for(size_t i=0; i<path.size(); ++i) {
      double len_to_prev = std::numeric_limits<double>::max();
      if(i>0) {
        double dx = path.at(i).pose.position.x - path_x.back();
        double dy = path.at(i).pose.position.y - path_y.back();
        len_to_prev = dx*dx + dy*dy;
      }

      if(len_to_prev > 1.0e-3) {
        path_x.push_back(path.at(i).pose.position.x);
        path_y.push_back(path.at(i).pose.position.y);
        path_z.push_back(path.at(i).pose.position.z);

        tf::Stamped<tf::Pose> tf_pose;
        tf::poseStampedMsgToTF(path.at(i),tf_pose);
        //        double useless_pitch, useless_roll, yaw;
        //        tf_pose.getBasis().getEulerYPR(yaw, useless_pitch, useless_roll);
        path_th.push_back(tf_pose.getRotation());
      }
    }
    if(estimate_theta) {
      path_th.resize(path_x.size());
    }
    path_s.resize(path_x.size());
    path_s.at(0) = 0.0;

    for(size_t i=0; i<path_x.size()-1; ++i) {
      double dx = path_x.at(i+1)-path_x.at(i);
      double dy = path_y.at(i+1)-path_y.at(i);
      path_s.at(i+1) = path_s.at(i) + sqrt(dx*dx + dy*dy);

      if(estimate_theta) {
        path_th.at(i) = tf::createQuaternionFromYaw(atan2(dy,dx));
      }
    }
    if(path_th.size()>1 && estimate_theta) {
      path_th.at(path_th.size()-1) = path_th.at(path_th.size()-2);
    }
  };

  auto veify_path = [this] () {
    //check that we don't have duplicate x,y,z values in the path
    //    for(size_t i=0; i<path_.size()-1; ++i) {
    //      geometry_msgs::PoseStamped const & curr = path_.at(i);
    //      geometry_msgs::PoseStamped const & nxt  = path_.at(i+1);

    //      double dx = curr.pose.position.x - nxt.pose.position.x;
    //      double dy = curr.pose.position.y - nxt.pose.position.y;
    //      double dz = curr.pose.position.z - nxt.pose.position.z;
    //      if( dx*dx + dy*dy + dz*dz < 1.0e-5 ) {
    //        std::stringstream ss;
    //        ss << "Distance^2 between consecutive points path_["<<i<<"] and path_["<<i+1<<"] is less than 1.0e-5!";
    //        ss << std::endl << "Path = ";
    //        for(geometry_msgs::PoseStamped const & pose : path_) {
    //          ss << pose.pose.position.x << ", " <<  pose.pose.position.y << ", " <<  pose.pose.position.z << "; ";
    //        }
    //        throw std::logic_error(ss.str());
    //      }
    //    }
    std::stringstream ss;
    ss << "Path direction: ";
    for(geometry_msgs::PoseStamped const & pose : path_) {
      ss << (pose.pose.position.z < 0 ? "R":"F") << ", ";
    }
    ROS_INFO_STREAM(ss.str());
  };



  switch(state_) {
  case NO_PATH:
  {
    s_start_ = 0.0;
    s_total_ = 0.0;
    path_  = path;
    state_ = PATH_LOCKED;
    //interpolate to find point on the path
    std::vector<double> path_x,path_y,path_z,path_s;
    std::vector<tf::Quaternion> path_th;
    get_interp_data(path_x,path_y,path_z,path_s,path_th,path,estimate_theta);

    //we should never lock a point after a direction change, since we assume that v=0 at these points?


    std::vector<double> s_interp = {std::min(PATH_LOCK_DISTANCE,path_s.back())};


    ROS_INFO("Will interpolate fixed point at s = %.2f from path with s=[%.2f,%.2f]",
             s_interp.at(0),path_s.front(),path_s.back());

    double x  = cpp_utils::interp<double>(s_interp, path_s, path_x, false).at(0);
    double y  = cpp_utils::interp<double>(s_interp, path_s, path_y, false).at(0);
    double z  = cpp_utils::interp<double>(s_interp, path_s, path_z, false).at(0);
    tf::Quaternion th = cpp_utils::interp_angle<double>(s_interp, path_s, path_th, false).at(0);

    fixed_pose_.pose.position.x = x;
    fixed_pose_.pose.position.y = y;
    //Need to make sure the fixed pose is reversing or not!
    fixed_pose_.pose.position.z = z;

    fixed_pose_.pose.orientation.w = th.getW();
    fixed_pose_.pose.orientation.x = th.getX();
    fixed_pose_.pose.orientation.y = th.getY();
    fixed_pose_.pose.orientation.z = th.getZ();

    ROS_INFO("No previous path for path_fixer, locking fixed point at %.2f %.2f %.2f",
             fixed_pose_.pose.position.x,fixed_pose_.pose.position.y,fixed_pose_.pose.position.z);

    publish_current_path_points(path_,0.0,0.0,1.0);

    veify_path();

    return path_;
  }
    break;
  case PATH_LOCKED:
  {
    //input to this iteration
    publish_current_path_points(path_,1.0,0.0,1.0,-0.5);

    double traveled_s = PlanStatusSingleton::getInstance().traveled_s;

    ROS_INFO("We have moved %.2f along our old path",traveled_s);

    //discard everything of our old path that is after PATH_LOCK_DISTANCE
    //do NOT interp a new point, since this is by defintion the start point of our new path
    std::vector<geometry_msgs::PoseStamped> to_keep = remove_after(path_,PATH_LOCK_DISTANCE,false);

    //path until last fixed point (RED)
    publish_current_path_points(to_keep,1.0,0.0,0.0,0.2);

    //add the new planned path
    to_keep.insert(to_keep.end(), path.begin(), path.end());

    geometry_msgs::PoseStamped previous_fixed_pose = fixed_pose_;

    std::vector<double> path_s = get_path_s(to_keep);

    double fixpoint_s = PATH_LOCK_DISTANCE+traveled_s;
    //first point larger than fixpoint s
    auto it           = std::upper_bound(path_s.begin(),path_s.end(),fixpoint_s);

    if(it == path_s.end()) {
      //let fixed_pose be the last point (goal)
      fixed_pose_ = to_keep.back();
    } else if(it == path_s.begin()){
      throw std::runtime_error("fixpoint s is smaller than zero!");
    } else {
      //interpolate a point
      size_t prev_i = it - path_s.begin() -1;
      size_t next_i = it - path_s.begin();
      double s_prev = *(it-1);
      double s_next = *it;
      fixed_pose_ = interp_pose(s_prev,s_next,fixpoint_s,to_keep.at(prev_i),to_keep.at(next_i));
    }

//    double dx = previous_fixed_pose.pose.position.x - fixed_pose_.pose.position.x;
//    double dy = previous_fixed_pose.pose.position.y - fixed_pose_.pose.position.y;
//    double dist = sqrt(dx*dx + dy*dy );
//    if( traveled_s > 0.01 && dist > 2.0*traveled_s) { ///@todo
//      std::stringstream ss;
//      ss << "previous fixed pose: " << previous_fixed_pose.pose.position.x << ", " << previous_fixed_pose.pose.position.y;
//      ss << " new fixed pose: " << fixed_pose_.pose.position.x << ", " << fixed_pose_.pose.position.y;
//      ss << " dist = " << dist << " traveled_s = " << traveled_s;
//      throw std::runtime_error(ss.str());
//    }


    //remove beginning of path corresponding to how we moved.
    //But, we should keep a small tail...
    path_ = remove_before(to_keep,std::max(0.0,traveled_s-0.01),true);

    ROS_INFO_STREAM("#nodes before cut = " << to_keep.size() << " after = " << path_.size());
    ROS_INFO_STREAM("length before cut = " << path_s.back() << " after = " << get_path_s(path_).back());

    publish_current_path_points(path,0.0,1.0,0.0,0.4);

    publish_current_path_points(path_,0.0,0.0,1.0);

    veify_path();

    return path_;
  }
    break;
  }

}



bool collision_check(costmap_2d::Costmap2D* costmap,
                     std::vector<geometry_msgs::Point> & footprint,
                     base_local_planner::WorldModel* world_model,
                     Eigen::Vector3d const & state)
{
  //we could try a simpler approac...
  //given a set of circles for the car, check these positions ONLY..


  uint grid_x, grid_y;
  if(!costmap->worldToMap(state(0),state(1),grid_x,grid_y)) {
    //outside grid
    ROS_DEBUG("Outside grid");

    return false;
  }
  unsigned int  index = costmap->getIndex(grid_x,grid_y);
  unsigned char cost  = costmap->getCharMap()[index];

  ROS_DEBUG("grid_x,grid_y = (%d,%d), cost = %d, getCost() = %d",
            grid_x,grid_y,cost,costmap->getCost(grid_x,grid_y));

  if(cost < 128) {
    //completely clear
    return false;
  }

  if(footprint.size() < 3) {
    //we have no footprint
    ROS_WARN_THROTTLE(1,"Invalid robot footprint, ignoring");
    return false;
  }
  ///@todo take a closer look at this: how to really use the world model
  //ignore any footprint with a point outside the costmap
  double cos_th = cos(state(2));
  double sin_th = sin(state(2));
  double const x_bl = costmap->getOriginX();
  double const y_bl = costmap->getOriginY();
  double const width  = costmap->getSizeInMetersX();
  double const height = costmap->getSizeInMetersY();

  for(geometry_msgs::Point const & p : footprint) {
    double x_p = state(0) + (p.x*cos_th - p.y*sin_th);
    double y_p = state(1) + (p.x*sin_th + p.y*cos_th);

    if( x_p >= x_bl && x_p <= x_bl+width && y_p >= y_bl && y_p <= y_bl+height) {
      //inside -- OK to check
      ROS_DEBUG("footprint point at %f %f inside costmap",x_p,y_p);

    } else {

      ROS_DEBUG("footprint point at %f %f outside costmap",x_p,y_p);
      return false;
    }
  }

  /* Documentation for footprintCost:
   *
   * @return Positive if all the points lie outside the footprint, negative otherwise
   */
  double footprint_cost = world_model->footprintCost(state(0),state(1),state(2),footprint);

  ROS_DEBUG("Footprint cost for pose %f %f %f = %f",state(0),state(1),state(2),footprint_cost);

  if(footprint_cost >= 0 ) { //&& footprint_cost < 150.0 ){
    return false; //no collision
  } else {
    return true; //collision
  }
}

}
