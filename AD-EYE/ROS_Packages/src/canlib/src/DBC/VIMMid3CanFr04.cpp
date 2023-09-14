#include "VIMMid3CanFr04.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ HmiAutnmsStsChecksum, { HmiAutnmsStsChecksum, 8, 8, SignalType::APP_UNSIGNED, 0, HmiAutnmsSts, ParentType::GROUP } });
    signals_info.insert({ HmiAutnmsStsCounter, { HmiAutnmsStsCounter, 0, 4, SignalType::APP_UNSIGNED, 0, HmiAutnmsSts, ParentType::GROUP } });
    signals_info.insert({ HmiAutnmsStsHmiAutnmsSts, { HmiAutnmsStsHmiAutnmsSts, 4, 3, SignalType::APP_UNSIGNED, 1, HmiAutnmsSts, ParentType::GROUP } });
    signals_info.insert({ IDcDcAvlLoSideExt, { IDcDcAvlLoSideExt, 16, 8, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ UDcDcAvlLoSideExt, { UDcDcAvlLoSideExt, 40, 8, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ IDcDcAvlMaxLoSideExt_UB, { IDcDcAvlMaxLoSideExt_UB, 30, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ UDcDcAvlLoSideExt_UB, { UDcDcAvlLoSideExt_UB, 29, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ IDcDcAvlLoSideExt_UB, { IDcDcAvlLoSideExt_UB, 31, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ HmiAutnmsSts_UB, { HmiAutnmsSts_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });
    signals_info.insert({ IDcDcAvlMaxLoSideExt, { IDcDcAvlMaxLoSideExt, 32, 8, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr04, ParentType::FRAME } });

    signalgroups_info.insert({ HmiAutnmsSts, { HmiAutnmsSts, 0x0, { HmiAutnmsStsChecksum, HmiAutnmsStsCounter, HmiAutnmsStsHmiAutnmsSts }, { E2EProfileType::None, "", "" }, VIMMid3CanFr04 } } );

    frames_info.insert({ VIMMid3CanFr04, { VIMMid3CanFr04, 260, 8, 45, { HmiAutnmsSts }, { IDcDcAvlLoSideExt, UDcDcAvlLoSideExt, IDcDcAvlMaxLoSideExt_UB, UDcDcAvlLoSideExt_UB, IDcDcAvlLoSideExt_UB, HmiAutnmsSts_UB, IDcDcAvlMaxLoSideExt } } });

    frame_ids.insert({ 260, VIMMid3CanFr04 });
}


}
}
