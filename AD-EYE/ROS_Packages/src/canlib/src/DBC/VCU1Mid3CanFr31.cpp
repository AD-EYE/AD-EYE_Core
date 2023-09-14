#include "VCU1Mid3CanFr31.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr31_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ VehOpReqInVehDynGroupSafeChks, { VehOpReqInVehDynGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, VehOpReqInVehDynGroupSafe, ParentType::GROUP } });
    signals_info.insert({ VehOpReqInVehDynGroupSafeCntr, { VehOpReqInVehDynGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, VehOpReqInVehDynGroupSafe, ParentType::GROUP } });
    signals_info.insert({ VehOpReqInVehDynGroupSafeVehOpReq, { VehOpReqInVehDynGroupSafeVehOpReq, 4, 2, SignalType::APP_UNSIGNED, 0, VehOpReqInVehDynGroupSafe, ParentType::GROUP } });
    signals_info.insert({ EstimdCoastALgtCpby_UB, { EstimdCoastALgtCpby_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr31, ParentType::FRAME } });
    signals_info.insert({ VehOpReqInVehDynGroupSafe_UB, { VehOpReqInVehDynGroupSafe_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr31, ParentType::FRAME } });
    signals_info.insert({ EstimdCoastALgtCpby, { EstimdCoastALgtCpby, 16, 8, SignalType::APP_UNSIGNED, 30, VCU1Mid3CanFr31, ParentType::FRAME } });

    signalgroups_info.insert({ VehOpReqInVehDynGroupSafe, { VehOpReqInVehDynGroupSafe, 0x1FC, { VehOpReqInVehDynGroupSafeChks, VehOpReqInVehDynGroupSafeCntr, VehOpReqInVehDynGroupSafeVehOpReq }, { E2EProfileType::P01a, VehOpReqInVehDynGroupSafeChks, VehOpReqInVehDynGroupSafeCntr }, VCU1Mid3CanFr31 } } );

    frames_info.insert({ VCU1Mid3CanFr31, { VCU1Mid3CanFr31, 131, 8, 30, { VehOpReqInVehDynGroupSafe }, { EstimdCoastALgtCpby_UB, VehOpReqInVehDynGroupSafe_UB, EstimdCoastALgtCpby } } });

    frame_ids.insert({ 131, VCU1Mid3CanFr31 });
}


}
}
