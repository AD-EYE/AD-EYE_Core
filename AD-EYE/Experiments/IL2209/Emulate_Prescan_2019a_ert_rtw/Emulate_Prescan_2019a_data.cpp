/*
 * Emulate_Prescan_2019a_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Emulate_Prescan_2019a".
 *
 * Model version              : 1.7
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C++ source code generated on : Fri Oct 30 10:03:25 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Emulate_Prescan_2019a.h"
#include "Emulate_Prescan_2019a_private.h"

/* Block parameters (default storage) */
P_Emulate_Prescan_2019a_T Emulate_Prescan_2019a_P = {
  /* Computed Parameter: Constant_Value
   * Referenced by: '<S1>/Constant'
   */
  {
    0U                                 /* Data */
  },

  /* Expression: 0
   * Referenced by: '<S2>/Constant1'
   */
  0.0,

  /* Computed Parameter: Delay_DelayLength
   * Referenced by: '<S2>/Delay'
   */
  1U,

  /* Computed Parameter: Delay1_DelayLength
   * Referenced by: '<S2>/Delay1'
   */
  1U,

  /* Computed Parameter: Delay_InitialCondition
   * Referenced by: '<S2>/Delay'
   */
  0U,

  /* Computed Parameter: Delay1_InitialCondition
   * Referenced by: '<S2>/Delay1'
   */
  0U,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S2>/Switch'
   */
  5U,

  /* Computed Parameter: Constant_Value_a
   * Referenced by: '<Root>/Constant'
   */
  1U
};
