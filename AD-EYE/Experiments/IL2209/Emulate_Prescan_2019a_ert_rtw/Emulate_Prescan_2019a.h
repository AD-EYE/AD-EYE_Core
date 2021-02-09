/*
 * Emulate_Prescan_2019a.h
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

#ifndef RTW_HEADER_Emulate_Prescan_2019a_h_
#define RTW_HEADER_Emulate_Prescan_2019a_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Emulate_Prescan_2019a_COMMON_INCLUDES_
# define Emulate_Prescan_2019a_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                              /* Emulate_Prescan_2019a_COMMON_INCLUDES_ */

#include "Emulate_Prescan_2019a_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  robotics_slros_internal_block_T obj; /* '<S3>/SinkBlock' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  uint16_T Delay_DSTATE;               /* '<S2>/Delay' */
  uint16_T Delay1_DSTATE;              /* '<S2>/Delay1' */
  boolean_T objisempty;                /* '<S3>/SinkBlock' */
} DW_Emulate_Prescan_2019a_T;

/* Parameters (default storage) */
struct P_Emulate_Prescan_2019a_T_ {
  SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16 Constant_Value;/* Computed Parameter: Constant_Value
                                                               * Referenced by: '<S1>/Constant'
                                                               */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S2>/Constant1'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S2>/Delay'
                                        */
  uint32_T Delay1_DelayLength;         /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<S2>/Delay1'
                                        */
  uint16_T Delay_InitialCondition; /* Computed Parameter: Delay_InitialCondition
                                    * Referenced by: '<S2>/Delay'
                                    */
  uint16_T Delay1_InitialCondition;
                                  /* Computed Parameter: Delay1_InitialCondition
                                   * Referenced by: '<S2>/Delay1'
                                   */
  uint16_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S2>/Switch'
                                        */
  uint16_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Emulate_Prescan_2019a_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_Emulate_Prescan_2019a_T Emulate_Prescan_2019a_P;

#ifdef __cplusplus

}
#endif

/* Block states (default storage) */
extern DW_Emulate_Prescan_2019a_T Emulate_Prescan_2019a_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void Emulate_Prescan_2019a_initialize(void);
  extern void Emulate_Prescan_2019a_step(void);
  extern void Emulate_Prescan_2019a_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_Emulate_Prescan_2019_T *const Emulate_Prescan_2019a_M;

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
 * '<Root>' : 'Emulate_Prescan_2019a'
 * '<S1>'   : 'Emulate_Prescan_2019a/Blank Message'
 * '<S2>'   : 'Emulate_Prescan_2019a/Prescan'
 * '<S3>'   : 'Emulate_Prescan_2019a/Publish'
 */
#endif                                 /* RTW_HEADER_Emulate_Prescan_2019a_h_ */
