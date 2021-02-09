/*
 * Experiment_cs_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Experiment_cs".
 *
 * Model version              : 1.76
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Tue Nov 24 15:43:46 2020
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Experiment_cs.h"
#include "Experiment_cs_private.h"

/* Block parameters (default storage) */
P_Experiment_cs_T Experiment_cs_P = {
  /* Variable: Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0
   * Referenced by: '<S13>/iniVEHposition wrtGLOB [m]'
   */
  52.875694274902344,

  /* Variable: Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0
   * Referenced by: '<S13>/iniVEHposition wrtGLOB [m]1'
   */
  69.944343566894531,

  /* Variable: Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0
   * Referenced by: '<S13>/iniVEHposition wrtGLOB [m]2'
   */
  0.68999999761581421,

  /* Variable: Experiment_cs_e1d584482631291c
   * Referenced by:
   *   '<S13>/iniVEHAngles wrtGLOB [rad]'
   *   '<S23>/UD'
   */
  0.0,

  /* Variable: Experiment_cs_e726c63043403dc7
   * Referenced by:
   *   '<S13>/iniBODYAngles wrtVEH [rad]1'
   *   '<S22>/UD'
   */
  0.0,

  /* Variable: Experiment_cs_f4cae83923a86e0b
   * Referenced by:
   *   '<S13>/iniBODYAngles wrtVEH [rad]'
   *   '<S21>/UD'
   */
  0.0
};

/* Constant parameters (default storage) */
const ConstP_Experiment_cs_T Experiment_cs_ConstP = {
  /* Expression: SParameter1
   * Referenced by: '<S3>/sfun_Controller'
   */
  { 69U, 120U, 112U, 101U, 114U, 105U, 109U, 101U, 110U, 116U, 46U, 112U, 101U,
    120U, 0U },

  /* Expression: SParameter2
   * Referenced by: '<S3>/sfun_Controller'
   */
  { 67U, 58U, 92U, 80U, 114U, 111U, 103U, 114U, 97U, 109U, 32U, 70U, 105U, 108U,
    101U, 115U, 92U, 83U, 105U, 109U, 99U, 101U, 110U, 116U, 101U, 114U, 32U,
    80U, 114U, 101U, 115U, 99U, 97U, 110U, 92U, 80U, 114U, 101U, 115U, 99U, 97U,
    110U, 95U, 50U, 48U, 50U, 48U, 46U, 51U, 92U, 77U, 111U, 100U, 101U, 108U,
    68U, 101U, 112U, 111U, 0U },

  /* Expression: SParameter3
   * Referenced by: '<S3>/sfun_Controller'
   */
  0U,

  /* Expression: SParameter9
   * Referenced by: '<S3>/sfun_Controller'
   */
  { 110U, 111U, 114U, 109U, 97U, 108U, 0U },

  /* Expression: SParameter10
   * Referenced by: '<S3>/sfun_Controller'
   */
  { 112U, 115U, 46U, 116U, 108U, 99U, 0U }
};
