/*
 * File: Odometry_publisher.c
 *
 *
 *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
 *
 *   This file is an S-function produced by the S-Function
 *   Builder which only recognizes certain fields.  Changes made
 *   outside these fields will be lost the next time the block is
 *   used to load, edit, and resave this file. This file will be overwritten
 *   by the S-function Builder block. If you want to edit this file by hand, 
 *   you must change it only in the area defined as:  
 *
 *        %%%-SFUNWIZ_defines_Changes_BEGIN
 *        #define NAME 'replacement text' 
 *        %%% SFUNWIZ_defines_Changes_END
 *
 *   DO NOT change NAME--Change the 'replacement text' only.
 *
 *   For better compatibility with the Simulink Coder, the
 *   "wrapper" S-function technique is used.  This is discussed
 *   in the Simulink Coder's Manual in the Chapter titled,
 *   "Wrapper S-functions".
 *
 *  -------------------------------------------------------------------------
 * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  ------------------------------------------------------------------------- 
 *
 * Created: Fri Jan 15 04:28:03 2021
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME Odometry_publisher
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS            16
/* Input Port  0 */
#define IN_PORT_0_NAME        seq
#define INPUT_0_WIDTH         1
#define INPUT_DIMS_0_COL      1
#define INPUT_0_DTYPE         real_T
#define INPUT_0_COMPLEX       COMPLEX_NO
#define IN_0_FRAME_BASED      FRAME_NO
#define IN_0_BUS_BASED        0
#define IN_0_BUS_NAME         
#define IN_0_DIMS             1-D
#define INPUT_0_FEEDTHROUGH   1
#define IN_0_ISSIGNED         0
#define IN_0_WORDLENGTH       8
#define IN_0_FIXPOINTSCALING  1
#define IN_0_FRACTIONLENGTH   9
#define IN_0_BIAS             0
#define IN_0_SLOPE            0.125
/* Input Port  1 */
#define IN_PORT_1_NAME        frameId_length
#define INPUT_1_WIDTH         1
#define INPUT_DIMS_1_COL      1
#define INPUT_1_DTYPE         real_T
#define INPUT_1_COMPLEX       COMPLEX_NO
#define IN_1_FRAME_BASED      FRAME_NO
#define IN_1_BUS_BASED        0
#define IN_1_BUS_NAME         
#define IN_1_DIMS             1-D
#define INPUT_1_FEEDTHROUGH   1
#define IN_1_ISSIGNED         0
#define IN_1_WORDLENGTH       8
#define IN_1_FIXPOINTSCALING  1
#define IN_1_FRACTIONLENGTH   9
#define IN_1_BIAS             0
#define IN_1_SLOPE            0.125
/* Input Port  2 */
#define IN_PORT_2_NAME        childFrameId_length
#define INPUT_2_WIDTH         1
#define INPUT_DIMS_2_COL      1
#define INPUT_2_DTYPE         real_T
#define INPUT_2_COMPLEX       COMPLEX_NO
#define IN_2_FRAME_BASED      FRAME_NO
#define IN_2_BUS_BASED        0
#define IN_2_BUS_NAME         
#define IN_2_DIMS             1-D
#define INPUT_2_FEEDTHROUGH   1
#define IN_2_ISSIGNED         0
#define IN_2_WORDLENGTH       8
#define IN_2_FIXPOINTSCALING  1
#define IN_2_FRACTIONLENGTH   9
#define IN_2_BIAS             0
#define IN_2_SLOPE            0.125
/* Input Port  3 */
#define IN_PORT_3_NAME        positionX
#define INPUT_3_WIDTH         1
#define INPUT_DIMS_3_COL      1
#define INPUT_3_DTYPE         real_T
#define INPUT_3_COMPLEX       COMPLEX_NO
#define IN_3_FRAME_BASED      FRAME_NO
#define IN_3_BUS_BASED        0
#define IN_3_BUS_NAME         
#define IN_3_DIMS             1-D
#define INPUT_3_FEEDTHROUGH   1
#define IN_3_ISSIGNED         0
#define IN_3_WORDLENGTH       8
#define IN_3_FIXPOINTSCALING  1
#define IN_3_FRACTIONLENGTH   9
#define IN_3_BIAS             0
#define IN_3_SLOPE            0.125
/* Input Port  4 */
#define IN_PORT_4_NAME        positionY
#define INPUT_4_WIDTH         1
#define INPUT_DIMS_4_COL      1
#define INPUT_4_DTYPE         real_T
#define INPUT_4_COMPLEX       COMPLEX_NO
#define IN_4_FRAME_BASED      FRAME_NO
#define IN_4_BUS_BASED        0
#define IN_4_BUS_NAME         
#define IN_4_DIMS             1-D
#define INPUT_4_FEEDTHROUGH   1
#define IN_4_ISSIGNED         0
#define IN_4_WORDLENGTH       8
#define IN_4_FIXPOINTSCALING  1
#define IN_4_FRACTIONLENGTH   9
#define IN_4_BIAS             0
#define IN_4_SLOPE            0.125
/* Input Port  5 */
#define IN_PORT_5_NAME        positionZ
#define INPUT_5_WIDTH         1
#define INPUT_DIMS_5_COL      1
#define INPUT_5_DTYPE         real_T
#define INPUT_5_COMPLEX       COMPLEX_NO
#define IN_5_FRAME_BASED      FRAME_NO
#define IN_5_BUS_BASED        0
#define IN_5_BUS_NAME         
#define IN_5_DIMS             1-D
#define INPUT_5_FEEDTHROUGH   1
#define IN_5_ISSIGNED         0
#define IN_5_WORDLENGTH       8
#define IN_5_FIXPOINTSCALING  1
#define IN_5_FRACTIONLENGTH   9
#define IN_5_BIAS             0
#define IN_5_SLOPE            0.125
/* Input Port  6 */
#define IN_PORT_6_NAME        orientW
#define INPUT_6_WIDTH         1
#define INPUT_DIMS_6_COL      1
#define INPUT_6_DTYPE         real_T
#define INPUT_6_COMPLEX       COMPLEX_NO
#define IN_6_FRAME_BASED      FRAME_NO
#define IN_6_BUS_BASED        0
#define IN_6_BUS_NAME         
#define IN_6_DIMS             1-D
#define INPUT_6_FEEDTHROUGH   1
#define IN_6_ISSIGNED         0
#define IN_6_WORDLENGTH       8
#define IN_6_FIXPOINTSCALING  1
#define IN_6_FRACTIONLENGTH   9
#define IN_6_BIAS             0
#define IN_6_SLOPE            0.125
/* Input Port  7 */
#define IN_PORT_7_NAME        orientX
#define INPUT_7_WIDTH         1
#define INPUT_DIMS_7_COL      1
#define INPUT_7_DTYPE         real_T
#define INPUT_7_COMPLEX       COMPLEX_NO
#define IN_7_FRAME_BASED      FRAME_NO
#define IN_7_BUS_BASED        0
#define IN_7_BUS_NAME         
#define IN_7_DIMS             1-D
#define INPUT_7_FEEDTHROUGH   1
#define IN_7_ISSIGNED         0
#define IN_7_WORDLENGTH       8
#define IN_7_FIXPOINTSCALING  1
#define IN_7_FRACTIONLENGTH   9
#define IN_7_BIAS             0
#define IN_7_SLOPE            0.125
/* Input Port  8 */
#define IN_PORT_8_NAME        orientY
#define INPUT_8_WIDTH         1
#define INPUT_DIMS_8_COL      1
#define INPUT_8_DTYPE         real_T
#define INPUT_8_COMPLEX       COMPLEX_NO
#define IN_8_FRAME_BASED      FRAME_NO
#define IN_8_BUS_BASED        0
#define IN_8_BUS_NAME         
#define IN_8_DIMS             1-D
#define INPUT_8_FEEDTHROUGH   1
#define IN_8_ISSIGNED         0
#define IN_8_WORDLENGTH       8
#define IN_8_FIXPOINTSCALING  1
#define IN_8_FRACTIONLENGTH   9
#define IN_8_BIAS             0
#define IN_8_SLOPE            0.125
/* Input Port  9 */
#define IN_PORT_9_NAME        orientZ
#define INPUT_9_WIDTH         1
#define INPUT_DIMS_9_COL      1
#define INPUT_9_DTYPE         real_T
#define INPUT_9_COMPLEX       COMPLEX_NO
#define IN_9_FRAME_BASED      FRAME_NO
#define IN_9_BUS_BASED        0
#define IN_9_BUS_NAME         
#define IN_9_DIMS             1-D
#define INPUT_9_FEEDTHROUGH   1
#define IN_9_ISSIGNED         0
#define IN_9_WORDLENGTH       8
#define IN_9_FIXPOINTSCALING  1
#define IN_9_FRACTIONLENGTH   9
#define IN_9_BIAS             0
#define IN_9_SLOPE            0.125
/* Input Port  10 */
#define IN_PORT_10_NAME        linearX
#define INPUT_10_WIDTH         1
#define INPUT_DIMS_10_COL      1
#define INPUT_10_DTYPE         real_T
#define INPUT_10_COMPLEX       COMPLEX_NO
#define IN_10_FRAME_BASED      FRAME_NO
#define IN_10_BUS_BASED        0
#define IN_10_BUS_NAME         
#define IN_10_DIMS             1-D
#define INPUT_10_FEEDTHROUGH   1
#define IN_10_ISSIGNED         0
#define IN_10_WORDLENGTH       8
#define IN_10_FIXPOINTSCALING  1
#define IN_10_FRACTIONLENGTH   9
#define IN_10_BIAS             0
#define IN_10_SLOPE            0.125
/* Input Port  11 */
#define IN_PORT_11_NAME        linearY
#define INPUT_11_WIDTH         1
#define INPUT_DIMS_11_COL      1
#define INPUT_11_DTYPE         real_T
#define INPUT_11_COMPLEX       COMPLEX_NO
#define IN_11_FRAME_BASED      FRAME_NO
#define IN_11_BUS_BASED        0
#define IN_11_BUS_NAME         
#define IN_11_DIMS             1-D
#define INPUT_11_FEEDTHROUGH   1
#define IN_11_ISSIGNED         0
#define IN_11_WORDLENGTH       8
#define IN_11_FIXPOINTSCALING  1
#define IN_11_FRACTIONLENGTH   9
#define IN_11_BIAS             0
#define IN_11_SLOPE            0.125
/* Input Port  12 */
#define IN_PORT_12_NAME        linearZ
#define INPUT_12_WIDTH         1
#define INPUT_DIMS_12_COL      1
#define INPUT_12_DTYPE         real_T
#define INPUT_12_COMPLEX       COMPLEX_NO
#define IN_12_FRAME_BASED      FRAME_NO
#define IN_12_BUS_BASED        0
#define IN_12_BUS_NAME         
#define IN_12_DIMS             1-D
#define INPUT_12_FEEDTHROUGH   1
#define IN_12_ISSIGNED         0
#define IN_12_WORDLENGTH       8
#define IN_12_FIXPOINTSCALING  1
#define IN_12_FRACTIONLENGTH   9
#define IN_12_BIAS             0
#define IN_12_SLOPE            0.125
/* Input Port  13 */
#define IN_PORT_13_NAME        angularX
#define INPUT_13_WIDTH         1
#define INPUT_DIMS_13_COL      1
#define INPUT_13_DTYPE         real_T
#define INPUT_13_COMPLEX       COMPLEX_NO
#define IN_13_FRAME_BASED      FRAME_NO
#define IN_13_BUS_BASED        0
#define IN_13_BUS_NAME         
#define IN_13_DIMS             1-D
#define INPUT_13_FEEDTHROUGH   1
#define IN_13_ISSIGNED         0
#define IN_13_WORDLENGTH       8
#define IN_13_FIXPOINTSCALING  1
#define IN_13_FRACTIONLENGTH   9
#define IN_13_BIAS             0
#define IN_13_SLOPE            0.125
/* Input Port  14 */
#define IN_PORT_14_NAME        angularY
#define INPUT_14_WIDTH         1
#define INPUT_DIMS_14_COL      1
#define INPUT_14_DTYPE         real_T
#define INPUT_14_COMPLEX       COMPLEX_NO
#define IN_14_FRAME_BASED      FRAME_NO
#define IN_14_BUS_BASED        0
#define IN_14_BUS_NAME         
#define IN_14_DIMS             1-D
#define INPUT_14_FEEDTHROUGH   1
#define IN_14_ISSIGNED         0
#define IN_14_WORDLENGTH       8
#define IN_14_FIXPOINTSCALING  1
#define IN_14_FRACTIONLENGTH   9
#define IN_14_BIAS             0
#define IN_14_SLOPE            0.125
/* Input Port  15 */
#define IN_PORT_15_NAME        angularZ
#define INPUT_15_WIDTH         1
#define INPUT_DIMS_15_COL      1
#define INPUT_15_DTYPE         real_T
#define INPUT_15_COMPLEX       COMPLEX_NO
#define IN_15_FRAME_BASED      FRAME_NO
#define IN_15_BUS_BASED        0
#define IN_15_BUS_NAME         
#define IN_15_DIMS             1-D
#define INPUT_15_FEEDTHROUGH   1
#define IN_15_ISSIGNED         0
#define IN_15_WORDLENGTH       8
#define IN_15_FIXPOINTSCALING  1
#define IN_15_FRACTIONLENGTH   9
#define IN_15_BIAS             0
#define IN_15_SLOPE            0.125

#define NUM_OUTPUTS           0

#define NPARAMS               4
/* Parameter 0 */
#define PARAMETER_0_NAME      topic
#define PARAMETER_0_DTYPE     int8_T
#define PARAMETER_0_COMPLEX   COMPLEX_NO
/* Parameter 1 */
#define PARAMETER_1_NAME      message_type
#define PARAMETER_1_DTYPE     int8_T
#define PARAMETER_1_COMPLEX   COMPLEX_NO
/* Parameter 2 */
#define PARAMETER_2_NAME      port
#define PARAMETER_2_DTYPE     real_T
#define PARAMETER_2_COMPLEX   COMPLEX_NO
/* Parameter 3 */
#define PARAMETER_3_NAME      timeout
#define PARAMETER_3_DTYPE     real_T
#define PARAMETER_3_COMPLEX   COMPLEX_NO

#define SAMPLE_TIME_0         INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES       0
#define DISC_STATES_IC        [0]
#define NUM_CONT_STATES       0
#define CONT_STATES_IC        [0]

#define SFUNWIZ_GENERATE_TLC  1
#define SOURCEFILES           "__SFB__C:\Program Files\MATLAB\R2019a\sys\lcc64\lcc64\lib64\ws2_32.lib__SFB__INC_PATH rosbridge/include__SFB__rosbridge/rosbridge_functions.c"
#define PANELINDEX            8
#define USE_SIMSTRUCT         0
#define SHOW_COMPILE_STEPS    0
#define CREATE_DEBUG_MEXFILE  0
#define SAVE_CODE_ONLY        0
#define SFUNWIZ_REVISION      3.0
/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"

#define PARAM_DEF0(S) ssGetSFcnParam(S, 0)
#define PARAM_DEF1(S) ssGetSFcnParam(S, 1)
#define PARAM_DEF2(S) ssGetSFcnParam(S, 2)
#define PARAM_DEF3(S) ssGetSFcnParam(S, 3)

#define IS_PARAM_INT8(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsInt8(pVal))

#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal))

extern void Odometry_publisher_Start_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3);
extern void Odometry_publisher_Outputs_wrapper(const real_T *seq,
			const real_T *frameId_length,
			const real_T *childFrameId_length,
			const real_T *positionX,
			const real_T *positionY,
			const real_T *positionZ,
			const real_T *orientW,
			const real_T *orientX,
			const real_T *orientY,
			const real_T *orientZ,
			const real_T *linearX,
			const real_T *linearY,
			const real_T *linearZ,
			const real_T *angularX,
			const real_T *angularY,
			const real_T *angularZ,
			void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3);
extern void Odometry_publisher_Terminate_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3);
/*====================*
 * S-function methods *
 *====================*/
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlCheckParameters =============================================
 * Abstract:
 *     Verify parameter definitions and types.
 */
static void mdlCheckParameters(SimStruct *S)
{
    int paramIndex  = 0;
    bool invalidParam = false;
    /* All parameters must match the S-function Builder Dialog */

    {
        const mxArray *pVal0 = ssGetSFcnParam(S, 0);
        if (!IS_PARAM_INT8(pVal0)) {
            invalidParam = true;
            paramIndex = 0;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal1 = ssGetSFcnParam(S, 1);
        if (!IS_PARAM_INT8(pVal1)) {
            invalidParam = true;
            paramIndex = 1;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal2 = ssGetSFcnParam(S, 2);
        if (!IS_PARAM_DOUBLE(pVal2)) {
            invalidParam = true;
            paramIndex = 2;
            goto EXIT_POINT;
        }
    }

    {
        const mxArray *pVal3 = ssGetSFcnParam(S, 3);
        if (!IS_PARAM_DOUBLE(pVal3)) {
            invalidParam = true;
            paramIndex = 3;
            goto EXIT_POINT;
        }
    }


    EXIT_POINT:
    if (invalidParam) {
        char parameterErrorMsg[1024];
        sprintf(parameterErrorMsg, "The data type and or complexity of parameter %d does not match the "
                "information specified in the S-function Builder dialog. "
                "For non-double parameters you will need to cast them using int8, int16, "
                "int32, uint8, uint16, uint32 or boolean.", paramIndex + 1);
        ssSetErrorStatus(S, parameterErrorMsg);
    }
    return;
}
#endif /* MDL_CHECK_PARAMETERS */
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS); /* Number of expected parameters */
    #if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) {
            return;
        }
    } else {
        return; /* Parameter mismatch will be reported by Simulink */
    }
    #endif

    ssSetArrayLayoutForCodeGen(S, SS_COLUMN_MAJOR);

    ssSetOperatingPointCompliance(S, DISALLOW_OPERATING_POINT);

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);


    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;
    /* Input Port 0 */
    ssSetInputPortWidth(S, 0, INPUT_0_WIDTH);
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 0, INPUT_0_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 0, INPUT_0_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/

    /* Input Port 1 */
    ssSetInputPortWidth(S, 1, INPUT_1_WIDTH);
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 1, INPUT_1_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 1, INPUT_1_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/

    /* Input Port 2 */
    ssSetInputPortWidth(S, 2, INPUT_2_WIDTH);
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 2, INPUT_2_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 2, INPUT_2_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/

    /* Input Port 3 */
    ssSetInputPortWidth(S, 3, INPUT_3_WIDTH);
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 3, INPUT_3_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 3, INPUT_3_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/

    /* Input Port 4 */
    ssSetInputPortWidth(S, 4, INPUT_4_WIDTH);
    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 4, INPUT_4_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 4, INPUT_4_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/

    /* Input Port 5 */
    ssSetInputPortWidth(S, 5, INPUT_5_WIDTH);
    ssSetInputPortDataType(S, 5, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 5, INPUT_5_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 5, INPUT_5_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 5, 1); /*direct input signal access*/

    /* Input Port 6 */
    ssSetInputPortWidth(S, 6, INPUT_6_WIDTH);
    ssSetInputPortDataType(S, 6, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 6, INPUT_6_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 6, INPUT_6_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 6, 1); /*direct input signal access*/

    /* Input Port 7 */
    ssSetInputPortWidth(S, 7, INPUT_7_WIDTH);
    ssSetInputPortDataType(S, 7, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 7, INPUT_7_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 7, INPUT_7_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 7, 1); /*direct input signal access*/

    /* Input Port 8 */
    ssSetInputPortWidth(S, 8, INPUT_8_WIDTH);
    ssSetInputPortDataType(S, 8, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 8, INPUT_8_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 8, INPUT_8_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 8, 1); /*direct input signal access*/

    /* Input Port 9 */
    ssSetInputPortWidth(S, 9, INPUT_9_WIDTH);
    ssSetInputPortDataType(S, 9, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 9, INPUT_9_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 9, INPUT_9_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 9, 1); /*direct input signal access*/

    /* Input Port 10 */
    ssSetInputPortWidth(S, 10, INPUT_10_WIDTH);
    ssSetInputPortDataType(S, 10, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 10, INPUT_10_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 10, INPUT_10_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 10, 1); /*direct input signal access*/

    /* Input Port 11 */
    ssSetInputPortWidth(S, 11, INPUT_11_WIDTH);
    ssSetInputPortDataType(S, 11, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 11, INPUT_11_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 11, INPUT_11_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 11, 1); /*direct input signal access*/

    /* Input Port 12 */
    ssSetInputPortWidth(S, 12, INPUT_12_WIDTH);
    ssSetInputPortDataType(S, 12, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 12, INPUT_12_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 12, INPUT_12_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 12, 1); /*direct input signal access*/

    /* Input Port 13 */
    ssSetInputPortWidth(S, 13, INPUT_13_WIDTH);
    ssSetInputPortDataType(S, 13, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 13, INPUT_13_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 13, INPUT_13_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 13, 1); /*direct input signal access*/

    /* Input Port 14 */
    ssSetInputPortWidth(S, 14, INPUT_14_WIDTH);
    ssSetInputPortDataType(S, 14, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 14, INPUT_14_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 14, INPUT_14_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 14, 1); /*direct input signal access*/

    /* Input Port 15 */
    ssSetInputPortWidth(S, 15, INPUT_15_WIDTH);
    ssSetInputPortDataType(S, 15, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 15, INPUT_15_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 15, INPUT_15_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 15, 1); /*direct input signal access*/


    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    ssSetNumPWork(S, 1);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetSimulinkVersionGeneratedIn(S, "9.3");

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR |
                     SS_OPTION_WORKS_WITH_CODE_REUSE));
}

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME_0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetInputPortDataType(S, 0, dType);
}

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)

static void mdlSetWorkWidths(SimStruct *S)
{

    const char_T *rtParamNames[] = {"P1","P2","P3","P4"};
    ssRegAllTunableParamsAsRunTimeParams(S, rtParamNames);

}

#endif

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
/* Function: mdlStart =======================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S)
{
    void **pW = ssGetPWork(S);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int8_T *topic = (const int8_T *) mxGetData(PARAM_DEF0(S));
    const int8_T *message_type = (const int8_T *) mxGetData(PARAM_DEF1(S));
    const real_T *port = (const real_T *) mxGetData(PARAM_DEF2(S));
    const real_T *timeout = (const real_T *) mxGetData(PARAM_DEF3(S));
    
    Odometry_publisher_Start_wrapper(pW, topic, p_width0, message_type, p_width1, port, p_width2, timeout, p_width3);
}
#endif /*  MDL_START */

/* Function: mdlOutputs =======================================================
 *
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    void **pW = ssGetPWork(S);
    const real_T *seq = (real_T *) ssGetInputPortRealSignal(S, 0);
    const real_T *frameId_length = (real_T *) ssGetInputPortRealSignal(S, 1);
    const real_T *childFrameId_length = (real_T *) ssGetInputPortRealSignal(S, 2);
    const real_T *positionX = (real_T *) ssGetInputPortRealSignal(S, 3);
    const real_T *positionY = (real_T *) ssGetInputPortRealSignal(S, 4);
    const real_T *positionZ = (real_T *) ssGetInputPortRealSignal(S, 5);
    const real_T *orientW = (real_T *) ssGetInputPortRealSignal(S, 6);
    const real_T *orientX = (real_T *) ssGetInputPortRealSignal(S, 7);
    const real_T *orientY = (real_T *) ssGetInputPortRealSignal(S, 8);
    const real_T *orientZ = (real_T *) ssGetInputPortRealSignal(S, 9);
    const real_T *linearX = (real_T *) ssGetInputPortRealSignal(S, 10);
    const real_T *linearY = (real_T *) ssGetInputPortRealSignal(S, 11);
    const real_T *linearZ = (real_T *) ssGetInputPortRealSignal(S, 12);
    const real_T *angularX = (real_T *) ssGetInputPortRealSignal(S, 13);
    const real_T *angularY = (real_T *) ssGetInputPortRealSignal(S, 14);
    const real_T *angularZ = (real_T *) ssGetInputPortRealSignal(S, 15);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int8_T *topic = (const int8_T *) mxGetData(PARAM_DEF0(S));
    const int8_T *message_type = (const int8_T *) mxGetData(PARAM_DEF1(S));
    const real_T *port = (const real_T *) mxGetData(PARAM_DEF2(S));
    const real_T *timeout = (const real_T *) mxGetData(PARAM_DEF3(S));
    
    Odometry_publisher_Outputs_wrapper(seq, frameId_length, childFrameId_length, positionX, positionY, positionZ, orientW, orientX, orientY, orientZ, linearX, linearY, linearZ, angularX, angularY, angularZ, pW, topic, p_width0, message_type, p_width1, port, p_width2, timeout, p_width3);

}

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    void **pW = ssGetPWork(S);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const int_T   p_width2  = mxGetNumberOfElements(PARAM_DEF2(S));
    const int_T   p_width3  = mxGetNumberOfElements(PARAM_DEF3(S));
    const int8_T *topic = (const int8_T *) mxGetData(PARAM_DEF0(S));
    const int8_T *message_type = (const int8_T *) mxGetData(PARAM_DEF1(S));
    const real_T *port = (const real_T *) mxGetData(PARAM_DEF2(S));
    const real_T *timeout = (const real_T *) mxGetData(PARAM_DEF3(S));
    
    Odometry_publisher_Terminate_wrapper(pW, topic, p_width0, message_type, p_width1, port, p_width2, timeout, p_width3);

}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif



