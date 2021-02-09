#ifndef RTW_HEADER_ExperimentIL2209_With_Rebuild_2_cs_cap_host_h_
#define RTW_HEADER_ExperimentIL2209_With_Rebuild_2_cs_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} ExperimentIL2209_With_Rebuild_2_cs_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void ExperimentIL2209_With_Rebuild_2_cs_host_InitializeDataMapInfo
    (ExperimentIL2209_With_Rebuild_2_cs_host_DataMapInfo_T *dataMap, const char *
     path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif           /* RTW_HEADER_ExperimentIL2209_With_Rebuild_2_cs_cap_host_h_ */

/* EOF: ExperimentIL2209_With_Rebuild_2_cs_capi_host.h */
