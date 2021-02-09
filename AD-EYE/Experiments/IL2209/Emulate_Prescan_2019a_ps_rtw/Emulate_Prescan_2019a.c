/*
 * Emulate_Prescan_2019a.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Emulate_Prescan_2019a".
 *
 * Model version              : 1.7
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Mon Nov 30 16:37:17 2020
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Emulate_Prescan_2019a_capi.h"
#include "Emulate_Prescan_2019a.h"
#include "Emulate_Prescan_2019a_private.h"

/* user code (top of source file) */
#include "Emulate_Prescan_2019a_prescan.h"

/* Block signals (default storage) */
B_Emulate_Prescan_2019a_T Emulate_Prescan_2019a_B;

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

/* Model output function */
static void Emulate_Prescan_2019a_output(void)
{
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

    Emulate_Prescan_2019a_B.Switch = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)
      -(int16_T)(uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  } else {
    Emulate_Prescan_2019a_B.Switch = (uint16_T)((uint32_T)
      Emulate_Prescan_2019a_DW.Delay1_DSTATE +
      Emulate_Prescan_2019a_DW.Delay_DSTATE);
  }

  /* End of Switch: '<S2>/Switch' */

  /* BusAssignment: '<Root>/Bus Assignment' */
  rtb_BusAssignment.Data = Emulate_Prescan_2019a_B.Switch;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S3>/SinkBlock' */
  Pub_Emulate_Prescan_2019a_12.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model update function */
static void Emulate_Prescan_2019a_update(void)
{
  /* Update for Delay: '<S2>/Delay' */
  Emulate_Prescan_2019a_DW.Delay_DSTATE = Emulate_Prescan_2019a_B.Switch;

  /* Update for Delay: '<S2>/Delay1' incorporates:
   *  Constant: '<Root>/Constant'
   */
  Emulate_Prescan_2019a_DW.Delay1_DSTATE =
    Emulate_Prescan_2019a_P.Constant_Value_a;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Emulate_Prescan_2019a_M->Timing.clockTick0)) {
    ++Emulate_Prescan_2019a_M->Timing.clockTickH0;
  }

  Emulate_Prescan_2019a_M->Timing.t[0] =
    Emulate_Prescan_2019a_M->Timing.clockTick0 *
    Emulate_Prescan_2019a_M->Timing.stepSize0 +
    Emulate_Prescan_2019a_M->Timing.clockTickH0 *
    Emulate_Prescan_2019a_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void Emulate_Prescan_2019a_initialize(void)
{
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
static void Emulate_Prescan_2019a_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S3>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&Emulate_Prescan_2019a_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Emulate_Prescan_2019a_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Emulate_Prescan_2019a_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  Emulate_Prescan_2019a_initialize();
}

void MdlTerminate(void)
{
  Emulate_Prescan_2019a_terminate();
}

/* Registration function */
RT_MODEL_Emulate_Prescan_2019_T *Emulate_Prescan_2019a(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Emulate_Prescan_2019a_M, 0,
                sizeof(RT_MODEL_Emulate_Prescan_2019_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Emulate_Prescan_2019a_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Emulate_Prescan_2019a_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Emulate_Prescan_2019a_M->Timing.sampleTimes =
      (&Emulate_Prescan_2019a_M->Timing.sampleTimesArray[0]);
    Emulate_Prescan_2019a_M->Timing.offsetTimes =
      (&Emulate_Prescan_2019a_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Emulate_Prescan_2019a_M->Timing.sampleTimes[0] = (1.0);

    /* task offsets */
    Emulate_Prescan_2019a_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Emulate_Prescan_2019a_M, &Emulate_Prescan_2019a_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Emulate_Prescan_2019a_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Emulate_Prescan_2019a_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Emulate_Prescan_2019a_M, 30.0);
  Emulate_Prescan_2019a_M->Timing.stepSize0 = 1.0;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    Emulate_Prescan_2019a_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Emulate_Prescan_2019a_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Emulate_Prescan_2019a_M->rtwLogInfo, (NULL));
    rtliSetLogT(Emulate_Prescan_2019a_M->rtwLogInfo, "tout");
    rtliSetLogX(Emulate_Prescan_2019a_M->rtwLogInfo, "");
    rtliSetLogXFinal(Emulate_Prescan_2019a_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Emulate_Prescan_2019a_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Emulate_Prescan_2019a_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Emulate_Prescan_2019a_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Emulate_Prescan_2019a_M->rtwLogInfo, 1);
    rtliSetLogY(Emulate_Prescan_2019a_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Emulate_Prescan_2019a_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Emulate_Prescan_2019a_M->rtwLogInfo, (NULL));
  }

  Emulate_Prescan_2019a_M->solverInfoPtr = (&Emulate_Prescan_2019a_M->solverInfo);
  Emulate_Prescan_2019a_M->Timing.stepSize = (1.0);
  rtsiSetFixedStepSize(&Emulate_Prescan_2019a_M->solverInfo, 1.0);
  rtsiSetSolverMode(&Emulate_Prescan_2019a_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Emulate_Prescan_2019a_M->blockIO = ((void *) &Emulate_Prescan_2019a_B);
  (void) memset(((void *) &Emulate_Prescan_2019a_B), 0,
                sizeof(B_Emulate_Prescan_2019a_T));

  /* parameters */
  Emulate_Prescan_2019a_M->defaultParam = ((real_T *)&Emulate_Prescan_2019a_P);

  /* states (dwork) */
  Emulate_Prescan_2019a_M->dwork = ((void *) &Emulate_Prescan_2019a_DW);
  (void) memset((void *)&Emulate_Prescan_2019a_DW, 0,
                sizeof(DW_Emulate_Prescan_2019a_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Emulate_Prescan_2019a_InitializeDataMapInfo();

  /* Initialize Sizes */
  Emulate_Prescan_2019a_M->Sizes.numContStates = (0);/* Number of continuous states */
  Emulate_Prescan_2019a_M->Sizes.numY = (0);/* Number of model outputs */
  Emulate_Prescan_2019a_M->Sizes.numU = (0);/* Number of model inputs */
  Emulate_Prescan_2019a_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Emulate_Prescan_2019a_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Emulate_Prescan_2019a_M->Sizes.numBlocks = (14);/* Number of blocks */
  Emulate_Prescan_2019a_M->Sizes.numBlockIO = (1);/* Number of block outputs */
  Emulate_Prescan_2019a_M->Sizes.numBlockPrms = (8);/* Sum of parameter "widths" */
  return Emulate_Prescan_2019a_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
