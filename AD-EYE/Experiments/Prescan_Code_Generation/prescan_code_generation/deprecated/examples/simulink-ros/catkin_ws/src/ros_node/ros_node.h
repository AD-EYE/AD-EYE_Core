/*
 * ros_node.h
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

#ifndef RTW_HEADER_ros_node_h_
#define RTW_HEADER_ros_node_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef ros_node_COMMON_INCLUDES_
# define ros_node_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* ros_node_COMMON_INCLUDES_ */

#include "ros_node_types.h"

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
  robotics_slros_internal_block_T obj; /* '<S2>/SinkBlock' */
  real_T Delay1_DSTATE;                /* '<Root>/Delay1' */
  real_T Delay_DSTATE;                 /* '<Root>/Delay' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  boolean_T objisempty;                /* '<S2>/SinkBlock' */
} DW_ros_node_T;

/* Parameters (default storage) */
struct P_ros_node_T_ {
  SL_Bus_ros_node_std_msgs_UInt8 Constant_Value;/* Computed Parameter: Constant_Value
                                                 * Referenced by: '<S1>/Constant'
                                                 */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<Root>/Delay1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<Root>/Delay'
                                        */
  real_T Switch_Threshold;             /* Expression: 10
                                        * Referenced by: '<Root>/Switch'
                                        */
  real_T Constant_Value_a;             /* Expression: 1
                                        * Referenced by: '<Root>/Constant'
                                        */
  uint32_T Delay1_DelayLength;         /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<Root>/Delay1'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<Root>/Delay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ros_node_T {
  const char_T *errorStatus;
};

/* Class declaration for model ros_node */
class ros_nodeModelClass {
  /* public data and function members */
 public:
  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  ros_nodeModelClass();

  /* Destructor */
  ~ros_nodeModelClass();

  /* Real-Time Model get method */
  RT_MODEL_ros_node_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  static P_ros_node_T ros_node_P;

  /* Block states */
  DW_ros_node_T ros_node_DW;

  /* Real-Time Model */
  RT_MODEL_ros_node_T ros_node_M;

  /* private member function(s) for subsystem '<Root>'*/
  void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj);
};

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
 * '<Root>' : 'ros_node'
 * '<S1>'   : 'ros_node/Blank Message'
 * '<S2>'   : 'ros_node/Publish'
 */
#endif                                 /* RTW_HEADER_ros_node_h_ */
