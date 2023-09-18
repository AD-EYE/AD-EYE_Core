#include "VCU1Mid3CanFr23.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr23_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ TirePValFrntLeTirepabsltVal1, { TirePValFrntLeTirepabsltVal1, 8, 8, true, SignalType::APP_UNSIGNED, 0, TirePValFrntLe, ParentType::GROUP } });
    signals_info.insert({ TirePValFrntLeTirePabsltValQF, { TirePValFrntLeTirePabsltValQF, 0, 2, true, SignalType::APP_UNSIGNED, 1, TirePValFrntLe, ParentType::GROUP } });
    signals_info.insert({ TirePValFrntLeTirePPosn, { TirePValFrntLeTirePPosn, 2, 1, true, SignalType::APP_UNSIGNED, 0, TirePValFrntLe, ParentType::GROUP } });
    signals_info.insert({ TirePValFrntRiTirePAbsltVal1, { TirePValFrntRiTirePAbsltVal1, 24, 8, true, SignalType::APP_UNSIGNED, 0, TirePValFrntRi, ParentType::GROUP } });
    signals_info.insert({ TirePValFrntRiTirePAbsltValQF, { TirePValFrntRiTirePAbsltValQF, 16, 2, true, SignalType::APP_UNSIGNED, 1, TirePValFrntRi, ParentType::GROUP } });
    signals_info.insert({ TirePValFrntRiTirePPosn, { TirePValFrntRiTirePPosn, 18, 1, true, SignalType::APP_UNSIGNED, 0, TirePValFrntRi, ParentType::GROUP } });
    signals_info.insert({ TirePValReLeTirePAbsltVal1, { TirePValReLeTirePAbsltVal1, 40, 8, true, SignalType::APP_UNSIGNED, 0, TirePValReLe, ParentType::GROUP } });
    signals_info.insert({ TirePValReLeTirePAbsltValQF, { TirePValReLeTirePAbsltValQF, 32, 2, true, SignalType::APP_UNSIGNED, 1, TirePValReLe, ParentType::GROUP } });
    signals_info.insert({ TirePValReLeTirePPosn, { TirePValReLeTirePPosn, 34, 1, true, SignalType::APP_UNSIGNED, 0, TirePValReLe, ParentType::GROUP } });
    signals_info.insert({ TirePValReRiTirePAbsltVal1, { TirePValReRiTirePAbsltVal1, 56, 8, true, SignalType::APP_UNSIGNED, 0, TirePValReRi, ParentType::GROUP } });
    signals_info.insert({ TirePValReRiTirePAbsltValQF, { TirePValReRiTirePAbsltValQF, 48, 2, true, SignalType::APP_UNSIGNED, 1, TirePValReRi, ParentType::GROUP } });
    signals_info.insert({ TirePValReRiTirePPosn, { TirePValReRiTirePPosn, 50, 1, true, SignalType::APP_UNSIGNED, 0, TirePValReRi, ParentType::GROUP } });
    signals_info.insert({ TirePWarnCmnTirePWarn, { TirePWarnCmnTirePWarn, 37, 2, true, SignalType::APP_UNSIGNED, 0, TirePWarnCmn, ParentType::GROUP } });
    signals_info.insert({ TirePWarnCmnTirePWarnType, { TirePWarnCmnTirePWarnType, 35, 2, true, SignalType::APP_UNSIGNED, 0, TirePWarnCmn, ParentType::GROUP } });
    signals_info.insert({ TirePWarnFrntLeTirePWarn, { TirePWarnFrntLeTirePWarn, 53, 2, true, SignalType::APP_UNSIGNED, 0, TirePWarnFrntLe, ParentType::GROUP } });
    signals_info.insert({ TirePWarnFrntLeTirePWarnType, { TirePWarnFrntLeTirePWarnType, 51, 2, true, SignalType::APP_UNSIGNED, 0, TirePWarnFrntLe, ParentType::GROUP } });
    signals_info.insert({ TirePMonSysFlt, { TirePMonSysFlt, 4, 3, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePMonSysFlt_UB, { TirePMonSysFlt_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePValFrntLe_UB, { TirePValFrntLe_UB, 3, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePValFrntRi_UB, { TirePValFrntRi_UB, 19, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePValReLe_UB, { TirePValReLe_UB, 20, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePValReRi_UB, { TirePValReRi_UB, 21, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePWarnCmn_UB, { TirePWarnCmn_UB, 39, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });
    signals_info.insert({ TirePWarnFrntLe_UB, { TirePWarnFrntLe_UB, 55, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr23, ParentType::FRAME } });

    signalgroups_info.insert({ TirePValFrntLe, { TirePValFrntLe, 0x0, { TirePValFrntLeTirepabsltVal1, TirePValFrntLeTirePabsltValQF, TirePValFrntLeTirePPosn }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr23 } } );
    signalgroups_info.insert({ TirePValFrntRi, { TirePValFrntRi, 0x0, { TirePValFrntRiTirePAbsltVal1, TirePValFrntRiTirePAbsltValQF, TirePValFrntRiTirePPosn }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr23 } } );
    signalgroups_info.insert({ TirePValReLe, { TirePValReLe, 0x0, { TirePValReLeTirePAbsltVal1, TirePValReLeTirePAbsltValQF, TirePValReLeTirePPosn }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr23 } } );
    signalgroups_info.insert({ TirePValReRi, { TirePValReRi, 0x0, { TirePValReRiTirePAbsltVal1, TirePValReRiTirePAbsltValQF, TirePValReRiTirePPosn }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr23 } } );
    signalgroups_info.insert({ TirePWarnCmn, { TirePWarnCmn, 0x0, { TirePWarnCmnTirePWarn, TirePWarnCmnTirePWarnType }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr23 } } );
    signalgroups_info.insert({ TirePWarnFrntLe, { TirePWarnFrntLe, 0x0, { TirePWarnFrntLeTirePWarn, TirePWarnFrntLeTirePWarnType }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr23 } } );

    frames_info.insert({ VCU1Mid3CanFr23, { VCU1Mid3CanFr23, 352, 8, 280, { TirePValFrntLe, TirePValFrntRi, TirePValReLe, TirePValReRi, TirePWarnCmn, TirePWarnFrntLe }, { TirePWarnCmn_UB, TirePValFrntRi_UB, TirePMonSysFlt_UB, TirePValReLe_UB, TirePMonSysFlt, TirePValReRi_UB, TirePWarnFrntLe_UB, TirePValFrntLe_UB } } });

    frame_ids.insert({ 352, VCU1Mid3CanFr23 });
}


}
}
