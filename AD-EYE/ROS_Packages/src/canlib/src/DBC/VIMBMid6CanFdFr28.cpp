#include "VIMBMid6CanFdFr28.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr28_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecALgtLimReqGroupSafeALgtMaxReq, { AdSecALgtLimReqGroupSafeALgtMaxReq, 8, 12, true, SignalType::APP_UNSIGNED, 3840, AdSecALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeALgtMinReq, { AdSecALgtLimReqGroupSafeALgtMinReq, 24, 12, true, SignalType::APP_UNSIGNED, 0, AdSecALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeChks, { AdSecALgtLimReqGroupSafeChks, 32, 8, true, SignalType::E2E_CHKS, 0, AdSecALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeCntr, { AdSecALgtLimReqGroupSafeCntr, 20, 4, true, SignalType::E2E_CNTR, 0, AdSecALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeALgtNomReqMax, { SecAdNomALgtReqGroupSafeALgtNomReqMax, 48, 12, true, SignalType::APP_UNSIGNED, 1920, SecAdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeALgtNomReqMin, { SecAdNomALgtReqGroupSafeALgtNomReqMin, 64, 12, true, SignalType::APP_UNSIGNED, 1920, SecAdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeChks, { SecAdNomALgtReqGroupSafeChks, 72, 8, true, SignalType::E2E_CHKS, 0, SecAdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeCntr, { SecAdNomALgtReqGroupSafeCntr, 60, 4, true, SignalType::E2E_CNTR, 0, SecAdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeNegLimForJerk, { SecAdNomALgtReqGroupSafeNegLimForJerk, 88, 12, true, SignalType::APP_UNSIGNED, 2000, SecAdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecAdNomALgtReqGroupSafePosLimForJerk, { SecAdNomALgtReqGroupSafePosLimForJerk, 104, 12, true, SignalType::APP_UNSIGNED, 2000, SecAdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecALgtLimReqGroupSafe_UB, { AdSecALgtLimReqGroupSafe_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr28, ParentType::FRAME } });
    signals_info.insert({ SecAdNomALgtReqGroupSafe_UB, { SecAdNomALgtReqGroupSafe_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr28, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecALgtLimReqGroupSafe, { AdSecALgtLimReqGroupSafe, 0x1C5, { AdSecALgtLimReqGroupSafeALgtMaxReq, AdSecALgtLimReqGroupSafeALgtMinReq, AdSecALgtLimReqGroupSafeChks, AdSecALgtLimReqGroupSafeCntr }, { E2EProfileType::P01a, AdSecALgtLimReqGroupSafeChks, AdSecALgtLimReqGroupSafeCntr }, VIMBMid6CanFdFr28 } } );
    signalgroups_info.insert({ SecAdNomALgtReqGroupSafe, { SecAdNomALgtReqGroupSafe, 0x2AA, { SecAdNomALgtReqGroupSafeALgtNomReqMax, SecAdNomALgtReqGroupSafeALgtNomReqMin, SecAdNomALgtReqGroupSafeChks, SecAdNomALgtReqGroupSafeCntr, SecAdNomALgtReqGroupSafeNegLimForJerk, SecAdNomALgtReqGroupSafePosLimForJerk }, { E2EProfileType::P01a, SecAdNomALgtReqGroupSafeChks, SecAdNomALgtReqGroupSafeCntr }, VIMBMid6CanFdFr28 } } );

    frames_info.insert({ VIMBMid6CanFdFr28, { VIMBMid6CanFdFr28, 80, 16, 10, { AdSecALgtLimReqGroupSafe, SecAdNomALgtReqGroupSafe }, { AdSecALgtLimReqGroupSafe_UB, SecAdNomALgtReqGroupSafe_UB } } });

    frame_ids.insert({ 80, VIMBMid6CanFdFr28 });
}


}
}
