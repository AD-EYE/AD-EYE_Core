/*
 * W12_Crossing_cs_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "W12_Crossing_cs".
 *
 * Model version              : 1.75
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Wed Feb 10 17:20:38 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "W12_Crossing_cs.h"
#include "W12_Crossing_cs_private.h"

/* Invariant block signals (default storage) */
const ConstB_W12_Crossing_cs_T W12_Crossing_cs_ConstB = {
  116U,                                /* '<S75>/Data Type Conversion' */
  140U,                                /* '<S75>/Data Type Conversion1' */
  165U,                                /* '<S75>/Data Type Conversion2' */
  155U,                                /* '<S76>/Data Type Conversion' */
  155U,                                /* '<S76>/Data Type Conversion1' */
  155U,                                /* '<S76>/Data Type Conversion2' */
  142U,                                /* '<S77>/Data Type Conversion' */
  142U,                                /* '<S77>/Data Type Conversion1' */
  142U,                                /* '<S77>/Data Type Conversion2' */
  108U,                                /* '<S86>/Data Type Conversion' */
  133U,                                /* '<S86>/Data Type Conversion1' */
  153U,                                /* '<S86>/Data Type Conversion2' */
  61U,                                 /* '<S87>/Data Type Conversion' */
  61U,                                 /* '<S87>/Data Type Conversion1' */
  61U                                  /* '<S87>/Data Type Conversion2' */
};

/* Block parameters (default storage) */
P_W12_Crossing_cs_T W12_Crossing_cs_P = {
  /* Variable: W12_Crossing_cs_1e72c7e30b0890ad
   * Referenced by: '<S10>/SpeedProfile'
   */
  871.0,

  /* Variable: W12_Crossing_cs_28e1fdd0f30fb13b
   * Referenced by: '<S8>/SpeedProfile'
   */
  868.0,

  /* Variable: W12_Crossing_cs_BMW_X5_SUV_1_Path_pathUniqueID
   * Referenced by: '<S3>/Path'
   */
  859.0,

  /* Variable: W12_Crossing_cs_BMW_X5_SUV_1_SpeedProfile_speedProfileUniqueID
   * Referenced by: '<S3>/SpeedProfile'
   */
  860.0,

  /* Variable: W12_Crossing_cs_Female_Regular_1_Path_pathUniqueID
   * Referenced by: '<S8>/Path'
   */
  867.0,

  /* Variable: W12_Crossing_cs_Male_Regular_1_Path_pathUniqueID
   * Referenced by: '<S10>/Path'
   */
  870.0
};

/* Constant parameters (default storage) */
const ConstP_W12_Crossing_cs_T W12_Crossing_cs_ConstP = {
  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S25>/Actuator'
   *   '<S26>/Actuator'
   *   '<S29>/Actuator'
   */
  { 0U, 2U, 0U, 1U, 43U },

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S27>/Actuator'
   *   '<S28>/Actuator'
   */
  { 0U, 2U, 0U, 1U, 38U },

  /* Expression: SParameter1
   * Referenced by: '<S7>/sfun_Controller'
   */
  { 87U, 49U, 50U, 95U, 67U, 114U, 111U, 115U, 115U, 105U, 110U, 103U, 46U, 112U,
    101U, 120U, 0U },

  /* Expression: SParameter2
   * Referenced by: '<S7>/sfun_Controller'
   */
  { 67U, 58U, 92U, 80U, 114U, 111U, 103U, 114U, 97U, 109U, 32U, 70U, 105U, 108U,
    101U, 115U, 92U, 83U, 105U, 109U, 99U, 101U, 110U, 116U, 101U, 114U, 32U,
    80U, 114U, 101U, 115U, 99U, 97U, 110U, 92U, 80U, 114U, 101U, 115U, 99U, 97U,
    110U, 95U, 50U, 48U, 50U, 48U, 46U, 49U, 92U, 77U, 111U, 100U, 101U, 108U,
    68U, 101U, 112U, 111U, 0U },

  /* Expression: SParameter3
   * Referenced by: '<S7>/sfun_Controller'
   */
  0U,

  /* Expression: SParameter9
   * Referenced by: '<S7>/sfun_Controller'
   */
  { 110U, 111U, 114U, 109U, 97U, 108U, 0U },

  /* Expression: SParameter10
   * Referenced by: '<S7>/sfun_Controller'
   */
  { 103U, 114U, 116U, 46U, 116U, 108U, 99U, 0U },

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S25>/Actuator'
   *   '<S26>/Actuator'
   */
  { 47U, 114U, 101U, 99U, 111U, 108U, 111U, 114U, 82U, 101U, 103U, 105U, 111U,
    110U, 58U, 110U, 97U, 109U, 101U, 61U, 76U, 111U, 119U, 101U, 114U, 32U, 66U,
    111U, 100U, 121U, 47U, 116U, 97U, 114U, 103U, 101U, 116U, 67U, 111U, 108U,
    111U, 114U, 0U },

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S27>/Actuator'
   *   '<S28>/Actuator'
   */
  { 47U, 114U, 101U, 99U, 111U, 108U, 111U, 114U, 82U, 101U, 103U, 105U, 111U,
    110U, 58U, 110U, 97U, 109U, 101U, 61U, 83U, 104U, 111U, 101U, 115U, 47U,
    116U, 97U, 114U, 103U, 101U, 116U, 67U, 111U, 108U, 111U, 114U, 0U },

  /* Expression: mbxruntime.parameters.convert(WorldModelSubPath)
   * Referenced by: '<S29>/Actuator'
   */
  { 47U, 114U, 101U, 99U, 111U, 108U, 111U, 114U, 82U, 101U, 103U, 105U, 111U,
    110U, 58U, 110U, 97U, 109U, 101U, 61U, 85U, 112U, 112U, 101U, 114U, 32U, 66U,
    111U, 100U, 121U, 47U, 116U, 97U, 114U, 103U, 101U, 116U, 67U, 111U, 108U,
    111U, 114U, 0U }
};
