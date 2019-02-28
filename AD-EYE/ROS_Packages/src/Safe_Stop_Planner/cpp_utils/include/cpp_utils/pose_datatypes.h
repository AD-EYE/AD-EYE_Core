/* Convert Pose in 3d or 2d between common ROS formats and eigen
 * also supports extracting angles and translation components
 *
 * Author:  Erik Ward
 * Licence: MIT
 */

#pragma once

#include <tf/transform_datatypes.h>
#include <eigen3/Eigen/Dense>

namespace cpp_utils {

inline tf::Quaternion get_tf_quat(double roll, double pitch, double yaw) {
  tf::Quaternion quat;
  quat.setRPY(roll,pitch,yaw);
  return quat;
}
inline tf::Quaternion get_tf_quat(double yaw) {
  return get_tf_quat(0,0,yaw);
}

inline tf::Stamped<tf::Pose> get_pose_tf(geometry_msgs::PoseStamped const & pose) {
  tf::Stamped<tf::Pose> pose_tf;
  poseStampedMsgToTF(pose,pose_tf);
  return pose_tf;
}

inline tf::Quaternion quat_to_tf_quat(geometry_msgs::Quaternion const & quat) {
  tf::Quaternion tf_quat;
  tf_quat.setX(quat.x);
  tf_quat.setY(quat.y);
  tf_quat.setZ(quat.z);
  tf_quat.setW(quat.w);
  return tf_quat;
}


template <typename TF_T>
void extract_rpy(double&  roll, double& pitch, double& yaw,
                 TF_T const & tf_transform) {
  tf::Matrix3x3(tf_transform.getRotation()).getEulerYPR(yaw,pitch, roll);
}

template <typename TF_T>
double extract_yaw(TF_T const & tf_transform) {
  double roll,pitch,yaw;
  extract_rpy(roll,pitch,yaw,tf_transform);
  return yaw;
}

inline void extract_rpy(double&  roll, double& pitch, double& yaw,
                        tf::Quaternion const & quat) {
  tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);
}

inline double extract_yaw(tf::Quaternion const & quat) {
  double roll, pitch, yaw;
  extract_rpy(roll,pitch,yaw,quat);
  return yaw;
}

inline double extract_yaw(geometry_msgs::Quaternion const & quat) {
  return extract_yaw(quat_to_tf_quat(quat));
}


inline geometry_msgs::Quaternion tf_quat_to_quat(tf::Quaternion const & tf_quat) {
  geometry_msgs::Quaternion quat;
  quat.x = tf_quat.x();
  quat.y = tf_quat.y();
  quat.z = tf_quat.z();
  quat.w = tf_quat.w();
  return quat;
}

template <typename TF_T>
Eigen::Vector3d extract_pose_SE2_from_tf(TF_T const & tf_transform) {
  Eigen::Vector3d p;
  p<< tf_transform.getOrigin().x(),
      tf_transform.getOrigin().y(),
      extract_yaw(tf_transform);
  return p;
}

Eigen::Vector3d extract_pose_SE2_from_geom_msgs(geometry_msgs::PoseStamped const & geom_pose) {

  Eigen::Vector3d p;

  p<<   geom_pose.pose.position.x,
        geom_pose.pose.position.y,
      extract_yaw(get_pose_tf(geom_pose));
  return p;
}



}
