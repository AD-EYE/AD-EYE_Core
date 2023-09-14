#include "VCU1Mid3CanFr28.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr28_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AsySftyDecelReq, { AsySftyDecelReq, 0, 8, SignalType::APP_UNSIGNED, 0, SftyDecelGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AsySftyEnaDecel, { AsySftyEnaDecel, 20, 1, SignalType::APP_UNSIGNED, 0, SftyDecelGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SftyDecelGroupSafeChks, { SftyDecelGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, SftyDecelGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SftyDecelGroupSafeCntr, { SftyDecelGroupSafeCntr, 16, 4, SignalType::E2E_CNTR, 0, SftyDecelGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SftyDecelGroupSafe_UB, { SftyDecelGroupSafe_UB, 31, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr28, ParentType::FRAME } });

    signalgroups_info.insert({ SftyDecelGroupSafe, { SftyDecelGroupSafe, 0x4C, { AsySftyDecelReq, AsySftyEnaDecel, SftyDecelGroupSafeChks, SftyDecelGroupSafeCntr }, { E2EProfileType::P01a, SftyDecelGroupSafeChks, SftyDecelGroupSafeCntr }, VCU1Mid3CanFr28 } } );

    frames_info.insert({ VCU1Mid3CanFr28, { VCU1Mid3CanFr28, 1136, 8, 1100, { SftyDecelGroupSafe }, { SftyDecelGroupSafe_UB } } });

    frame_ids.insert({ 1136, VCU1Mid3CanFr28 });
}


}
}
