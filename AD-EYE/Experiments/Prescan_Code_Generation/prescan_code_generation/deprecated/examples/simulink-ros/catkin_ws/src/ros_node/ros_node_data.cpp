/*
 * ros_node_data.cpp
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

#include "ros_node.h"
#include "ros_node_private.h"

/* Block parameters (default storage) */
P_ros_node_T ros_nodeModelClass::ros_node_P = {
  /* Computed Parameter: Constant_Value
   * Referenced by: '<S1>/Constant'
   */
  {
    0U                                 /* Data */
  },

  /* Expression: 0
   * Referenced by: '<Root>/Constant1'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<Root>/Delay1'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<Root>/Delay'
   */
  0.0,

  /* Expression: 10
   * Referenced by: '<Root>/Switch'
   */
  10.0,

  /* Expression: 1
   * Referenced by: '<Root>/Constant'
   */
  1.0,

  /* Computed Parameter: Delay1_DelayLength
   * Referenced by: '<Root>/Delay1'
   */
  1U,

  /* Computed Parameter: Delay_DelayLength
   * Referenced by: '<Root>/Delay'
   */
  1U
};
