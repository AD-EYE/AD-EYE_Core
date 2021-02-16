/*
 * W12_Crossing_cs.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "W12_Crossing_cs".
 *
 * Model version              : 1.75
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Wed Feb 10 17:20:38 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_W12_Crossing_cs_h_
#define RTW_HEADER_W12_Crossing_cs_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef W12_Crossing_cs_COMMON_INCLUDES_
# define W12_Crossing_cs_COMMON_INCLUDES_
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
#include "prescan_speedprofile_data.h"
#include "prescan_motion_data.h"
#include "prescan_path_data.h"
#include "prescan_stateactuator_data.h"
#include "prescan_animactuator_data.h"
#include "prescan_coloractuator_data.h"
#include "prescan_color_data.h"
#include "prescan_scenarioengine_data.h"
#include "prescan_synchronizer_data.h"
#include "prescan_selfsensor_data.h"
#include "prescan_camera_data.h"
#include "prescan_pcs_data.h"
#include "prescan_radar_data.h"
#include "prescan_scannersensor_data.h"
#include "prescan_header_data.h"
#include "prescan_terminator_data.h"
#endif                                 /* W12_Crossing_cs_COMMON_INCLUDES_ */

#include "W12_Crossing_cs_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
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
# define rtmGetDataMapInfo(rtm)        ()
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ()
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
#define W12_Crossing_cs_rtModel        RT_MODEL_W12_Crossing_cs_T

/* Block signals (default storage) */
typedef struct {
  uint8_T Sensor_e[6062040];           /* '<S9>/Sensor' */
  uint8_T Sensor_i[2073600];           /* '<S5>/Sensor' */
  real_T Clock;                        /* '<S23>/Clock' */
  real_T Fcn;                          /* '<S79>/Fcn' */
  real_T Fcn_j;                        /* '<S89>/Fcn' */
  uint8_T Selector[691200];            /* '<S30>/Selector' */
  uint8_T Selector1[691200];           /* '<S30>/Selector1' */
  uint8_T Selector2[691200];           /* '<S30>/Selector2' */
  uint8_T Selector_n[691200];          /* '<S32>/Selector' */
  uint8_T Selector1_p[691200];         /* '<S32>/Selector1' */
  uint8_T Selector2_i[691200];         /* '<S32>/Selector2' */
  uint8_T Selector_p[2020680];         /* '<S33>/Selector' */
  uint8_T Selector1_l[2020680];        /* '<S33>/Selector1' */
  uint8_T Selector2_i1[2020680];       /* '<S33>/Selector2' */
  uint8_T Selector_nx[691200];         /* '<S31>/Selector' */
  uint8_T Selector1_b[691200];         /* '<S31>/Selector1' */
  uint8_T Selector2_o[691200];         /* '<S31>/Selector2' */
  real32_T Sensor_c[14400];            /* '<S11>/Sensor' */
  real32_T Sensor_f[14400];            /* '<S12>/Sensor' */
  real32_T Sensor_p[14400];            /* '<S13>/Sensor' */
  real32_T Sensor_h[14400];            /* '<S14>/Sensor' */
} B_W12_Crossing_cs_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S79>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_n;/* '<S89>/Discrete-Time Integrator' */
  real_T fighandle;                    /* '<S3>/Camera_1_CM_Display' */
  real_T counter;                      /* '<S3>/Camera_1_CM_Display' */
  real_T fighandle_a;                  /* '<S3>/Camera_tl_CM_Display' */
  real_T counter_p;                    /* '<S3>/Camera_tl_CM_Display' */
  real_T fighandle_f;                  /* '<S3>/HumViewCamera_CM_Display' */
  real_T counter_i;                    /* '<S3>/HumViewCamera_CM_Display' */
  real_T fighandle_h;                  /* '<S3>/Camera_2_CM_Display' */
  real_T counter_pd;                   /* '<S3>/Camera_2_CM_Display' */
  void *sfun_Controller_PWORK[2];      /* '<S7>/sfun_Controller' */
  void *SpeedProfile_PWORK[2];         /* '<S8>/SpeedProfile' */
  void *Path_PWORK[3];                 /* '<S8>/Path' */
  void *Actuator_PWORK[2];             /* '<S1>/Actuator' */
  void *Actuator_PWORK_o[2];           /* '<S21>/Actuator' */
  void *Actuator_PWORK_i[2];           /* '<S25>/Actuator' */
  void *Actuator_PWORK_o3[2];          /* '<S27>/Actuator' */
  void *Actuator_PWORK_c[2];           /* '<S29>/Actuator' */
  void *SpeedProfile_PWORK_j[2];       /* '<S10>/SpeedProfile' */
  void *Path_PWORK_p[3];               /* '<S10>/Path' */
  void *Actuator_PWORK_f[2];           /* '<S2>/Actuator' */
  void *Actuator_PWORK_b[2];           /* '<S22>/Actuator' */
  void *Actuator_PWORK_ig[2];          /* '<S26>/Actuator' */
  void *Actuator_PWORK_m[2];           /* '<S28>/Actuator' */
  void *SpeedProfile_PWORK_b[2];       /* '<S3>/SpeedProfile' */
  void *Path_PWORK_n[3];               /* '<S3>/Path' */
  void *Actuator_PWORK_o3e[2];         /* '<S20>/Actuator' */
  void *sfun_ScenarioEngine_PWORK;     /* '<S23>/sfun_ScenarioEngine' */
  void *sfun_Synchronizer_PWORK[2];    /* '<S24>/sfun_Synchronizer' */
  void *Sensor_PWORK[2];               /* '<S18>/Sensor' */
  void *Sensor_PWORK_n[2];             /* '<S19>/Sensor' */
  void *Sensor_PWORK_k[2];             /* '<S17>/Sensor' */
  void *Sensor_PWORK_c;                /* '<S4>/Sensor' */
  void *Sensor_PWORK_j;                /* '<S6>/Sensor' */
  void *Sensor_PWORK_nn;               /* '<S9>/Sensor' */
  void *Sensor_PWORK_a;                /* '<S5>/Sensor' */
  void *Sensor_PWORK_p;                /* '<S11>/Sensor' */
  void *Sensor_PWORK_l;                /* '<S12>/Sensor' */
  void *Sensor_PWORK_d;                /* '<S13>/Sensor' */
  void *Sensor_PWORK_b;                /* '<S14>/Sensor' */
  void *Sensor_PWORK_bx[2];            /* '<S16>/Sensor' */
  void *sfun_Terminator_PWORK[2];      /* '<S15>/sfun_Terminator' */
  int32_T sfun_Controller_dtSizeInfo[2];/* '<S7>/sfun_Controller' */
  int32_T sfun_Controller_dtBusInfo[2];/* '<S7>/sfun_Controller' */
  int32_T SpeedProfile_dtSizeInfo[2];  /* '<S8>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo[6];   /* '<S8>/SpeedProfile' */
  int32_T Path_dtSizeInfo[3];          /* '<S8>/Path' */
  int32_T Path_dtBusInfo[36];          /* '<S8>/Path' */
  int32_T Actuator_dtSizeInfo[3];      /* '<S1>/Actuator' */
  int32_T Actuator_dtBusInfo[4];       /* '<S1>/Actuator' */
  int32_T Actuator_dtSizeInfo_d[2];    /* '<S21>/Actuator' */
  int32_T Actuator_dtBusInfo_l[30];    /* '<S21>/Actuator' */
  int32_T Actuator_dtSizeInfo_h[2];    /* '<S25>/Actuator' */
  int32_T Actuator_dtBusInfo_c[8];     /* '<S25>/Actuator' */
  int32_T Actuator_dtSizeInfo_n[2];    /* '<S27>/Actuator' */
  int32_T Actuator_dtBusInfo_f[8];     /* '<S27>/Actuator' */
  int32_T Actuator_dtSizeInfo_e[2];    /* '<S29>/Actuator' */
  int32_T Actuator_dtBusInfo_k[8];     /* '<S29>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_c[2];/* '<S10>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_o[6]; /* '<S10>/SpeedProfile' */
  int32_T Path_dtSizeInfo_d[3];        /* '<S10>/Path' */
  int32_T Path_dtBusInfo_l[36];        /* '<S10>/Path' */
  int32_T Actuator_dtSizeInfo_k[3];    /* '<S2>/Actuator' */
  int32_T Actuator_dtBusInfo_o[4];     /* '<S2>/Actuator' */
  int32_T Actuator_dtSizeInfo_l[2];    /* '<S22>/Actuator' */
  int32_T Actuator_dtBusInfo_i[30];    /* '<S22>/Actuator' */
  int32_T Actuator_dtSizeInfo_lt[2];   /* '<S26>/Actuator' */
  int32_T Actuator_dtBusInfo_l2[8];    /* '<S26>/Actuator' */
  int32_T Actuator_dtSizeInfo_b[2];    /* '<S28>/Actuator' */
  int32_T Actuator_dtBusInfo_lj[8];    /* '<S28>/Actuator' */
  int32_T SpeedProfile_dtSizeInfo_a[2];/* '<S3>/SpeedProfile' */
  int32_T SpeedProfile_dtBusInfo_ok[6];/* '<S3>/SpeedProfile' */
  int32_T Path_dtSizeInfo_p[3];        /* '<S3>/Path' */
  int32_T Path_dtBusInfo_b[36];        /* '<S3>/Path' */
  int32_T Actuator_dtSizeInfo_e2[2];   /* '<S20>/Actuator' */
  int32_T Actuator_dtBusInfo_ku[30];   /* '<S20>/Actuator' */
  int32_T sfun_Synchronizer_dtSizeInfo[2];/* '<S24>/sfun_Synchronizer' */
  int32_T sfun_Synchronizer_dtBusInfo[4];/* '<S24>/sfun_Synchronizer' */
  int32_T Sensor_dtSizeInfo[2];        /* '<S18>/Sensor' */
  int32_T Sensor_dtBusInfo[22];        /* '<S18>/Sensor' */
  int32_T Sensor_dtSizeInfo_f[2];      /* '<S19>/Sensor' */
  int32_T Sensor_dtBusInfo_d[22];      /* '<S19>/Sensor' */
  int32_T Sensor_dtSizeInfo_j[2];      /* '<S17>/Sensor' */
  int32_T Sensor_dtBusInfo_de[22];     /* '<S17>/Sensor' */
  int32_T Sensor_dtSizeInfo_m[6];      /* '<S16>/Sensor' */
  int32_T Sensor_dtBusInfo_c[34];      /* '<S16>/Sensor' */
  int32_T sfun_Terminator_dtSizeInfo[2];/* '<S15>/sfun_Terminator' */
  int32_T sfun_Terminator_dtBusInfo[2];/* '<S15>/sfun_Terminator' */
} DW_W12_Crossing_cs_T;

/* Invariant block signals (default storage) */
typedef struct {
  const uint8_T R;                     /* '<S75>/Data Type Conversion' */
  const uint8_T G;                     /* '<S75>/Data Type Conversion1' */
  const uint8_T B;                     /* '<S75>/Data Type Conversion2' */
  const uint8_T R_o;                   /* '<S76>/Data Type Conversion' */
  const uint8_T G_n;                   /* '<S76>/Data Type Conversion1' */
  const uint8_T B_c;                   /* '<S76>/Data Type Conversion2' */
  const uint8_T R_k;                   /* '<S77>/Data Type Conversion' */
  const uint8_T G_p;                   /* '<S77>/Data Type Conversion1' */
  const uint8_T B_m;                   /* '<S77>/Data Type Conversion2' */
  const uint8_T R_c;                   /* '<S86>/Data Type Conversion' */
  const uint8_T G_b;                   /* '<S86>/Data Type Conversion1' */
  const uint8_T B_d;                   /* '<S86>/Data Type Conversion2' */
  const uint8_T R_b;                   /* '<S87>/Data Type Conversion' */
  const uint8_T G_h;                   /* '<S87>/Data Type Conversion1' */
  const uint8_T B_my;                  /* '<S87>/Data Type Conversion2' */
} ConstB_W12_Crossing_cs_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S25>/Actuator'
   *   '<S26>/Actuator'
   *   '<S29>/Actuator'
   */
  uint32_T pooled16[5];

  /* Pooled Parameter (Expression: tabledata)
   * Referenced by:
   *   '<S27>/Actuator'
   *   '<S28>/Actuator'
   */
  uint32_T pooled17[5];

  /* Expression: SParameter1
   * Referenced by: '<S7>/sfun_Controller'
   */
  uint8_T sfun_Controller_p1[17];

  /* Expression: SParameter2
   * Referenced by: '<S7>/sfun_Controller'
   */
  uint8_T sfun_Controller_p2[60];

  /* Expression: SParameter3
   * Referenced by: '<S7>/sfun_Controller'
   */
  uint8_T sfun_Controller_p3;

  /* Expression: SParameter9
   * Referenced by: '<S7>/sfun_Controller'
   */
  uint8_T sfun_Controller_p9[7];

  /* Expression: SParameter10
   * Referenced by: '<S7>/sfun_Controller'
   */
  uint8_T sfun_Controller_p10[8];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S25>/Actuator'
   *   '<S26>/Actuator'
   */
  uint8_T pooled19[43];

  /* Pooled Parameter (Expression: mbxruntime.parameters.convert(WorldModelSubPath))
   * Referenced by:
   *   '<S27>/Actuator'
   *   '<S28>/Actuator'
   */
  uint8_T pooled20[38];

  /* Expression: mbxruntime.parameters.convert(WorldModelSubPath)
   * Referenced by: '<S29>/Actuator'
   */
  uint8_T Actuator_p2[43];
} ConstP_W12_Crossing_cs_T;

/* Backward compatible GRT Identifiers */
#define rtB                            W12_Crossing_cs_B
#define BlockIO                        B_W12_Crossing_cs_T
#define rtP                            W12_Crossing_cs_P
#define Parameters                     P_W12_Crossing_cs_T
#define rtDWork                        W12_Crossing_cs_DW
#define D_Work                         DW_W12_Crossing_cs_T
#define tConstBlockIOType              ConstB_W12_Crossing_cs_T
#define rtC                            W12_Crossing_cs_ConstB
#define ConstParam                     ConstP_W12_Crossing_cs_T
#define rtcP                           W12_Crossing_cs_ConstP

/* Parameters (default storage) */
struct P_W12_Crossing_cs_T_ {
  real_T W12_Crossing_cs_1e72c7e30b0890ad;
                                   /* Variable: W12_Crossing_cs_1e72c7e30b0890ad
                                    * Referenced by: '<S10>/SpeedProfile'
                                    */
  real_T W12_Crossing_cs_28e1fdd0f30fb13b;
                                   /* Variable: W12_Crossing_cs_28e1fdd0f30fb13b
                                    * Referenced by: '<S8>/SpeedProfile'
                                    */
  real_T W12_Crossing_cs_BMW_X5_SUV_1_Path_pathUniqueID;
                     /* Variable: W12_Crossing_cs_BMW_X5_SUV_1_Path_pathUniqueID
                      * Referenced by: '<S3>/Path'
                      */
  real_T W12_Crossing_cs_BMW_X5_SUV_1_SpeedProfile_speedProfileUniqueID;
     /* Variable: W12_Crossing_cs_BMW_X5_SUV_1_SpeedProfile_speedProfileUniqueID
      * Referenced by: '<S3>/SpeedProfile'
      */
  real_T W12_Crossing_cs_Female_Regular_1_Path_pathUniqueID;
                 /* Variable: W12_Crossing_cs_Female_Regular_1_Path_pathUniqueID
                  * Referenced by: '<S8>/Path'
                  */
  real_T W12_Crossing_cs_Male_Regular_1_Path_pathUniqueID;
                   /* Variable: W12_Crossing_cs_Male_Regular_1_Path_pathUniqueID
                    * Referenced by: '<S10>/Path'
                    */
};

/* Real-time Model Data Structure */
struct tag_RTM_W12_Crossing_cs_T {
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
extern P_W12_Crossing_cs_T W12_Crossing_cs_P;

/* Block signals (default storage) */
extern B_W12_Crossing_cs_T W12_Crossing_cs_B;

/* Block states (default storage) */
extern DW_W12_Crossing_cs_T W12_Crossing_cs_DW;
extern const ConstB_W12_Crossing_cs_T W12_Crossing_cs_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_W12_Crossing_cs_T W12_Crossing_cs_ConstP;

/*====================*
 * External functions *
 *====================*/
extern W12_Crossing_cs_rtModel *W12_Crossing_cs(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

/* Real-time Model object */
extern RT_MODEL_W12_Crossing_cs_T *const W12_Crossing_cs_M;

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
 * '<Root>' : 'W12_Crossing_cs'
 * '<S1>'   : 'W12_Crossing_cs/ANIM_Female_Regular_1'
 * '<S2>'   : 'W12_Crossing_cs/ANIM_Male_Regular_1'
 * '<S3>'   : 'W12_Crossing_cs/BMW_X5_SUV_1'
 * '<S4>'   : 'W12_Crossing_cs/Camera_1'
 * '<S5>'   : 'W12_Crossing_cs/Camera_2'
 * '<S6>'   : 'W12_Crossing_cs/Camera_tl'
 * '<S7>'   : 'W12_Crossing_cs/Controller'
 * '<S8>'   : 'W12_Crossing_cs/Female_Regular_1'
 * '<S9>'   : 'W12_Crossing_cs/HumViewCamera'
 * '<S10>'  : 'W12_Crossing_cs/Male_Regular_1'
 * '<S11>'  : 'W12_Crossing_cs/PointCloudSensor_1'
 * '<S12>'  : 'W12_Crossing_cs/PointCloudSensor_2'
 * '<S13>'  : 'W12_Crossing_cs/PointCloudSensor_3'
 * '<S14>'  : 'W12_Crossing_cs/PointCloudSensor_4'
 * '<S15>'  : 'W12_Crossing_cs/PreScanTerminator'
 * '<S16>'  : 'W12_Crossing_cs/Radar_1'
 * '<S17>'  : 'W12_Crossing_cs/SELF_BMW_X5_SUV_1'
 * '<S18>'  : 'W12_Crossing_cs/SELF_Female_Regular_1'
 * '<S19>'  : 'W12_Crossing_cs/SELF_Male_Regular_1'
 * '<S20>'  : 'W12_Crossing_cs/STATE_BMW_X5_SUV_1_bus'
 * '<S21>'  : 'W12_Crossing_cs/STATE_Female_Regular_1_bus'
 * '<S22>'  : 'W12_Crossing_cs/STATE_Male_Regular_1_bus'
 * '<S23>'  : 'W12_Crossing_cs/ScenarioEngine'
 * '<S24>'  : 'W12_Crossing_cs/Synchronizer'
 * '<S25>'  : 'W12_Crossing_cs/VISUColorRegion_Lower_Body_Female_Regular_1'
 * '<S26>'  : 'W12_Crossing_cs/VISUColorRegion_Lower_Body_Male_Regular_1'
 * '<S27>'  : 'W12_Crossing_cs/VISUColorRegion_Shoes_Female_Regular_1'
 * '<S28>'  : 'W12_Crossing_cs/VISUColorRegion_Shoes_Male_Regular_1'
 * '<S29>'  : 'W12_Crossing_cs/VISUColorRegion_Upper_Body_Female_Regular_1'
 * '<S30>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Camera_1_CM_Demux'
 * '<S31>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Camera_2_CM_Demux'
 * '<S32>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Camera_tl_CM_Demux'
 * '<S33>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/HumViewCamera_CM_Demux'
 * '<S34>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_1_Angles_Demux'
 * '<S35>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_1_Intensity_Demux'
 * '<S36>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_1_Range_Demux'
 * '<S37>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_2_Angles_Demux'
 * '<S38>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_2_Intensity_Demux'
 * '<S39>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_2_Range_Demux'
 * '<S40>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_3_Angles_Demux'
 * '<S41>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_3_Intensity_Demux'
 * '<S42>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_3_Range_Demux'
 * '<S43>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_4_Angles_Demux'
 * '<S44>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_4_Intensity_Demux'
 * '<S45>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/PointCloudSensor_4_Range_Demux'
 * '<S46>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux'
 * '<S47>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/SELF_Demux'
 * '<S48>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion'
 * '<S49>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Cnvert1'
 * '<S50>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals'
 * '<S51>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals1'
 * '<S52>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals10'
 * '<S53>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals11'
 * '<S54>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals12'
 * '<S55>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals13'
 * '<S56>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals14'
 * '<S57>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals15'
 * '<S58>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals16'
 * '<S59>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals17'
 * '<S60>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals18'
 * '<S61>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals2'
 * '<S62>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals3'
 * '<S63>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals4'
 * '<S64>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals5'
 * '<S65>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals6'
 * '<S66>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals7'
 * '<S67>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals8'
 * '<S68>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Signal2ArrayOfSignals9'
 * '<S69>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Cnvert1/Degrees to Radians'
 * '<S70>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/Radar_1_Demux/ScannerSensorLegacyBusConversion/Cnvert1/Degrees to Radians1'
 * '<S71>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/SELF_Demux/compas converter'
 * '<S72>'  : 'W12_Crossing_cs/BMW_X5_SUV_1/SELF_Demux/compas converter/cart2compas'
 * '<S73>'  : 'W12_Crossing_cs/Female_Regular_1/Animation'
 * '<S74>'  : 'W12_Crossing_cs/Female_Regular_1/SELF_Demux'
 * '<S75>'  : 'W12_Crossing_cs/Female_Regular_1/VISUColorRegion_Lower_Body_Mux'
 * '<S76>'  : 'W12_Crossing_cs/Female_Regular_1/VISUColorRegion_Shoes_Mux'
 * '<S77>'  : 'W12_Crossing_cs/Female_Regular_1/VISUColorRegion_Upper_Body_Mux'
 * '<S78>'  : 'W12_Crossing_cs/Female_Regular_1/Animation/animation mode'
 * '<S79>'  : 'W12_Crossing_cs/Female_Regular_1/Animation/elapsed track'
 * '<S80>'  : 'W12_Crossing_cs/Female_Regular_1/Animation/animation mode/Running'
 * '<S81>'  : 'W12_Crossing_cs/Female_Regular_1/Animation/animation mode/Walking'
 * '<S82>'  : 'W12_Crossing_cs/Female_Regular_1/SELF_Demux/compas converter'
 * '<S83>'  : 'W12_Crossing_cs/Female_Regular_1/SELF_Demux/compas converter/cart2compas'
 * '<S84>'  : 'W12_Crossing_cs/Male_Regular_1/Animation'
 * '<S85>'  : 'W12_Crossing_cs/Male_Regular_1/SELF_Demux'
 * '<S86>'  : 'W12_Crossing_cs/Male_Regular_1/VISUColorRegion_Lower_Body_Mux'
 * '<S87>'  : 'W12_Crossing_cs/Male_Regular_1/VISUColorRegion_Shoes_Mux'
 * '<S88>'  : 'W12_Crossing_cs/Male_Regular_1/Animation/animation mode'
 * '<S89>'  : 'W12_Crossing_cs/Male_Regular_1/Animation/elapsed track'
 * '<S90>'  : 'W12_Crossing_cs/Male_Regular_1/Animation/animation mode/Running'
 * '<S91>'  : 'W12_Crossing_cs/Male_Regular_1/Animation/animation mode/Walking'
 * '<S92>'  : 'W12_Crossing_cs/Male_Regular_1/SELF_Demux/compas converter'
 * '<S93>'  : 'W12_Crossing_cs/Male_Regular_1/SELF_Demux/compas converter/cart2compas'
 */
#endif                                 /* RTW_HEADER_W12_Crossing_cs_h_ */
