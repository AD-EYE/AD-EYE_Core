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
#include "ExperimentIL2209_With_Rebuild_2_cs_capi_host.h"
#define ARRAY_SIZE(x)                  ( sizeof(x) / sizeof((x)[0]) )
#define FOUND                          (1)
#define NOT_FOUND                      (0)

const char *tuningVariableNamesInRegistry[] = {
  "ExperimentIL2209_With_Rebuild_2_cs_0c060923bf5c447f",
  "ExperimentIL2209_With_Rebuild_2_cs_a90dd231a019fe8f",
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
  ExperimentIL2209_With_Rebuild_2_cs_host_DataMapInfo_T dataMap;
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
  ExperimentIL2209_With_Rebuild_2_cs_host_InitializeDataMapInfo(&dataMap, 0);
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
