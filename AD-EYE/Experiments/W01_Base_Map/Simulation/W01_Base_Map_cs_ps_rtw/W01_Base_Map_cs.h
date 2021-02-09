/*
 * W01_Base_Map_cs.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "W01_Base_Map_cs".
 *
 * Model version              : 1.290
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Thu Jan 21 23:46:14 2021
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_W01_Base_Map_cs_h_
#define RTW_HEADER_W01_Base_Map_cs_h_
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap.h"
#ifndef W01_Base_Map_cs_COMMON_INCLUDES_
# define W01_Base_Map_cs_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "prescan_controller_data.h"
#include "prescan_SFunLibrary.h"
#include "prescan_CreateLogHandler.h"
#include "prescan_CreateErrorHandler.h"
#include "prescan_modify.h"
#include "ModuleDLL.h"
#include "prescan_visulightactuator_data.h"
#include "prescan_xyz_data.h"
#include "prescan_rpy_data.h"
#include "prescan_rgb_data.h"
#include "prescan_speedprofile_data.h"
#include "prescan_motion_data.h"
#include "prescan_path_data.h"
#include "prescan_stateactuator_data.h"
#include "prescan_animactuator_data.h"
#include "prescan_coloractuator_data.h"
#include "prescan_color_data.h"
#include "prescan_selfsensor_data.h"
#include "prescan_scenarioengine_data.h"
#include "prescan_synchronizer_data.h"
#include "prescan_airsensor_data.h"
#include "prescan_header_data.h"
#include "prescan_radar_data.h"
#include "prescan_scannersensor_data.h"
#include "prescan_pcs_data.h"
#include "prescan_camera_data.h"
#include "prescan_terminator_data.h"
#include "stdlib.h"
#endif                                 /* W01_Base_Map_cs_COMMON_INCLUDES_ */

#include "W01_Base_Map_cs_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_assert.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetCtrlRateMdlRefTiming
# define rtmGetCtrlRateMdlRefTiming(rtm) ()
#endif

#ifndef rtmSetCtrlRateMdlRefTiming
# define rtmSetCtrlRateMdlRefTiming(rtm, val) ()
#endif

#ifndef rtmGetCtrlRateMdlRefTimingPtr
# define rtmGetCtrlRateMdlRefTimingPtr(rtm) ()
#endif

#ifndef rtmSetCtrlRateMdlRefTimingPtr
# define rtmSetCtrlRateMdlRefTimingPtr(rtm, val) ()
#endif

#ifndef rtmGetCtrlRateNumTicksToNextHit
# define rtmGetCtrlRateNumTicksToNextHit(rtm) ()
#endif

#ifndef rtmSetCtrlRateNumTicksToNextHit
# define rtmSetCtrlRateNumTicksToNextHit(rtm, val) ()
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ()
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ()
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ()
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumPeriodicContStates
# define rtmGetNumPeriodicContStates(rtm) ((rtm)->Sizes.numPeriodicContStates)
#endif

#ifndef rtmSetNumPeriodicContStates
# define rtmSetNumPeriodicContStates(rtm, val) ((rtm)->Sizes.numPeriodicContStates = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ()
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ()
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ()
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ()
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ()
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSelf
# define rtmGetSelf(rtm)               ()
#endif

#ifndef rtmSetSelf
# define rtmSetSelf(rtm, val)          ()
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ()
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ()
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGettimingBridge
# define rtmGettimingBridge(rtm)       ()
#endif

#ifndef rtmSettimingBridge
# define rtmSettimingBridge(rtm, val)  ()
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) ((tid) == 0)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtmIsMajorTimeStep((rtm)) && (rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]]))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define W01_Base_Map_cs_rtModel        RT_MODEL_W01_Base_Map_cs_T

/* Block signals for system '<S107>/Coordinate Transformation Conversion' */
typedef struct {
  real_T CoordinateTransformationConve_f[4];
                             /* '<S107>/Coordinate Transformation Conversion' */
} B_CoordinateTransformationCon_T;

/* Block states (default storage) for system '<S107>/Coordinate Transformation Conversion' */
typedef struct {
  robotics_slcore_internal_bloc_T obj;
                             /* '<S107>/Coordinate Transformation Conversion' */
  boolean_T objisempty;      /* '<S107>/Coordinate Transformation Conversion' */
} DW_CoordinateTransformationCo_T;

/* Block signals for system '<S113>/Rain Model' */
typedef struct {
  real_T Product3_n[3600];             /* '<S208>/Product3' */
  real_T Product4_f[3600];             /* '<S208>/Product4' */
  real_T Product7_h[3600];             /* '<S208>/Product7' */
} B_RainModel_W01_Base_Map_cs_T;

/* Block states (default storage) for system '<S113>/Rain Model' */
typedef struct {
  uint32_T RandomSource1_SEED_DWORK;   /* '<S208>/Random Source1' */
  uint32_T RandomSource1_STATE_DWORK[2];/* '<S208>/Random Source1' */
} DW_RainModel_W01_Base_Map_cs_T;

/* Block states (default storage) for system '<S113>/If Action Subsystem1' */
typedef struct {
  uint32_T RandomSource1_SEED_DWORK;   /* '<S207>/Random Source1' */
  uint32_T RandomSource1_STATE_DWORK[2];/* '<S207>/Random Source1' */
  uint32_T RandomSource2_SEED_DWORK;   /* '<S207>/Random Source2' */
  uint32_T RandomSource2_STATE_DWORK[2];/* '<S207>/Random Source2' */
} DW_IfActionSubsystem1_W01_B_o_T;

/* Block signals (default storage) */
typedef struct {
  uint8_T Sensor_m[6062040];           /* '<S18>/Sensor' */
  uint8_T Sensor_g[2073600];           /* '<S10>/Sensor' */
  uint8_T MatrixConcatenate[2073600];  /* '<S145>/Matrix Concatenate' */
  real32_T MatrixConcatenate5_c[14400];/* '<S129>/Matrix Concatenate5' */
  real32_T MatrixConcatenate5_l[14400];/* '<S130>/Matrix Concatenate5' */
  real32_T MatrixConcatenate5_k[14400];/* '<S131>/Matrix Concatenate5' */
  real32_T Selector_h[3600];           /* '<S134>/Selector' */
  real32_T Selector3[3600];            /* '<S133>/Selector3' */
  real32_T Selector_m[3600];           /* '<S132>/Selector' */
  real32_T Selector1_m[3600];          /* '<S132>/Selector1' */
  real32_T Merge7_i[3600];             /* '<S116>/Merge7' */
  real32_T Product3_f[3600];           /* '<S239>/Product3' */
  real32_T Product1_b[3600];           /* '<S239>/Product1' */
  real32_T Merge_k[3600];              /* '<S116>/Merge' */
  real32_T Selector_hz[3600];          /* '<S137>/Selector' */
  real32_T Selector3_k[3600];          /* '<S136>/Selector3' */
  real32_T Selector_k[3600];           /* '<S135>/Selector' */
  real32_T Selector1_f[3600];          /* '<S135>/Selector1' */
  real32_T Merge5_e[3600];             /* '<S116>/Merge5' */
  real32_T Merge6_h[3600];             /* '<S116>/Merge6' */
  real32_T Selector_i[3600];           /* '<S140>/Selector' */
  real32_T Selector3_f[3600];          /* '<S139>/Selector3' */
  real32_T Selector_f[3600];           /* '<S138>/Selector' */
  real32_T Selector1_k[3600];          /* '<S138>/Selector1' */
  real32_T Selector_b_c[3600];         /* '<S143>/Selector' */
  real32_T Selector3_i[3600];          /* '<S142>/Selector3' */
  real32_T Selector_g[3600];           /* '<S141>/Selector' */
  real32_T Selector1_c_k[3600];        /* '<S141>/Selector1' */
  real_T TSamp;                        /* '<S356>/TSamp' */
  real_T TSamp_h;                      /* '<S357>/TSamp' */
  real_T TSamp_p;                      /* '<S358>/TSamp' */
  real_T TSamp_g;                      /* '<S359>/TSamp' */
  real_T TSamp_i;                      /* '<S360>/TSamp' */
  real_T TSamp_k;                      /* '<S361>/TSamp' */
  real_T Velocity;
  real_T SFunctionBuilder_o1;          /* '<S194>/S-Function Builder' */
  real_T SFunctionBuilder_o2;          /* '<S194>/S-Function Builder' */
  real_T SFunctionBuilder_o3;          /* '<S194>/S-Function Builder' */
  real_T SFunctionBuilder_o4;          /* '<S194>/S-Function Builder' */
  real_T SFunctionBuilder_o5;          /* '<S194>/S-Function Builder' */
  real_T SFunctionBuilder_o6;          /* '<S194>/S-Function Builder' */
  real_T Clock;                        /* '<S193>/Clock' */
  real_T Memory;                       /* '<S193>/Memory' */
  real_T Merge;                        /* '<S193>/Merge' */
  real_T TmpSignalConversionAtDotProduct[3];
  real_T TSamp_j;                      /* '<S178>/TSamp' */
  real_T TSamp_gj;                     /* '<S179>/TSamp' */
  real_T TSamp_o;                      /* '<S180>/TSamp' */
  real_T TSamp_f;                      /* '<S181>/TSamp' */
  real_T TSamp_os;                     /* '<S182>/TSamp' */
  real_T TSamp_om;                     /* '<S183>/TSamp' */
  real_T Clock_f;                      /* '<S45>/Clock' */
  real_T Fcn;                          /* '<S300>/Fcn' */
  real_T Fcn_c;                        /* '<S311>/Fcn' */
  real_T Fcn_l;                        /* '<S330>/Fcn' */
  real_T Fcn_f;                        /* '<S379>/Fcn' */
  real_T Fcn_g;                        /* '<S390>/Fcn' */
  real_T SFunctionBuilder;             /* '<S220>/S-Function Builder' */
  real_T Add3;                         /* '<S106>/Add3' */
  real_T Add2;                         /* '<S106>/Add2' */
  real_T Add1;                         /* '<S106>/Add1' */
  real_T Merge_f[7];                   /* '<S112>/Merge' */
  real_T SFunctionBuilder_p;           /* '<S225>/S-Function Builder' */
  real_T SFunctionBuilder_d;           /* '<S221>/S-Function Builder' */
  real_T SFunctionBuilder_m;           /* '<S222>/S-Function Builder' */
  real_T SFunctionBuilder_k;           /* '<S223>/S-Function Builder' */
  real_T SFunctionBuilder_dw;          /* '<S224>/S-Function Builder' */
  real_T SFunctionBuilder_n;           /* '<S218>/S-Function Builder' */
  real_T SFunctionBuilder_i;           /* '<S226>/S-Function Builder' */
  real_T SFunctionBuilder_h;           /* '<S219>/S-Function Builder' */
  real_T VectorConcatenate[21];        /* '<Root>/Vector Concatenate' */
  real_T TargetTypeID[7];              /* '<S265>/Data Type Conversion1' */
  real_T Assignment[7];                /* '<S268>/Assignment' */
  real_T Assignment_b[7];              /* '<S282>/Assignment' */
  real_T Assignment_g[7];              /* '<S283>/Assignment' */
  real_T Add5;                         /* '<S155>/Add5' */
  real_T Gain1;                        /* '<S260>/Gain1' */
  real_T TmpSignalConversionAtSFunctionB[11];
  real_T Add5_f;                       /* '<S152>/Add5' */
  real_T Gain1_n;                      /* '<S254>/Gain1' */
  real_T Gain1_h;                      /* '<S251>/Gain1' */
  real_T Product;                      /* '<S150>/Product' */
  real_T Add5_m;                       /* '<S150>/Add5' */
  real_T Add4;                         /* '<S149>/Add4' */
  real_T Floor;                        /* '<S147>/Floor' */
  real_T Product_p;                    /* '<S147>/Product' */
  uint32_T Add5_a;                     /* '<S94>/Add5' */
  real32_T DataTypeConversion2[21];    /* '<S159>/Data Type Conversion2' */
  real32_T MathFunction1[57600];       /* '<S151>/Math Function1' */
  uint8_T Selector[691200];            /* '<S103>/Selector' */
  uint8_T Selector1[691200];           /* '<S103>/Selector1' */
  uint8_T Selector2[691200];           /* '<S103>/Selector2' */
  uint8_T Selector_b[691200];          /* '<S105>/Selector' */
  uint8_T Selector1_p[691200];         /* '<S105>/Selector1' */
  uint8_T Selector2_f[691200];         /* '<S105>/Selector2' */
  uint8_T Selector_c[2020680];         /* '<S127>/Selector' */
  uint8_T Selector1_c[2020680];        /* '<S127>/Selector1' */
  uint8_T Selector2_h[2020680];        /* '<S127>/Selector2' */
  uint8_T Selector_o[691200];          /* '<S104>/Selector' */
  uint8_T Selector1_d[691200];         /* '<S104>/Selector1' */
  uint8_T Selector2_j[691200];         /* '<S104>/Selector2' */
  uint8_T MathFunction3[2073600];      /* '<S146>/Math Function3' */
  uint8_T MathFunction3_i[2073600];    /* '<S145>/Math Function3' */
  uint8_T MathFunction3_h[2073600];    /* '<S144>/Math Function3' */
  uint8_T Merge_m[691200];             /* '<S111>/Merge' */
  uint8_T Merge1_b[691200];            /* '<S111>/Merge1' */
  uint8_T Merge2_b[691200];            /* '<S111>/Merge2' */
  uint8_T Merge_n[691200];             /* '<S110>/Merge' */
  uint8_T Merge1_c[691200];            /* '<S110>/Merge1' */
  uint8_T Merge2_l[691200];            /* '<S110>/Merge2' */
  uint8_T Merge_ng[691200];            /* '<S109>/Merge' */
  uint8_T Merge1_p[691200];            /* '<S109>/Merge1' */
  uint8_T Merge2_p[691200];            /* '<S109>/Merge2' */
  uint8_T MathFunction[691200];        /* '<S145>/Math Function' */
  real32_T Sensor_n0[14400];           /* '<S24>/Sensor' */
  real32_T MatrixConcatenate5_b[14400];/* '<S128>/Matrix Concatenate5' */
  B_CoordinateTransformationCon_T CoordinateTransformationConve_f;
                             /* '<S107>/Coordinate Transformation Conversion' */
  B_RainModel_W01_Base_Map_cs_T RainModel_o;/* '<S116>/Rain Model' */
  B_RainModel_W01_Base_Map_cs_T RainModel_p;/* '<S115>/Rain Model' */
  B_RainModel_W01_Base_Map_cs_T RainModel_h;/* '<S114>/Rain Model' */
  B_RainModel_W01_Base_Map_cs_T RainModel;/* '<S113>/Rain Model' */
  B_CoordinateTransformationCon_T CoordinateTransformationConve_i;
                             /* '<S107>/Coordinate Transformation Conversion' */
} B_W01_Base_Map_cs_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UD_DSTATE;                    /* '<S356>/UD' */
  real_T UD_DSTATE_h;                  /* '<S357>/UD' */
  real_T UD_DSTATE_j;                  /* '<S358>/UD' */
  real_T UD_DSTATE_jb;                 /* '<S359>/UD' */
  real_T UD_DSTATE_m;                  /* '<S360>/UD' */
  real_T UD_DSTATE_c;                  /* '<S361>/UD' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S300>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_o;/* '<S311>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_j;/* '<S330>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_p;/* '<S379>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_k;/* '<S390>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTAT_j2[3];/* '<S171>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator4_DSTATE;/* '<S173>/Discrete-Time Integrator4' */
  real_T UD_DSTATE_g;                  /* '<S178>/UD' */
  real_T UD_DSTATE_d;                  /* '<S179>/UD' */
  real_T UD_DSTATE_k;                  /* '<S180>/UD' */
  real_T DiscreteTimeIntegrator6_DSTATE;/* '<S173>/Discrete-Time Integrator6' */
  real_T DiscreteTimeIntegrator5_DSTATE;/* '<S173>/Discrete-Time Integrator5' */
  real_T UD_DSTATE_i;                  /* '<S181>/UD' */
  real_T UD_DSTATE_ms;                 /* '<S182>/UD' */
  real_T UD_DSTATE_o;                  /* '<S183>/UD' */
  real_T Memory_PreviousInput;         /* '<S193>/Memory' */
  real_T fighandle;                    /* '<S8>/Camera_1_CM_Display' */
  real_T counter;                      /* '<S8>/Camera_1_CM_Display' */
  real_T fighandle_j;                  /* '<S8>/Camera_tl_CM_Display' */
  real_T counter_g;                    /* '<S8>/Camera_tl_CM_Display' */
  real_T fighandle_m;                  /* '<S8>/HumViewCamera_CM_Display' */
  real_T counter_o;                    /* '<S8>/HumViewCamera_CM_Display' */
  real_T fighandle_o;                  /* '<S8>/Camera_2_CM_Display' */
  real_T counter_d;                    /* '<S8>/Camera_2_CM_Display' */
  real_T Memory2_PreviousInput;        /* '<S155>/Memory2' */
  real_T Memory2_PreviousInput_o;      /* '<S152>/Memory2' */
  real_T TimeStampA;                   /* '<S150>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S150>/Derivative' */
  real_T TimeStampB;                   /* '<S150>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S150>/Derivative' */
  real_T Memory2_PreviousInput_c;      /* '<S150>/Memory2' */
  real_T Memory1_PreviousInput;        /* '<S149>/Memory1' */
  real_T NextOutput[7];                /* '<S228>/Random Number' */
  real_T NextOutput_e[7];              /* '<S228>/Random Number1' */
  real_T NextOutput_f[7];              /* '<S228>/Random Number2' */
  void *sfun_Controller_PWORK[2];      /* '<S15>/sfun_Controller' */
  void *Actuator_PWORK[2];             /* '<S48>/Actuator' */
  void *Actuator_PWORK_o[2];           /* '<S49>/Actuator' */
  void *Actuator_PWORK_l[2];           /* '<S50>/Actuator' */
  void *Actuator_PWORK_d[2];           /* '<S52>/Actuator' */
  void *Actuator_PWORK_g[2];           /* '<S53>/Actuator' */
  void *Actuator_PWORK_e[2];           /* '<S54>/Actuator' */
  void *Actuator_PWORK_j[2];           /* '<S56>/Actuator' */
  void *Actuator_PWORK_oz[2];          /* '<S57>/Actuator' */
  void *Actuator_PWORK_f[2];           /* '<S58>/Actuator' */
  void *Actuator_PWORK_k[2];           /* '<S60>/Actuator' */
  void *Actuator_PWORK_m[2];           /* '<S61>/Actuator' */
  void *Actuator_PWORK_c[2];           /* '<S62>/Actuator' */
  void *Actuator_PWORK_lo[2];          /* '<S64>/Actuator' */
  void *Actuator_PWORK_e5[2];          /* '<S65>/Actuator' */
  void *Actuator_PWORK_h[2];           /* '<S66>/Actuator' */
  void *Actuator_PWORK_lz[2];          /* '<S68>/Actuator' */
  void *Actuator_PWORK_f4[2];          /* '<S69>/Actuator' */
  void *Actuator_PWORK_n[2];           /* '<S70>/Actuator' */
  void *Actuator_PWORK_mu[2];          /* '<S72>/Actuator' */
  void *Actuator_PWORK_gu[2];          /* '<S73>/Actuator' */
  void *Actuator_PWORK_fv[2];          /* '<S74>/Actuator' */
  void *Actuator_PWORK_ot[2];          /* '<S76>/Actuator' */
  void *Actuator_PWORK_lf[2];          /* '<S77>/Actuator' */
  void *Actuator_PWORK_lh[2];          /* '<S78>/Actuator' */
  void *SpeedProfile_PWORK[2];         /* '<S7>/SpeedProfile' */
  void *Path_PWORK[3];                 /* '<S7>/Path' */
  void *Actuator_PWORK_jo[2];          /* '<S36>/Actuator' */
  void *SpeedProfile_PWORK_d[2];       /* '<S14>/SpeedProfile' */
  void *Path_PWORK_c[3];               /* '<S14>/Path' */
  void *Actuator_PWORK_dz[2];          /* '<S40>/Actuator' */
  void *Actuator_PWORK_gn[2];          /* '<S42>/Actuator' */
  void *SpeedProfile_PWORK_e[2];       /* '<S12>/SpeedProfile' */
  void *Path_PWORK_e[3];               /* '<S12>/Path' */
  void *Actuator_PWORK_fc[2];          /* '<S2>/Actuator' */
  void *Actuator_PWORK_dl[2];          /* '<S38>/Actuator' */
  void *Actuator_PWORK_l4[2];          /* '<S79>/Actuator' */
  void *Actuator_PWORK_a[2];           /* '<S84>/Actuator' */
  void *Actuator_PWORK_ev[2];          /* '<S89>/Actuator' */
  void *SpeedProfile_PWORK_h[2];       /* '<S13>/SpeedProfile' */
  void *Path_PWORK_h[3];               /* '<S13>/Path' */
  void *Actuator_PWORK_i[2];           /* '<S3>/Actuator' */
  void *Actuator_PWORK_dc[2];          /* '<S39>/Actuator' */
  void *Actuator_PWORK_lzg[2];         /* '<S80>/Actuator' */
  void *Actuator_PWORK_fq[2];          /* '<S85>/Actuator' */
  void *Actuator_PWORK_eq[2];          /* '<S90>/Actuator' */
  void *SpeedProfile_PWORK_b[2];       /* '<S16>/SpeedProfile' */
  void *Path_PWORK_i[3];               /* '<S16>/Path' */
  void *Actuator_PWORK_if[2];          /* '<S4>/Actuator' */
  void *Actuator_PWORK_ho[2];          /* '<S41>/Actuator' */
  void *Actuator_PWORK_hh[2];          /* '<S81>/Actuator' */
  void *Actuator_PWORK_iw[2];          /* '<S86>/Actuator' */
  void *Actuator_PWORK_ha[2];          /* '<S91>/Actuator' */
  void *SpeedProfile_PWORK_n[2];       /* '<S19>/SpeedProfile' */
  void *Path_PWORK_m[3];               /* '<S19>/Path' */
  void *Actuator_PWORK_m1[2];          /* '<S5>/Actuator' */
  void *Actuator_PWORK_p[2];           /* '<S43>/Actuator' */
  void *Actuator_PWORK_jr[2];          /* '<S82>/Actuator' */
  void *Actuator_PWORK_jw[2];          /* '<S87>/Actuator' */
  void *Actuator_PWORK_gnk[2];         /* '<S92>/Actuator' */
  void *SpeedProfile_PWORK_i[2];       /* '<S20>/SpeedProfile' */
  void *Path_PWORK_a[3];               /* '<S20>/Path' */
  void *Actuator_PWORK_jn[2];          /* '<S6>/Actuator' */
  void *Actuator_PWORK_cf[2];          /* '<S44>/Actuator' */
  void *Actuator_PWORK_n2[2];          /* '<S83>/Actuator' */
  void *Actuator_PWORK_g1[2];          /* '<S88>/Actuator' */
  void *Actuator_PWORK_f5[2];          /* '<S93>/Actuator' */
  void *Sensor_PWORK[2];               /* '<S28>/Sensor' */
  void *SFunctionBuilder_PWORK;        /* '<S194>/S-Function Builder' */
  void *Actuator_PWORK_k2[2];          /* '<S37>/Actuator' */
  void *sfun_ScenarioEngine_PWORK;     /* '<S45>/sfun_ScenarioEngine' */
  void *sfun_Synchronizer_PWORK[2];    /* '<S46>/sfun_Synchronizer' */
  void *Sensor_PWORK_f[2];             /* '<S33>/Sensor' */
  void *Sensor_PWORK_a[2];             /* '<S27>/Sensor' */
  void *Sensor_PWORK_j[2];             /* '<S31>/Sensor' */
  void *Sensor_PWORK_m[2];             /* '<S1>/Sensor' */
  void* Assertion_slioAccessor;        /* '<S366>/Assertion' */
  void* Assertion_slioAccessor_p;      /* '<S367>/Assertion' */
  void *Sensor_PWORK_h[2];             /* '<S29>/Sensor' */
  void *Sensor_PWORK_n[2];             /* '<S30>/Sensor' */
  void *Sensor_PWORK_p[2];             /* '<S32>/Sensor' */
  void *Sensor_PWORK_p0[2];            /* '<S34>/Sensor' */
  void *Sensor_PWORK_k[2];             /* '<S35>/Sensor' */
  void *SFunctionBuilder_PWORK_l;      /* '<S220>/S-Function Builder' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S8>/Scope' */

  void* Assertion_slioAccessor_i;      /* '<S188>/Assertion' */
  void* Assertion_slioAccessor_f;      /* '<S189>/Assertion' */
  void *SFunctionBuilder_PWORK_a;      /* '<S225>/S-Function Builder' */
  void *Sensor_PWORK_b[2];             /* '<S26>/Sensor' */
  void *SFunctionBuilder_PWORK_k;      /* '<S221>/S-Function Builder' */
  void *Sensor_PWORK_l;                /* '<S21>/Sensor' */
  void *SFunctionBuilder_PWORK_p;      /* '<S222>/S-Function Builder' */
  void *Sensor_PWORK_c;                /* '<S22>/Sensor' */
  void *SFunctionBuilder_PWORK_j;      /* '<S223>/S-Function Builder' */
  void *Sensor_PWORK_g;                /* '<S23>/Sensor' */
  void *SFunctionBuilder_PWORK_b;      /* '<S224>/S-Function Builder' */
  void *Sensor_PWORK_bp;               /* '<S24>/Sensor' */
  void *Sensor_PWORK_i;                /* '<S9>/Sensor' */
  void *SFunctionBuilder_PWORK_ka;     /* '<S218>/S-Function Builder' */
  void *Sensor_PWORK_cg;               /* '<S11>/Sensor' */
  void *SFunctionBuilder_PWORK_c;      /* '<S226>/S-Function Builder' */
  void *Sensor_PWORK_o;                /* '<S18>/Sensor' */
  void *Sensor_PWORK_a2;               /* '<S10>/Sensor' */
  void *SFunctionBuilder_PWORK_av;     /* '<S219>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_m;      /* '<S262>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_jv;     /* '<S263>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_f;      /* '<S264>/S-Function Builder' */
  void *sfun_Terminator_PWORK[2];      /* '<S25>/sfun_Terminator' */
  void *SFunctionBuilder_PWORK_pp;     /* '<S443>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_j0;     /* '<S292>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_h;      /* '<S261>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_o;      /* '<S259>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_al;     /* '<S258>/S-Function Builder' */
  void *SFunctionBuilder1_PWORK;       /* '<S255>/S-Function Builder1' */
  void *SFunctionBuilder_PWORK_kd;     /* '<S253>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_bo;     /* '<S252>/S-Function Builder' */
  void *SFunctionBuilder1_PWORK_d;     /* '<S247>/S-Function Builder1' */
  void *SFunctionBuilder1_PWORK_p;     /* '<S246>/S-Function Builder1' */
  void *SFunctionBuilder_PWORK_hu;     /* '<S245>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_g;      /* '<S243>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_b0;     /* '<S242>/S-Function Builder' */
  void *SFunctionBuilder_PWORK_a4;     /* '<S241>/S-Function Builder' */
  int32_T sfun_Controller_dtSizeInfo[2];/* '<S15>/sfun_Controller' */
  int32_T sfun_Controller_dtBusInfo[2];/* '<S15>/sfun_Controller' */
  int32_T Actuator_dtSizeInfo[6];      /* '<S48>/Actuator' */
  int32_T Actuator_dtBusInfo[22];      /* '<S48>/Actuator' */
  int32_T Actuator_dtSizeInfo_c[6];    /* '<S49>/Actuator' */
  int32_T Actuator_dtBusInfo_p[22];    /* '<S49>/Actuator' */
  int32_T Actuator_dtSizeInfo_i[6];    /* '<S50>/Actuator' */
  int32_T Actuator_dtBusInfo_o[22];    /* '<S50>/Actuator' */
  int32_T Actuator_dtSizeInfo_j[6];    /* '<S52>/Actuator' */
  int32_T Actuator_dtBusInfo_h[22];    /* '<S52>/Actuator' */
  int32_T Actuator_dtSizeInfo_l[6];    /* '<S53>/Actuator' */
  int32_T Actuator_dtBusInfo_a[22];    /* '<S53>/Actuator' */
  int32_T Actuator_dtSizeInfo_n[6];    /* '<S54>/Actuator' */
  int32_T Actuator_dtBusInfo_e[22];    /* '<S54>/Actuator' */
  int32_T Actuator_dtSizeInfo_k[6];    /* '<S56>/Actuator' */
  int32_T Actuator_dtBusInfo_m[22];    /* '<S56>/Actuator' */
  int32_T Actuator_dtSizeInfo_a[6];    /* '<S57>/Actuator' */
  int32_T Actuator_dtBusInfo_f[22];    /* '<S57>/Actuator' */
  int32_T Actuator_dtSizeInfo_e[6];    /* '<S58>/Actuator' */
  int32_T Actuator_dtBusInfo_i[22];    /* '<S58>/Actuator' */
  int32_T Actuator_dtSizeInfo_i5[6];   /* '<S60>/Actuator' */
  int32_T Actuator_dtBusInfo_j[22];    /* '<S60>/Actuator' */
  int32_T Actuator_dtSizeInfo_m[6];    /* '<S61>/Actuator' */
  int32_T Actuator_dtBusInfo_i5[22];   /* '<S61>/Actuator' */
  int32_T Actuator_dtSizeInfo_jj[6];   /* '<S62>/Actuator' */
  int32_T Actuator_dtBusInfo_d[22];    /* '<S62>/Actuator' */
  int32_T Actuator_dtSizeInfo_ik[6];   /* '<S64>/Actuator' */
  int32_T Actuator_dtBusInfo_es[22];   /* '<S64>/Actuator' */
  int32_T Actuator_dtSizeInfo_p[6];    /* '<S65>/Actuator' */
  int32_T Actuator_dtBusInfo_ol[22];   /* '<S65>/Actuator' */
  int32_T Actuator_dtSizeInfo_d[6];    /* '<S66>/Actuator' */
  int32_T Actuator_dtBusInfo_k[22];    /* '<S66>/Actuator' */
  int32_T Actuator_dtSizeInfo_kc[6];   /* '<S68>/Actuator' */
  int32_T Actuator_dtBusInfo_e5[22];   /* '<S68>/Actuator' */
  int32_T Actuator_dtSizeInfo_n2[6];   /* '<S69>/Actuator' */
  int32_T Actuator_dtBusInfo_m2[22];   /* '<S69>/Actuator' */
  int32_T Actuator_dtSizeInfo_jf[6];   /* '<S70>/Actuator' */
  int32_T Actuator_dtBusInfo_b[22];    /* '<S70>/Actuator' */
  int32_T Actuator_dtSizeInfo_jr[6];   /* '<S72>/Actuator' */
  int32_T Actuator_dtBusInfo_l[22];    /* '<S72>/Actuator' */
  int32_T Actuator_dtSizeInfo_ju[6];   /* '<S73>/Actuator' */
  int32_T Actuator_dtBusInfo_c[22];    /* '<S73>/Actuator' */
  int32_T Actuator_dtSizeInfo_g[6];    /* '<S74>/Actuator' */
  int32_T Actuator_dtBusInfo_n[22];    /* '<S74>/Actuator' */
  int32_T Actuator_dtSizeInfo_kw[6];   /* '<S76>/Actuator' */
  int32_T Actuator_dtBusInfo_kh[22];   /* '<S76>/Actuator' */
  int32_T Actuator_dtSizeInfo_pc[6];   /* '<S77>/Actuator' */
  int32_T Actuator_dtBusInfo_g[22];    /* '<S77>/Actuator' */
  int32_T Actuator_dtSizeInfo_li[6];   /* '<S78>/Actuator' */
  int32_T Actuator_dtBusInfo_kn[22];   /* '<S78>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo[2];  /* '<S7>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo[6];   /* '<S7>/SpeedProfile' */
  int32_T Path_dtSizeInfo[3];          /* '<S7>/Path' */
  int32_T Path_dtBusInfo[36];          /* '<S7>/Path' */
  int32_T Actuator_dtSizeInfo_m4[2];   /* '<S36>/Actuator' */
  int32_T Actuator_dtBusInfo_n2[30];   /* '<S36>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_b[2];/* '<S14>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_j[6]; /* '<S14>/SpeedProfile' */
  int32_T Path_dtSizeInfo_e[3];        /* '<S14>/Path' */
  int32_T Path_dtBusInfo_a[36];        /* '<S14>/Path' */
  int32_T Actuator_dtSizeInfo_g2[2];   /* '<S40>/Actuator' */
  int32_T Actuator_dtBusInfo_eh[30];   /* '<S40>/Actuator' */
  int32_T Actuator_dtSizeInfo_po[2];   /* '<S42>/Actuator' */
  int32_T Actuator_dtBusInfo_in[30];   /* '<S42>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_l[2];/* '<S12>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_l[6]; /* '<S12>/SpeedProfile' */
  int32_T Path_dtSizeInfo_p[3];        /* '<S12>/Path' */
  int32_T Path_dtBusInfo_c[36];        /* '<S12>/Path' */
  int32_T Actuator_dtSizeInfo_dg[3];   /* '<S2>/Actuator' */
  int32_T Actuator_dtBusInfo_cp[4];    /* '<S2>/Actuator' */
  int32_T Actuator_dtSizeInfo_kf[2];   /* '<S38>/Actuator' */
  int32_T Actuator_dtBusInfo_h1[30];   /* '<S38>/Actuator' */
  int32_T Actuator_dtSizeInfo_me[2];   /* '<S79>/Actuator' */
  int32_T Actuator_dtBusInfo_nq[8];    /* '<S79>/Actuator' */
  int32_T Actuator_dtSizeInfo_h[2];    /* '<S84>/Actuator' */
  int32_T Actuator_dtBusInfo_gw[8];    /* '<S84>/Actuator' */
  int32_T Actuator_dtSizeInfo_mb[2];   /* '<S89>/Actuator' */
  int32_T Actuator_dtBusInfo_ls[8];    /* '<S89>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_m[2];/* '<S13>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_g[6]; /* '<S13>/SpeedProfile' */
  int32_T Path_dtSizeInfo_i[3];        /* '<S13>/Path' */
  int32_T Path_dtBusInfo_ct[36];       /* '<S13>/Path' */
  int32_T Actuator_dtSizeInfo_f[3];    /* '<S3>/Actuator' */
  int32_T Actuator_dtBusInfo_ie[4];    /* '<S3>/Actuator' */
  int32_T Actuator_dtSizeInfo_ir[2];   /* '<S39>/Actuator' */
  int32_T Actuator_dtBusInfo_mh[30];   /* '<S39>/Actuator' */
  int32_T Actuator_dtSizeInfo_my[2];   /* '<S80>/Actuator' */
  int32_T Actuator_dtBusInfo_dp[8];    /* '<S80>/Actuator' */
  int32_T Actuator_dtSizeInfo_eh[2];   /* '<S85>/Actuator' */
  int32_T Actuator_dtBusInfo_kr[8];    /* '<S85>/Actuator' */
  int32_T Actuator_dtSizeInfo_f4[2];   /* '<S90>/Actuator' */
  int32_T Actuator_dtBusInfo_fr[8];    /* '<S90>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_e[2];/* '<S16>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_e[6]; /* '<S16>/SpeedProfile' */
  int32_T Path_dtSizeInfo_h[3];        /* '<S16>/Path' */
  int32_T Path_dtBusInfo_p[36];        /* '<S16>/Path' */
  int32_T Actuator_dtSizeInfo_pm[3];   /* '<S4>/Actuator' */
  int32_T Actuator_dtBusInfo_fo[4];    /* '<S4>/Actuator' */
  int32_T Actuator_dtSizeInfo_o[2];    /* '<S41>/Actuator' */
  int32_T Actuator_dtBusInfo_e3[30];   /* '<S41>/Actuator' */
  int32_T Actuator_dtSizeInfo_ca[2];   /* '<S81>/Actuator' */
  int32_T Actuator_dtBusInfo_i1[8];    /* '<S81>/Actuator' */
  int32_T Actuator_dtSizeInfo_jm[2];   /* '<S86>/Actuator' */
  int32_T Actuator_dtBusInfo_bf[8];    /* '<S86>/Actuator' */
  int32_T Actuator_dtSizeInfo_f4f[2];  /* '<S91>/Actuator' */
  int32_T Actuator_dtBusInfo_ns[8];    /* '<S91>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_bw[2];/* '<S19>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_f[6]; /* '<S19>/SpeedProfile' */
  int32_T Path_dtSizeInfo_d[3];        /* '<S19>/Path' */
  int32_T Path_dtBusInfo_a5[36];       /* '<S19>/Path' */
  int32_T Actuator_dtSizeInfo_jw[3];   /* '<S5>/Actuator' */
  int32_T Actuator_dtBusInfo_go[4];    /* '<S5>/Actuator' */
  int32_T Actuator_dtSizeInfo_ie[2];   /* '<S43>/Actuator' */
  int32_T Actuator_dtBusInfo_eu[30];   /* '<S43>/Actuator' */
  int32_T Actuator_dtSizeInfo_gu[2];   /* '<S82>/Actuator' */
  int32_T Actuator_dtBusInfo_p1[8];    /* '<S82>/Actuator' */
  int32_T Actuator_dtSizeInfo_l1[2];   /* '<S87>/Actuator' */
  int32_T Actuator_dtBusInfo_pw[8];    /* '<S87>/Actuator' */
  int32_T Actuator_dtSizeInfo_ed[2];   /* '<S92>/Actuator' */
  int32_T Actuator_dtBusInfo_n1[8];    /* '<S92>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_k[2];/* '<S20>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_m[6]; /* '<S20>/SpeedProfile' */
  int32_T Path_dtSizeInfo_m[3];        /* '<S20>/Path' */
  int32_T Path_dtBusInfo_m[36];        /* '<S20>/Path' */
  int32_T Actuator_dtSizeInfo_au[3];   /* '<S6>/Actuator' */
  int32_T Actuator_dtBusInfo_ms[4];    /* '<S6>/Actuator' */
  int32_T Actuator_dtSizeInfo_ai[2];   /* '<S44>/Actuator' */
  int32_T Actuator_dtBusInfo_ht[30];   /* '<S44>/Actuator' */
  int32_T Actuator_dtSizeInfo_p0[2];   /* '<S83>/Actuator' */
  int32_T Actuator_dtBusInfo_ka[8];    /* '<S83>/Actuator' */
  int32_T Actuator_dtSizeInfo_cx[2];   /* '<S88>/Actuator' */
  int32_T Actuator_dtBusInfo_iv[8];    /* '<S88>/Actuator' */
  int32_T Actuator_dtSizeInfo_h0[2];   /* '<S93>/Actuator' */
  int32_T Actuator_dtBusInfo_ed[8];    /* '<S93>/Actuator' */
  int32_T Sensor_dtSizeInfo[2];        /* '<S28>/Sensor' */
  int32_T Sensor_dtBusInfo[22];        /* '<S28>/Sensor' */
  int32_T Actuator_dtSizeInfo_ikl[2];  /* '<S37>/Actuator' */
  int32_T Actuator_dtBusInfo_cv[30];   /* '<S37>/Actuator' */
  int32_T sfun_Synchronizer_dtSizeInfo[2];/* '<S46>/sfun_Synchronizer' */
  int32_T sfun_Synchronizer_dtBusInfo[4];/* '<S46>/sfun_Synchronizer' */
  int32_T Sensor_dtSizeInfo_o[2];      /* '<S33>/Sensor' */
  int32_T Sensor_dtBusInfo_m[22];      /* '<S33>/Sensor' */
  int32_T Sensor_dtSizeInfo_p[2];      /* '<S27>/Sensor' */
  int32_T Sensor_dtBusInfo_mj[22];     /* '<S27>/Sensor' */
  int32_T Sensor_dtSizeInfo_d[2];      /* '<S31>/Sensor' */
  int32_T Sensor_dtBusInfo_c[22];      /* '<S31>/Sensor' */
  int32_T Sensor_dtSizeInfo_j[6];      /* '<S1>/Sensor' */
  int32_T Sensor_dtBusInfo_o[14];      /* '<S1>/Sensor' */
  int32_T Sensor_dtSizeInfo_l[2];      /* '<S29>/Sensor' */
  int32_T Sensor_dtBusInfo_d[22];      /* '<S29>/Sensor' */
  int32_T Sensor_dtSizeInfo_c[2];      /* '<S30>/Sensor' */
  int32_T Sensor_dtBusInfo_mp[22];     /* '<S30>/Sensor' */
  int32_T Sensor_dtSizeInfo_g[2];      /* '<S32>/Sensor' */
  int32_T Sensor_dtBusInfo_l[22];      /* '<S32>/Sensor' */
  int32_T Sensor_dtSizeInfo_e[2];      /* '<S34>/Sensor' */
  int32_T Sensor_dtBusInfo_h[22];      /* '<S34>/Sensor' */
  int32_T Sensor_dtSizeInfo_a[2];      /* '<S35>/Sensor' */
  int32_T Sensor_dtBusInfo_n[22];      /* '<S35>/Sensor' */
  int32_T Sensor_dtSizeInfo_oi[6];     /* '<S26>/Sensor' */
  int32_T Sensor_dtBusInfo_a[34];      /* '<S26>/Sensor' */
  int32_T sfun_Terminator_dtSizeInfo[2];/* '<S25>/sfun_Terminator' */
  int32_T sfun_Terminator_dtBusInfo[2];/* '<S25>/sfun_Terminator' */
  uint32_T Memory2_PreviousInput_cm;   /* '<S94>/Memory2' */
  uint32_T RandSeed[7];                /* '<S228>/Random Number' */
  uint32_T RandSeed_e[7];              /* '<S228>/Random Number1' */
  uint32_T RandSeed_n[7];              /* '<S228>/Random Number2' */
  uint32_T RandomSource1_SEED_DWORK;   /* '<S205>/Random Source1' */
  uint32_T RandomSource1_STATE_DWORK[2];/* '<S205>/Random Source1' */
  uint32_T RandomSource2_SEED_DWORK;   /* '<S205>/Random Source2' */
  uint32_T RandomSource2_STATE_DWORK[2];/* '<S205>/Random Source2' */
  uint32_T RandomSource3_SEED_DWORK;   /* '<S205>/Random Source3' */
  uint32_T RandomSource3_STATE_DWORK[2];/* '<S205>/Random Source3' */
  int8_T If_ActiveSubsystem;           /* '<S193>/If' */
  int8_T If_ActiveSubsystem_n;         /* '<S126>/If' */
  int8_T If_ActiveSubsystem_f;         /* '<S153>/If' */
  boolean_T ROSSendSimulinkState_MODE; /* '<S8>/ROS Send Simulink State' */
  boolean_T ROSSendIMU_MODE;           /* '<S8>/ROS Send IMU' */
  boolean_T ROSSendGoal_MODE;          /* '<S8>/ROS Send Goal' */
  boolean_T ROSSendClock_MODE;         /* '<S8>/ROS Send Clock' */
  DW_CoordinateTransformationCo_T CoordinateTransformationConve_f;
                             /* '<S107>/Coordinate Transformation Conversion' */
  DW_IfActionSubsystem1_W01_B_o_T IfActionSubsystem1_jk;/* '<S116>/If Action Subsystem1' */
  DW_RainModel_W01_Base_Map_cs_T RainModel_o;/* '<S116>/Rain Model' */
  DW_IfActionSubsystem1_W01_B_o_T IfActionSubsystem1_j;/* '<S115>/If Action Subsystem1' */
  DW_RainModel_W01_Base_Map_cs_T RainModel_p;/* '<S115>/Rain Model' */
  DW_IfActionSubsystem1_W01_B_o_T IfActionSubsystem1_f;/* '<S114>/If Action Subsystem1' */
  DW_RainModel_W01_Base_Map_cs_T RainModel_h;/* '<S114>/Rain Model' */
  DW_IfActionSubsystem1_W01_B_o_T IfActionSubsystem1_i;/* '<S113>/If Action Subsystem1' */
  DW_RainModel_W01_Base_Map_cs_T RainModel;/* '<S113>/Rain Model' */
  DW_CoordinateTransformationCo_T CoordinateTransformationConve_i;
                             /* '<S107>/Coordinate Transformation Conversion' */
} DW_W01_Base_Map_cs_T;

/* Invariant block signals for system '<S113>/Rain Model' */
typedef struct {
  const real_T Gain4;                  /* '<S208>/Gain4' */
  const real_T MathFunction6;          /* '<S208>/Math Function6' */
  const real_T Subtract3;              /* '<S208>/Subtract3' */
  const real_T MathFunction7;          /* '<S208>/Math Function7' */
  const real_T MathFunction2;          /* '<S208>/Math Function2' */
  const real_T MathFunction3;          /* '<S208>/Math Function3' */
  const real_T Gain1;                  /* '<S208>/Gain1' */
  const real_T p_min;                  /* '<S208>/Divide' */
} ConstB_RainModel_W01_Base_Map_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain1[3];               /* '<S398>/Gain1' */
  const real_T Gain1_c[3];             /* '<S399>/Gain1' */
  const real_T Gain1_f[3];             /* '<S400>/Gain1' */
  const real_T Gain1_l[3];             /* '<S404>/Gain1' */
  const real_T Gain1_p[3];             /* '<S405>/Gain1' */
  const real_T Gain1_a[3];             /* '<S406>/Gain1' */
  const real_T Gain1_pf[3];            /* '<S410>/Gain1' */
  const real_T Gain1_i[3];             /* '<S411>/Gain1' */
  const real_T Gain1_o[3];             /* '<S412>/Gain1' */
  const real_T Gain1_m[3];             /* '<S416>/Gain1' */
  const real_T Gain1_g[3];             /* '<S417>/Gain1' */
  const real_T Gain1_j[3];             /* '<S418>/Gain1' */
  const real_T Gain1_ja[3];            /* '<S422>/Gain1' */
  const real_T Gain1_ax[3];            /* '<S423>/Gain1' */
  const real_T Gain1_axg[3];           /* '<S424>/Gain1' */
  const real_T Gain1_at[3];            /* '<S428>/Gain1' */
  const real_T Gain1_h[3];             /* '<S429>/Gain1' */
  const real_T Gain1_l4[3];            /* '<S430>/Gain1' */
  const real_T Gain1_mq[3];            /* '<S434>/Gain1' */
  const real_T Gain1_iy[3];            /* '<S435>/Gain1' */
  const real_T Gain1_cx[3];            /* '<S436>/Gain1' */
  const real_T Gain1_d[3];             /* '<S440>/Gain1' */
  const real_T Gain1_po[3];            /* '<S441>/Gain1' */
  const real_T Gain1_k[3];             /* '<S442>/Gain1' */
  const real_T VectorConcatenate3[3];  /* '<S106>/Vector Concatenate3' */
  const real_T Width5;                 /* '<S155>/Width5' */
  const real_T Width5_f;               /* '<S153>/Width5' */
  const real_T Width5_m;               /* '<S152>/Width5' */
  const real_T Width5_g;               /* '<S150>/Width5' */
  const real_T Width4;                 /* '<S149>/Width4' */
  const real_T Width;                  /* '<S146>/Width' */
  const real_T Width1;                 /* '<S146>/Width1' */
  const real_T Width5_i;               /* '<S146>/Width5' */
  const real_T DataTypeConversion;     /* '<S146>/Data Type Conversion' */
  const real_T Width9;                 /* '<S146>/Width9' */
  const real_T Width10;                /* '<S146>/Width10' */
  const real_T Width_f;                /* '<S145>/Width' */
  const real_T Width1_c;               /* '<S145>/Width1' */
  const real_T Width5_k;               /* '<S145>/Width5' */
  const real_T DataTypeConversion_j;   /* '<S145>/Data Type Conversion' */
  const real_T Width9_n;               /* '<S145>/Width9' */
  const real_T Width10_c;              /* '<S145>/Width10' */
  const real_T Width_l;                /* '<S144>/Width' */
  const real_T Width1_o;               /* '<S144>/Width1' */
  const real_T Width5_fb;              /* '<S144>/Width5' */
  const real_T DataTypeConversion_h;   /* '<S144>/Data Type Conversion' */
  const real_T Width9_i;               /* '<S144>/Width9' */
  const real_T Width10_j;              /* '<S144>/Width10' */
  const uint32_T Width5_p;             /* '<S94>/Width5' */
  const uint32_T Width_m;              /* '<S94>/Width' */
  const uint32_T Width1_k;             /* '<S94>/Width1' */
  const uint32_T Width2;               /* '<S94>/Width2' */
  const uint32_T Product;              /* '<S146>/Product' */
  const uint32_T Product_o;            /* '<S145>/Product' */
  const uint32_T Product_c;            /* '<S144>/Product' */
  const real32_T Gain1_g2;             /* '<S231>/Gain1' */
  const real32_T TrigonometricFunction1;/* '<S229>/Trigonometric Function1' */
  const real32_T TrigonometricFunction;/* '<S229>/Trigonometric Function' */
  const real32_T Gain1_d1;             /* '<S234>/Gain1' */
  const real32_T TrigonometricFunction1_k;/* '<S232>/Trigonometric Function1' */
  const real32_T TrigonometricFunction_o;/* '<S232>/Trigonometric Function' */
  const real32_T Gain1_dv;             /* '<S237>/Gain1' */
  const real32_T TrigonometricFunction1_f;/* '<S235>/Trigonometric Function1' */
  const real32_T TrigonometricFunction_j;/* '<S235>/Trigonometric Function' */
  const real32_T Gain1_kz;             /* '<S240>/Gain1' */
  const real32_T TrigonometricFunction1_g;/* '<S238>/Trigonometric Function1' */
  const real32_T TrigonometricFunction_b;/* '<S238>/Trigonometric Function' */
  const real32_T Width5_fn;            /* '<S159>/Width5' */
  const real32_T Width5_fj;            /* '<S151>/Width5' */
  const int32_T TextureResourceID;     /* '<S395>/Data Type Conversion' */
  const int32_T TextureResourceID_e;   /* '<S396>/Data Type Conversion' */
  const int32_T TextureResourceID_l;   /* '<S397>/Data Type Conversion' */
  const int32_T TextureResourceID_c;   /* '<S401>/Data Type Conversion' */
  const int32_T TextureResourceID_k;   /* '<S402>/Data Type Conversion' */
  const int32_T TextureResourceID_h;   /* '<S403>/Data Type Conversion' */
  const int32_T TextureResourceID_a;   /* '<S407>/Data Type Conversion' */
  const int32_T TextureResourceID_f;   /* '<S408>/Data Type Conversion' */
  const int32_T TextureResourceID_lx;  /* '<S409>/Data Type Conversion' */
  const int32_T TextureResourceID_ln;  /* '<S413>/Data Type Conversion' */
  const int32_T TextureResourceID_kr;  /* '<S414>/Data Type Conversion' */
  const int32_T TextureResourceID_lp;  /* '<S415>/Data Type Conversion' */
  const int32_T TextureResourceID_o;   /* '<S419>/Data Type Conversion' */
  const int32_T TextureResourceID_oa;  /* '<S420>/Data Type Conversion' */
  const int32_T TextureResourceID_kh;  /* '<S421>/Data Type Conversion' */
  const int32_T TextureResourceID_fl;  /* '<S425>/Data Type Conversion' */
  const int32_T TextureResourceID_lb;  /* '<S426>/Data Type Conversion' */
  const int32_T TextureResourceID_d;   /* '<S427>/Data Type Conversion' */
  const int32_T TextureResourceID_b;   /* '<S431>/Data Type Conversion' */
  const int32_T TextureResourceID_os;  /* '<S432>/Data Type Conversion' */
  const int32_T TextureResourceID_lpc; /* '<S433>/Data Type Conversion' */
  const int32_T TextureResourceID_j;   /* '<S437>/Data Type Conversion' */
  const int32_T TextureResourceID_g;   /* '<S438>/Data Type Conversion' */
  const int32_T TextureResourceID_al;  /* '<S439>/Data Type Conversion' */
  const uint8_T R;                     /* '<S296>/Data Type Conversion' */
  const uint8_T G;                     /* '<S296>/Data Type Conversion1' */
  const uint8_T B;                     /* '<S296>/Data Type Conversion2' */
  const uint8_T R_n;                   /* '<S297>/Data Type Conversion' */
  const uint8_T G_c;                   /* '<S297>/Data Type Conversion1' */
  const uint8_T B_m;                   /* '<S297>/Data Type Conversion2' */
  const uint8_T R_c;                   /* '<S298>/Data Type Conversion' */
  const uint8_T G_l;                   /* '<S298>/Data Type Conversion1' */
  const uint8_T B_g;                   /* '<S298>/Data Type Conversion2' */
  const uint8_T R_l;                   /* '<S307>/Data Type Conversion' */
  const uint8_T G_m;                   /* '<S307>/Data Type Conversion1' */
  const uint8_T B_b;                   /* '<S307>/Data Type Conversion2' */
  const uint8_T R_m;                   /* '<S308>/Data Type Conversion' */
  const uint8_T G_k;                   /* '<S308>/Data Type Conversion1' */
  const uint8_T B_e;                   /* '<S308>/Data Type Conversion2' */
  const uint8_T R_i;                   /* '<S309>/Data Type Conversion' */
  const uint8_T G_i;                   /* '<S309>/Data Type Conversion1' */
  const uint8_T B_e0;                  /* '<S309>/Data Type Conversion2' */
  const uint8_T R_nd;                  /* '<S326>/Data Type Conversion' */
  const uint8_T G_ia;                  /* '<S326>/Data Type Conversion1' */
  const uint8_T B_d;                   /* '<S326>/Data Type Conversion2' */
  const uint8_T R_e;                   /* '<S327>/Data Type Conversion' */
  const uint8_T G_d;                   /* '<S327>/Data Type Conversion1' */
  const uint8_T B_j;                   /* '<S327>/Data Type Conversion2' */
  const uint8_T R_b;                   /* '<S328>/Data Type Conversion' */
  const uint8_T G_p;                   /* '<S328>/Data Type Conversion1' */
  const uint8_T B_jn;                  /* '<S328>/Data Type Conversion2' */
  const uint8_T R_mu;                  /* '<S375>/Data Type Conversion' */
  const uint8_T G_l1;                  /* '<S375>/Data Type Conversion1' */
  const uint8_T B_b1;                  /* '<S375>/Data Type Conversion2' */
  const uint8_T R_k;                   /* '<S376>/Data Type Conversion' */
  const uint8_T G_ph;                  /* '<S376>/Data Type Conversion1' */
  const uint8_T B_f;                   /* '<S376>/Data Type Conversion2' */
  const uint8_T R_i4;                  /* '<S377>/Data Type Conversion' */
  const uint8_T G_n;                   /* '<S377>/Data Type Conversion1' */
  const uint8_T B_fz;                  /* '<S377>/Data Type Conversion2' */
  const uint8_T R_ez;                  /* '<S386>/Data Type Conversion' */
  const uint8_T G_j;                   /* '<S386>/Data Type Conversion1' */
  const uint8_T B_bh;                  /* '<S386>/Data Type Conversion2' */
  const uint8_T R_ll;                  /* '<S387>/Data Type Conversion' */
  const uint8_T G_nc;                  /* '<S387>/Data Type Conversion1' */
  const uint8_T B_k;                   /* '<S387>/Data Type Conversion2' */
  const uint8_T R_f;                   /* '<S388>/Data Type Conversion' */
  const uint8_T G_iq;                  /* '<S388>/Data Type Conversion1' */
  const uint8_T B_i;                   /* '<S388>/Data Type Conversion2' */
  ConstB_RainModel_W01_Base_Map_T RainModel_o;/* '<S116>/Rain Model' */
  ConstB_RainModel_W01_Base_Map_T RainModel_p;/* '<S115>/Rain Model' */
  ConstB_RainModel_W01_Base_Map_T RainModel_h;/* '<S114>/Rain Model' */
  ConstB_RainModel_W01_Base_Map_T RainModel;/* '<S113>/Rain Model' */
} ConstB_W01_Base_Map_cs_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S8>/Constant27'
   *   '<S8>/Constant6'
   *   '<S8>/EnableSendFeatures'
   *   '<S8>/EnableSendSwitch'
   *   '<S8>/GoalOrientX'
   *   '<S8>/GoalOrientY'
   *   '<S8>/GoalPoseZ'
   *   '<S8>/Localization'
   *   '<S15>/sfun_Controller'
   *   '<S21>/Sensor'
   *   '<S22>/Sensor'
   *   '<S23>/Sensor'
   *   '<S24>/Sensor'
   *   '<S47>/Green_ID'
   *   '<S47>/Green_Mux_const'
   *   '<S47>/Orange_ID'
   *   '<S47>/Orange_Mux_const'
   *   '<S47>/Red_ID'
   *   '<S47>/Red_Mux_const'
   *   '<S51>/Constant1'
   *   '<S51>/Constant2'
   *   '<S51>/Green_ID'
   *   '<S51>/Orange_ID'
   *   '<S51>/Red_ID'
   *   '<S55>/Green_ID'
   *   '<S55>/Green_Mux_const'
   *   '<S55>/Orange_ID'
   *   '<S55>/Orange_Mux_const'
   *   '<S55>/Red_ID'
   *   '<S55>/Red_Mux_const'
   *   '<S59>/Green_ID'
   *   '<S59>/Green_Mux_const'
   *   '<S59>/Orange_ID'
   *   '<S59>/Orange_Mux_const'
   *   '<S59>/Red_ID'
   *   '<S59>/Red_Mux_const'
   *   '<S63>/Green_ID'
   *   '<S63>/Green_Mux_const'
   *   '<S63>/Orange_ID'
   *   '<S63>/Orange_Mux_const'
   *   '<S63>/Red_ID'
   *   '<S63>/Red_Mux_const'
   *   '<S67>/Constant1'
   *   '<S67>/Constant2'
   *   '<S67>/Green_ID'
   *   '<S67>/Orange_ID'
   *   '<S67>/Red_ID'
   *   '<S71>/Green_ID'
   *   '<S71>/Green_Mux_const'
   *   '<S71>/Orange_ID'
   *   '<S71>/Orange_Mux_const'
   *   '<S71>/Red_ID'
   *   '<S71>/Red_Mux_const'
   *   '<S75>/Green_ID'
   *   '<S75>/Green_Mux_const'
   *   '<S75>/Orange_ID'
   *   '<S75>/Orange_Mux_const'
   *   '<S75>/Red_ID'
   *   '<S75>/Red_Mux_const'
   *   '<S149>/Memory1'
   *   '<S150>/Memory2'
   *   '<S152>/Constant18'
   *   '<S152>/Constant19'
   *   '<S152>/Constant20'
   *   '<S152>/Constant21'
   *   '<S152>/Memory2'
   *   '<S155>/Constant18'
   *   '<S155>/Constant19'
   *   '<S155>/Constant20'
   *   '<S155>/Constant21'
   *   '<S155>/Memory2'
   *   '<S171>/Discrete-Time Integrator'
   *   '<S172>/Constant'
   *   '<S173>/Discrete-Time Integrator4'
   *   '<S173>/Discrete-Time Integrator5'
   *   '<S173>/Discrete-Time Integrator6'
   *   '<S208>/Constant8'
   *   '<S208>/Random Source1'
   *   '<S211>/Constant8'
   *   '<S211>/Random Source1'
   *   '<S214>/Constant8'
   *   '<S214>/Random Source1'
   *   '<S217>/Constant8'
   *   '<S217>/Random Source1'
   *   '<S228>/Random Number'
   *   '<S228>/Random Number1'
   *   '<S228>/Random Number2'
   *   '<S257>/Out1'
   *   '<S257>/Out2'
   *   '<S257>/Out3'
   *   '<S257>/Out4'
   *   '<S257>/Out5'
   *   '<S257>/Out6'
   *   '<S257>/Out7'
   *   '<S257>/Out8'
   *   '<S257>/Out9'
   *   '<S257>/Out10'
   *   '<S257>/Out11'
   *   '<S257>/Localization'
   *   '<S300>/Discrete-Time Integrator'
   *   '<S311>/Discrete-Time Integrator'
   *   '<S330>/Discrete-Time Integrator'
   *   '<S351>/Constant'
   *   '<S379>/Discrete-Time Integrator'
   *   '<S390>/Discrete-Time Integrator'
   *   '<S175>/pitch_vehicle'
   *   '<S175>/roll_vehicle'
   *   '<S175>/yaw_body'
   *   '<S193>/Memory'
   *   '<S302>/Constant'
   *   '<S313>/Constant'
   *   '<S332>/Constant'
   *   '<S353>/pitch_vehicle'
   *   '<S353>/roll_vehicle'
   *   '<S353>/yaw_body'
   *   '<S381>/Constant'
   *   '<S392>/Constant'
   *   '<S178>/UD'
   *   '<S179>/UD'
   *   '<S180>/UD'
   *   '<S356>/UD'
   *   '<S357>/UD'
   *   '<S358>/UD'
   */
  real_T pooled1;

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<Root>/Enable'
   *   '<S8>/Constant11'
   *   '<S8>/Detection'
   *   '<S8>/EnableSendCamera1'
   *   '<S8>/EnableSendCamera2'
   *   '<S8>/EnableSendCameraTL'
   *   '<S8>/EnableSendClock'
   *   '<S8>/EnableSendGNSS'
   *   '<S8>/EnableSendIMU'
   *   '<S8>/EnableSendLidar'
   *   '<S8>/EnableSendOdometry'
   *   '<S8>/EnableSendRadar'
   *   '<S8>/EnableSendVelocity'
   *   '<S8>/FakeLocalization'
   *   '<S8>/Map'
   *   '<S8>/MissionPlanning'
   *   '<S8>/MotionPlanning'
   *   '<S8>/Recording'
   *   '<S8>/Rviz'
   *   '<S8>/Sensing'
   *   '<S8>/Ssmp'
   *   '<S8>/Switch'
   *   '<S9>/Sensor'
   *   '<S10>/Sensor'
   *   '<S11>/Sensor'
   *   '<S15>/sfun_Controller'
   *   '<S18>/Sensor'
   *   '<S51>/Constant'
   *   '<S67>/Constant'
   *   '<S159>/Constant'
   *   '<S294>/WalkingScale'
   *   '<S305>/WalkingScale'
   *   '<S324>/WalkingScale'
   *   '<S373>/WalkingScale'
   *   '<S384>/WalkingScale'
   *   '<S208>/Constant2'
   *   '<S208>/Constant9'
   *   '<S208>/Random Source1'
   *   '<S211>/Constant2'
   *   '<S211>/Constant9'
   *   '<S211>/Random Source1'
   *   '<S214>/Constant2'
   *   '<S214>/Constant9'
   *   '<S214>/Random Source1'
   *   '<S217>/Constant2'
   *   '<S217>/Constant9'
   *   '<S217>/Random Source1'
   *   '<S257>/Detection'
   *   '<S257>/FakeLocalization'
   *   '<S257>/Map'
   *   '<S257>/MissionPlanning'
   *   '<S257>/MotionPlanning'
   *   '<S257>/Recording'
   *   '<S257>/Rviz'
   *   '<S257>/Sensing'
   *   '<S257>/Ssmp'
   *   '<S257>/Switch'
   */
  real_T pooled2;

  /* Expression: 1:1:n
   * Referenced by: '<S228>/Random Number'
   */
  real_T RandomNumber_Seed[7];

  /* Expression: n+1:1:2*n
   * Referenced by: '<S228>/Random Number1'
   */
  real_T RandomNumber1_Seed[7];

  /* Expression: 2*n+1:1:3*n
   * Referenced by: '<S228>/Random Number2'
   */
  real_T RandomNumber2_Seed[7];

  /* Pooled Parameter (Expression: port)
   * Referenced by:
   *   '<S443>/S-Function Builder'
   *   '<S218>/S-Function Builder'
   *   '<S219>/S-Function Builder'
   *   '<S220>/S-Function Builder'
   *   '<S221>/S-Function Builder'
   *   '<S222>/S-Function Builder'
   *   '<S223>/S-Function Builder'
   *   '<S224>/S-Function Builder'
   *   '<S225>/S-Function Builder'
   *   '<S226>/S-Function Builder'
   *   '<S241>/S-Function Builder'
   *   '<S242>/S-Function Builder'
   *   '<S243>/S-Function Builder'
   *   '<S245>/S-Function Builder'
   *   '<S246>/S-Function Builder1'
   *   '<S247>/S-Function Builder1'
   *   '<S252>/S-Function Builder'
   *   '<S253>/S-Function Builder'
   *   '<S255>/S-Function Builder1'
   *   '<S258>/S-Function Builder'
   *   '<S259>/S-Function Builder'
   *   '<S261>/S-Function Builder'
   *   '<S262>/S-Function Builder'
   *   '<S263>/S-Function Builder'
   *   '<S264>/S-Function Builder'
   *   '<S292>/S-Function Builder'
   *   '<S194>/S-Function Builder'
   */
  real_T pooled8;

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S294>/Switch'
   *   '<S305>/Switch'
   *   '<S324>/Switch'
   *   '<S373>/Switch'
   *   '<S384>/Switch'
   *   '<S443>/S-Function Builder'
   *   '<S218>/S-Function Builder'
   *   '<S219>/S-Function Builder'
   *   '<S220>/S-Function Builder'
   *   '<S221>/S-Function Builder'
   *   '<S222>/S-Function Builder'
   *   '<S223>/S-Function Builder'
   *   '<S224>/S-Function Builder'
   *   '<S225>/S-Function Builder'
   *   '<S226>/S-Function Builder'
   *   '<S241>/S-Function Builder'
   *   '<S242>/S-Function Builder'
   *   '<S243>/S-Function Builder'
   *   '<S245>/S-Function Builder'
   *   '<S246>/S-Function Builder1'
   *   '<S252>/S-Function Builder'
   *   '<S253>/S-Function Builder'
   *   '<S255>/S-Function Builder1'
   *   '<S258>/S-Function Builder'
   *   '<S259>/S-Function Builder'
   *   '<S261>/S-Function Builder'
   *   '<S262>/S-Function Builder'
   *   '<S263>/S-Function Builder'
   *   '<S264>/S-Function Builder'
   *   '<S292>/S-Function Builder'
   *   '<S163>/Gain'
   *   '<S163>/Gain1'
   *   '<S163>/Gain2'
   *   '<S164>/Gain'
   *   '<S164>/Gain1'
   *   '<S164>/Gain2'
   *   '<S165>/Gain'
   *   '<S165>/Gain1'
   *   '<S165>/Gain2'
   *   '<S194>/S-Function Builder'
   */
  real_T pooled9;

  /* Expression: timeout
   * Referenced by: '<S247>/S-Function Builder1'
   */
  real_T SFunctionBuilder1_P4;

  /* Expression: -9.82
   * Referenced by: '<S150>/Constant'
   */
  real_T Constant_Value;

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(MeshOnColor))
   * Referenced by:
   *   '<S48>/Actuator'
   *   '<S52>/Actuator'
   *   '<S56>/Actuator'
   *   '<S60>/Actuator'
   *   '<S64>/Actuator'
   *   '<S68>/Actuator'
   *   '<S72>/Actuator'
   *   '<S76>/Actuator'
   */
  real_T pooled16[16];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(MeshOffColor))
   * Referenced by:
   *   '<S48>/Actuator'
   *   '<S52>/Actuator'
   *   '<S56>/Actuator'
   *   '<S60>/Actuator'
   *   '<S64>/Actuator'
   *   '<S68>/Actuator'
   *   '<S72>/Actuator'
   *   '<S76>/Actuator'
   */
  real_T pooled17[16];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(MeshOnColor))
   * Referenced by:
   *   '<S49>/Actuator'
   *   '<S53>/Actuator'
   *   '<S57>/Actuator'
   *   '<S61>/Actuator'
   *   '<S65>/Actuator'
   *   '<S69>/Actuator'
   *   '<S73>/Actuator'
   *   '<S77>/Actuator'
   */
  real_T pooled19[16];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(MeshOffColor))
   * Referenced by:
   *   '<S49>/Actuator'
   *   '<S53>/Actuator'
   *   '<S57>/Actuator'
   *   '<S61>/Actuator'
   *   '<S65>/Actuator'
   *   '<S69>/Actuator'
   *   '<S73>/Actuator'
   *   '<S77>/Actuator'
   */
  real_T pooled20[16];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(MeshOnColor))
   * Referenced by:
   *   '<S50>/Actuator'
   *   '<S54>/Actuator'
   *   '<S58>/Actuator'
   *   '<S62>/Actuator'
   *   '<S66>/Actuator'
   *   '<S70>/Actuator'
   *   '<S74>/Actuator'
   *   '<S78>/Actuator'
   */
  real_T pooled22[16];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(MeshOffColor))
   * Referenced by:
   *   '<S50>/Actuator'
   *   '<S54>/Actuator'
   *   '<S58>/Actuator'
   *   '<S62>/Actuator'
   *   '<S66>/Actuator'
   *   '<S70>/Actuator'
   *   '<S74>/Actuator'
   *   '<S78>/Actuator'
   */
  real_T pooled23[16];

  /* Expression: 249
   * Referenced by: '<S8>/GoalPoseX'
   */
  real_T GoalPoseX_Value;

  /* Expression: 136
   * Referenced by: '<S8>/GoalPoseY'
   */
  real_T GoalPoseY_Value;

  /* Pooled Parameter (Expression: 0.707)
   * Referenced by:
   *   '<S8>/GoalOrientW'
   *   '<S8>/GoalOrientZ'
   */
  real_T pooled60;

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S8>/OrientationLidar1'
   *   '<S205>/Random Source1'
   *   '<S205>/Random Source2'
   *   '<S205>/Random Source3'
   *   '<S207>/Random Source1'
   *   '<S207>/Random Source2'
   *   '<S210>/Random Source1'
   *   '<S210>/Random Source2'
   *   '<S213>/Random Source1'
   *   '<S213>/Random Source2'
   *   '<S216>/Random Source1'
   *   '<S216>/Random Source2'
   */
  real32_T pooled62;

  /* Pooled Parameter (Expression: VarVal)
   * Referenced by:
   *   '<S205>/Random Source1'
   *   '<S205>/Random Source2'
   *   '<S205>/Random Source3'
   *   '<S207>/Random Source1'
   *   '<S207>/Random Source2'
   *   '<S210>/Random Source1'
   *   '<S210>/Random Source2'
   *   '<S213>/Random Source1'
   *   '<S213>/Random Source2'
   *   '<S216>/Random Source1'
   *   '<S216>/Random Source2'
   */
  real32_T pooled63;

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S48>/Actuator'
   *   '<S52>/Actuator'
   *   '<S56>/Actuator'
   *   '<S60>/Actuator'
   *   '<S64>/Actuator'
   *   '<S68>/Actuator'
   *   '<S72>/Actuator'
   *   '<S76>/Actuator'
   */
  uint32_T pooled67[16];

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S49>/Actuator'
   *   '<S53>/Actuator'
   *   '<S57>/Actuator'
   *   '<S61>/Actuator'
   *   '<S65>/Actuator'
   *   '<S69>/Actuator'
   *   '<S73>/Actuator'
   *   '<S77>/Actuator'
   */
  uint32_T pooled68[16];

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S50>/Actuator'
   *   '<S54>/Actuator'
   *   '<S58>/Actuator'
   *   '<S62>/Actuator'
   *   '<S66>/Actuator'
   *   '<S70>/Actuator'
   *   '<S74>/Actuator'
   *   '<S78>/Actuator'
   */
  uint32_T pooled69[16];

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S79>/Actuator'
   *   '<S80>/Actuator'
   *   '<S81>/Actuator'
   *   '<S82>/Actuator'
   *   '<S83>/Actuator'
   *   '<S89>/Actuator'
   *   '<S90>/Actuator'
   *   '<S91>/Actuator'
   *   '<S92>/Actuator'
   *   '<S93>/Actuator'
   */
  uint32_T pooled70[5];

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S84>/Actuator'
   *   '<S85>/Actuator'
   *   '<S86>/Actuator'
   *   '<S87>/Actuator'
   *   '<S88>/Actuator'
   */
  uint32_T pooled71[5];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S8>/Activation request'
   *   '<S8>/Initial checks'
   */
  boolean_T pooled72;

  /* Computed Parameter: Fault_Value
   * Referenced by: '<S8>/Fault'
   */
  boolean_T Fault_Value;

  /* Expression: int8(topic)
   * Referenced by: '<S241>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1[19];

  /* Pooled Parameter (Expression: int8(message_type))
   * Referenced by:
   *   '<S241>/S-Function Builder'
   *   '<S242>/S-Function Builder'
   *   '<S243>/S-Function Builder'
   */
  int8_T pooled73[17];

  /* Expression: int8(frame_id)
   * Referenced by: '<S241>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P3[8];

  /* Expression: int8(topic)
   * Referenced by: '<S242>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_f[19];

  /* Expression: int8(frame_id)
   * Referenced by: '<S242>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P3_a[8];

  /* Expression: int8(topic)
   * Referenced by: '<S243>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_k[13];

  /* Expression: int8(frame_id)
   * Referenced by: '<S243>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P3_g[9];

  /* Expression: int8(topic)
   * Referenced by: '<S245>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_p[6];

  /* Expression: int8(message_type)
   * Referenced by: '<S245>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P2[19];

  /* Expression: int8(topic)
   * Referenced by: '<S246>/S-Function Builder1'
   */
  int8_T SFunctionBuilder1_P1[19];

  /* Expression: int8(message_type)
   * Referenced by: '<S246>/S-Function Builder1'
   */
  int8_T SFunctionBuilder1_P2[18];

  /* Expression: int8(topic)
   * Referenced by: '<S247>/S-Function Builder1'
   */
  int8_T SFunctionBuilder1_P1_b[9];

  /* Expression: int8(message_type)
   * Referenced by: '<S247>/S-Function Builder1'
   */
  int8_T SFunctionBuilder1_P2_f[25];

  /* Expression: int8(topic)
   * Referenced by: '<S252>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_c[8];

  /* Expression: int8(message_type)
   * Referenced by: '<S252>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P2_b[15];

  /* Expression: int8(topic)
   * Referenced by: '<S253>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_m[19];

  /* Pooled Parameter (Expression: int8(message_type))
   * Referenced by:
   *   '<S253>/S-Function Builder'
   *   '<S292>/S-Function Builder'
   */
  int8_T pooled74[26];

  /* Expression: int8(topic)
   * Referenced by: '<S255>/S-Function Builder1'
   */
  int8_T SFunctionBuilder1_P1_g[13];

  /* Expression: int8(message_type)
   * Referenced by: '<S255>/S-Function Builder1'
   */
  int8_T SFunctionBuilder1_P2_fs[17];

  /* Expression: int8(topic)
   * Referenced by: '<S258>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_e[15];

  /* Expression: int8(message_type)
   * Referenced by: '<S258>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P2_g[24];

  /* Expression: int8(topic)
   * Referenced by: '<S259>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_fq[14];

  /* Expression: int8(message_type)
   * Referenced by: '<S259>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P2_a[14];

  /* Expression: int8(topic)
   * Referenced by: '<S261>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_o[17];

  /* Pooled Parameter (Expression: int8(message_type))
   * Referenced by:
   *   '<S261>/S-Function Builder'
   *   '<S194>/S-Function Builder'
   */
  int8_T pooled75[26];

  /* Expression: int8(topic)
   * Referenced by: '<S292>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_a[16];

  /* Expression: int8(topic)
   * Referenced by: '<S443>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_i[14];

  /* Expression: int8(message_type)
   * Referenced by: '<S443>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P2_j[23];

  /* Expression: int8(topic)
   * Referenced by: '<S194>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_ej[7];

  /* Expression: int8(topic)
   * Referenced by: '<S220>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_d[21];

  /* Pooled Parameter (Expression: int8(message_type))
   * Referenced by:
   *   '<S218>/S-Function Builder'
   *   '<S219>/S-Function Builder'
   *   '<S220>/S-Function Builder'
   *   '<S221>/S-Function Builder'
   *   '<S222>/S-Function Builder'
   *   '<S223>/S-Function Builder'
   *   '<S224>/S-Function Builder'
   *   '<S225>/S-Function Builder'
   *   '<S226>/S-Function Builder'
   */
  int8_T pooled76[14];

  /* Expression: int8(topic)
   * Referenced by: '<S225>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_m5[22];

  /* Expression: int8(topic)
   * Referenced by: '<S221>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_dp[23];

  /* Expression: int8(topic)
   * Referenced by: '<S222>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_pl[23];

  /* Expression: int8(topic)
   * Referenced by: '<S223>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_h[23];

  /* Expression: int8(topic)
   * Referenced by: '<S224>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_g[23];

  /* Expression: int8(topic)
   * Referenced by: '<S218>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_og[24];

  /* Expression: int8(topic)
   * Referenced by: '<S226>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_fs[26];

  /* Expression: int8(topic)
   * Referenced by: '<S219>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_mg[24];

  /* Expression: int8(topic)
   * Referenced by: '<S262>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_n[15];

  /* Pooled Parameter (Expression: int8(message_type))
   * Referenced by:
   *   '<S262>/S-Function Builder'
   *   '<S263>/S-Function Builder'
   *   '<S264>/S-Function Builder'
   */
  int8_T pooled77[13];

  /* Expression: int8(topic)
   * Referenced by: '<S263>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_an[19];

  /* Expression: int8(topic)
   * Referenced by: '<S264>/S-Function Builder'
   */
  int8_T SFunctionBuilder_P1_b[6];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S149>/Constant9'
   *   '<S247>/S-Function Builder1'
   */
  uint8_T pooled80[5];

  /* Expression: uint8(['map'])
   * Referenced by: '<S94>/Constant25'
   */
  uint8_T Constant25_Value_l[3];

  /* Expression: SParameter1
   * Referenced by: '<S15>/sfun_Controller'
   */
  uint8_T sfun_Controller_p1[17];

  /* Expression: SParameter2
   * Referenced by: '<S15>/sfun_Controller'
   */
  uint8_T sfun_Controller_p2[60];

  /* Expression: SParameter3
   * Referenced by: '<S15>/sfun_Controller'
   */
  uint8_T sfun_Controller_p3;

  /* Expression: SParameter9
   * Referenced by: '<S15>/sfun_Controller'
   */
  uint8_T sfun_Controller_p9[7];

  /* Expression: SParameter10
   * Referenced by: '<S15>/sfun_Controller'
   */
  uint8_T sfun_Controller_p10[7];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S48>/Actuator'
   */
  uint8_T Actuator_p2[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S48>/Actuator'
   */
  uint8_T pooled82[31];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(TextureResources))
   * Referenced by:
   *   '<S48>/Actuator'
   *   '<S49>/Actuator'
   *   '<S50>/Actuator'
   *   '<S52>/Actuator'
   *   '<S53>/Actuator'
   *   '<S54>/Actuator'
   *   '<S56>/Actuator'
   *   '<S57>/Actuator'
   *   '<S58>/Actuator'
   *   '<S60>/Actuator'
   *   '<S61>/Actuator'
   *   '<S62>/Actuator'
   *   '<S64>/Actuator'
   *   '<S65>/Actuator'
   *   '<S66>/Actuator'
   *   '<S68>/Actuator'
   *   '<S69>/Actuator'
   *   '<S70>/Actuator'
   *   '<S72>/Actuator'
   *   '<S73>/Actuator'
   *   '<S74>/Actuator'
   *   '<S76>/Actuator'
   *   '<S77>/Actuator'
   *   '<S78>/Actuator'
   */
  uint8_T pooled83[52];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S49>/Actuator'
   */
  uint8_T Actuator_p2_h[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S49>/Actuator'
   */
  uint8_T pooled84[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S50>/Actuator'
   */
  uint8_T Actuator_p2_l[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S50>/Actuator'
   */
  uint8_T pooled85[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S52>/Actuator'
   */
  uint8_T Actuator_p2_e[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S52>/Actuator'
   */
  uint8_T pooled86[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S53>/Actuator'
   */
  uint8_T Actuator_p2_hg[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S53>/Actuator'
   */
  uint8_T pooled87[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S54>/Actuator'
   */
  uint8_T Actuator_p2_e4[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S54>/Actuator'
   */
  uint8_T pooled88[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S56>/Actuator'
   */
  uint8_T Actuator_p2_o[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S56>/Actuator'
   */
  uint8_T pooled89[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S57>/Actuator'
   */
  uint8_T Actuator_p2_a[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S57>/Actuator'
   */
  uint8_T pooled90[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S58>/Actuator'
   */
  uint8_T Actuator_p2_hx[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S58>/Actuator'
   */
  uint8_T pooled91[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S60>/Actuator'
   */
  uint8_T Actuator_p2_hz[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S60>/Actuator'
   */
  uint8_T pooled92[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S61>/Actuator'
   */
  uint8_T Actuator_p2_ae[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S61>/Actuator'
   */
  uint8_T pooled93[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S62>/Actuator'
   */
  uint8_T Actuator_p2_m[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S62>/Actuator'
   */
  uint8_T pooled94[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S64>/Actuator'
   */
  uint8_T Actuator_p2_mz[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S64>/Actuator'
   */
  uint8_T pooled95[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S65>/Actuator'
   */
  uint8_T Actuator_p2_ll[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S65>/Actuator'
   */
  uint8_T pooled96[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S66>/Actuator'
   */
  uint8_T Actuator_p2_lz[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S66>/Actuator'
   */
  uint8_T pooled97[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S68>/Actuator'
   */
  uint8_T Actuator_p2_hn[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S68>/Actuator'
   */
  uint8_T pooled98[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S69>/Actuator'
   */
  uint8_T Actuator_p2_l1[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S69>/Actuator'
   */
  uint8_T pooled99[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S70>/Actuator'
   */
  uint8_T Actuator_p2_c[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S70>/Actuator'
   */
  uint8_T pooled100[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S72>/Actuator'
   */
  uint8_T Actuator_p2_l2[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S72>/Actuator'
   */
  uint8_T pooled101[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S73>/Actuator'
   */
  uint8_T Actuator_p2_i[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S73>/Actuator'
   */
  uint8_T pooled102[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S74>/Actuator'
   */
  uint8_T Actuator_p2_k[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S74>/Actuator'
   */
  uint8_T pooled103[29];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S76>/Actuator'
   */
  uint8_T Actuator_p2_cp[59];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S76>/Actuator'
   */
  uint8_T pooled104[31];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S77>/Actuator'
   */
  uint8_T Actuator_p2_cr[60];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S77>/Actuator'
   */
  uint8_T pooled105[32];

  /* Expression: mbxruntime.parameters.convert(LightName)
   * Referenced by: '<S78>/Actuator'
   */
  uint8_T Actuator_p2_p[57];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by: '<S78>/Actuator'
   */
  uint8_T pooled106[29];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S79>/Actuator'
   *   '<S80>/Actuator'
   *   '<S81>/Actuator'
   *   '<S82>/Actuator'
   *   '<S83>/Actuator'
   */
  uint8_T pooled108[43];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S84>/Actuator'
   *   '<S85>/Actuator'
   *   '<S86>/Actuator'
   *   '<S87>/Actuator'
   *   '<S88>/Actuator'
   */
  uint8_T pooled109[38];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S89>/Actuator'
   *   '<S90>/Actuator'
   *   '<S91>/Actuator'
   *   '<S92>/Actuator'
   *   '<S93>/Actuator'
   */
  uint8_T pooled110[43];
} ConstP_W01_Base_Map_cs_T;

/* Backward compatible GRT Identifiers */
#define rtB                            W01_Base_Map_cs_B
#define BlockIO                        B_W01_Base_Map_cs_T
#define rtP                            W01_Base_Map_cs_P
#define Parameters                     P_W01_Base_Map_cs_T
#define rtDWork                        W01_Base_Map_cs_DW
#define D_Work                         DW_W01_Base_Map_cs_T
#define tConstBlockIOType              ConstB_W01_Base_Map_cs_T
#define rtC                            W01_Base_Map_cs_ConstB
#define ConstParam                     ConstP_W01_Base_Map_cs_T
#define rtcP                           W01_Base_Map_cs_ConstP

/* Parameters (default storage) */
struct P_W01_Base_Map_cs_T_ {
  real_T W01_Base_Map_cs_328ec7e3a8cd5b54;
                                   /* Variable: W01_Base_Map_cs_328ec7e3a8cd5b54
                                    * Referenced by: '<S14>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_423c72fa17799c7f;
                                   /* Variable: W01_Base_Map_cs_423c72fa17799c7f
                                    * Referenced by:
                                    *   '<S351>/iniBODYAngles wrtVEH [rad]'
                                    *   '<S359>/UD'
                                    */
  real_T W01_Base_Map_cs_514c2dea2cdbe680;
                                   /* Variable: W01_Base_Map_cs_514c2dea2cdbe680
                                    * Referenced by: '<S12>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_51d6e6e467bedba1;
                                   /* Variable: W01_Base_Map_cs_51d6e6e467bedba1
                                    * Referenced by: '<S13>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_563ebd29d1fd6c09;
                                   /* Variable: W01_Base_Map_cs_563ebd29d1fd6c09
                                    * Referenced by: '<S172>/iniVEHposition wrtGLOB [m]1'
                                    */
  real_T W01_Base_Map_cs_57ea59d0358dab77;
                                   /* Variable: W01_Base_Map_cs_57ea59d0358dab77
                                    * Referenced by: '<S20>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_669d1acb174df2b9;
                                   /* Variable: W01_Base_Map_cs_669d1acb174df2b9
                                    * Referenced by: '<S351>/iniVEHposition wrtGLOB [m]2'
                                    */
  real_T W01_Base_Map_cs_774a522413284ef7;
                                   /* Variable: W01_Base_Map_cs_774a522413284ef7
                                    * Referenced by:
                                    *   '<S351>/iniVEHAngles wrtGLOB [rad]'
                                    *   '<S361>/UD'
                                    */
  real_T W01_Base_Map_cs_9538d35a279fbe4e;
                                   /* Variable: W01_Base_Map_cs_9538d35a279fbe4e
                                    * Referenced by:
                                    *   '<S172>/iniBODYAngles wrtVEH [rad]'
                                    *   '<S181>/UD'
                                    */
  real_T W01_Base_Map_cs_9f504bb84aebc2fd;
                                   /* Variable: W01_Base_Map_cs_9f504bb84aebc2fd
                                    * Referenced by:
                                    *   '<S172>/iniBODYAngles wrtVEH [rad]1'
                                    *   '<S182>/UD'
                                    */
  real_T W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID;
                  /* Variable: W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID
                   * Referenced by: '<S7>/Path'
                   */
  real_T W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID;
               /* Variable: W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID
                * Referenced by: '<S12>/Path'
                */
  real_T W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID;
               /* Variable: W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID
                * Referenced by: '<S13>/Path'
                */
  real_T W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID;
           /* Variable: W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID
            * Referenced by: '<S14>/Path'
            */
  real_T W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID;
              /* Variable: W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID
               * Referenced by: '<S16>/Path'
               */
  real_T W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID;
                /* Variable: W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID
                 * Referenced by: '<S19>/Path'
                 */
  real_T W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID;
                /* Variable: W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID
                 * Referenced by: '<S20>/Path'
                 */
  real_T W01_Base_Map_cs_a242ed7539861165;
                                   /* Variable: W01_Base_Map_cs_a242ed7539861165
                                    * Referenced by:
                                    *   '<S172>/iniVEHAngles wrtGLOB [rad]'
                                    *   '<S183>/UD'
                                    */
  real_T W01_Base_Map_cs_ae41b72d7e14f81d;
                                   /* Variable: W01_Base_Map_cs_ae41b72d7e14f81d
                                    * Referenced by: '<S351>/iniVEHposition wrtGLOB [m]1'
                                    */
  real_T W01_Base_Map_cs_b5931a786e299506;
                                   /* Variable: W01_Base_Map_cs_b5931a786e299506
                                    * Referenced by: '<S7>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_b7f45a070fa6e639;
                                   /* Variable: W01_Base_Map_cs_b7f45a070fa6e639
                                    * Referenced by: '<S172>/iniVEHposition wrtGLOB [m]'
                                    */
  real_T W01_Base_Map_cs_c02beb48492dde12;
                                   /* Variable: W01_Base_Map_cs_c02beb48492dde12
                                    * Referenced by: '<S19>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_c75b75e9f6b035bf;
                                   /* Variable: W01_Base_Map_cs_c75b75e9f6b035bf
                                    * Referenced by:
                                    *   '<S351>/iniBODYAngles wrtVEH [rad]1'
                                    *   '<S360>/UD'
                                    */
  real_T W01_Base_Map_cs_cf83ac8e8b053cbf;
                                   /* Variable: W01_Base_Map_cs_cf83ac8e8b053cbf
                                    * Referenced by: '<S16>/SpeedProfile'
                                    */
  real_T W01_Base_Map_cs_d4423fcf1c0d6fc4;
                                   /* Variable: W01_Base_Map_cs_d4423fcf1c0d6fc4
                                    * Referenced by: '<S172>/iniVEHposition wrtGLOB [m]2'
                                    */
  real_T W01_Base_Map_cs_df133aa86d9852fe;
                                   /* Variable: W01_Base_Map_cs_df133aa86d9852fe
                                    * Referenced by: '<S351>/iniVEHposition wrtGLOB [m]'
                                    */
};

/* Real-time Model Data Structure */
struct tag_RTM_W01_Base_Map_cs_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;
  void *blockIO;
  const void *constBlockIO;
  void *defaultParam;
  ZCSigState *prevZCSigState;
  real_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  void *zcSignalValues;
  void *inputs;
  void *outputs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  void *dwork;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[2];
    time_T offsetTimesArray[2];
    int_T sampleTimeTaskIDArray[2];
    int_T sampleHitArray[2];
    int_T perTaskSampleHitsArray[4];
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_W01_Base_Map_cs_T W01_Base_Map_cs_P;

/* Block signals (default storage) */
extern B_W01_Base_Map_cs_T W01_Base_Map_cs_B;

/* Block states (default storage) */
extern DW_W01_Base_Map_cs_T W01_Base_Map_cs_DW;
extern const ConstB_W01_Base_Map_cs_T W01_Base_Map_cs_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_W01_Base_Map_cs_T W01_Base_Map_cs_ConstP;

/*====================*
 * External functions *
 *====================*/
extern W01_Base_Map_cs_rtModel *W01_Base_Map_cs(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  W01_Base_Map_cs_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_W01_Base_Map_cs_T *const W01_Base_Map_cs_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'W01_Base_Map_cs'
 * '<S1>'   : 'W01_Base_Map_cs/AIR_1'
 * '<S2>'   : 'W01_Base_Map_cs/ANIM_Child_RegularAni_1'
 * '<S3>'   : 'W01_Base_Map_cs/ANIM_Child_RegularAni_2'
 * '<S4>'   : 'W01_Base_Map_cs/ANIM_Female_RegularAni_1'
 * '<S5>'   : 'W01_Base_Map_cs/ANIM_Male_RegularAni_1'
 * '<S6>'   : 'W01_Base_Map_cs/ANIM_Male_RegularAni_2'
 * '<S7>'   : 'W01_Base_Map_cs/Audi_A8_Sedan_1'
 * '<S8>'   : 'W01_Base_Map_cs/BMW_X5_SUV_1'
 * '<S9>'   : 'W01_Base_Map_cs/Camera_1'
 * '<S10>'  : 'W01_Base_Map_cs/Camera_2'
 * '<S11>'  : 'W01_Base_Map_cs/Camera_tl'
 * '<S12>'  : 'W01_Base_Map_cs/Child_RegularAni_1'
 * '<S13>'  : 'W01_Base_Map_cs/Child_RegularAni_2'
 * '<S14>'  : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1'
 * '<S15>'  : 'W01_Base_Map_cs/Controller'
 * '<S16>'  : 'W01_Base_Map_cs/Female_RegularAni_1'
 * '<S17>'  : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1'
 * '<S18>'  : 'W01_Base_Map_cs/HumViewCamera'
 * '<S19>'  : 'W01_Base_Map_cs/Male_RegularAni_1'
 * '<S20>'  : 'W01_Base_Map_cs/Male_RegularAni_2'
 * '<S21>'  : 'W01_Base_Map_cs/PointCloudSensor_1'
 * '<S22>'  : 'W01_Base_Map_cs/PointCloudSensor_2'
 * '<S23>'  : 'W01_Base_Map_cs/PointCloudSensor_3'
 * '<S24>'  : 'W01_Base_Map_cs/PointCloudSensor_4'
 * '<S25>'  : 'W01_Base_Map_cs/PreScanTerminator'
 * '<S26>'  : 'W01_Base_Map_cs/Radar_1'
 * '<S27>'  : 'W01_Base_Map_cs/SELF_Audi_A8_Sedan_1'
 * '<S28>'  : 'W01_Base_Map_cs/SELF_BMW_X5_SUV_1'
 * '<S29>'  : 'W01_Base_Map_cs/SELF_Child_RegularAni_1'
 * '<S30>'  : 'W01_Base_Map_cs/SELF_Child_RegularAni_2'
 * '<S31>'  : 'W01_Base_Map_cs/SELF_Citroen_C3_Hatchback_1'
 * '<S32>'  : 'W01_Base_Map_cs/SELF_Female_RegularAni_1'
 * '<S33>'  : 'W01_Base_Map_cs/SELF_Ford_Fiesta_Hatchback_1'
 * '<S34>'  : 'W01_Base_Map_cs/SELF_Male_RegularAni_1'
 * '<S35>'  : 'W01_Base_Map_cs/SELF_Male_RegularAni_2'
 * '<S36>'  : 'W01_Base_Map_cs/STATE_Audi_A8_Sedan_1_bus'
 * '<S37>'  : 'W01_Base_Map_cs/STATE_BMW_X5_SUV_1_bus'
 * '<S38>'  : 'W01_Base_Map_cs/STATE_Child_RegularAni_1_bus'
 * '<S39>'  : 'W01_Base_Map_cs/STATE_Child_RegularAni_2_bus'
 * '<S40>'  : 'W01_Base_Map_cs/STATE_Citroen_C3_Hatchback_1_bus'
 * '<S41>'  : 'W01_Base_Map_cs/STATE_Female_RegularAni_1_bus'
 * '<S42>'  : 'W01_Base_Map_cs/STATE_Ford_Fiesta_Hatchback_1_bus'
 * '<S43>'  : 'W01_Base_Map_cs/STATE_Male_RegularAni_1_bus'
 * '<S44>'  : 'W01_Base_Map_cs/STATE_Male_RegularAni_2_bus'
 * '<S45>'  : 'W01_Base_Map_cs/ScenarioEngine'
 * '<S46>'  : 'W01_Base_Map_cs/Synchronizer'
 * '<S47>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1'
 * '<S48>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1_Green'
 * '<S49>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1_Orange'
 * '<S50>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1_Red'
 * '<S51>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2'
 * '<S52>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2_Green'
 * '<S53>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2_Orange'
 * '<S54>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2_Red'
 * '<S55>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3'
 * '<S56>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3_Green'
 * '<S57>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3_Orange'
 * '<S58>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3_Red'
 * '<S59>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4'
 * '<S60>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4_Green'
 * '<S61>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4_Orange'
 * '<S62>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4_Red'
 * '<S63>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5'
 * '<S64>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5_Green'
 * '<S65>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5_Orange'
 * '<S66>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5_Red'
 * '<S67>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6'
 * '<S68>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6_Green'
 * '<S69>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6_Orange'
 * '<S70>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6_Red'
 * '<S71>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7'
 * '<S72>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7_Green'
 * '<S73>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7_Orange'
 * '<S74>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7_Red'
 * '<S75>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8'
 * '<S76>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8_Green'
 * '<S77>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8_Orange'
 * '<S78>'  : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8_Red'
 * '<S79>'  : 'W01_Base_Map_cs/VISUColorRegion_Lower_Body_Child_RegularAni_1'
 * '<S80>'  : 'W01_Base_Map_cs/VISUColorRegion_Lower_Body_Child_RegularAni_2'
 * '<S81>'  : 'W01_Base_Map_cs/VISUColorRegion_Lower_Body_Female_RegularAni_1'
 * '<S82>'  : 'W01_Base_Map_cs/VISUColorRegion_Lower_Body_Male_RegularAni_1'
 * '<S83>'  : 'W01_Base_Map_cs/VISUColorRegion_Lower_Body_Male_RegularAni_2'
 * '<S84>'  : 'W01_Base_Map_cs/VISUColorRegion_Shoes_Child_RegularAni_1'
 * '<S85>'  : 'W01_Base_Map_cs/VISUColorRegion_Shoes_Child_RegularAni_2'
 * '<S86>'  : 'W01_Base_Map_cs/VISUColorRegion_Shoes_Female_RegularAni_1'
 * '<S87>'  : 'W01_Base_Map_cs/VISUColorRegion_Shoes_Male_RegularAni_1'
 * '<S88>'  : 'W01_Base_Map_cs/VISUColorRegion_Shoes_Male_RegularAni_2'
 * '<S89>'  : 'W01_Base_Map_cs/VISUColorRegion_Upper_Body_Child_RegularAni_1'
 * '<S90>'  : 'W01_Base_Map_cs/VISUColorRegion_Upper_Body_Child_RegularAni_2'
 * '<S91>'  : 'W01_Base_Map_cs/VISUColorRegion_Upper_Body_Female_RegularAni_1'
 * '<S92>'  : 'W01_Base_Map_cs/VISUColorRegion_Upper_Body_Male_RegularAni_1'
 * '<S93>'  : 'W01_Base_Map_cs/VISUColorRegion_Upper_Body_Male_RegularAni_2'
 * '<S94>'  : 'W01_Base_Map_cs/pose_otheCar'
 * '<S95>'  : 'W01_Base_Map_cs/Audi_A8_Sedan_1/Car_Pos_and_Orient'
 * '<S96>'  : 'W01_Base_Map_cs/Audi_A8_Sedan_1/SELF_Demux'
 * '<S97>'  : 'W01_Base_Map_cs/Audi_A8_Sedan_1/Car_Pos_and_Orient/Degrees to Radians1'
 * '<S98>'  : 'W01_Base_Map_cs/Audi_A8_Sedan_1/Car_Pos_and_Orient/Degrees to Radians2'
 * '<S99>'  : 'W01_Base_Map_cs/Audi_A8_Sedan_1/Car_Pos_and_Orient/Degrees to Radians5'
 * '<S100>' : 'W01_Base_Map_cs/Audi_A8_Sedan_1/Car_Pos_and_Orient/Rotation Angles to Quaternions'
 * '<S101>' : 'W01_Base_Map_cs/Audi_A8_Sedan_1/SELF_Demux/compas converter'
 * '<S102>' : 'W01_Base_Map_cs/Audi_A8_Sedan_1/SELF_Demux/compas converter/cart2compas'
 * '<S103>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Camera_1_CM_Demux'
 * '<S104>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Camera_2_CM_Demux'
 * '<S105>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Camera_tl_CM_Demux'
 * '<S106>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link'
 * '<S107>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car_Pose'
 * '<S108>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty'
 * '<S109>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera'
 * '<S110>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera2'
 * '<S111>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera3'
 * '<S112>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection GNSS'
 * '<S113>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar'
 * '<S114>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar1'
 * '<S115>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar2'
 * '<S116>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar3'
 * '<S117>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Camera 1'
 * '<S118>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Camera 2'
 * '<S119>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener GNSS'
 * '<S120>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 1'
 * '<S121>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 2'
 * '<S122>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 3'
 * '<S123>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 4'
 * '<S124>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Radar'
 * '<S125>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener TL Camera'
 * '<S126>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Radar'
 * '<S127>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/HumViewCamera_CM_Demux'
 * '<S128>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter'
 * '<S129>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter1'
 * '<S130>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter2'
 * '<S131>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter3'
 * '<S132>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_1_Angles_Demux'
 * '<S133>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_1_Intensity_Demux'
 * '<S134>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_1_Range_Demux'
 * '<S135>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_2_Angles_Demux'
 * '<S136>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_2_Intensity_Demux'
 * '<S137>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_2_Range_Demux'
 * '<S138>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_3_Angles_Demux'
 * '<S139>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_3_Intensity_Demux'
 * '<S140>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_3_Range_Demux'
 * '<S141>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_4_Angles_Demux'
 * '<S142>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_4_Intensity_Demux'
 * '<S143>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/PointCloudSensor_4_Range_Demux'
 * '<S144>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera'
 * '<S145>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera 2'
 * '<S146>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera TL'
 * '<S147>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Clock'
 * '<S148>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send GNSS'
 * '<S149>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Goal'
 * '<S150>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send IMU'
 * '<S151>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Lidar'
 * '<S152>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Odometry'
 * '<S153>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Simulink State'
 * '<S154>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Switch Command'
 * '<S155>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Velocity'
 * '<S156>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS send RCV states'
 * '<S157>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux'
 * '<S158>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/SELF_Demux'
 * '<S159>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/radarDetections'
 * '<S160>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Conjugate1'
 * '<S161>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation'
 * '<S162>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation/Quaternion Normalize'
 * '<S163>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation/V1'
 * '<S164>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation/V2'
 * '<S165>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation/V3'
 * '<S166>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S167>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car to Base_link/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S168>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car_Pose/Degrees to Radians1'
 * '<S169>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car_Pose/Degrees to Radians2'
 * '<S170>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Car_Pose/Degrees to Radians5'
 * '<S171>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/MuxState'
 * '<S172>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1'
 * '<S173>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/Subsystem1'
 * '<S174>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/MuxState/Transformation_BODY2GLOBAL'
 * '<S175>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState'
 * '<S176>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Degrees to Radians'
 * '<S177>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Degrees to Radians1'
 * '<S178>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Discrete Derivative'
 * '<S179>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Discrete Derivative1'
 * '<S180>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Discrete Derivative2'
 * '<S181>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Discrete Derivative3'
 * '<S182>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Discrete Derivative4'
 * '<S183>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Discrete Derivative5'
 * '<S184>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Transformation_BODY2GLOBAL'
 * '<S185>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/Transformation_BODY2GLOBAL1'
 * '<S186>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll'
 * '<S187>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)'
 * '<S188>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/270 deg detection'
 * '<S189>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/90 deg detection'
 * '<S190>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/Angle -360 to +360 deg limiter'
 * '<S191>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/Degrees to Radians'
 * '<S192>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/STATE_BMW_X5_SUV_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/Radians to Degrees'
 * '<S193>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/Subsystem1/Subsystem'
 * '<S194>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/Subsystem1/TwistStamped Subscriber'
 * '<S195>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/Subsystem1/Subsystem/If Action Subsystem'
 * '<S196>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/Subsystem1/Subsystem/If Action Subsystem1'
 * '<S197>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Dynamics_Empty/Subsystem1/Subsystem/If Action Subsystem2'
 * '<S198>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera/If Action Subsystem'
 * '<S199>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera/If Action Subsystem1'
 * '<S200>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera2/If Action Subsystem'
 * '<S201>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera2/If Action Subsystem1'
 * '<S202>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera3/If Action Subsystem'
 * '<S203>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Camera3/If Action Subsystem1'
 * '<S204>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection GNSS/If Action Subsystem'
 * '<S205>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection GNSS/If Action Subsystem1'
 * '<S206>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar/If Action Subsystem'
 * '<S207>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar/If Action Subsystem1'
 * '<S208>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar/Rain Model'
 * '<S209>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar1/If Action Subsystem'
 * '<S210>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar1/If Action Subsystem1'
 * '<S211>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar1/Rain Model'
 * '<S212>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar2/If Action Subsystem'
 * '<S213>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar2/If Action Subsystem1'
 * '<S214>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar2/Rain Model'
 * '<S215>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar3/If Action Subsystem'
 * '<S216>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar3/If Action Subsystem1'
 * '<S217>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Lidar3/Rain Model'
 * '<S218>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Camera 1/Int16 Subscriber'
 * '<S219>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Camera 2/Int16 Subscriber'
 * '<S220>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener GNSS/Int16 Subscriber'
 * '<S221>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 1/Int16 Subscriber'
 * '<S222>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 2/Int16 Subscriber'
 * '<S223>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 3/Int16 Subscriber'
 * '<S224>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Lidar 4/Int16 Subscriber'
 * '<S225>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener Radar/Int16 Subscriber'
 * '<S226>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Listener TL Camera/Int16 Subscriber'
 * '<S227>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Radar/If Action Subsystem'
 * '<S228>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Fault Injection Radar/If Action Subsystem1'
 * '<S229>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter/Rotate over Z'
 * '<S230>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter/Spherical to cartesian'
 * '<S231>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter/Rotate over Z/Degrees to Radians1'
 * '<S232>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter1/Rotate over Z'
 * '<S233>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter1/Spherical to cartesian'
 * '<S234>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter1/Rotate over Z/Degrees to Radians1'
 * '<S235>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter2/Rotate over Z'
 * '<S236>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter2/Spherical to cartesian'
 * '<S237>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter2/Rotate over Z/Degrees to Radians1'
 * '<S238>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter3/Rotate over Z'
 * '<S239>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter3/Spherical to cartesian'
 * '<S240>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Lidar Adapter3/Rotate over Z/Degrees to Radians1'
 * '<S241>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera/Image Publisher'
 * '<S242>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera 2/Image Publisher'
 * '<S243>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera TL/Image Publisher'
 * '<S244>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Camera TL/VECTORES'
 * '<S245>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Clock/Clock Publisher'
 * '<S246>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send GNSS/geometry_msgs//Pose'
 * '<S247>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Goal/geometry_msgs//PoseStamped'
 * '<S248>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send IMU/Degrees to Radians1'
 * '<S249>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send IMU/Degrees to Radians2'
 * '<S250>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send IMU/Degrees to Radians3'
 * '<S251>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send IMU/Degrees to Radians4'
 * '<S252>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send IMU/sensor_msgs//Imu'
 * '<S253>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Lidar/Float32MultiArray Publisher'
 * '<S254>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Odometry/Degrees to Radians3'
 * '<S255>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Odometry/nav_msgs//Odometry'
 * '<S256>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Simulink State/If Action Subsystem'
 * '<S257>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Simulink State/If Action Subsystem2'
 * '<S258>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Simulink State/Int32MultiArray Publisher'
 * '<S259>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Switch Command/std_msgs//Int32 Publisher'
 * '<S260>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Velocity/Degrees to Radians3'
 * '<S261>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS Send Velocity/geometry_msgs//TwistStamped'
 * '<S262>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS send RCV states/Bool Publisher'
 * '<S263>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS send RCV states/Bool Publisher1'
 * '<S264>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/ROS send RCV states/Bool Publisher2'
 * '<S265>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion'
 * '<S266>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Cnvert1'
 * '<S267>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals'
 * '<S268>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals1'
 * '<S269>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals10'
 * '<S270>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals11'
 * '<S271>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals12'
 * '<S272>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals13'
 * '<S273>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals14'
 * '<S274>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals15'
 * '<S275>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals16'
 * '<S276>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals17'
 * '<S277>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals18'
 * '<S278>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals2'
 * '<S279>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals3'
 * '<S280>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals4'
 * '<S281>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals5'
 * '<S282>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals6'
 * '<S283>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals7'
 * '<S284>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals8'
 * '<S285>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals9'
 * '<S286>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Cnvert1/Degrees to Radians'
 * '<S287>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Cnvert1/Degrees to Radians1'
 * '<S288>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/SELF_Demux/compas converter'
 * '<S289>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/SELF_Demux/compas converter/cart2compas'
 * '<S290>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/radarDetections/Degrees to Radians'
 * '<S291>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/radarDetections/Degrees to Radians1'
 * '<S292>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/radarDetections/Float32MultiArray Publisher'
 * '<S293>' : 'W01_Base_Map_cs/BMW_X5_SUV_1/radarDetections/Spherical to cartesian'
 * '<S294>' : 'W01_Base_Map_cs/Child_RegularAni_1/Animation'
 * '<S295>' : 'W01_Base_Map_cs/Child_RegularAni_1/SELF_Demux'
 * '<S296>' : 'W01_Base_Map_cs/Child_RegularAni_1/VISUColorRegion_Lower_Body_Mux'
 * '<S297>' : 'W01_Base_Map_cs/Child_RegularAni_1/VISUColorRegion_Shoes_Mux'
 * '<S298>' : 'W01_Base_Map_cs/Child_RegularAni_1/VISUColorRegion_Upper_Body_Mux'
 * '<S299>' : 'W01_Base_Map_cs/Child_RegularAni_1/Animation/animation mode'
 * '<S300>' : 'W01_Base_Map_cs/Child_RegularAni_1/Animation/elapsed track'
 * '<S301>' : 'W01_Base_Map_cs/Child_RegularAni_1/Animation/animation mode/Running'
 * '<S302>' : 'W01_Base_Map_cs/Child_RegularAni_1/Animation/animation mode/Walking'
 * '<S303>' : 'W01_Base_Map_cs/Child_RegularAni_1/SELF_Demux/compas converter'
 * '<S304>' : 'W01_Base_Map_cs/Child_RegularAni_1/SELF_Demux/compas converter/cart2compas'
 * '<S305>' : 'W01_Base_Map_cs/Child_RegularAni_2/Animation'
 * '<S306>' : 'W01_Base_Map_cs/Child_RegularAni_2/SELF_Demux'
 * '<S307>' : 'W01_Base_Map_cs/Child_RegularAni_2/VISUColorRegion_Lower_Body_Mux'
 * '<S308>' : 'W01_Base_Map_cs/Child_RegularAni_2/VISUColorRegion_Shoes_Mux'
 * '<S309>' : 'W01_Base_Map_cs/Child_RegularAni_2/VISUColorRegion_Upper_Body_Mux'
 * '<S310>' : 'W01_Base_Map_cs/Child_RegularAni_2/Animation/animation mode'
 * '<S311>' : 'W01_Base_Map_cs/Child_RegularAni_2/Animation/elapsed track'
 * '<S312>' : 'W01_Base_Map_cs/Child_RegularAni_2/Animation/animation mode/Running'
 * '<S313>' : 'W01_Base_Map_cs/Child_RegularAni_2/Animation/animation mode/Walking'
 * '<S314>' : 'W01_Base_Map_cs/Child_RegularAni_2/SELF_Demux/compas converter'
 * '<S315>' : 'W01_Base_Map_cs/Child_RegularAni_2/SELF_Demux/compas converter/cart2compas'
 * '<S316>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/Car_Pos_and_Orient'
 * '<S317>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/SELF_Demux'
 * '<S318>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/Car_Pos_and_Orient/Degrees to Radians1'
 * '<S319>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/Car_Pos_and_Orient/Degrees to Radians2'
 * '<S320>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/Car_Pos_and_Orient/Degrees to Radians5'
 * '<S321>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/Car_Pos_and_Orient/Rotation Angles to Quaternions'
 * '<S322>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/SELF_Demux/compas converter'
 * '<S323>' : 'W01_Base_Map_cs/Citroen_C3_Hatchback_1/SELF_Demux/compas converter/cart2compas'
 * '<S324>' : 'W01_Base_Map_cs/Female_RegularAni_1/Animation'
 * '<S325>' : 'W01_Base_Map_cs/Female_RegularAni_1/SELF_Demux'
 * '<S326>' : 'W01_Base_Map_cs/Female_RegularAni_1/VISUColorRegion_Lower_Body_Mux'
 * '<S327>' : 'W01_Base_Map_cs/Female_RegularAni_1/VISUColorRegion_Shoes_Mux'
 * '<S328>' : 'W01_Base_Map_cs/Female_RegularAni_1/VISUColorRegion_Upper_Body_Mux'
 * '<S329>' : 'W01_Base_Map_cs/Female_RegularAni_1/Animation/animation mode'
 * '<S330>' : 'W01_Base_Map_cs/Female_RegularAni_1/Animation/elapsed track'
 * '<S331>' : 'W01_Base_Map_cs/Female_RegularAni_1/Animation/animation mode/Running'
 * '<S332>' : 'W01_Base_Map_cs/Female_RegularAni_1/Animation/animation mode/Walking'
 * '<S333>' : 'W01_Base_Map_cs/Female_RegularAni_1/SELF_Demux/compas converter'
 * '<S334>' : 'W01_Base_Map_cs/Female_RegularAni_1/SELF_Demux/compas converter/cart2compas'
 * '<S335>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux'
 * '<S336>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Car_Pos_and_Orient'
 * '<S337>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty'
 * '<S338>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/SELF_Demux'
 * '<S339>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Activate_Switch'
 * '<S340>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Signal2ArrayOfSignals1'
 * '<S341>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Signal2ArrayOfSignals2'
 * '<S342>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Signal2ArrayOfSignals3'
 * '<S343>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Signal2ArrayOfSignals4'
 * '<S344>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Signal2ArrayOfSignals5'
 * '<S345>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/AIR_1_Demux/Signal2ArrayOfSignals6'
 * '<S346>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Car_Pos_and_Orient/Degrees to Radians1'
 * '<S347>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Car_Pos_and_Orient/Degrees to Radians2'
 * '<S348>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Car_Pos_and_Orient/Degrees to Radians5'
 * '<S349>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Car_Pos_and_Orient/Rotation Angles to Quaternions'
 * '<S350>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/MuxState'
 * '<S351>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1'
 * '<S352>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/MuxState/Transformation_BODY2GLOBAL'
 * '<S353>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState'
 * '<S354>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Degrees to Radians'
 * '<S355>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Degrees to Radians1'
 * '<S356>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Discrete Derivative'
 * '<S357>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Discrete Derivative1'
 * '<S358>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Discrete Derivative2'
 * '<S359>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Discrete Derivative3'
 * '<S360>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Discrete Derivative4'
 * '<S361>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Discrete Derivative5'
 * '<S362>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Transformation_BODY2GLOBAL'
 * '<S363>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/Transformation_BODY2GLOBAL1'
 * '<S364>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll'
 * '<S365>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)'
 * '<S366>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/270 deg detection'
 * '<S367>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/90 deg detection'
 * '<S368>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/Angle -360 to +360 deg limiter'
 * '<S369>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/Degrees to Radians'
 * '<S370>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/Dynamics_Empty/STATE_Ford_Fiesta_Hatchback_1/state2FullState/limit roll/Substitute 90 & 270 deg (and its plurals)/Radians to Degrees'
 * '<S371>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/SELF_Demux/compas converter'
 * '<S372>' : 'W01_Base_Map_cs/Ford_Fiesta_Hatchback_1/SELF_Demux/compas converter/cart2compas'
 * '<S373>' : 'W01_Base_Map_cs/Male_RegularAni_1/Animation'
 * '<S374>' : 'W01_Base_Map_cs/Male_RegularAni_1/SELF_Demux'
 * '<S375>' : 'W01_Base_Map_cs/Male_RegularAni_1/VISUColorRegion_Lower_Body_Mux'
 * '<S376>' : 'W01_Base_Map_cs/Male_RegularAni_1/VISUColorRegion_Shoes_Mux'
 * '<S377>' : 'W01_Base_Map_cs/Male_RegularAni_1/VISUColorRegion_Upper_Body_Mux'
 * '<S378>' : 'W01_Base_Map_cs/Male_RegularAni_1/Animation/animation mode'
 * '<S379>' : 'W01_Base_Map_cs/Male_RegularAni_1/Animation/elapsed track'
 * '<S380>' : 'W01_Base_Map_cs/Male_RegularAni_1/Animation/animation mode/Running'
 * '<S381>' : 'W01_Base_Map_cs/Male_RegularAni_1/Animation/animation mode/Walking'
 * '<S382>' : 'W01_Base_Map_cs/Male_RegularAni_1/SELF_Demux/compas converter'
 * '<S383>' : 'W01_Base_Map_cs/Male_RegularAni_1/SELF_Demux/compas converter/cart2compas'
 * '<S384>' : 'W01_Base_Map_cs/Male_RegularAni_2/Animation'
 * '<S385>' : 'W01_Base_Map_cs/Male_RegularAni_2/SELF_Demux'
 * '<S386>' : 'W01_Base_Map_cs/Male_RegularAni_2/VISUColorRegion_Lower_Body_Mux'
 * '<S387>' : 'W01_Base_Map_cs/Male_RegularAni_2/VISUColorRegion_Shoes_Mux'
 * '<S388>' : 'W01_Base_Map_cs/Male_RegularAni_2/VISUColorRegion_Upper_Body_Mux'
 * '<S389>' : 'W01_Base_Map_cs/Male_RegularAni_2/Animation/animation mode'
 * '<S390>' : 'W01_Base_Map_cs/Male_RegularAni_2/Animation/elapsed track'
 * '<S391>' : 'W01_Base_Map_cs/Male_RegularAni_2/Animation/animation mode/Running'
 * '<S392>' : 'W01_Base_Map_cs/Male_RegularAni_2/Animation/animation mode/Walking'
 * '<S393>' : 'W01_Base_Map_cs/Male_RegularAni_2/SELF_Demux/compas converter'
 * '<S394>' : 'W01_Base_Map_cs/Male_RegularAni_2/SELF_Demux/compas converter/cart2compas'
 * '<S395>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1/Green_Mux'
 * '<S396>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1/Orange_Mux'
 * '<S397>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1/Red_Mux'
 * '<S398>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1/Green_Mux/Degrees to Radians'
 * '<S399>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1/Orange_Mux/Degrees to Radians'
 * '<S400>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_1/Red_Mux/Degrees to Radians'
 * '<S401>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2/Green_Mux'
 * '<S402>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2/Orange_Mux'
 * '<S403>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2/Red_Mux'
 * '<S404>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2/Green_Mux/Degrees to Radians'
 * '<S405>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2/Orange_Mux/Degrees to Radians'
 * '<S406>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_2/Red_Mux/Degrees to Radians'
 * '<S407>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3/Green_Mux'
 * '<S408>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3/Orange_Mux'
 * '<S409>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3/Red_Mux'
 * '<S410>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3/Green_Mux/Degrees to Radians'
 * '<S411>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3/Orange_Mux/Degrees to Radians'
 * '<S412>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_3/Red_Mux/Degrees to Radians'
 * '<S413>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4/Green_Mux'
 * '<S414>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4/Orange_Mux'
 * '<S415>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4/Red_Mux'
 * '<S416>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4/Green_Mux/Degrees to Radians'
 * '<S417>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4/Orange_Mux/Degrees to Radians'
 * '<S418>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_4/Red_Mux/Degrees to Radians'
 * '<S419>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5/Green_Mux'
 * '<S420>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5/Orange_Mux'
 * '<S421>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5/Red_Mux'
 * '<S422>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5/Green_Mux/Degrees to Radians'
 * '<S423>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5/Orange_Mux/Degrees to Radians'
 * '<S424>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_5/Red_Mux/Degrees to Radians'
 * '<S425>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6/Green_Mux'
 * '<S426>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6/Orange_Mux'
 * '<S427>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6/Red_Mux'
 * '<S428>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6/Green_Mux/Degrees to Radians'
 * '<S429>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6/Orange_Mux/Degrees to Radians'
 * '<S430>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_6/Red_Mux/Degrees to Radians'
 * '<S431>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7/Green_Mux'
 * '<S432>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7/Orange_Mux'
 * '<S433>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7/Red_Mux'
 * '<S434>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7/Green_Mux/Degrees to Radians'
 * '<S435>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7/Orange_Mux/Degrees to Radians'
 * '<S436>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_7/Red_Mux/Degrees to Radians'
 * '<S437>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8/Green_Mux'
 * '<S438>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8/Orange_Mux'
 * '<S439>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8/Red_Mux'
 * '<S440>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8/Green_Mux/Degrees to Radians'
 * '<S441>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8/Orange_Mux/Degrees to Radians'
 * '<S442>' : 'W01_Base_Map_cs/TrafficLightRoadSideNL_8/Red_Mux/Degrees to Radians'
 * '<S443>' : 'W01_Base_Map_cs/pose_otheCar/PoseArray Publisher'
 */
#endif                                 /* RTW_HEADER_W01_Base_Map_cs_h_ */
