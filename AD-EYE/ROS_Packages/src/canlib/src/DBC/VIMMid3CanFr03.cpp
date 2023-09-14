#include "VIMMid3CanFr03.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PwrDoorPassReClsReqAPI_UB, { PwrDoorPassReClsReqAPI_UB, 15, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorPassClsReqAPI, { PwrDoorPassClsReqAPI, 4, 3, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorDrvrClsReqAPI_UB, { PwrDoorDrvrClsReqAPI_UB, 3, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorPassClsReqAPI_UB, { PwrDoorPassClsReqAPI_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorPassReClsReqAPI, { PwrDoorPassReClsReqAPI, 12, 3, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorDrvrReClsReqAPI, { PwrDoorDrvrReClsReqAPI, 8, 3, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorDrvrReClsReqAPI_UB, { PwrDoorDrvrReClsReqAPI_UB, 11, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PwrDoorDrvrClsReqAPI, { PwrDoorDrvrClsReqAPI, 0, 3, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr03, ParentType::FRAME } });


    frames_info.insert({ VIMMid3CanFr03, { VIMMid3CanFr03, 296, 8, 260, {  }, { PwrDoorPassReClsReqAPI_UB, PwrDoorPassClsReqAPI, PwrDoorDrvrClsReqAPI_UB, PwrDoorPassClsReqAPI_UB, PwrDoorPassReClsReqAPI, PwrDoorDrvrReClsReqAPI, PwrDoorDrvrReClsReqAPI_UB, PwrDoorDrvrClsReqAPI } } });

    frame_ids.insert({ 296, VIMMid3CanFr03 });
}


}
}
