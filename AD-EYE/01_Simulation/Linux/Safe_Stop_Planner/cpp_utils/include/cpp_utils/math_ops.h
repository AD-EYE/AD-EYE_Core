#pragma once

#include <math.h>

namespace cpp_utils {

/**
 * @brief angle_diff Return normalized angle difference
 * @param alpha
 * @param beta
 * @return
 */
inline double angle_diff(double alpha, double beta) {
  auto mod = [] (double x, double n) {
    return x-floor(x/n)*n;
  };

  double diff = alpha-beta;
  return mod((diff + M_PI),2*M_PI)-M_PI;
}

/**
 * @brief get_closest_angle
 * @param alpha
 * @param beta
 * @return unwind/windup alpha to be close to beta (i.e. remove/add multiples of 2*pi)
 *
 */
inline double get_closest_angle(double alpha, double beta, double tol=M_PI/2) {
  while(alpha-beta > 2*M_PI-tol) {
    alpha -= 2*M_PI;
  }
  while(alpha-beta < -(2*M_PI-tol)) {
    alpha += 2*M_PI;
  }
  return alpha;
}

template <typename T>
inline T sign(T a) {
  if(a>0) {
    return (T)1.0;
  } else if(a<0) {
    return (T)-1.0;
  }
  return 0;
}

}
