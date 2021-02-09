/*
 * ros_subsystem.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ros_subsystem".
 *
 * Model version              : 1.88
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C++ source code generated on : Wed Nov 25 12:48:30 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ros_subsystem.h"
#include "ros_subsystem_private.h"

/* Block states (default storage) */
DW_ros_subsystem_T ros_subsystem_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ros_subsystem_T ros_subsystem_U;

/* Real-time model */
RT_MODEL_ros_subsystem_T ros_subsystem_M_;
RT_MODEL_ros_subsystem_T *const ros_subsystem_M = &ros_subsystem_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj);
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void ros_subsystem_step(void)
{
  SL_Bus_ros_subsystem_std_msgs_Float32 rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Inport: '<Root>/<VelocityX>'
   */
  rtb_BusAssignment.Data = static_cast<real32_T>(ros_subsystem_U.VelocityX);

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_ros_subsystem_5.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model initialize function */
void ros_subsystem_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(ros_subsystem_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&ros_subsystem_DW, 0,
                sizeof(DW_ros_subsystem_T));

  /* external inputs */
  ros_subsystem_U.VelocityX = 0.0;

  {
    static const char_T tmp[11] = { '/', 'v', 'e', 'l', 'o', 'c', 'i', 't', 'y',
      '_', 'x' };

    char_T tmp_0[12];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    ros_subsystem_DW.obj.matlabCodegenIsDeleted = true;
    ros_subsystem_DW.obj.isInitialized = 0;
    ros_subsystem_DW.obj.matlabCodegenIsDeleted = false;
    ros_subsystem_DW.objisempty = true;
    ros_subsystem_DW.obj.isSetupComplete = false;
    ros_subsystem_DW.obj.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[11] = '\x00';
    Pub_ros_subsystem_5.createPublisher(tmp_0, 1);
    ros_subsystem_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }
}

/* Model terminate function */
void ros_subsystem_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&ros_subsystem_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
