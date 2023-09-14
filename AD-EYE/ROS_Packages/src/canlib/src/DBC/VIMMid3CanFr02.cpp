#include "VIMMid3CanFr02.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ OkToClsDoorOkToClsDoorChks, { OkToClsDoorOkToClsDoorChks, 24, 8, SignalType::E2E_CHKS, 0, OkToClsDoor, ParentType::GROUP } });
    signals_info.insert({ OkToClsDoorOkToClsDoorCntr, { OkToClsDoorOkToClsDoorCntr, 16, 4, SignalType::E2E_CNTR, 0, OkToClsDoor, ParentType::GROUP } });
    signals_info.insert({ OkToClsDoorOkToClsDoorDrvr, { OkToClsDoorOkToClsDoorDrvr, 20, 3, SignalType::APP_UNSIGNED, 0, OkToClsDoor, ParentType::GROUP } });
    signals_info.insert({ OkToClsDoorOkToClsDoorDrvrRe, { OkToClsDoorOkToClsDoorDrvrRe, 8, 3, SignalType::APP_UNSIGNED, 0, OkToClsDoor, ParentType::GROUP } });
    signals_info.insert({ OkToClsDoorOkToClsDoorPass, { OkToClsDoorOkToClsDoorPass, 11, 3, SignalType::APP_UNSIGNED, 0, OkToClsDoor, ParentType::GROUP } });
    signals_info.insert({ OkToClsDoorOkToClsDoorPassRe, { OkToClsDoorOkToClsDoorPassRe, 0, 3, SignalType::APP_UNSIGNED, 0, OkToClsDoor, ParentType::GROUP } });
    signals_info.insert({ OkToOpenDoorOkToOpenDoorChks, { OkToOpenDoorOkToOpenDoorChks, 56, 8, SignalType::E2E_CHKS, 0, OkToOpenDoor, ParentType::GROUP } });
    signals_info.insert({ OkToOpenDoorOkToOpenDoorCntr, { OkToOpenDoorOkToOpenDoorCntr, 48, 4, SignalType::E2E_CNTR, 0, OkToOpenDoor, ParentType::GROUP } });
    signals_info.insert({ OkToOpenDoorOkToOpenDoorDrvr, { OkToOpenDoorOkToOpenDoorDrvr, 52, 3, SignalType::APP_UNSIGNED, 0, OkToOpenDoor, ParentType::GROUP } });
    signals_info.insert({ OkToOpenDoorOkToOpenDoorDrvrRe, { OkToOpenDoorOkToOpenDoorDrvrRe, 40, 3, SignalType::APP_UNSIGNED, 0, OkToOpenDoor, ParentType::GROUP } });
    signals_info.insert({ OkToOpenDoorOkToOpenDoorPass, { OkToOpenDoorOkToOpenDoorPass, 43, 3, SignalType::APP_UNSIGNED, 0, OkToOpenDoor, ParentType::GROUP } });
    signals_info.insert({ OkToOpenDoorOkToOpenDoorPassRe, { OkToOpenDoorOkToOpenDoorPassRe, 32, 3, SignalType::APP_UNSIGNED, 0, OkToOpenDoor, ParentType::GROUP } });
    signals_info.insert({ CnvincAPIEna, { CnvincAPIEna, 5, 2, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr02, ParentType::FRAME } });
    signals_info.insert({ OkToOpenDoor_UB, { OkToOpenDoor_UB, 4, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr02, ParentType::FRAME } });
    signals_info.insert({ OkToClsDoor_UB, { OkToClsDoor_UB, 3, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr02, ParentType::FRAME } });
    signals_info.insert({ CnvincAPIEna_UB, { CnvincAPIEna_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr02, ParentType::FRAME } });

    signalgroups_info.insert({ OkToClsDoor, { OkToClsDoor, 0x411, { OkToClsDoorOkToClsDoorChks, OkToClsDoorOkToClsDoorCntr, OkToClsDoorOkToClsDoorDrvr, OkToClsDoorOkToClsDoorDrvrRe, OkToClsDoorOkToClsDoorPass, OkToClsDoorOkToClsDoorPassRe }, { E2EProfileType::P01a, OkToClsDoorOkToClsDoorChks, OkToClsDoorOkToClsDoorCntr }, VIMMid3CanFr02 } } );
    signalgroups_info.insert({ OkToOpenDoor, { OkToOpenDoor, 0x410, { OkToOpenDoorOkToOpenDoorChks, OkToOpenDoorOkToOpenDoorCntr, OkToOpenDoorOkToOpenDoorDrvr, OkToOpenDoorOkToOpenDoorDrvrRe, OkToOpenDoorOkToOpenDoorPass, OkToOpenDoorOkToOpenDoorPassRe }, { E2EProfileType::P01a, OkToOpenDoorOkToOpenDoorChks, OkToOpenDoorOkToOpenDoorCntr }, VIMMid3CanFr02 } } );

    frames_info.insert({ VIMMid3CanFr02, { VIMMid3CanFr02, 297, 8, 260, { OkToClsDoor, OkToOpenDoor }, { CnvincAPIEna, OkToOpenDoor_UB, OkToClsDoor_UB, CnvincAPIEna_UB } } });

    frame_ids.insert({ 297, VIMMid3CanFr02 });
}


}
}
