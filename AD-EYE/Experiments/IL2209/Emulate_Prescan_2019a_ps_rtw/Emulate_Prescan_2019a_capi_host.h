#ifndef RTW_HEADER_Emulate_Prescan_2019a_cap_host_h_
#define RTW_HEADER_Emulate_Prescan_2019a_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} Emulate_Prescan_2019a_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void Emulate_Prescan_2019a_host_InitializeDataMapInfo
    (Emulate_Prescan_2019a_host_DataMapInfo_T *dataMap, const char *path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                        /* RTW_HEADER_Emulate_Prescan_2019a_cap_host_h_ */

/* EOF: Emulate_Prescan_2019a_capi_host.h */
