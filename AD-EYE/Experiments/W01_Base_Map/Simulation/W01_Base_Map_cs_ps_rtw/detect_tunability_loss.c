/*
 * This file is compiled into a mex function that throws a warning when loss of tunability
 * is detected.
 */

/* Avoid empty translation unit warning (ANSI C). */
typedef int dummy_t;

#ifdef HOST_CAPI_BUILD
#include "mex.h"
#include "rtwtypes.h"
#include "rtw_modelmap.h"
#include "W01_Base_Map_cs_capi_host.h"
#define ARRAY_SIZE(x)                  ( sizeof(x) / sizeof((x)[0]) )
#define FOUND                          (1)
#define NOT_FOUND                      (0)

const char *tuningVariableNamesInRegistry[] = {
  "W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID",
  "W01_Base_Map_cs_b5931a786e299506",
  "W01_Base_Map_cs_9f504bb84aebc2fd",
  "W01_Base_Map_cs_9538d35a279fbe4e",
  "W01_Base_Map_cs_a242ed7539861165",
  "W01_Base_Map_cs_b7f45a070fa6e639",
  "W01_Base_Map_cs_563ebd29d1fd6c09",
  "W01_Base_Map_cs_d4423fcf1c0d6fc4",
  "W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID",
  "W01_Base_Map_cs_514c2dea2cdbe680",
  "W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID",
  "W01_Base_Map_cs_51d6e6e467bedba1",
  "W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID",
  "W01_Base_Map_cs_328ec7e3a8cd5b54",
  "W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID",
  "W01_Base_Map_cs_cf83ac8e8b053cbf",
  "W01_Base_Map_cs_c75b75e9f6b035bf",
  "W01_Base_Map_cs_423c72fa17799c7f",
  "W01_Base_Map_cs_774a522413284ef7",
  "W01_Base_Map_cs_df133aa86d9852fe",
  "W01_Base_Map_cs_ae41b72d7e14f81d",
  "W01_Base_Map_cs_669d1acb174df2b9",
  "W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID",
  "W01_Base_Map_cs_c02beb48492dde12",
  "W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID",
  "W01_Base_Map_cs_57ea59d0358dab77",
  0                                    /* Declare at least one array element. */
};

int_T prescan_CAPI_find(rtwCAPI_ModelMappingInfo* capiMap, const char_T
  * tuningVariable)
{
  uint_T nModelParams = rtwCAPI_GetNumModelParameters(capiMap);
  const rtwCAPI_ModelParameters* modelParams = rtwCAPI_GetModelParameters
    (capiMap);
  uint_T idx;
  const char_T* paramName;
  for (idx=0; idx < nModelParams; idx++) {
    paramName = rtwCAPI_GetModelParameterName(modelParams, idx);
    if (strcmp(paramName,tuningVariable) == 0) {
      return FOUND;
    }
  }

  return NOT_FOUND;
}

void mexFunction(int numberOfOutputs, mxArray *outputs[], int numberOfInputs,
                 const mxArray *inputs[])
{
  rtwCAPI_ModelMappingInfo* capiMap = NULL;
  W01_Base_Map_cs_host_DataMapInfo_T dataMap;
  uint_T warningCount = 0;
  uint_T idx = 0;

  /* Check for proper number of arguments. */
  if (numberOfInputs != 0) {
    mexErrMsgIdAndTxt( "Prescan:TestAutomation", "Too many input arguments.");
  }

  if (numberOfOutputs > 1) {
    mexErrMsgIdAndTxt( "Prescan:TestAutomation", "Too many expected outputs.");
  }

  /* Initialize CAPI. */
  W01_Base_Map_cs_host_InitializeDataMapInfo(&dataMap, 0);
  capiMap = &dataMap.mmi;
  for (idx = 0; idx < ARRAY_SIZE(tuningVariableNamesInRegistry) - 1; idx++) {
    if (prescan_CAPI_find(capiMap, tuningVariableNamesInRegistry[idx]) ==
        NOT_FOUND) {
      mexPrintf("#### Warning: Loss of tunability detected for variable: <%s>.\n",
                tuningVariableNamesInRegistry[idx]);
      warningCount++;
    }
  }

  outputs[0] = mxCreateDoubleScalar(warningCount);
}

#endif
