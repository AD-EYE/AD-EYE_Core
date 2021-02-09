/*
 * ros_subsystem.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ros_subsystem".
 *
 * Model version              : 1.88
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Wed Nov 25 12:58:24 2020
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ros_subsystem_capi.h"
#include "ros_subsystem.h"
#include "ros_subsystem_private.h"

/* user code (top of source file) */
#include "ros_subsystem_prescan.h"

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

/* Model output function */
static void ros_subsystem_output(void)
{
  SL_Bus_ros_subsystem_std_msgs_Float32 rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Inport: '<Root>/<VelocityX>'
   */
  rtb_BusAssignment.Data = (real32_T)ros_subsystem_U.VelocityX;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_ros_subsystem_5.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model update function */
static void ros_subsystem_update(void)
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
  if (!(++ros_subsystem_M->Timing.clockTick0)) {
    ++ros_subsystem_M->Timing.clockTickH0;
  }

  ros_subsystem_M->Timing.t[0] = ros_subsystem_M->Timing.clockTick0 *
    ros_subsystem_M->Timing.stepSize0 + ros_subsystem_M->Timing.clockTickH0 *
    ros_subsystem_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void ros_subsystem_initialize(void)
{
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
static void ros_subsystem_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&ros_subsystem_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  ros_subsystem_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ros_subsystem_update();
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
  ros_subsystem_initialize();
}

void MdlTerminate(void)
{
  ros_subsystem_terminate();
}

/* Registration function */
RT_MODEL_ros_subsystem_T *ros_subsystem(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ros_subsystem_M, 0,
                sizeof(RT_MODEL_ros_subsystem_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ros_subsystem_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    ros_subsystem_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ros_subsystem_M->Timing.sampleTimes =
      (&ros_subsystem_M->Timing.sampleTimesArray[0]);
    ros_subsystem_M->Timing.offsetTimes =
      (&ros_subsystem_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ros_subsystem_M->Timing.sampleTimes[0] = (0.05);

    /* task offsets */
    ros_subsystem_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(ros_subsystem_M, &ros_subsystem_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ros_subsystem_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    ros_subsystem_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ros_subsystem_M, 300.0);
  ros_subsystem_M->Timing.stepSize0 = 0.05;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    ros_subsystem_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ros_subsystem_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ros_subsystem_M->rtwLogInfo, (NULL));
    rtliSetLogT(ros_subsystem_M->rtwLogInfo, "");
    rtliSetLogX(ros_subsystem_M->rtwLogInfo, "");
    rtliSetLogXFinal(ros_subsystem_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ros_subsystem_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ros_subsystem_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ros_subsystem_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ros_subsystem_M->rtwLogInfo, 1);
    rtliSetLogY(ros_subsystem_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ros_subsystem_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ros_subsystem_M->rtwLogInfo, (NULL));
  }

  ros_subsystem_M->solverInfoPtr = (&ros_subsystem_M->solverInfo);
  ros_subsystem_M->Timing.stepSize = (0.05);
  rtsiSetFixedStepSize(&ros_subsystem_M->solverInfo, 0.05);
  rtsiSetSolverMode(&ros_subsystem_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* parameters */
  ros_subsystem_M->defaultParam = ((real_T *)&ros_subsystem_P);

  /* states (dwork) */
  ros_subsystem_M->dwork = ((void *) &ros_subsystem_DW);
  (void) memset((void *)&ros_subsystem_DW, 0,
                sizeof(DW_ros_subsystem_T));

  /* external inputs */
  ros_subsystem_M->inputs = (((void*)&ros_subsystem_U));
  ros_subsystem_U.VelocityX = 0.0;

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  ros_subsystem_InitializeDataMapInfo();

  /* Initialize Sizes */
  ros_subsystem_M->Sizes.numContStates = (0);/* Number of continuous states */
  ros_subsystem_M->Sizes.numY = (0);   /* Number of model outputs */
  ros_subsystem_M->Sizes.numU = (1);   /* Number of model inputs */
  ros_subsystem_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  ros_subsystem_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ros_subsystem_M->Sizes.numBlocks = (6);/* Number of blocks */
  ros_subsystem_M->Sizes.numBlockIO = (0);/* Number of block outputs */
  ros_subsystem_M->Sizes.numBlockPrms = (1);/* Sum of parameter "widths" */
  return ros_subsystem_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
