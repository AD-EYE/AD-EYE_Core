/*
 * W01_Base_Map_cs_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "W01_Base_Map_cs".
 *
 * Model version              : 1.298
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Sat Feb 20 15:25:39 2021
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_W01_Base_Map_cs_types_h_
#define RTW_HEADER_W01_Base_Map_cs_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "prescan_header_data.h"
#include "prescan_airsensor_data.h"
#include "prescan_animactuator_data.h"
#include "prescan_selfsensor_data.h"
#include "prescan_motion_data.h"
#include "prescan_stateactuator_data.h"
#include "prescan_scannersensor_data.h"
#include "prescan_color_data.h"
#include "prescan_controller_data.h"
#include "prescan_terminator_data.h"
#include "prescan_synchronizer_data.h"
#include "prescan_xyz_data.h"
#include "prescan_rpy_data.h"
#include "prescan_rgb_data.h"
#include "prescan_visulightactuator_data.h"
#ifndef typedef_robotics_slcore_internal_bloc_T
#define typedef_robotics_slcore_internal_bloc_T

typedef struct {
  int32_T isInitialized;
} robotics_slcore_internal_bloc_T;

#endif                               /*typedef_robotics_slcore_internal_bloc_T*/

/* Parameters (default storage) */
typedef struct P_W01_Base_Map_cs_T_ P_W01_Base_Map_cs_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_W01_Base_Map_cs_T RT_MODEL_W01_Base_Map_cs_T;

#endif                                 /* RTW_HEADER_W01_Base_Map_cs_types_h_ */
