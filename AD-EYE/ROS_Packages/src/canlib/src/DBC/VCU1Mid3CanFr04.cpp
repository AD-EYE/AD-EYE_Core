#include "VCU1Mid3CanFr04.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ FricEstimnFromVehDyn, { FricEstimnFromVehDyn, 56, 8, true, SignalType::APP_UNSIGNED, 0, FricEstimnFromVehDynGroup, ParentType::GROUP } });
    signals_info.insert({ FricEstimnFromVehDynQly, { FricEstimnFromVehDynQly, 48, 3, true, SignalType::APP_UNSIGNED, 1, FricEstimnFromVehDynGroup, ParentType::GROUP } });
    signals_info.insert({ PrpsnTqDirCpbyChks, { PrpsnTqDirCpbyChks, 40, 8, true, SignalType::E2E_CHKS, 0, PrpsnTqDirCpby, ParentType::GROUP } });
    signals_info.insert({ PrpsnTqDirCpbyCntr, { PrpsnTqDirCpbyCntr, 32, 4, true, SignalType::E2E_CNTR, 0, PrpsnTqDirCpby, ParentType::GROUP } });
    signals_info.insert({ PrpsnTqDirCpbySts, { PrpsnTqDirCpbySts, 36, 3, true, SignalType::APP_UNSIGNED, 0, PrpsnTqDirCpby, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiToAPILiExtFctCntr, { SwtExtrLiToAPILiExtFctCntr, 20, 2, true, SignalType::E2E_CNTR, 0, SwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiToAPILiExtFctCrc, { SwtExtrLiToAPILiExtFctCrc, 24, 8, true, SignalType::E2E_CHKS, 0, SwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiToAPILiExtFctQf, { SwtExtrLiToAPILiExtFctQf, 18, 2, true, SignalType::APP_UNSIGNED, 0, SwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiToAPILiExtFctReq1, { SwtExtrLiToAPILiExtFctReq1, 16, 2, true, SignalType::APP_UNSIGNED, 0, SwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ FricEstimnFromVehDynGroup_UB, { FricEstimnFromVehDynGroup_UB, 51, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ PrpsnTqDirCpby_UB, { PrpsnTqDirCpby_UB, 39, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ SwtExtrLiToAPI_UB, { SwtExtrLiToAPI_UB, 22, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr04, ParentType::FRAME } });

    signalgroups_info.insert({ FricEstimnFromVehDynGroup, { FricEstimnFromVehDynGroup, 0x0, { FricEstimnFromVehDyn, FricEstimnFromVehDynQly }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr04 } } );
    signalgroups_info.insert({ PrpsnTqDirCpby, { PrpsnTqDirCpby, 0x1CD, { PrpsnTqDirCpbyChks, PrpsnTqDirCpbyCntr, PrpsnTqDirCpbySts }, { E2EProfileType::P01a, PrpsnTqDirCpbyChks, PrpsnTqDirCpbyCntr }, VCU1Mid3CanFr04 } } );
    signalgroups_info.insert({ SwtExtrLiToAPI, { SwtExtrLiToAPI, 0x0, { SwtExtrLiToAPILiExtFctCntr, SwtExtrLiToAPILiExtFctCrc, SwtExtrLiToAPILiExtFctQf, SwtExtrLiToAPILiExtFctReq1 }, { E2EProfileType::P05, SwtExtrLiToAPILiExtFctCrc, SwtExtrLiToAPILiExtFctCntr }, VCU1Mid3CanFr04 } } );

    frames_info.insert({ VCU1Mid3CanFr04, { VCU1Mid3CanFr04, 98, 8, 40, { FricEstimnFromVehDynGroup, PrpsnTqDirCpby, SwtExtrLiToAPI }, { SwtExtrLiToAPI_UB, PrpsnTqDirCpby_UB, FricEstimnFromVehDynGroup_UB } } });

    frame_ids.insert({ 98, VCU1Mid3CanFr04 });
}


}
}
