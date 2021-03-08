#ifndef RTW_HEADER_Experiment_Prescan_Code_Generation_cs_cap_host_h_
#define RTW_HEADER_Experiment_Prescan_Code_Generation_cs_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} Experiment_Prescan_Code_Generation_cs_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void Experiment_Prescan_Code_Generation_cs_host_InitializeDataMapInfo
    (Experiment_Prescan_Code_Generation_cs_host_DataMapInfo_T *dataMap, const
     char *path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif        /* RTW_HEADER_Experiment_Prescan_Code_Generation_cs_cap_host_h_ */

/* EOF: Experiment_Prescan_Code_Generation_cs_capi_host.h */
