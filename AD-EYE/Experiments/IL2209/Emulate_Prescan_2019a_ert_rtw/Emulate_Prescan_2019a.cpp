/*
 * Emulate_Prescan_2019a.cpp
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

/* Block states (default storage) */
DW_Emulate_Prescan_2019a_T Emulate_Prescan_2019a_DW;

/* Real-time model */
RT_MODEL_Emulate_Prescan_2019_T Emulate_Prescan_2019a_M_;
RT_MODEL_Emulate_Prescan_2019_T *const Emulate_Prescan_2019a_M =
  &Emulate_Prescan_2019a_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj);
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void Emulate_Prescan_2019a_step(void)
{
  /* local block i/o variables */
  uint16_T rtb_Switch;
  SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16 rtb_BusAssignment;
  real_T tmp;

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Delay: '<S2>/Delay'
   *  Delay: '<S2>/Delay1'
   *  Sum: '<S2>/Sum'
   */
  if (Emulate_Prescan_2019a_DW.Delay_DSTATE >=
      Emulate_Prescan_2019a_P.Switch_Threshold) {
    tmp = floor(Emulate_Prescan_2019a_P.Constant1_Value);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    rtb_Switch = static_cast<uint16_T>((tmp < 0.0 ? static_cast<int32_T>
      (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>(-tmp))))
      : static_cast<int32_T>(static_cast<uint16_T>(tmp))));
  } else {
    rtb_Switch = static_cast<uint16_T>((static_cast<uint32_T>
      (Emulate_Prescan_2019a_DW.Delay1_DSTATE) +
      Emulate_Prescan_2019a_DW.Delay_DSTATE));
  }

  /* End of Switch: '<S2>/Switch' */

  /* BusAssignment: '<Root>/Bus Assignment' */
  rtb_BusAssignment.Data = rtb_Switch;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S3>/SinkBlock' */
  Pub_Emulate_Prescan_2019a_12.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  /* Update for Delay: '<S2>/Delay' */
  Emulate_Prescan_2019a_DW.Delay_DSTATE = rtb_Switch;

  /* Update for Delay: '<S2>/Delay1' incorporates:
   *  Constant: '<Root>/Constant'
   */
  Emulate_Prescan_2019a_DW.Delay1_DSTATE =
    Emulate_Prescan_2019a_P.Constant_Value_a;
}

/* Model initialize function */
void Emulate_Prescan_2019a_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(Emulate_Prescan_2019a_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Emulate_Prescan_2019a_DW, 0,
                sizeof(DW_Emulate_Prescan_2019a_T));

  {
    static const char_T tmp[8] = { '/', 'c', 'o', 'u', 'n', 't', 'e', 'r' };

    char_T tmp_0[9];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S3>/SinkBlock' */
    Emulate_Prescan_2019a_DW.obj.matlabCodegenIsDeleted = true;
    Emulate_Prescan_2019a_DW.obj.isInitialized = 0;
    Emulate_Prescan_2019a_DW.obj.matlabCodegenIsDeleted = false;
    Emulate_Prescan_2019a_DW.objisempty = true;
    Emulate_Prescan_2019a_DW.obj.isSetupComplete = false;
    Emulate_Prescan_2019a_DW.obj.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[8] = '\x00';
    Pub_Emulate_Prescan_2019a_12.createPublisher(tmp_0, 1);
    Emulate_Prescan_2019a_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* InitializeConditions for Delay: '<S2>/Delay' */
  Emulate_Prescan_2019a_DW.Delay_DSTATE =
    Emulate_Prescan_2019a_P.Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S2>/Delay1' */
  Emulate_Prescan_2019a_DW.Delay1_DSTATE =
    Emulate_Prescan_2019a_P.Delay1_InitialCondition;
}

/* Model terminate function */
void Emulate_Prescan_2019a_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S3>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&Emulate_Prescan_2019a_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
