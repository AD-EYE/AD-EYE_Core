/*
 * Emulate_Prescan_2019a_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Emulate_Prescan_2019a".
 *
 * Model version              : 1.7
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Mon Nov 30 16:37:17 2020
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Emulate_Prescan_2019a_types_h_
#define RTW_HEADER_Emulate_Prescan_2019a_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16_
#define DEFINED_TYPEDEF_FOR_SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16_

typedef struct {
  uint16_T Data;
} SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16;

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
typedef struct P_Emulate_Prescan_2019a_T_ P_Emulate_Prescan_2019a_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Emulate_Prescan_2019a_T RT_MODEL_Emulate_Prescan_2019_T;

#endif                           /* RTW_HEADER_Emulate_Prescan_2019a_types_h_ */
