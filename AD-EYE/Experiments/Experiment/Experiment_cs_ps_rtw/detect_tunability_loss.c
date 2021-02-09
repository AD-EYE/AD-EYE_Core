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
#include "Experiment_cs_capi_host.h"
#define ARRAY_SIZE(x)                  ( sizeof(x) / sizeof((x)[0]) )
#define FOUND                          (1)
#define NOT_FOUND                      (0)

const char *tuningVariableNamesInRegistry[] = {
  "Experiment_cs_e726c63043403dc7",
  "Experiment_cs_f4cae83923a86e0b",
  "Experiment_cs_e1d584482631291c",
  "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0",
  "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0",
  "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0",
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
  Experiment_cs_host_DataMapInfo_T dataMap;
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
  Experiment_cs_host_InitializeDataMapInfo(&dataMap, 0);
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
