/*
 *  rtmodel.h:
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
/*
 * rtmodel.h
 *
 * Code generation for Simulink model "ros_node".
 *
 * Simulink Coder version                : 9.1 (R2019a) 23-Nov-2018
 * C++ source code generated on : Sat Dec 12 09:39:45 2020
 *
 * Note that the generated code is not dependent on this header file.
 * The file is used in cojuction with the automatic build procedure.
 * It is included by the sample main executable harness
 * MATLAB/rtw/c/src/common/rt_main.c.
 *
 */
#ifndef RTW_HEADER_rtmodel_h_
#define RTW_HEADER_rtmodel_h_

/*
 *  Includes the appropriate headers when we are using rtModel
 */
#include "ros_node.h"
#define GRTINTERFACE                   0

/*
 * ROOT_IO_FORMAT: 0 (Individual arguments)
 * ROOT_IO_FORMAT: 1 (Structure reference)
 * ROOT_IO_FORMAT: 2 (Part of model data structure)
 */
# define ROOT_IO_FORMAT                2

/* Macros generated for backwards compatibility  */
#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

#include "ros_node.h"

/*
 * ROOT_IO_FORMAT: 0 (Individual arguments)
 * ROOT_IO_FORMAT: 1 (Structure reference)
 * ROOT_IO_FORMAT: 2 (Part of model data structure)
 */
# define ROOT_IO_FORMAT                2

/* Macros generated for backwards compatibility  */
#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

#define MODEL_CLASSNAME                ros_nodeModelClass
#define MODEL_STEPNAME                 step
#endif                                 /* RTW_HEADER_rtmodel_h_ */
