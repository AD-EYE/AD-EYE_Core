/*
 * ros_node_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ros_node".
 *
 * Model version              : 1.6
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C++ source code generated on : Sat Dec 12 09:39:45 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ros_node_types_h_
#define RTW_HEADER_ros_node_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_node_std_msgs_UInt8_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_node_std_msgs_UInt8_

typedef struct {
  uint8_T Data;
} SL_Bus_ros_node_std_msgs_UInt8;

#endif

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_block_T;

#endif                               /*typedef_robotics_slros_internal_block_T*/

/* Parameters (default storage) */
typedef struct P_ros_node_T_ P_ros_node_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_ros_node_T RT_MODEL_ros_node_T;

#endif                                 /* RTW_HEADER_ros_node_types_h_ */
