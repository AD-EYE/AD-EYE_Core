#ifndef RTW_HEADER_ros_subsystem_cap_host_h_
#define RTW_HEADER_ros_subsystem_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} ros_subsystem_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void ros_subsystem_host_InitializeDataMapInfo(ros_subsystem_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                /* RTW_HEADER_ros_subsystem_cap_host_h_ */

/* EOF: ros_subsystem_capi_host.h */
