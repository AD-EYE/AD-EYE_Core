/*
 * Experiment_cs_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Experiment_cs".
 *
 * Model version              : 1.104
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Mon Jan 11 14:47:30 2021
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
  /* Variable: Experiment_cs_5636da37c22e663b
   * Referenced by: '<S3>/SpeedProfile'
   */
  34.0,

  /* Variable: Experiment_cs_Mazda_RX8_Coupe_1_Path_pathUniqueID
   * Referenced by: '<S3>/Path'
   */
  32.0
};

/* Constant parameters (default storage) */
const ConstP_Experiment_cs_T Experiment_cs_ConstP = {
  /* Expression: port
   * Referenced by: '<S5>/S-Function Builder'
   */
  9090.0,

  /* Expression: timeout
   * Referenced by: '<S5>/S-Function Builder'
   */
  2.0,

  /* Expression: int8(topic)
   * Referenced by: '<S5>/S-Function Builder'
   */
  { 47, 109, 121, 95, 116, 111, 112, 105, 99 },

  /* Expression: int8(message_type)
   * Referenced by: '<S5>/S-Function Builder'
   */
  { 115, 116, 100, 95, 109, 115, 103, 115, 47, 70, 108, 111, 97, 116, 54, 52 },

  /* Expression: SParameter1
   * Referenced by: '<S2>/sfun_Controller'
   */
  { 69U, 120U, 112U, 101U, 114U, 105U, 109U, 101U, 110U, 116U, 46U, 112U, 101U,
    120U, 0U },

  /* Expression: SParameter2
   * Referenced by: '<S2>/sfun_Controller'
   */
  { 67U, 58U, 92U, 80U, 114U, 111U, 103U, 114U, 97U, 109U, 32U, 70U, 105U, 108U,
    101U, 115U, 92U, 83U, 105U, 109U, 99U, 101U, 110U, 116U, 101U, 114U, 32U,
    80U, 114U, 101U, 115U, 99U, 97U, 110U, 92U, 80U, 114U, 101U, 115U, 99U, 97U,
    110U, 95U, 50U, 48U, 50U, 48U, 46U, 49U, 92U, 77U, 111U, 100U, 101U, 108U,
    68U, 101U, 112U, 111U, 0U },

  /* Expression: SParameter3
   * Referenced by: '<S2>/sfun_Controller'
   */
  0U,

  /* Expression: SParameter9
   * Referenced by: '<S2>/sfun_Controller'
   */
  { 110U, 111U, 114U, 109U, 97U, 108U, 0U },

  /* Expression: SParameter10
   * Referenced by: '<S2>/sfun_Controller'
   */
  { 112U, 115U, 46U, 116U, 108U, 99U, 0U }
};
