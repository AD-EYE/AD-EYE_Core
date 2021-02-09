/*
 * W01_Base_Map_cs_capi.c
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

#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "W01_Base_Map_cs_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "W01_Base_Map_cs.h"
#include "W01_Base_Map_cs_capi.h"
#include "W01_Base_Map_cs_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Individual block tuning is not valid when inline parameters is *
 * selected. An empty map is produced to provide a consistent     *
 * interface independent  of inlining parameters.                 *
 */
static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Tunable variable parameters */
static const rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, TARGET_STRING("W01_Base_Map_cs_328ec7e3a8cd5b54"), 0, 0, 0 },

  { 1, TARGET_STRING("W01_Base_Map_cs_423c72fa17799c7f"), 0, 0, 0 },

  { 2, TARGET_STRING("W01_Base_Map_cs_514c2dea2cdbe680"), 0, 0, 0 },

  { 3, TARGET_STRING("W01_Base_Map_cs_51d6e6e467bedba1"), 0, 0, 0 },

  { 4, TARGET_STRING("W01_Base_Map_cs_563ebd29d1fd6c09"), 0, 0, 0 },

  { 5, TARGET_STRING("W01_Base_Map_cs_57ea59d0358dab77"), 0, 0, 0 },

  { 6, TARGET_STRING("W01_Base_Map_cs_669d1acb174df2b9"), 0, 0, 0 },

  { 7, TARGET_STRING("W01_Base_Map_cs_774a522413284ef7"), 0, 0, 0 },

  { 8, TARGET_STRING("W01_Base_Map_cs_9538d35a279fbe4e"), 0, 0, 0 },

  { 9, TARGET_STRING("W01_Base_Map_cs_9f504bb84aebc2fd"), 0, 0, 0 },

  { 10, TARGET_STRING("W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID"), 0, 0,
    0 },

  { 11, TARGET_STRING("W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID"), 0,
    0, 0 },

  { 12, TARGET_STRING("W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID"), 0,
    0, 0 },

  { 13, TARGET_STRING("W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID"),
    0, 0, 0 },

  { 14, TARGET_STRING("W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID"),
    0, 0, 0 },

  { 15, TARGET_STRING("W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID"), 0,
    0, 0 },

  { 16, TARGET_STRING("W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID"), 0,
    0, 0 },

  { 17, TARGET_STRING("W01_Base_Map_cs_a242ed7539861165"), 0, 0, 0 },

  { 18, TARGET_STRING("W01_Base_Map_cs_ae41b72d7e14f81d"), 0, 0, 0 },

  { 19, TARGET_STRING("W01_Base_Map_cs_b5931a786e299506"), 0, 0, 0 },

  { 20, TARGET_STRING("W01_Base_Map_cs_b7f45a070fa6e639"), 0, 0, 0 },

  { 21, TARGET_STRING("W01_Base_Map_cs_c02beb48492dde12"), 0, 0, 0 },

  { 22, TARGET_STRING("W01_Base_Map_cs_c75b75e9f6b035bf"), 0, 0, 0 },

  { 23, TARGET_STRING("W01_Base_Map_cs_cf83ac8e8b053cbf"), 0, 0, 0 },

  { 24, TARGET_STRING("W01_Base_Map_cs_d4423fcf1c0d6fc4"), 0, 0, 0 },

  { 25, TARGET_STRING("W01_Base_Map_cs_df133aa86d9852fe"), 0, 0, 0 },

  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &W01_Base_Map_cs_P.W01_Base_Map_cs_328ec7e3a8cd5b54,/* 0: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_423c72fa17799c7f,/* 1: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_514c2dea2cdbe680,/* 2: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_51d6e6e467bedba1,/* 3: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_563ebd29d1fd6c09,/* 4: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_57ea59d0358dab77,/* 5: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_669d1acb174df2b9,/* 6: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_774a522413284ef7,/* 7: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_9538d35a279fbe4e,/* 8: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_9f504bb84aebc2fd,/* 9: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID,/* 10: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID,/* 11: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID,/* 12: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID,/* 13: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID,/* 14: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID,/* 15: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID,/* 16: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_a242ed7539861165,/* 17: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_ae41b72d7e14f81d,/* 18: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_b5931a786e299506,/* 19: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_b7f45a070fa6e639,/* 20: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_c02beb48492dde12,/* 21: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_c75b75e9f6b035bf,/* 22: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_cf83ac8e8b053cbf,/* 23: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_d4423fcf1c0d6fc4,/* 24: Model Parameter */
  &W01_Base_Map_cs_P.W01_Base_Map_cs_df133aa86d9852fe,/* 25: Model Parameter */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer */
  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1                                    /* 1 */
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  {
    (NULL), (NULL), 0, 0
  }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { (NULL), 0,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 0,
    rtModelParameters, 26 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 4001907819U,
    2311700194U,
    1692253392U,
    1012238352U },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  W01_Base_Map_cs_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void W01_Base_Map_cs_InitializeDataMapInfo(void)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(W01_Base_Map_cs_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(W01_Base_Map_cs_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(W01_Base_Map_cs_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(W01_Base_Map_cs_M->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(W01_Base_Map_cs_M->DataMapInfo.mmi,
    rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(W01_Base_Map_cs_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(W01_Base_Map_cs_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(W01_Base_Map_cs_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C" {

#endif

  void W01_Base_Map_cs_host_InitializeDataMapInfo
    (W01_Base_Map_cs_host_DataMapInfo_T *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* EOF: W01_Base_Map_cs_capi.c */
