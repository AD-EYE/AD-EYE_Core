#include "cpp_utils/path_ops.h"
#include "cpp_utils/interp.h"
#include <iostream>
#include <tf/transform_datatypes.h>

namespace cpp_utils {

void PathDistanceChecker::free_resources() {
  if(path_kdtree_ != NULL)
    delete path_kdtree_;
}




void PathDistanceChecker::initialize_path(std::vector<geometry_msgs::PoseStamped> & path){
  free_resources();

  if(path.size()<2) {
    throw std::runtime_error(std::string(__func__)+std::string(": path must contain at least two elements"));
  }

  //It is very importatn that the points of the path has some distance between them, otherwise we can't do
  //some of the operations

  std::vector<geometry_msgs::PoseStamped> pruned_path = {path.at(0)};
  for(size_t i=1; i<path.size(); ++i) {
    double dx = path.at(i).pose.position.x-pruned_path.back().pose.position.x;
    double dy = path.at(i).pose.position.y-pruned_path.back().pose.position.y;
    double dist = dx*dx + dy*dy;
    if(dist > 0.01) {
      pruned_path.push_back(path.at(i));
    }
  }
  if(pruned_path.size()<2) {
    throw std::runtime_error(std::string(__func__)+std::string(": path must contain at least two elements that are not the same"));
  }

  path_data_.path_.resize(pruned_path.size());
  path_rot_.resize(pruned_path.size());
  path_x_.resize(pruned_path.size());
  path_y_.resize(pruned_path.size());
  path_s_.resize(pruned_path.size());

  for(size_t i=0; i<pruned_path.size(); ++i) {
    geometry_msgs::PoseStamped const & pose = pruned_path.at(i);
    path_data_.path_.at(i) << pose.pose.position.x,pose.pose.position.y;

    path_x_.at(i) = pose.pose.position.x;
    path_y_.at(i) = pose.pose.position.y;

    tf::Stamped<tf::Pose> tf_pose;
    tf::poseStampedMsgToTF(pose,tf_pose);
    path_rot_.at(i) = tf_pose.getRotation();

    if(i==0) {
      path_s_.at(i) = 0.0;
    } else {
      Eigen::Vector2f delta = path_data_.path_.at(i)-path_data_.path_.at(i-1);
      path_s_.at(i) = path_s_.at(i-1) + delta.norm();
    }
  }
  path_kdtree_ = new kdtree_t(2,path_data_,nanoflann::KDTreeSingleIndexAdaptorParams(10));
  path_kdtree_->buildIndex();
  initialized_ = true;
}

void PathDistanceChecker::initialize_path(std::vector<Eigen::Vector2f> &path) {
  free_resources();

  if(path.size()<2) {
    throw std::runtime_error(std::string(__func__)+std::string(": path must contain at least two elements"));
  }


  path_data_.path_ = path;

  path_s_.resize(path.size());
  path_s_[0] = 0.0;
  for(size_t i=1; i<path.size(); ++i) {
    Eigen::Vector2f delta = path[i]-path[i-1];
    path_s_[i] = path_s_[i-1] + delta.norm();
  }
  path_x_.resize(path.size());
  path_y_.resize(path.size());
  path_rot_.resize(path.size());
  path_theta_.resize(path.size());

  for(size_t i=0; i<path.size()-1; ++i) {
    path_theta_[i] = atan2(path[i](1)-path[i-1](1),path[i](0)-path[i-1](0));
  }
  path_theta_[path.size()-1] = path_theta_[path.size()-2];

  for(size_t i=0; i<path.size(); ++i) {
    path_rot_.at(i) = tf::createQuaternionFromYaw(path_theta_.at(i));
  }


  for(size_t i=0; i<path.size(); ++i) {
    path_x_[i] = path[i](0);
    path_y_[i] = path[i](1);
  }

  path_kdtree_ = new kdtree_t(2,path_data_,nanoflann::KDTreeSingleIndexAdaptorParams(10));
  path_kdtree_->buildIndex();
  initialized_ = true;
}

PathDistanceChecker::~PathDistanceChecker() {
  free_resources();
}



Eigen::Vector3f PathDistanceChecker::get_pose(PathDist<float> pd) {
  if(!initialized_) {
    throw std::logic_error("Cannot get a pose relative path, without initializing with a path");
  }
  std::vector<float> s_vals;
  s_vals.push_back(pd.s);

  float x_  = interp(s_vals,path_s_,path_x_,true).at(0);
  float y_  = interp(s_vals,path_s_,path_y_,true).at(0);
  tf::Quaternion rot = interp_angle(s_vals,path_s_,path_rot_,true).at(0);

  double roll,pitch,th_;
  tf::Matrix3x3(rot).getRPY(roll,pitch,th_);

  //float th_ = interp(s_vals,path_s_,path_theta_,true).at(0);
  Eigen::Vector2f v; v << cos(th_+M_PI/2),sin(th_+M_PI/2);
  v*=pd.signed_d;

  Eigen::Vector3f pose;
  pose << x_+v(0),y_+v(1),th_;
  return pose;
}

std::vector<int> PathDistanceChecker::get_points_by_distance(Eigen::Vector2f query) const {
  std::vector<std::pair<int,float>> idx_dist(path_data_.path_.size());

  for(size_t i=0; i<path_data_.path_.size(); ++i) {
    idx_dist.at(i) = std::make_pair(i,(query-path_data_.path_.at(i)).norm());
  }

  //sort by second thing
  std::sort(idx_dist.begin(),idx_dist.end(),
            [] (std::pair<int,float> const & a,std::pair<int,float> const & b)
  {
    return a.second < b.second;
  });

  std::vector<int> idx(idx_dist.size());
  for(size_t i=0; i<idx_dist.size(); ++i) {
    idx.at(i) = idx_dist.at(i).first;
  }
  return idx;
}

PathDist<float> PathDistanceChecker::get_next_path_distance(float position_x, float position_y,
                                                     float atleast_s, float expected_s, float tol) const{
  if(!initialized_)
    throw std::runtime_error("Cannot get path distance without initializing with a path!");

  using namespace Eigen;
  Vector2f p; p << position_x, position_y;

  std::vector<Vector2f> const & path = path_data_.path_;

  float min_d;
  int   min_d_idx;

  std::stringstream ss;

  auto get_min_pd = [this,&atleast_s,&expected_s,&tol,&p,&path,&min_d,&min_d_idx,&ss] (bool debug_print){

    min_d = std::numeric_limits<float>::max();
    min_d_idx = -1;

    float s_path = 0.0;

    PathDist<float> min_dist;

    for(int i=0; i<path.size()-1; ++i) {


      Vector2f base = path.at(i);
      Vector2f tip  = path.at(i+1);

      Vector2f a = p-base;
      Vector2f b = tip-base;


      float nxt_s_path = s_path+b.norm();



      //only do projections on path segements that include, or are beyond atleast_s
      if(nxt_s_path < atleast_s) {
        if(debug_print) {
          ss << "i = " << i << " nxt_s_path = " << nxt_s_path << " atleast_s " << atleast_s << std::endl;
        }
        s_path += b.norm();
        continue;
      }

      //if the path segment contains atleast_s
      //do the projection only on the remaining segment
      //AND scalar projection must be positive!
      float s_extra = 0.0;
      if(atleast_s-s_path > 0) {
        base += b*(atleast_s-s_path);
        b = tip-base;
        a = p-base;
        s_extra = atleast_s-s_path;
      }



      //projection of a onto b
      float t = a.dot(b) / b.norm();

      Vector2f a_1 = t*b/b.norm();
      Vector2f a_2 = a-a_1;

      //orthogonal distance
      float d = a_2.norm();

      float node_s = t+s_path+s_extra;


      if(debug_print) {
        ss << "i = " <<i << " d = " << d << " node_s = " << node_s
           << "( t = " << t  << ", s_path = " << s_path << ") " <<std::endl;
      }



      //distance along the path since atleast_s


      if(d < min_d && std::abs(node_s-expected_s) <= tol) {
        min_d_idx = i;
        min_d = d;

        //it must at-least increase by epsilon
        //this is such a hack! :(
        node_s = std::max(node_s,atleast_s+1.0e-2f);
        min_dist = PathDist<float>(node_s,d,side_of_line(p,base,tip)*d);
      }

      s_path += b.norm();
    }

//    if(min_d_idx < 0) {
//      //return the last point...
//      min_d_idx = path.size()-1;
//      min_dist = PathDist(s_path,0.0,0.0);
//    }
    return min_dist;
  };
  PathDist<float> min_dist = get_min_pd(true);

  //ROS_INFO_STREAM(ss.str());

  if(min_d_idx < 0) {
    //get_min_pd(true);
    //throw std::logic_error("No valid min distance point found:\n"+ss.str());
    throw std::logic_error(ss.str());
  }
  return min_dist;
}

PathDist<float> PathDistanceChecker::get_path_distance(float position_x, float position_y, float guess_s, float tol) const {
  if(!initialized_)
    throw std::runtime_error("Cannot get path distance without initializing with a path!");

  //search for two nearest neightbours
//  std::vector<size_t>   ret_indexes(2);
//  std::vector<float>    out_dists_sqr(2);
//  nanoflann::KNNResultSet<float> resultSet(2);
//  resultSet.init(&ret_indexes[0],&out_dists_sqr[0]);
//  float query_pt[2] = {postion_x,position_y};
//  path_kdtree_->findNeighbors(resultSet,&query_pt[0],nanoflann::SearchParams());

//  std::sort(ret_indexes.begin(),ret_indexes.end());

  //Just do orthogonal projection as normal! Take the "s" with the closest
  //orthogonal distance
  using namespace Eigen;
  Vector2f p; p << position_x, position_y;

  std::vector<Vector2f> const & path = path_data_.path_;

  float min_d = std::numeric_limits<float>::max();
  int   min_d_idx = -1;

  float s_path = 0.0;

  PathDist<float> min_dist;

  for(int i=0; i<path.size()-1; ++i) {

    Vector2f base = path.at(i);
    Vector2f tip  = path.at(i+1);

    Vector2f a = p-base;
    Vector2f b = tip-base;


    //projection of a onto b
    float t = a.dot(b) / b.norm();

    Vector2f a_1 = t*b/b.norm();
    Vector2f a_2 = a-a_1;

    //orthogonal distance
    float d = a_2.norm();

    if(t < 0) {
      d = a.norm();
    }
    if(t > b.norm()) {
      d = (p-tip).norm();
    }

    float node_s = t+s_path;

    if(d < min_d && std::abs(node_s-guess_s) <= tol) {
      min_d_idx = i;
      min_d = d;

      min_dist = PathDist<float>(node_s,d,side_of_line(p,base,tip)*d);
    }

    s_path += b.norm();
  }
  if(min_d_idx < 0) {
    throw std::logic_error("No valid min distance point found");
  }
  return min_dist;



  /*
  Eigen::Vector2f query; query << position_x,position_y;
  std::vector<int> ret_indexes = get_points_by_distance(query);

  using namespace Eigen;

  std::vector<Vector2f> const & path = path_data_.path_;

  Vector2f base = path[ret_indexes[0]];
  Vector2f tip  = path[ret_indexes[1]];

  Vector2f t_b, t_t;

  if(ret_indexes[0] == 0) {
    t_b = path[1]-path[0];
  } else {
    t_b = path[ret_indexes[0]+1]-path[ret_indexes[0]-1];
  }

  t_b = t_b / t_b.norm();

  if(ret_indexes[1] == path.size()-1) {
    t_t = path.back()-path[path.size()-2];
  } else {
    t_t = path[ret_indexes[1]+1]-path[ret_indexes[1]-1];
  }

  t_t = t_t / t_t.norm();

  Vector2f t_bt = tip-base;
  float l       = t_bt.norm();
  t_bt          = t_bt/l;

  float x_b,y_b;
  std::tie(x_b,y_b) = orth_proj_comp(t_b,t_bt);
  float m_b  = y_b/x_b;
  if(std::isnan(m_b)) {
    std::cout << "m_b is nan: y_b = " << y_b << ", x_b = " << x_b << std::endl;
    std::cout << "t_b = " << t_b.transpose() << " t_bt = " << t_bt.transpose() << std::endl;
    std::cout << "base = " << base.transpose() << " tip = " << tip.transpose() << std::endl;
    std::cout << "ret_indexes = " << ret_indexes.at(0) << ", " << ret_indexes.at(1) << std::endl;
    std::cout << "out of " << path_data_.path_.size() << std::endl;
  }
  //assert(!std::isnan(m_b) && "m_b is nan");
  float x_t,y_t;
  std::tie(x_t,y_t) = orth_proj_comp(t_t,t_bt);
  float m_t = y_t/x_t;
  if(std::isnan(m_t)) {
    std::cout << "m_t is nan: y_t = " << y_t << ", x_t = " << x_t << std::endl;
    std::cout << "t_b = " << t_t.transpose() << " t_bt = " << t_bt.transpose() << std::endl;
  }
  //assert(!std::isnan(m_t) && "m_t is nan");

  Vector2f position; position<<position_x,position_y;
  Vector2f v = position-base;

  float x,y;
  std::tie(x,y) = orth_proj_comp(v,t_bt);

  float lmbd = (x+y*m_b)/(l-y*(m_t-m_b));
  //assert(!std::isnan(lmbd) && "lmbd is nan");

  Vector2f p_lmbd = lmbd*tip + (1-lmbd)*base;

  Vector2f n_lmbd = position-p_lmbd;

  float d = n_lmbd.norm();
  //side of line
  float signed_d = side_of_line(position,base,tip) * d;

  return PathDist(path_s_[ret_indexes[0]]+l*lmbd,d,signed_d);
  */
}

}
