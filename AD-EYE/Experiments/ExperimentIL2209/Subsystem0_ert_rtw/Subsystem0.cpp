/*
 * Subsystem0.cpp
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

#include "Subsystem0.h"
#include "Subsystem0_private.h"

/* Block states (default storage) */
DW_Subsystem0_T Subsystem0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Subsystem0_T Subsystem0_U;

/* Real-time model */
RT_MODEL_Subsystem0_T Subsystem0_M_;
RT_MODEL_Subsystem0_T *const Subsystem0_M = &Subsystem0_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj);
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void Subsystem0_step(void)
{
  SL_Bus_Subsystem0_std_msgs_Float32 rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Inport: '<Root>/<VelocityX>'
   */
  rtb_BusAssignment.Data = static_cast<real32_T>(Subsystem0_U.VelocityX);

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_Subsystem0_5.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model initialize function */
void Subsystem0_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Subsystem0_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Subsystem0_DW, 0,
                sizeof(DW_Subsystem0_T));

  /* external inputs */
  Subsystem0_U.VelocityX = 0.0;

  {
    static const char_T tmp[11] = { '/', 'v', 'e', 'l', 'o', 'c', 'i', 't', 'y',
      '_', 'x' };

    char_T tmp_0[12];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    Subsystem0_DW.obj.matlabCodegenIsDeleted = true;
    Subsystem0_DW.obj.isInitialized = 0;
    Subsystem0_DW.obj.matlabCodegenIsDeleted = false;
    Subsystem0_DW.objisempty = true;
    Subsystem0_DW.obj.isSetupComplete = false;
    Subsystem0_DW.obj.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[11] = '\x00';
    Pub_Subsystem0_5.createPublisher(tmp_0, 1);
    Subsystem0_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }
}

/* Model terminate function */
void Subsystem0_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&Subsystem0_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
