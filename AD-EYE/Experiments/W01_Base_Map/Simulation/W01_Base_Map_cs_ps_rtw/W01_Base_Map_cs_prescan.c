#include "W01_Base_Map_cs.h"
#include "W01_Base_Map_cs_prescan.h"
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

void W01_Base_Map_cs_prescan_parameters(RT_MODEL_W01_Base_Map_cs_T *const
  W01_Base_Map_cs_M)
{
  rtwCAPI_ModelMappingInfo* capiMap = &(rtmGetDataMapInfo(W01_Base_Map_cs_M).mmi);
  char csName[256], experimentFileName[256];
  size_t csNameLen;
  prescan_object_t* experimentHandle;
  prescan_object_t* tunableDataHandle;
  const char pbExt[] = ".pb";
  prescan_bool_t isRegenerationNeeded;
  prescan_bool_t isApiSuccessful;
  strcpy(csName,"W01_Base_Map_cs");
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

  /* 0 : registry tuning variable = "W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID");
    if (W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Audi_A8_Sedan_1_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Audi_A8_Sedan_1"));
    }
  }

  /* 1 : registry tuning variable = "W01_Base_Map_cs_b5931a786e299506" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_b5931a786e299506 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_b5931a786e299506");
    if (W01_Base_Map_cs_b5931a786e299506 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_b5931a786e299506>.\n");
    } else {
      *W01_Base_Map_cs_b5931a786e299506 = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Audi_A8_Sedan_1"));
    }
  }

  /* 2 : registry tuning variable = "W01_Base_Map_cs_9f504bb84aebc2fd" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_9f504bb84aebc2fd = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_9f504bb84aebc2fd");
    if (W01_Base_Map_cs_9f504bb84aebc2fd == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_9f504bb84aebc2fd>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:14/pose/orientation/pitch";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *W01_Base_Map_cs_9f504bb84aebc2fd = (real_T)(p1 * 57.2958);
    }
  }

  /* 3 : registry tuning variable = "W01_Base_Map_cs_9538d35a279fbe4e" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_9538d35a279fbe4e = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_9538d35a279fbe4e");
    if (W01_Base_Map_cs_9538d35a279fbe4e == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_9538d35a279fbe4e>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:14/pose/orientation/roll";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *W01_Base_Map_cs_9538d35a279fbe4e = (real_T)(p1 * 57.2958);
    }
  }

  /* 4 : registry tuning variable = "W01_Base_Map_cs_a242ed7539861165" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_a242ed7539861165 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_a242ed7539861165");
    if (W01_Base_Map_cs_a242ed7539861165 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_a242ed7539861165>.\n");
    } else {
      double p1 = 0.0081962821266734747;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:14/pose/orientation/yaw";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *W01_Base_Map_cs_a242ed7539861165 = (real_T)(p1 * 57.2958);
    }
  }

  /* 5 : registry tuning variable = "W01_Base_Map_cs_b7f45a070fa6e639" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_b7f45a070fa6e639 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_b7f45a070fa6e639");
    if (W01_Base_Map_cs_b7f45a070fa6e639 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_b7f45a070fa6e639>.\n");
    } else {
      double p1 = 82.909647010266738;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:14/pose/position/x";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:14/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:14/pose/orientation/pitch";
      double p4 = 0.0081962821266734747;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:14/pose/orientation/yaw";
      double p5 = 1.690000057220459;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:14/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:14/cogOffset/y";
      double p7 = 0.68999999761581421;
      const char* p7_modelName = "pimp/worldmodel";
      const char* p7_modelPath = "object:14/cogOffset/z";
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
      *W01_Base_Map_cs_b7f45a070fa6e639 = (real_T)(p1 +
        prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 0));
    }
  }

  /* 6 : registry tuning variable = "W01_Base_Map_cs_563ebd29d1fd6c09" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_563ebd29d1fd6c09 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_563ebd29d1fd6c09");
    if (W01_Base_Map_cs_563ebd29d1fd6c09 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_563ebd29d1fd6c09>.\n");
    } else {
      double p1 = 171.25636633333505;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:14/pose/position/y";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:14/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:14/pose/orientation/pitch";
      double p4 = 0.0081962821266734747;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:14/pose/orientation/yaw";
      double p5 = 1.690000057220459;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:14/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:14/cogOffset/y";
      double p7 = 0.68999999761581421;
      const char* p7_modelName = "pimp/worldmodel";
      const char* p7_modelPath = "object:14/cogOffset/z";
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
      *W01_Base_Map_cs_563ebd29d1fd6c09 = (real_T)(p1 +
        prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 1));
    }
  }

  /* 7 : registry tuning variable = "W01_Base_Map_cs_d4423fcf1c0d6fc4" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_d4423fcf1c0d6fc4 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_d4423fcf1c0d6fc4");
    if (W01_Base_Map_cs_d4423fcf1c0d6fc4 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_d4423fcf1c0d6fc4>.\n");
    } else {
      double p1 = -2.2204460492503131E-16;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:14/pose/position/z";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:14/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:14/pose/orientation/pitch";
      double p4 = 0.0081962821266734747;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:14/pose/orientation/yaw";
      double p5 = 1.690000057220459;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:14/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:14/cogOffset/y";
      double p7 = 0.68999999761581421;
      const char* p7_modelName = "pimp/worldmodel";
      const char* p7_modelPath = "object:14/cogOffset/z";
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
      *W01_Base_Map_cs_d4423fcf1c0d6fc4 = (real_T)(p1 +
        prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 2));
    }
  }

  /* 8 : registry tuning variable = "W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID");
    if (W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Child_RegularAni_1_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Child_RegularAni_1"));
    }
  }

  /* 9 : registry tuning variable = "W01_Base_Map_cs_514c2dea2cdbe680" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_514c2dea2cdbe680 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_514c2dea2cdbe680");
    if (W01_Base_Map_cs_514c2dea2cdbe680 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_514c2dea2cdbe680>.\n");
    } else {
      *W01_Base_Map_cs_514c2dea2cdbe680 = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Child_RegularAni_1"));
    }
  }

  /* 10 : registry tuning variable = "W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID");
    if (W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Child_RegularAni_2_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Child_RegularAni_2"));
    }
  }

  /* 11 : registry tuning variable = "W01_Base_Map_cs_51d6e6e467bedba1" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_51d6e6e467bedba1 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_51d6e6e467bedba1");
    if (W01_Base_Map_cs_51d6e6e467bedba1 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_51d6e6e467bedba1>.\n");
    } else {
      *W01_Base_Map_cs_51d6e6e467bedba1 = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Child_RegularAni_2"));
    }
  }

  /* 12 : registry tuning variable = "W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID");
    if (W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Citroen_C3_Hatchback_1_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Citroen_C3_Hatchback_1"));
    }
  }

  /* 13 : registry tuning variable = "W01_Base_Map_cs_328ec7e3a8cd5b54" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_328ec7e3a8cd5b54 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_328ec7e3a8cd5b54");
    if (W01_Base_Map_cs_328ec7e3a8cd5b54 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_328ec7e3a8cd5b54>.\n");
    } else {
      *W01_Base_Map_cs_328ec7e3a8cd5b54 = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Citroen_C3_Hatchback_1"));
    }
  }

  /* 14 : registry tuning variable = "W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID");
    if (W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Female_RegularAni_1_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Female_RegularAni_1"));
    }
  }

  /* 15 : registry tuning variable = "W01_Base_Map_cs_cf83ac8e8b053cbf" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_cf83ac8e8b053cbf = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_cf83ac8e8b053cbf");
    if (W01_Base_Map_cs_cf83ac8e8b053cbf == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_cf83ac8e8b053cbf>.\n");
    } else {
      *W01_Base_Map_cs_cf83ac8e8b053cbf = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Female_RegularAni_1"));
    }
  }

  /* 16 : registry tuning variable = "W01_Base_Map_cs_c75b75e9f6b035bf" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_c75b75e9f6b035bf = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_c75b75e9f6b035bf");
    if (W01_Base_Map_cs_c75b75e9f6b035bf == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_c75b75e9f6b035bf>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/orientation/pitch";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *W01_Base_Map_cs_c75b75e9f6b035bf = (real_T)(p1 * 57.2958);
    }
  }

  /* 17 : registry tuning variable = "W01_Base_Map_cs_423c72fa17799c7f" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_423c72fa17799c7f = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_423c72fa17799c7f");
    if (W01_Base_Map_cs_423c72fa17799c7f == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_423c72fa17799c7f>.\n");
    } else {
      double p1 = 0.0;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/orientation/roll";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *W01_Base_Map_cs_423c72fa17799c7f = (real_T)(p1 * 57.2958);
    }
  }

  /* 18 : registry tuning variable = "W01_Base_Map_cs_774a522413284ef7" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_774a522413284ef7 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_774a522413284ef7");
    if (W01_Base_Map_cs_774a522413284ef7 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_774a522413284ef7>.\n");
    } else {
      double p1 = 0.00077834401161473786;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/orientation/yaw";
      prescan_experiment_get_double(experimentHandle, p1_modelName, p1_modelPath,
        &p1);
      *W01_Base_Map_cs_774a522413284ef7 = (real_T)(p1 * 57.2958);
    }
  }

  /* 19 : registry tuning variable = "W01_Base_Map_cs_df133aa86d9852fe" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_df133aa86d9852fe = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_df133aa86d9852fe");
    if (W01_Base_Map_cs_df133aa86d9852fe == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_df133aa86d9852fe>.\n");
    } else {
      double p1 = 70.774005861361758;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/position/x";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:0/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:0/pose/orientation/pitch";
      double p4 = 0.00077834401161473786;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:0/pose/orientation/yaw";
      double p5 = 1.4800000190734863;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:0/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:0/cogOffset/y";
      double p7 = 0.52999997138977051;
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
      *W01_Base_Map_cs_df133aa86d9852fe = (real_T)(p1 +
        prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 0));
    }
  }

  /* 20 : registry tuning variable = "W01_Base_Map_cs_ae41b72d7e14f81d" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_ae41b72d7e14f81d = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_ae41b72d7e14f81d");
    if (W01_Base_Map_cs_ae41b72d7e14f81d == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_ae41b72d7e14f81d>.\n");
    } else {
      double p1 = 171.27722939862053;
      const char* p1_modelName = "pimp/worldmodel";
      const char* p1_modelPath = "object:0/pose/position/y";
      double p2 = 0.0;
      const char* p2_modelName = "pimp/worldmodel";
      const char* p2_modelPath = "object:0/pose/orientation/roll";
      double p3 = 0.0;
      const char* p3_modelName = "pimp/worldmodel";
      const char* p3_modelPath = "object:0/pose/orientation/pitch";
      double p4 = 0.00077834401161473786;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:0/pose/orientation/yaw";
      double p5 = 1.4800000190734863;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:0/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:0/cogOffset/y";
      double p7 = 0.52999997138977051;
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
      *W01_Base_Map_cs_ae41b72d7e14f81d = (real_T)(p1 +
        prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 1));
    }
  }

  /* 21 : registry tuning variable = "W01_Base_Map_cs_669d1acb174df2b9" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_669d1acb174df2b9 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_669d1acb174df2b9");
    if (W01_Base_Map_cs_669d1acb174df2b9 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_669d1acb174df2b9>.\n");
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
      double p4 = 0.00077834401161473786;
      const char* p4_modelName = "pimp/worldmodel";
      const char* p4_modelPath = "object:0/pose/orientation/yaw";
      double p5 = 1.4800000190734863;
      const char* p5_modelName = "pimp/worldmodel";
      const char* p5_modelPath = "object:0/cogOffset/x";
      double p6 = 0.0;
      const char* p6_modelName = "pimp/worldmodel";
      const char* p6_modelPath = "object:0/cogOffset/y";
      double p7 = 0.52999997138977051;
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
      *W01_Base_Map_cs_669d1acb174df2b9 = (real_T)(p1 +
        prescan_testautomation_cog_correction(p2, p3, p4, p5, p6, p7, 2));
    }
  }

  /* 22 : registry tuning variable = "W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID");
    if (W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Male_RegularAni_1_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Male_RegularAni_1"));
    }
  }

  /* 23 : registry tuning variable = "W01_Base_Map_cs_c02beb48492dde12" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_c02beb48492dde12 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_c02beb48492dde12");
    if (W01_Base_Map_cs_c02beb48492dde12 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_c02beb48492dde12>.\n");
    } else {
      *W01_Base_Map_cs_c02beb48492dde12 = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Male_RegularAni_1"));
    }
  }

  /* 24 : registry tuning variable = "W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID");
    if (W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID>.\n");
    } else {
      *W01_Base_Map_cs_Male_RegularAni_2_Path_pathUniqueID = (real_T)
        (prescan_testautomation_find_path_id_by_actor_name(experimentHandle,
          "Male_RegularAni_2"));
    }
  }

  /* 25 : registry tuning variable = "W01_Base_Map_cs_57ea59d0358dab77" type="real_T" size=1.0 */
  {
    real_T* W01_Base_Map_cs_57ea59d0358dab77 = (real_T*)
      prescan_CAPI_get_address_by_name(capiMap,
      "W01_Base_Map_cs_57ea59d0358dab77");
    if (W01_Base_Map_cs_57ea59d0358dab77 == NULL) {
      printf("WARNING: Address not found. Possible loss of tunability detected for variable: <W01_Base_Map_cs_57ea59d0358dab77>.\n");
    } else {
      *W01_Base_Map_cs_57ea59d0358dab77 = (real_T)
        (prescan_testautomation_find_speed_profile_by_name(experimentHandle,
          "Male_RegularAni_2"));
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
