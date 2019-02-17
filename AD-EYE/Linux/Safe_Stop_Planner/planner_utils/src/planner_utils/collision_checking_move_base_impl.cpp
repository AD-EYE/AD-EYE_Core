#include <base_local_planner/costmap_model.h>
#include <cpp_utils/pose_datatypes.h>

//#include "collision_checking_move_base_impl.hpp"
#include <planner_utils/collision_checking_move_base_impl.hpp>
//#include <planner_utils/planner_utils.hpp>

namespace planner_utils {

std::vector<geometry_msgs::Point> MoveBaseColCheckShape::get_vertices_transformed(geometry_msgs::PoseStamped const & pose) const {
  throw std::runtime_error(std::string(__PRETTY_FUNCTION__)+std::string(" not implemented"));
}

std::vector<geometry_msgs::Point> MoveBaseColCheckShape::get_vertices() const {
  return footprint_;
}

MoveBaseColCheckShape::MoveBaseColCheckShape(std::vector<geometry_msgs::Point> footprint) :
  footprint_(footprint)
{}


MoveBaseCostmapChecker::MoveBaseCostmapChecker(costmap_2d::Costmap2DROS* costmap_ros) {
  costmap_ros_     = costmap_ros;
  costmap_         = costmap_ros->getCostmap();
  world_model_     = new base_local_planner::CostmapModel(*costmap_);
  col_check_shape_ = new MoveBaseColCheckShape(costmap_ros->getRobotFootprint());
}

MoveBaseCostmapChecker::MoveBaseCostmapChecker(MoveBaseCostmapChecker const & other) {
  costmap_ros_ = other.costmap_ros_;
  costmap_     = other.costmap_;
  footprint_   = other.footprint_;
  world_model_     = new base_local_planner::CostmapModel(*costmap_);
  col_check_shape_ = new MoveBaseColCheckShape(costmap_ros_->getRobotFootprint());
}

MoveBaseCostmapChecker& MoveBaseCostmapChecker::operator= (const MoveBaseCostmapChecker& other){
  costmap_ros_ = other.costmap_ros_;
  costmap_     = other.costmap_;
  footprint_   = other.footprint_;
  world_model_     = new base_local_planner::CostmapModel(*costmap_);
  col_check_shape_ = new MoveBaseColCheckShape(costmap_ros_->getRobotFootprint());
}

void MoveBaseCostmapChecker::prepare() {
  //No-op since move-base already makes sure data is OK
}

//We have to do this for it to work, but should be fast
//enough to do inside every call to "in_collision"
void MoveBaseCostmapChecker::swap_pointers() {
  costmap_   = costmap_ros_->getCostmap();
  footprint_ = costmap_ros_->getRobotFootprint();
  if(costmap_ == NULL) {
    ROS_ERROR("costmap is NULL!");
  }
  if(footprint_.size() == 0) {
    ROS_ERROR("footprint is empty!");
  }
}

MoveBaseCostmapChecker::~MoveBaseCostmapChecker() {
  delete world_model_;
  delete col_check_shape_;
}

double MoveBaseCostmapChecker::distance_to_closest_obstacle(const geometry_msgs::PoseStamped &pose) {
  throw std::runtime_error(std::string(__PRETTY_FUNCTION__)+std::string(" operation not supported"));
}

double MoveBaseCostmapChecker::max_val_for_footprint( geometry_msgs::PoseStamped const & pose ) {
  swap_pointers();

  ROS_DEBUG_STREAM(__PRETTY_FUNCTION__);

  Eigen::Vector3d state = cpp_utils::extract_pose_SE2_from_geom_msgs(pose);

  uint grid_x, grid_y;
  if(!costmap_->worldToMap(state(0),state(1),grid_x,grid_y)) {
    //outside grid
    //ROS_INFO("Outside grid: (%i, %i)", grid_x, grid_y);
    return do_collision_check_outside_region_;
  }
  //ROS_INFO("Inside grid: (%i, %i)", grid_x, grid_y);
  ROS_DEBUG_STREAM("Position = " << pose.pose.position.x << ", " <<
                   pose.pose.position.y << " grid = " << grid_x << ", "<< grid_y);

  //this does NOT assume inflation, so we can't skip checking for some
  //specific value of base_link cost
  unsigned int  index = costmap_->getIndex(grid_x,grid_y);
  //ROS_INFO("this returns pointindex: %i", index);
  unsigned char cost  = costmap_->getCharMap()[index];
  //ROS_INFO("this returns pointcost: %i", cost);
  
  if(footprint_.size() < 3) {
    //we have no footprint
    ROS_INFO("Invalid robot footprint, using center");
    return cost;
  }

  double cos_th = cos(state(2));
  double sin_th = sin(state(2));
  double const x_bl = costmap_->getOriginX();
  double const y_bl = costmap_->getOriginY();
  //ROS_INFO("Origin: (%f, %f)", x_bl, y_bl);
  double const width  = costmap_->getSizeInMetersX();
  double const height = costmap_->getSizeInMetersY();

  for(geometry_msgs::Point const & p : footprint_) {
    double x_p = state(0) + (p.x*cos_th - p.y*sin_th);
    double y_p = state(1) + (p.x*sin_th + p.y*cos_th);
    if( x_p >= x_bl && x_p <= x_bl+width && y_p >= y_bl && y_p <= y_bl+height) {
      //inside -- OK to check
      //ROS_INFO("footprint point at %f %f inside costmap",x_p,y_p);

    } else {

      //ROS_INFO("footprint point at %f %f outside costmap",x_p,y_p);
      if(do_collision_check_outside_region_) {
        return std::numeric_limits<double>::max(); //defined to be in collision
      } else {
        ///@todo remove points outside region from footprint?
        /// THIS IS A HACK...
        return 0; //defined to be OK
      }
    }
  }

  /* Documentation for footprintCost:
   *
   * @return Positive if all the points lie outside the footprint, negative otherwise
   */
  double footprint_cost = world_model_->footprintCost(state(0),state(1),state(2),footprint_);

  return footprint_cost;

}

bool MoveBaseCostmapChecker::in_collision(const geometry_msgs::PoseStamped &pose) {

  swap_pointers();

  ROS_DEBUG_STREAM(__PRETTY_FUNCTION__);

  Eigen::Vector3d state = cpp_utils::extract_pose_SE2_from_geom_msgs(pose);


  uint grid_x, grid_y;
  if(!costmap_->worldToMap(state(0),state(1),grid_x,grid_y)) {
    //outside grid
    ROS_DEBUG_STREAM("Outside grid");
    return do_collision_check_outside_region_;
  }
  ROS_DEBUG_STREAM("Position = " << pose.pose.position.x << ", " <<
                   pose.pose.position.y << " grid = " << grid_x << ", "<< grid_y);

  unsigned int  index = costmap_->getIndex(grid_x,grid_y);
  unsigned char cost  = costmap_->getCharMap()[index];
  if(cost < 128) {
    ROS_DEBUG_STREAM("completely clear");
    //completely clear
    return false;
  }

  if(footprint_.size() < 3) {
    //we have no footprint
    ROS_WARN_THROTTLE(1,"Invalid robot footprint, ignoring");
    return false;
  }

  double cos_th = cos(state(2));
  double sin_th = sin(state(2));
  double const x_bl = costmap_->getOriginX();
  double const y_bl = costmap_->getOriginY();
  double const width  = costmap_->getSizeInMetersX();
  double const height = costmap_->getSizeInMetersY();

  for(geometry_msgs::Point const & p : footprint_) {
    double x_p = state(0) + (p.x*cos_th - p.y*sin_th);
    double y_p = state(1) + (p.x*sin_th + p.y*cos_th);

    if( x_p >= x_bl && x_p <= x_bl+width && y_p >= y_bl && y_p <= y_bl+height) {
      //inside -- OK to check
      ROS_DEBUG("footprint point at %f %f inside costmap",x_p,y_p);

    } else {

      ROS_DEBUG("footprint point at %f %f outside costmap",x_p,y_p);
      if(do_collision_check_outside_region_) {
        return true; //defined to be in collision
      } else {
        ///@todo remove points outside region from footprint?
        return false; //defined to be OK
      }
    }
  }

  /* Documentation for footprintCost:
   *
   * @return Positive if all the points lie outside the footprint, negative otherwise
   */
  double footprint_cost = world_model_->footprintCost(state(0),state(1),state(2),footprint_);

  ROS_DEBUG("Footprint cost for pose %f %f %f = %f",state(0),state(1),state(2),footprint_cost);

  if(footprint_cost >= 0 ) { //&& footprint_cost < 150.0 ){
    return false; //no collision
  } else {
    return true; //collision
  }

}


std::vector<TwoDCollisionCheckerI::COLLISION_CHECK_TYPE> MoveBaseCostmapChecker::get_supported_types() const {
  return std::vector<TwoDCollisionCheckerI::COLLISION_CHECK_TYPE>(1,TwoDCollisionCheckerI::COLLISION_CHECK_TYPE::CONVEX_POLY);
}

ConvexPolygonRobotShapeI const & MoveBaseCostmapChecker::get_polygon_shape() const {
  return *col_check_shape_;
}

CircleCoverRobotShapeI const & MoveBaseCostmapChecker::get_circle_shape() const {
  throw std::runtime_error(std::string(__PRETTY_FUNCTION__)+
                           std::string(" Operation not supported, ros costmap uses polygon shape"));
}

}
