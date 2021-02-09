/*
 * Subsystem0.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Subsystem0".
 *
 * Model version              : 1.99
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C++ source code generated on : Wed Nov 25 16:11:06 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Subsystem0_h_
#define RTW_HEADER_Subsystem0_h_
#include <stddef.h>
#include <string.h>
#ifndef Subsystem0_COMMON_INCLUDES_
# define Subsystem0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* Subsystem0_COMMON_INCLUDES_ */

#include "Subsystem0_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  robotics_slros_internal_block_T obj; /* '<S2>/SinkBlock' */
  boolean_T objisempty;                /* '<S2>/SinkBlock' */
} DW_Subsystem0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T VelocityX;                    /* '<Root>/<VelocityX>' */
} ExtU_Subsystem0_T;

/* Parameters (default storage) */
struct P_Subsystem0_T_ {
  SL_Bus_Subsystem0_std_msgs_Float32 Constant_Value;/* Computed Parameter: Constant_Value
                                                     * Referenced by: '<S1>/Constant'
                                                     */
};

/* Real-time Model Data Structure */
struct tag_RTM_Subsystem0_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_Subsystem0_T Subsystem0_P;

#ifdef __cplusplus

}
#endif

/* Block states (default storage) */
extern DW_Subsystem0_T Subsystem0_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* External inputs (root inport signals with default storage) */
  extern ExtU_Subsystem0_T Subsystem0_U;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void Subsystem0_initialize(void);
  extern void Subsystem0_step(void);
  extern void Subsystem0_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_Subsystem0_T *const Subsystem0_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Subsystem0'
 * '<S1>'   : 'Subsystem0/Blank Message'
 * '<S2>'   : 'Subsystem0/Publish'
 */
#endif                                 /* RTW_HEADER_Subsystem0_h_ */
