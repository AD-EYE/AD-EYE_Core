#include "Emulate_Prescan_2019a.h"
#include "Emulate_Prescan_2019a_prescan.h"
#include "rtwtypes.h"
#include "rtw_modelmap.h"
#include "prescan_api_error.h"
#include "prescan_api_experiment.h"
#include "prescan_internal_tunabledata.h"
#include "prescan_internal_testautomation.h"
#include <string.h>

void* prescan_CAPI_get_address_by_name(rtwCAPI_ModelMappingInfo* capiMap, const
  char_T* tuningVariable)
{
  uint_T nModelParams = rtwCAPI_GetNumModelParameters(capiMap);
  const rtwCAPI_ModelParameters* modelParams = rtwCAPI_GetModelParameters
    (capiMap);
  uint_T idx;
  uint_T addrIdx;
  const char_T* paramName;
  for (idx=0; idx < nModelParams; idx++) {
    paramName = rtwCAPI_GetModelParameterName(modelParams, idx);
    if (strcmp(paramName, tuningVariable) == 0) {
      void** dataAddrMap = rtwCAPI_GetDataAddressMap(capiMap);
      addrIdx = rtwCAPI_GetModelParameterAddrIdx(modelParams, idx);
      return (void *) rtwCAPI_GetDataAddress(dataAddrMap, addrIdx);
    }
  }

  return 0;
}

void Emulate_Prescan_2019a_prescan_parameters(RT_MODEL_Emulate_Prescan_2019_T *
  const Emulate_Prescan_2019a_M)
{
  rtwCAPI_ModelMappingInfo* capiMap = &(rtmGetDataMapInfo
    (Emulate_Prescan_2019a_M).mmi);
  char csName[256], experimentFileName[256];
  size_t csNameLen;
  prescan_object_t* experimentHandle;
  prescan_object_t* tunableDataHandle;
  const char pbExt[] = ".pb";
  prescan_bool_t isRegenerationNeeded;
  prescan_bool_t isApiSuccessful;
  strcpy(csName,"Emulate_Prescan_2019a");
  csNameLen = strlen(csName);
  csName[csNameLen-3]= '\0';
  strcpy(experimentFileName, strcat(csName,pbExt));
  if (PRESCAN_SUCCESS != prescan_experiment_create_from_file(experimentFileName,
       &experimentHandle)) {
    printf("ERROR: %s\nAborting simulation.\n",
           prescan_error_get_last_error_message());
    exit(1);
  }

  /* Check consistency of tunable data */
  if (PRESCAN_SUCCESS != prescan_tunabledata_create(experimentHandle,
       &tunableDataHandle)) {
    printf("ERROR: %s\nAborting simulation.\n",
           prescan_error_get_last_error_message());
    prescan_experiment_destroy(&experimentHandle);
    exit(1);
  }

  isApiSuccessful = prescan_tunabledata_is_regeneration_needed(tunableDataHandle,
    &isRegenerationNeeded);
  if (PRESCAN_SUCCESS != isApiSuccessful || isRegenerationNeeded) {
    printf("ERROR: %s\nAborting simulation.\n",
           prescan_error_get_last_error_message());
    prescan_tunabledata_destroy(&tunableDataHandle);
    prescan_experiment_destroy(&experimentHandle);
    exit(1);
  }

  prescan_tunabledata_destroy(&tunableDataHandle);

  /* Reset errors before adding tunable data */
  prescan_error_last_error_reset();
  prescan_experiment_destroy(&experimentHandle);

  {
    const char* errorMessage = prescan_error_get_last_error_message();
    if (errorMessage) {
      printf("%s\n", errorMessage);
      prescan_error_last_error_reset();
    }
  }
}
