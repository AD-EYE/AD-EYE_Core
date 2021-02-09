#include "Experiment_cs.h"
#include "Experiment_cs_prescan.h"
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

void Experiment_cs_prescan_parameters(RT_MODEL_Experiment_cs_T *const
  Experiment_cs_M)
{
  rtwCAPI_ModelMappingInfo* capiMap = &(rtmGetDataMapInfo(Experiment_cs_M).mmi);
  char csName[256], experimentFileName[256];
  size_t csNameLen;
  prescan_object_t* experimentHandle;
  prescan_object_t* tunableDataHandle;
  const char pbExt[] = ".pb";
  prescan_bool_t isRegenerationNeeded;
  prescan_bool_t isApiSuccessful;
  strcpy(csName,"Experiment_cs");
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

  /* 0 : registry tuning variable = "Experiment_cs_e726c63043403dc7" type="real_T" size=1.0 */
  {
    real_T* Experiment_cs_e726c63043403dc7 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap, "Experiment_cs_e726c63043403dc7");
    if (Experiment_cs_e726c63043403dc7 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <Experiment_cs_e726c63043403dc7>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/orientation/pitch";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *Experiment_cs_e726c63043403dc7 = (real_T)(p1 * 57.2958);
    }
  }

  /* 1 : registry tuning variable = "Experiment_cs_f4cae83923a86e0b" type="real_T" size=1.0 */
  {
    real_T* Experiment_cs_f4cae83923a86e0b = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap, "Experiment_cs_f4cae83923a86e0b");
    if (Experiment_cs_f4cae83923a86e0b == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <Experiment_cs_f4cae83923a86e0b>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/orientation/roll";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *Experiment_cs_f4cae83923a86e0b = (real_T)(p1 * 57.2958);
    }
  }

  /* 2 : registry tuning variable = "Experiment_cs_e1d584482631291c" type="real_T" size=1.0 */
  {
    real_T* Experiment_cs_e1d584482631291c = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap, "Experiment_cs_e1d584482631291c");
    if (Experiment_cs_e1d584482631291c == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <Experiment_cs_e1d584482631291c>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/orientation/yaw";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *Experiment_cs_e1d584482631291c = (real_T)(p1 * 57.2958);
    }
  }

  /* 3 : registry tuning variable = "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0" type="real_T" size=1.0 */
  {
    real_T* Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0 =
      (real_T*) prescan_CAPI_get_address_by_name(capiMap,
      "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0");
    if (Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0 == NULL)
    {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0>.\n");
    } else {
      double p1 = 51.185694217681885;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/position/x";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:0/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:0/pose/orientation/pitch";
      double p4 = 0.0;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:0/pose/orientation/yaw";
      double p5 = 1.690000057220459;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:0/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:0/cogOffset/y";
      double p7 = 0.68999999761581421;
      const char* p7_modelName = "pimp/worldmodel";
      const char* p7_modelPath = "object:0/cogOffset/z";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      prescan_experiment_get_double(experimentHandle, p2_modelName, p2_modelPath,
        &p2);
      prescan_experiment_get_double(experimentHandle, p3_modelName, p3_modelPath,
        &p3);
      prescan_experiment_get_double(experimentHandle, p4_modelName, p4_modelPath,
        &p4);
      prescan_experiment_get_double(experimentHandle, p5_modelName, p5_modelPath,
        &p5);
      prescan_experiment_get_double(experimentHandle, p6_modelName, p6_modelPath,
        &p6);
      prescan_experiment_get_double(experimentHandle, p7_modelName, p7_modelPath,
        &p7);
      *Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_x0 = (real_T)
        (p1 + prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 0));
    }
  }

  /* 4 : registry tuning variable = "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0" type="real_T" size=1.0 */
  {
    real_T* Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0 =
      (real_T*) prescan_CAPI_get_address_by_name(capiMap,
      "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0");
    if (Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0 == NULL)
    {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0>.\n");
    } else {
      double p1 = 69.944343566894531;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/position/y";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:0/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:0/pose/orientation/pitch";
      double p4 = 0.0;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:0/pose/orientation/yaw";
      double p5 = 1.690000057220459;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:0/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:0/cogOffset/y";
      double p7 = 0.68999999761581421;
      const char* p7_modelName = "pimp/worldmodel";
      const char* p7_modelPath = "object:0/cogOffset/z";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      prescan_experiment_get_double(experimentHandle, p2_modelName, p2_modelPath,
        &p2);
      prescan_experiment_get_double(experimentHandle, p3_modelName, p3_modelPath,
        &p3);
      prescan_experiment_get_double(experimentHandle, p4_modelName, p4_modelPath,
        &p4);
      prescan_experiment_get_double(experimentHandle, p5_modelName, p5_modelPath,
        &p5);
      prescan_experiment_get_double(experimentHandle, p6_modelName, p6_modelPath,
        &p6);
      prescan_experiment_get_double(experimentHandle, p7_modelName, p7_modelPath,
        &p7);
      *Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_y0 = (real_T)
        (p1 + prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 1));
    }
  }

  /* 5 : registry tuning variable = "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0" type="real_T" size=1.0 */
  {
    real_T* Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0 =
      (real_T*) prescan_CAPI_get_address_by_name(capiMap,
      "Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0");
    if (Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0 == NULL)
    {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/position/z";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:0/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:0/pose/orientation/pitch";
      double p4 = 0.0;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:0/pose/orientation/yaw";
      double p5 = 1.690000057220459;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:0/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:0/cogOffset/y";
      double p7 = 0.68999999761581421;
      const char* p7_modelName = "pimp/worldmodel";
      const char* p7_modelPath = "object:0/cogOffset/z";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      prescan_experiment_get_double(experimentHandle, p2_modelName, p2_modelPath,
        &p2);
      prescan_experiment_get_double(experimentHandle, p3_modelName, p3_modelPath,
        &p3);
      prescan_experiment_get_double(experimentHandle, p4_modelName, p4_modelPath,
        &p4);
      prescan_experiment_get_double(experimentHandle, p5_modelName, p5_modelPath,
        &p5);
      prescan_experiment_get_double(experimentHandle, p6_modelName, p6_modelPath,
        &p6);
      prescan_experiment_get_double(experimentHandle, p7_modelName, p7_modelPath,
        &p7);
      *Experiment_cs_BMW_X5_SUV_1_Dynamics_Empty_STATE_BMW_X5_SUV_1_z0 = (real_T)
        (p1 + prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 2));
    }
  }

  prescan_experiment_destroy(&experimentHandle);

  {
    const char* errorMessage = prescan_error_get_last_error_message();
    if (errorMessage) {
      printf("%s\n", errorMessage);
      prescan_error_last_error_reset();
    }
  }
}
