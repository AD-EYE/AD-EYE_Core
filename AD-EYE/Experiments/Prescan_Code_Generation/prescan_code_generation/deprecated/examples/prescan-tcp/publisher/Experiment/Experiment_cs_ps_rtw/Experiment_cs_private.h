/*
 * Experiment_cs_private.h
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

#ifndef RTW_HEADER_Experiment_cs_private_h_
#define RTW_HEADER_Experiment_cs_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#ifdef __cplusplus

extern "C" {

#endif

  extern void publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void publisher_Outputs_wrapper(const real_T *data,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_Experiment_cs_private_h_ */
