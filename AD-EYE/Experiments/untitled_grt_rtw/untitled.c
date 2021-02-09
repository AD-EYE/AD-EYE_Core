/*
 * untitled.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "untitled".
 *
 * Model version              : 1.0
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Sun Oct 25 09:20:48 2020
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include "untitled_private.h"

/* Block states (default storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;
real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T y;
  real_T sr;
  real_T si;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

/* Model step function */
void untitled_step(void)
{
  /* local block i/o variables */
  real_T rtb_Sinenoise;
  real_T rtb_Bandpassfilteredsignal;
  int32_T denIdx;
  real_T HoldSine;
  int32_T j;
  real_T DiscreteFilter_tmp;

  /* Sin: '<Root>/Sine Wave' */
  if (untitled_DW.systemEnable != 0) {
    DiscreteFilter_tmp = untitled_P.SineWave_Freq * untitled_M->Timing.taskTime0;
    untitled_DW.lastSin = sin(DiscreteFilter_tmp);
    untitled_DW.lastCos = cos(DiscreteFilter_tmp);
    untitled_DW.systemEnable = 0;
  }

  /* RandomNumber: '<Root>/Random Number' */
  rtb_Bandpassfilteredsignal = untitled_DW.NextOutput;

  /* Sum: '<Root>/Sum' incorporates:
   *  Sin: '<Root>/Sine Wave'
   */
  rtb_Sinenoise = (((untitled_DW.lastSin * untitled_P.SineWave_PCos +
                     untitled_DW.lastCos * untitled_P.SineWave_PSin) *
                    untitled_P.SineWave_HCos + (untitled_DW.lastCos *
    untitled_P.SineWave_PCos - untitled_DW.lastSin * untitled_P.SineWave_PSin) *
                    untitled_P.SineWave_Hsin) * untitled_P.SineWave_Amp +
                   untitled_P.SineWave_Bias) + rtb_Bandpassfilteredsignal;

  /* DiscreteFilter: '<Root>/Discrete Filter' */
  DiscreteFilter_tmp = rtb_Sinenoise;
  denIdx = 1;
  for (j = 0; j < 8; j++) {
    DiscreteFilter_tmp -= untitled_P.DiscreteFilter_DenCoef[denIdx] *
      untitled_DW.DiscreteFilter_states[j];
    denIdx++;
  }

  DiscreteFilter_tmp /= untitled_P.DiscreteFilter_DenCoef[0];
  HoldSine = untitled_P.DiscreteFilter_NumCoef[0] * DiscreteFilter_tmp;
  denIdx = 1;
  for (j = 0; j < 8; j++) {
    HoldSine += untitled_P.DiscreteFilter_NumCoef[denIdx] *
      untitled_DW.DiscreteFilter_states[j];
    denIdx++;
  }

  rtb_Bandpassfilteredsignal = HoldSine;

  /* End of DiscreteFilter: '<Root>/Discrete Filter' */
  /* Update for Sin: '<Root>/Sine Wave' */
  HoldSine = untitled_DW.lastSin;
  untitled_DW.lastSin = untitled_DW.lastSin * untitled_P.SineWave_HCos +
    untitled_DW.lastCos * untitled_P.SineWave_Hsin;
  untitled_DW.lastCos = untitled_DW.lastCos * untitled_P.SineWave_HCos -
    HoldSine * untitled_P.SineWave_Hsin;

  /* Update for RandomNumber: '<Root>/Random Number' */
  untitled_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf(&untitled_DW.RandSeed) *
    untitled_P.RandomNumber_StdDev + untitled_P.RandomNumber_Mean;

  /* Update for DiscreteFilter: '<Root>/Discrete Filter' */
  for (j = 0; j < 7; j++) {
    untitled_DW.DiscreteFilter_states[7 - j] =
      untitled_DW.DiscreteFilter_states[6 - j];
  }

  untitled_DW.DiscreteFilter_states[0] = DiscreteFilter_tmp;

  /* End of Update for DiscreteFilter: '<Root>/Discrete Filter' */

  /* Matfile logging */
  rt_UpdateTXYLogVars(untitled_M->rtwLogInfo, (&untitled_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.000125s, 0.0s] */
    if ((rtmGetTFinal(untitled_M)!=-1) &&
        !((rtmGetTFinal(untitled_M)-untitled_M->Timing.taskTime0) >
          untitled_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++untitled_M->Timing.clockTick0)) {
    ++untitled_M->Timing.clockTickH0;
  }

  untitled_M->Timing.taskTime0 = untitled_M->Timing.clockTick0 *
    untitled_M->Timing.stepSize0 + untitled_M->Timing.clockTickH0 *
    untitled_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)untitled_M, 0,
                sizeof(RT_MODEL_untitled_T));
  rtmSetTFinal(untitled_M, -1);
  untitled_M->Timing.stepSize0 = 0.000125;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    untitled_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogT(untitled_M->rtwLogInfo, "");
    rtliSetLogX(untitled_M->rtwLogInfo, "");
    rtliSetLogXFinal(untitled_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(untitled_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(untitled_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(untitled_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(untitled_M->rtwLogInfo, 1);
    rtliSetLogY(untitled_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(untitled_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&untitled_DW, 0,
                sizeof(DW_untitled_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(untitled_M->rtwLogInfo, 0.0, rtmGetTFinal
    (untitled_M), untitled_M->Timing.stepSize0, (&rtmGetErrorStatus(untitled_M)));

  {
    uint32_T tseed;
    int32_T t;
    int32_T i;
    real_T tmp;

    /* InitializeConditions for RandomNumber: '<Root>/Random Number' */
    tmp = floor(untitled_P.RandomNumber_Seed);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    i = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)i << 16U)) + t) << 16U) + t) + i;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    untitled_DW.RandSeed = tseed;
    untitled_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf(&untitled_DW.RandSeed) *
      untitled_P.RandomNumber_StdDev + untitled_P.RandomNumber_Mean;

    /* End of InitializeConditions for RandomNumber: '<Root>/Random Number' */

    /* InitializeConditions for DiscreteFilter: '<Root>/Discrete Filter' */
    for (i = 0; i < 8; i++) {
      untitled_DW.DiscreteFilter_states[i] =
        untitled_P.DiscreteFilter_InitialStates;
    }

    /* End of InitializeConditions for DiscreteFilter: '<Root>/Discrete Filter' */
  }

  /* Enable for Sin: '<Root>/Sine Wave' */
  untitled_DW.systemEnable = 1;
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* (no terminate code required) */
}
