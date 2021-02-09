/*
 * untitled_data.c
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

/* Block parameters (default storage) */
P_untitled_T untitled_P = {
  /* Expression: 1
   * Referenced by: '<Root>/Sine Wave'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Sine Wave'
   */
  0.0,

  /* Expression: 2*pi*100
   * Referenced by: '<Root>/Sine Wave'
   */
  628.31853071795865,

  /* Computed Parameter: SineWave_Hsin
   * Referenced by: '<Root>/Sine Wave'
   */
  0.078459095727844944,

  /* Computed Parameter: SineWave_HCos
   * Referenced by: '<Root>/Sine Wave'
   */
  0.996917333733128,

  /* Computed Parameter: SineWave_PSin
   * Referenced by: '<Root>/Sine Wave'
   */
  -0.078459095727844944,

  /* Computed Parameter: SineWave_PCos
   * Referenced by: '<Root>/Sine Wave'
   */
  0.996917333733128,

  /* Expression: 0
   * Referenced by: '<Root>/Random Number'
   */
  0.0,

  /* Computed Parameter: RandomNumber_StdDev
   * Referenced by: '<Root>/Random Number'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Random Number'
   */
  0.0,

  /* Expression: [0.000987947087024  -0.007866111001516   0.027438142026555  -0.054764720946282   0.068409485670105  -0.054764720946282   0.027438142026555  -0.007866111001516   0.000987947087024]
   * Referenced by: '<Root>/Discrete Filter'
   */
  { 0.000987947087024, -0.007866111001516, 0.027438142026555, -0.054764720946282,
    0.068409485670105, -0.054764720946282, 0.027438142026555, -0.007866111001516,
    0.000987947087024 },

  /* Expression: [1.000000000000000  -7.944031997545686  27.635065757644615 -54.984635962907035  68.438574736652072 -54.568127619544200  27.217980746836638  -7.764868315600190   0.970042656129287]
   * Referenced by: '<Root>/Discrete Filter'
   */
  { 1.0, -7.9440319975456859, 27.635065757644615, -54.984635962907035,
    68.438574736652072, -54.5681276195442, 27.217980746836638, -7.76486831560019,
    0.970042656129287 },

  /* Expression: 0
   * Referenced by: '<Root>/Discrete Filter'
   */
  0.0
};
