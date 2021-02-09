/*
 * Subsystem0.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Subsystem0".
 *
 * Model version              : 1.99
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Wed Nov 25 16:13:06 2020
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Subsystem0_capi.h"
#include "Subsystem0.h"
#include "Subsystem0_private.h"

/* user code (top of source file) */
#include "Subsystem0_prescan.h"

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

/* Model output function */
static void Subsystem0_output(void)
{
  SL_Bus_Subsystem0_std_msgs_Float32 rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Inport: '<Root>/<VelocityX>'
   */
  rtb_BusAssignment.Data = (real32_T)Subsystem0_U.VelocityX;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_Subsystem0_5.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model update function */
static void Subsystem0_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Subsystem0_M->Timing.clockTick0)) {
    ++Subsystem0_M->Timing.clockTickH0;
  }

  Subsystem0_M->Timing.t[0] = Subsystem0_M->Timing.clockTick0 *
    Subsystem0_M->Timing.stepSize0 + Subsystem0_M->Timing.clockTickH0 *
    Subsystem0_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void Subsystem0_initialize(void)
{
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
static void Subsystem0_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&Subsystem0_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Subsystem0_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Subsystem0_update();
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
  Subsystem0_initialize();
}

void MdlTerminate(void)
{
  Subsystem0_terminate();
}

/* Registration function */
RT_MODEL_Subsystem0_T *Subsystem0(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Subsystem0_M, 0,
                sizeof(RT_MODEL_Subsystem0_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Subsystem0_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Subsystem0_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Subsystem0_M->Timing.sampleTimes = (&Subsystem0_M->Timing.sampleTimesArray[0]);
    Subsystem0_M->Timing.offsetTimes = (&Subsystem0_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Subsystem0_M->Timing.sampleTimes[0] = (0.05);

    /* task offsets */
    Subsystem0_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Subsystem0_M, &Subsystem0_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Subsystem0_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Subsystem0_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Subsystem0_M, 300.0);
  Subsystem0_M->Timing.stepSize0 = 0.05;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    Subsystem0_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Subsystem0_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Subsystem0_M->rtwLogInfo, (NULL));
    rtliSetLogT(Subsystem0_M->rtwLogInfo, "");
    rtliSetLogX(Subsystem0_M->rtwLogInfo, "");
    rtliSetLogXFinal(Subsystem0_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Subsystem0_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Subsystem0_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Subsystem0_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(Subsystem0_M->rtwLogInfo, 1);
    rtliSetLogY(Subsystem0_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Subsystem0_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Subsystem0_M->rtwLogInfo, (NULL));
  }

  Subsystem0_M->solverInfoPtr = (&Subsystem0_M->solverInfo);
  Subsystem0_M->Timing.stepSize = (0.05);
  rtsiSetFixedStepSize(&Subsystem0_M->solverInfo, 0.05);
  rtsiSetSolverMode(&Subsystem0_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* parameters */
  Subsystem0_M->defaultParam = ((real_T *)&Subsystem0_P);

  /* states (dwork) */
  Subsystem0_M->dwork = ((void *) &Subsystem0_DW);
  (void) memset((void *)&Subsystem0_DW, 0,
                sizeof(DW_Subsystem0_T));

  /* external inputs */
  Subsystem0_M->inputs = (((void*)&Subsystem0_U));
  Subsystem0_U.VelocityX = 0.0;

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Subsystem0_InitializeDataMapInfo();

  /* Initialize Sizes */
  Subsystem0_M->Sizes.numContStates = (0);/* Number of continuous states */
  Subsystem0_M->Sizes.numY = (0);      /* Number of model outputs */
  Subsystem0_M->Sizes.numU = (1);      /* Number of model inputs */
  Subsystem0_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  Subsystem0_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Subsystem0_M->Sizes.numBlocks = (6); /* Number of blocks */
  Subsystem0_M->Sizes.numBlockIO = (0);/* Number of block outputs */
  Subsystem0_M->Sizes.numBlockPrms = (1);/* Sum of parameter "widths" */
  return Subsystem0_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
