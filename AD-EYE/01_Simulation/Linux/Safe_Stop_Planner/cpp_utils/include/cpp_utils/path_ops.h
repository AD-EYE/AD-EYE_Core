#pragma once

#include <vector>
#include "third_party/nanoflann.hpp"
#include <eigen3/Eigen/Dense>
#include <geometry_msgs/PoseStamped.h>
#include <tf/LinearMath/Quaternion.h>

namespace cpp_utils {

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

template <typename T>
struct PathDist {
  T s;
  T d;
  // > 0 to the left < 0 to the right
  T signed_d;

  PathDist() {
    s=0;d=0;signed_d=0;
  }
  PathDist(T _s, T _d, T _signed_d) {
    s=_s; d=_d; signed_d = _signed_d;
  }
};


/**
 * @brief side_of_line +1 if to the left, 0 if on line, -1 if to right
 * @param p
 * @param l_start
 * @param l_end
 * @return
 */
template <typename T>
T side_of_line(Eigen::Matrix<T,2,1> const & pnt,
               Eigen::Matrix<T,2,1> const & l_start,
               Eigen::Matrix<T,2,1> const & l_end) {
  Eigen::Matrix<T,2,1> v1 = pnt-l_start;
  Eigen::Matrix<T,2,1> v2 = l_end-l_start;


  //z component of (v1,0) x (v2,0)
  auto twoD_cross = [] (Eigen::Matrix<T,2,1> const & v1,Eigen::Matrix<T,2,1> const &  v2)
  {
    return v1(0)*v2(1) - v1(1)*v2(0);
  };

  return -sgn<T>(twoD_cross(v1,v2));
}



struct PathData {
  std::vector<Eigen::Vector2f> path_;

  inline size_t kdtree_get_point_count() const { return path_.size(); }

  inline float kdtree_distance(float const * p1, size_t const idx_p2, size_t /*size*/) const
  {
    float dx = p1[0]-path_[idx_p2](0);
    float dy = p1[1]-path_[idx_p2](1);
    return dx*dx + dy*dy;
  }

  inline float kdtree_get_pt(const size_t idx, int dim) const {
    if(dim == 0) {
      return path_[idx](0);
    } else {
      return path_[idx](1);
    }
  }

  template <class BBOX>
  bool kdtree_get_bbox(BBOX& /* bb */) const { return false; }
};

template <typename T>
std::tuple<T,T> orth_proj_comp(Eigen::Matrix<T,2,1> const & a,
                               Eigen::Matrix<T,2,1> const & b) {
  T s = a.transpose()*b;
  Eigen::Matrix<T,2,1> a1 = s*b;
  Eigen::Matrix<T,2,1> a2 = a-a1;

  return std::make_tuple(s,a2.norm());
}

template <typename T>
T get_min_pseudo_dist_for_path(T & min_d_s,
                               std::vector<Eigen::Matrix<T,2,1>> const & path,
                               Eigen::Matrix<T,2,1> const & position) {

  T min_d = std::numeric_limits<T>::max();
  min_d_s = 0;

  //int min_d_idx = -1;

  T s_path = 0.0;

  for(int i=0; i<(int)(path.size()-1); ++i) {

    Eigen::Matrix<T,2,1> base = path.at(i);
    Eigen::Matrix<T,2,1> tip  = path.at(i+1);

    Eigen::Matrix<T,2,1> t_b, t_t;

    if(i==0) {
      t_b = path.at(1)-path.at(0);
    } else {
      t_b = path.at(i+1)-path.at(i-1);
    }

    t_b = t_b / t_b.norm();

    if(i+1 == (int)path.size()-1) {
      t_t = path.back()-path.at(path.size()-2);
    } else {
      t_t = path.at(i+2)-path.at(i);
    }

    t_t = t_t / t_t.norm();

    Eigen::Matrix<T,2,1> t_bt = tip-base;
    T l                       = t_bt.norm();
    t_bt                      = t_bt/l;

    T x_b,y_b;
    std::tie(x_b,y_b) = orth_proj_comp(t_b,t_bt);
    T m_b  = y_b/x_b;
//    if(std::isnan(m_b)) {
//      std::cout << "m_b is nan: y_b = " << y_b << ", x_b = " << x_b << std::endl;
//      std::cout << "t_b = " << t_b.transpose() << " t_bt = " << t_bt.transpose() << std::endl;
//      std::cout << "base = " << base.transpose() << " tip = " << tip.transpose() << std::endl;
//      std::cout << "ret_indexes = " << ret_indexes.at(0) << ", " << ret_indexes.at(1) << std::endl;
//      std::cout << "out of " << path_data_.path_.size() << std::endl;
//    }
    //assert(!std::isnan(m_b) && "m_b is nan");
    float x_t,y_t;
    std::tie(x_t,y_t) = orth_proj_comp(t_t,t_bt);
    float m_t = y_t/x_t;
//    if(std::isnan(m_t)) {
//      std::cout << "m_t is nan: y_t = " << y_t << ", x_t = " << x_t << std::endl;
//      std::cout << "t_b = " << t_t.transpose() << " t_bt = " << t_bt.transpose() << std::endl;
//    }
    //assert(!std::isnan(m_t) && "m_t is nan");

    Eigen::Matrix<T,2,1> v = position-base;

    T x,y;
    std::tie(x,y) = orth_proj_comp(v,t_bt);

    T lmbd = (x+y*m_b)/(l-y*(m_t-m_b));
    //assert(!std::isnan(lmbd) && "lmbd is nan");

    Eigen::Matrix<T,2,1> p_lmbd = lmbd*tip + (1-lmbd)*base;

    Eigen::Matrix<T,2,1> n_lmbd = position-p_lmbd;

    T d = n_lmbd.norm();
    //side of line
    //T signed_d = side_of_line(position,base,tip) * d;

    if(!std::isnan(d) && d < min_d) {
      min_d = d;
      min_d_s = s_path + l*lmbd;
    }

    s_path += l;
  }

  return min_d;
}

template <typename T>
T get_min_orth_dist_for_path(T & min_d_s,
                             std::vector<Eigen::Matrix<T,2,1>> const & path,
                             Eigen::Matrix<T,2,1> p) {

  T min_d = std::numeric_limits<T>::max();
  //int min_d_idx = -1;

  T s_path = 0.0;

  for(int i=0; i<(int)(path.size()-1); ++i) {

    Eigen::Matrix<T,2,1> base = path.at(i);
    Eigen::Matrix<T,2,1> tip  = path.at(i+1);

    Eigen::Matrix<T,2,1> a = p-base;
    Eigen::Matrix<T,2,1> b = tip-base;

    //projection of a onto b
    T t = a.dot(b) / b.norm();

    Eigen::Matrix<T,2,1> a_1 = t*b/b.norm();
    Eigen::Matrix<T,2,1> a_2 = a-a_1;

    //orthogonal distance
    T d_orth = a_2.norm();

    T d = d_orth;
    if(t < 0) {
      //use Euclidean distance to base instead to determine closest
      d = a.norm();
    } else if( t > b.norm()) {
      //use Euclidean distance to tip instead to determine closest
      d = (p-tip).norm();
    }

    if(d < min_d ) {
      //min_d_idx = i;
      min_d = d;
      min_d_s = s_path + t; //we do extrapolation to figure out "s"
    }

    s_path += b.norm();
  }
  return min_d;
}



/**
 * @brief The PathDistanceTracker struct
 *
 * Also contains state machine where the user can advance segments
 */
struct PathDistanceTracker {
private:
  std::vector<std::vector<Eigen::Vector2d>> path_segments_;
  //std::vector<std::vector<double>> path_segment_theta_;
  std::vector<std::vector<tf::Quaternion>> path_segment_rot_;

  std::vector<bool> path_segment_reverse_;

  //begin s of each segment
  std::vector<double> path_segment_limits_;
  double s_last_;
  bool initialized_;

  size_t current_segment_index_;

public:
  PathDistanceTracker() : initialized_(false) {

  }

  size_t get_number_of_segments() const {
    return path_segments_.size();
  }

  size_t get_current_segment_index() const {
    return current_segment_index_;
  }

  void initialize_path(std::vector<Eigen::Vector2d> const & path,
                       /*std::vector<double> const & path_theta,*/
                       std::vector<tf::Quaternion> const & path_rot,
                       std::vector<bool> const & reverse) {

    using namespace Eigen;

    path_segments_.clear();
    path_segment_limits_.clear();
    path_segment_reverse_.clear();
    //path_segment_theta_.clear();
    path_segment_rot_.clear();

    if(path.size() != reverse.size()) {
      throw std::logic_error("path and reverse status must be the same size");
    }
    if(path.size() < 2) {
      throw std::logic_error("path must be of atleast size 2");
    }

    //we split the path into segments that are in the same direction
    VectorXd path_s(path.size());
    path_s(0) = 0.0;
    for(size_t i=1; i<path.size(); ++i) {
      path_s(i) = path_s(i-1) + (path.at(i)-path.at(i-1)).norm();
    }
    s_last_ = path_s(path.size()-1);

    //the first segment always contains the first point
    path_segment_limits_.push_back(path_s(0));
    std::vector<Vector2d> segment;
    //std::vector<double> segment_theta;
    std::vector<tf::Quaternion> segment_rot;

    segment.push_back(path.front());
    //segment_theta.push_back(path_theta.front());
    segment_rot.push_back(path_rot.front());

    path_segment_reverse_.push_back(reverse.at(0));


    for(size_t i=1; i<reverse.size(); ++i) {
      if(reverse.at(i) != reverse.at(i-1)) {

        path_segments_.push_back(segment);
        //path_segment_theta_.push_back(segment_theta);
        path_segment_rot_.push_back(segment_rot);

        //new segment
        path_segment_limits_.push_back(path_s(i-1));

        segment = std::vector<Vector2d>();
        //segment_theta = std::vector<double>();
        segment_rot = std::vector<tf::Quaternion>();

        //switch point also included
        segment.push_back(path.at(i-1));
        //segment_theta.push_back(path_theta.at(i-1));
        segment_rot.push_back(path_rot.at(i-1));

        path_segment_reverse_.push_back(reverse.at(i));

      }
      segment.push_back(path.at(i));
      //segment_theta.push_back(path_theta.at(i));
      segment_rot.push_back(path_rot.at(i));
    }
    path_segments_.push_back(segment);
    //path_segment_theta_.push_back(segment_theta);
    path_segment_rot_.push_back(segment_rot);
    initialized_ = true;

    bool err_found = false;
    for(size_t i =0; i<path_segments_.size(); ++i) {
      if(path_segments_.at(i).size() < 2) {
        std::cerr << "Got path segment with less than two elements!" << std::endl;
        err_found = true;
      }
    }
    if(err_found) {
      std::cerr << "We have " << path_segments_.size() << " segments: beginning at, num elem, reverse:";
      for(size_t i =0; i<path_segment_limits_.size(); ++i) {
        double seg_start = path_segment_limits_.at(i);
        std::cerr << seg_start << ", " << path_segments_.at(i).size() << ", "
                  << (path_segment_reverse_.at(i) ? "R" : "F") << "; ";
      }
      std::cerr << std::endl;
    }

  }

  void reset_segment_index() {
    current_segment_index_ = 0;
  }

  void set_segment_index(double s) {
    if(!initialized_) {
      throw std::logic_error("Need a path to do calculations");
    }
    current_segment_index_ = get_segment_index_for_s(s);
  }

  bool advance_segment_index() {
    if(!initialized_) {
      throw std::logic_error("Need a path to do calculations");
    }

    if(current_segment_index_ < path_segment_limits_.size()-1) {
      current_segment_index_++;
      return false;
    }
    return true;
  }

  double get_current_segment_data(std::vector<double> & x,
                                  std::vector<double> & y,
                                  /*std::vector<double> & th*/
                                  std::vector<tf::Quaternion> & rot) {
    x.clear();
    y.clear();

    for(Eigen::Vector2d const & p : path_segments_.at(current_segment_index_)) {
      x.push_back(p(0));
      y.push_back(p(1));
    }
    //th = path_segment_theta_.at(current_segment_);
    rot = path_segment_rot_.at(current_segment_index_);

    assert(x.size() == y.size());
    assert(rot.size() == y.size());
    return path_segment_limits_.at(current_segment_index_);
  }

  size_t get_segment_index_for_s(double s) {
    if(!initialized_) {
      throw std::logic_error("Need a path to do calculations");
    }

    //get the next segment start s that is larger than start_s
    size_t seg_idx = 0;
    auto seg_it = std::upper_bound(path_segment_limits_.begin(),
                                   path_segment_limits_.end(),
                                   s);
    if(seg_it == path_segment_limits_.begin()) {
      //first segement starts after prev_s!
      std::cout << "Warning first segment starts after prev_s, still using it" << std::endl;
    } else {
      seg_idx = seg_it - path_segment_limits_.begin() - 1;
    }
    if(seg_idx >= path_segment_limits_.size()) {
      return path_segment_limits_.size();
    } else {
      return seg_idx;
    }
  }

  double get_next_switch_s_for_current_segment() {
    if(current_segment_index_ < path_segment_limits_.size()-1)
      return path_segment_limits_.at(current_segment_index_+1);
    else
      return s_last_;
  }

  bool get_reverse_status_for_current_segment() {
    return path_segment_reverse_.at(current_segment_index_);
  }

  PathDist<double> get_tracked_distance_for_current_segment(bool & at_next_segment,
                                                            Eigen::Vector2d position,
                                                            double segment_clear_dist=0.1,
                                                            bool in_path_s=false) {

    if(!initialized_) {
      throw std::logic_error("Need a path to do calculations");
    }

    at_next_segment = false;

    double s_on_path_seg;
    double d = get_min_orth_dist_for_path(s_on_path_seg,path_segments_.at(current_segment_index_),position);

    double position_s = s_on_path_seg+path_segment_limits_.at(current_segment_index_);

//    std::cout << "current_segment+1 = " << current_segment_+1
//              << " path_segment_limits.size()-1 " <<path_segment_limits_.size()-1
//              << std::endl;
    if(current_segment_index_+1 <= path_segment_limits_.size()-1) {
//      std::cout << "position_s = " << position_s << " path_segment_limits_.at(...) = "
//                << path_segment_limits_.at(current_segment_+1) << std::endl;
      if(position_s > path_segment_limits_.at(current_segment_index_+1)-segment_clear_dist) {
        at_next_segment = true;
      }
    }

    ///@todo set correct sign on d
    if(in_path_s)
      return PathDist<double>(position_s,d,d);
    else
      return PathDist<double>(s_on_path_seg,d,d);
  }

  double get_next_switch_s(double start_s) {
    if(!initialized_) {
      throw std::logic_error("Need a path to do calculations");
    }

    //get the next segment start s that is larger than start_s
    size_t seg_idx = 0;
    auto seg_it = std::upper_bound(path_segment_limits_.begin(),
                                   path_segment_limits_.end(),
                                   start_s);
    if(seg_it == path_segment_limits_.begin()) {
      //first segement starts after prev_s!
      std::cout << "Warning first segment starts after prev_s, still using it" << std::endl;
    } else {
      seg_idx = seg_it - path_segment_limits_.begin() - 1;
    }
    if(seg_idx >= path_segment_limits_.size()-1) {
      return s_last_;
    } else {
      return path_segment_limits_.at(seg_idx+1);
    }
  }

  PathDist<double> get_tracked_distance(double prev_s, Eigen::Vector2d position, double segment_clear_dist=0.1) {
    if(!initialized_) {
      throw std::logic_error("Need a path to do distance calculations");
    }

    //we assume that we can only be at the segement indicated by prev_s, however
    //we do extrapolate here, so when we go beoynd the last point -segment_clear_dist
    //we will get onto the next segment

    //get the current segment

    //get the next segment start s that is larger than prev_s
    size_t seg_idx = 0;
    auto seg_it = std::upper_bound(path_segment_limits_.begin(),
                                   path_segment_limits_.end(),
                                   prev_s);
    if(seg_it == path_segment_limits_.begin()) {
      //first segement starts after prev_s!
      std::cout << "Warning first segment starts after prev_s, still using it" << std::endl;
    } else {
      seg_idx = seg_it - path_segment_limits_.begin() - 1;
    }
    std::cout << "using segment idx = " << seg_idx << " with limits ["
              << path_segment_limits_.at(seg_idx) << ", ";
    if(seg_idx+1 < path_segment_limits_.size()) {
      std::cout << path_segment_limits_.at(seg_idx+1);
    } else {
      std::cout << "end";
    }
    std::cout << "] for prev_s = " << prev_s <<std::endl;

    double s_on_path_seg;
    double d = get_min_orth_dist_for_path(s_on_path_seg,path_segments_.at(seg_idx),position);

//    double s_on_path_seg;
//    double d =  get_min_pseudo_dist_for_path(s_on_path_seg,path_segments_.at(seg_idx),position);

    std::cout << "min_d = " << d << " s_on_path_seg = " << s_on_path_seg << std::endl;

    double position_s = s_on_path_seg+path_segment_limits_.at(seg_idx);

    //if we are within segement_clear_dist, we are by definition on the next segment
    if(seg_idx+1 <= path_segment_limits_.size()-1) {
      if(position_s > path_segment_limits_.at(seg_idx+1)-segment_clear_dist) {
        position_s = std::max(position_s,path_segment_limits_.at(seg_idx+1)+0.0001);
      }
    }

    ///@todo set correct sign on d
    return PathDist<double>(position_s,d,d);
  }

};



struct PathDistanceChecker {
private:

  bool     initialized_ = false;
  PathData path_data_;
  std::vector<float> path_s_;
  std::vector<float> path_x_;
  std::vector<float> path_y_;
  std::vector<float> path_theta_;
  std::vector<tf::Quaternion> path_rot_;

  typedef nanoflann::KDTreeSingleIndexAdaptor<
  nanoflann::L2_Simple_Adaptor<float,PathData>,
  PathData,
  2> kdtree_t;

  //nanoflann::KDTreeSingleIndexAdaptor does not have a default ctor!
  kdtree_t * path_kdtree_ = NULL;

  //  InterpMultilinear<1,float> * interp_theta_ = NULL;
  //  InterpMultilinear<1,float> * interp_x_     = NULL;
  //  InterpMultilinear<1,float> * interp_y_     = NULL;
  //  std::vector< std::vector<float>::iterator > grid_iter_list_;
  //  array<int,1> grid_sizes_;

  void free_resources();

  std::vector<int> get_points_by_distance(Eigen::Vector2f query) const;
public:

  void initialize_path(std::vector<Eigen::Vector2f> & path);

  void initialize_path(std::vector<geometry_msgs::PoseStamped> & path);

  ~PathDistanceChecker();

  /**
   * @brief get_path_distance
   * @param postion_x
   * @param position_y
   * @return longitudinal distance along path "s" and lateral distance "d"
   * based on lanelet pseudo distance. Computed w.r.t. path set in initialize_path
   */
  PathDist<float> get_path_distance(float position_x, float position_y, float guess_s, float tol=0.1) const;

  PathDist<float> get_next_path_distance(float position_x, float position_y, float atleast_s,
                                         float expected_s, float tol=0.1) const;

  Eigen::Vector3f get_pose(PathDist<float> pd);
};


///TODO, think about how a road-network graph would fit into
/// this. We probably want a nice interface where we can get the center of the current lane
/// along with lane width of it along with neighbouring lanes.

}
