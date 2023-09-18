#include "VCU1Mid3CanFr36.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr36_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ ALgtMaxAvlALgtMaxAvl, { ALgtMaxAvlALgtMaxAvl, 24, 8, true, SignalType::APP_UNSIGNED, 30, ALgtMaxAvl, ParentType::GROUP } });
    signals_info.insert({ ALgtMaxAvlALgtMaxAvlLong, { ALgtMaxAvlALgtMaxAvlLong, 48, 8, true, SignalType::APP_UNSIGNED, 30, ALgtMaxAvl, ParentType::GROUP } });
    signals_info.insert({ ALgtMaxAvlChks, { ALgtMaxAvlChks, 24, 8, true, SignalType::E2E_CHKS, 0, ALgtMaxAvl, ParentType::GROUP } });
    signals_info.insert({ ALgtMaxAvlCntr, { ALgtMaxAvlCntr, 0, 4, true, SignalType::E2E_CNTR, 0, ALgtMaxAvl, ParentType::GROUP } });
    signals_info.insert({ ALgtMaxAvlDecelLgtMaxAvl, { ALgtMaxAvlDecelLgtMaxAvl, 16, 8, true, SignalType::APP_UNSIGNED, 0, ALgtMaxAvl, ParentType::GROUP } });
    signals_info.insert({ WhlLockStsChks, { WhlLockStsChks, 56, 8, true, SignalType::E2E_CHKS, 0, WhlLockSts, ParentType::GROUP } });
    signals_info.insert({ WhlLockStsCntr, { WhlLockStsCntr, 48, 4, true, SignalType::E2E_CNTR, 0, WhlLockSts, ParentType::GROUP } });
    signals_info.insert({ WhlLockStsDegradedSts, { WhlLockStsDegradedSts, 40, 2, true, SignalType::APP_UNSIGNED, 0, WhlLockSts, ParentType::GROUP } });
    signals_info.insert({ WhlLockStsLockSts, { WhlLockStsLockSts, 52, 3, true, SignalType::APP_UNSIGNED, 0, WhlLockSts, ParentType::GROUP } });
    signals_info.insert({ ALgtMaxAvl_UB, { ALgtMaxAvl_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr36, ParentType::FRAME } });
    signals_info.insert({ WhlLockSts_UB, { WhlLockSts_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr36, ParentType::FRAME } });

    signalgroups_info.insert({ ALgtMaxAvl, { ALgtMaxAvl, 0x1CA, { ALgtMaxAvlALgtMaxAvl, ALgtMaxAvlALgtMaxAvlLong, ALgtMaxAvlChks, ALgtMaxAvlCntr, ALgtMaxAvlDecelLgtMaxAvl }, { E2EProfileType::P01a, ALgtMaxAvlChks, ALgtMaxAvlCntr }, VCU1Mid3CanFr36 } } );
    signalgroups_info.insert({ WhlLockSts, { WhlLockSts, 0x1C9, { WhlLockStsChks, WhlLockStsCntr, WhlLockStsDegradedSts, WhlLockStsLockSts }, { E2EProfileType::P01a, WhlLockStsChks, WhlLockStsCntr }, VCU1Mid3CanFr36 } } );

    frames_info.insert({ VCU1Mid3CanFr36, { VCU1Mid3CanFr36, 148, 8, 20, { ALgtMaxAvl, WhlLockSts }, { WhlLockSts_UB, ALgtMaxAvl_UB } } });

    frame_ids.insert({ 148, VCU1Mid3CanFr36 });
}


}
}
