#include "VIMMid3CanFr01.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SnsrClngReqIfClngProg, { SnsrClngReqIfClngProg, 28, 4, SignalType::APP_UNSIGNED, 0, SnsrClngReqIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngReqIfSnsrSeld, { SnsrClngReqIfSnsrSeld, 24, 4, SignalType::APP_UNSIGNED, 0, SnsrClngReqIf, ParentType::GROUP } });
    signals_info.insert({ WiprFrntReqIfFrntWiprLvrCmd1, { WiprFrntReqIfFrntWiprLvrCmd1, 32, 3, SignalType::APP_UNSIGNED, 0, WiprFrntReqIf, ParentType::GROUP } });
    signals_info.insert({ WiprFrntReqIfFrntWiprLvrCntr, { WiprFrntReqIfFrntWiprLvrCntr, 35, 2, SignalType::APP_UNSIGNED, 0, WiprFrntReqIf, ParentType::GROUP } });
    signals_info.insert({ WiprFrntReqIfFrntWiprLvrCrc, { WiprFrntReqIfFrntWiprLvrCrc, 40, 8, SignalType::APP_UNSIGNED, 0, WiprFrntReqIf, ParentType::GROUP } });
    signals_info.insert({ WiprFrntReqIfFrntWiprLvrQf, { WiprFrntReqIfFrntWiprLvrQf, 37, 2, SignalType::APP_UNSIGNED, 0, WiprFrntReqIf, ParentType::GROUP } });
    signals_info.insert({ WipgSpdIntlIf_UB, { WipgSpdIntlIf_UB, 10, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ WiprReCmdIf, { WiprReCmdIf, 1, 2, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ HvSysActvReqExt_UB, { HvSysActvReqExt_UB, 5, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ SwtBeamHiFromAPI, { SwtBeamHiFromAPI, 6, 2, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ SwtBeamHiFromAPI_UB, { SwtBeamHiFromAPI_UB, 20, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ RainSnsrCmdIf_UB, { RainSnsrCmdIf_UB, 9, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ RainSnsrCmdIf, { RainSnsrCmdIf, 8, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ WinWshngCmdIf_UB, { WinWshngCmdIf_UB, 0, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ HornActvnReqIf, { HornActvnReqIf, 22, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ WiprFrntReqIf_UB, { WiprFrntReqIf_UB, 39, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ WinWshngCmdIf, { WinWshngCmdIf, 14, 2, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ WipgSpdIntlIf, { WipgSpdIntlIf, 11, 3, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ SnsrClngReqIf_UB, { SnsrClngReqIf_UB, 21, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ HornActvnReqIf_UB, { HornActvnReqIf_UB, 23, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ HvSysActvReqExt, { HvSysActvReqExt, 4, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ WiprReCmdIf_UB, { WiprReCmdIf_UB, 3, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr01, ParentType::FRAME } });

    signalgroups_info.insert({ SnsrClngReqIf, { SnsrClngReqIf, 0x0, { SnsrClngReqIfClngProg, SnsrClngReqIfSnsrSeld }, { E2EProfileType::None, "", "" }, VIMMid3CanFr01 } } );
    signalgroups_info.insert({ WiprFrntReqIf, { WiprFrntReqIf, 0x0, { WiprFrntReqIfFrntWiprLvrCmd1, WiprFrntReqIfFrntWiprLvrCntr, WiprFrntReqIfFrntWiprLvrCrc, WiprFrntReqIfFrntWiprLvrQf }, { E2EProfileType::None, "", "" }, VIMMid3CanFr01 } } );

    frames_info.insert({ VIMMid3CanFr01, { VIMMid3CanFr01, 84, 8, 15, { SnsrClngReqIf, WiprFrntReqIf }, { WipgSpdIntlIf_UB, WiprReCmdIf, HvSysActvReqExt_UB, SwtBeamHiFromAPI, SwtBeamHiFromAPI_UB, RainSnsrCmdIf_UB, RainSnsrCmdIf, WinWshngCmdIf_UB, HornActvnReqIf, WiprFrntReqIf_UB, WinWshngCmdIf, WipgSpdIntlIf, SnsrClngReqIf_UB, HornActvnReqIf_UB, HvSysActvReqExt, WiprReCmdIf_UB } } });

    frame_ids.insert({ 84, VIMMid3CanFr01 });
}


}
}
