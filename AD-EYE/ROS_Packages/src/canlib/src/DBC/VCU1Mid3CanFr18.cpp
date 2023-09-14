#include "VCU1Mid3CanFr18.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr18_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AccrPedlPsdAccrPedlPsd, { AccrPedlPsdAccrPedlPsd, 11, 1, SignalType::APP_UNSIGNED, 0, AccrPedlPsd, ParentType::GROUP } });
    signals_info.insert({ AccrPedlPsdAccrPedlPsdChks, { AccrPedlPsdAccrPedlPsdChks, 0, 8, SignalType::E2E_CHKS, 0, AccrPedlPsd, ParentType::GROUP } });
    signals_info.insert({ AccrPedlPsdAccrPedlPsdCntr, { AccrPedlPsdAccrPedlPsdCntr, 12, 4, SignalType::E2E_CNTR, 0, AccrPedlPsd, ParentType::GROUP } });
    signals_info.insert({ AccrPedlPsdAccrPedlPsdSts, { AccrPedlPsdAccrPedlPsdSts, 10, 1, SignalType::APP_UNSIGNED, 0, AccrPedlPsd, ParentType::GROUP } });
    signals_info.insert({ BrkPedlNotPsdSafe, { BrkPedlNotPsdSafe, 31, 1, SignalType::APP_UNSIGNED, 0, BrkPedlPsdSafeGroup, ParentType::GROUP } });
    signals_info.insert({ BrkPedlPsd, { BrkPedlPsd, 30, 1, SignalType::APP_UNSIGNED, 0, BrkPedlPsdSafeGroup, ParentType::GROUP } });
    signals_info.insert({ BrkPedlPsdChks, { BrkPedlPsdChks, 32, 8, SignalType::E2E_CHKS, 0, BrkPedlPsdSafeGroup, ParentType::GROUP } });
    signals_info.insert({ BrkPedlPsdCntr, { BrkPedlPsdCntr, 24, 4, SignalType::E2E_CNTR, 0, BrkPedlPsdSafeGroup, ParentType::GROUP } });
    signals_info.insert({ BrkPedlPsdQf, { BrkPedlPsdQf, 28, 2, SignalType::APP_UNSIGNED, 1, BrkPedlPsdSafeGroup, ParentType::GROUP } });
    signals_info.insert({ OvrdDecelByDrvrOvrdDecelByDrvr, { OvrdDecelByDrvrOvrdDecelByDrvr, 44, 1, SignalType::APP_UNSIGNED, 0, OvrdDecelByDrvr, ParentType::GROUP } });
    signals_info.insert({ OvrdDecelByDrvrOvrdDecelByDrvrChks, { OvrdDecelByDrvrOvrdDecelByDrvrChks, 48, 8, SignalType::E2E_CHKS, 0, OvrdDecelByDrvr, ParentType::GROUP } });
    signals_info.insert({ OvrdDecelByDrvrOvrdDecelByDrvrCntr, { OvrdDecelByDrvrOvrdDecelByDrvrCntr, 40, 4, SignalType::E2E_CNTR, 0, OvrdDecelByDrvr, ParentType::GROUP } });
    signals_info.insert({ HvSysActvStsExt1_UB, { HvSysActvStsExt1_UB, 47, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });
    signals_info.insert({ AsySftyBrkDlyEstimd, { AsySftyBrkDlyEstimd, 16, 7, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });
    signals_info.insert({ HvSysActvStsExt1, { HvSysActvStsExt1, 46, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });
    signals_info.insert({ OvrdDecelByDrvr_UB, { OvrdDecelByDrvr_UB, 45, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });
    signals_info.insert({ AsySftyBrkDlyEstimd_UB, { AsySftyBrkDlyEstimd_UB, 23, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });
    signals_info.insert({ AccrPedlPsd_UB, { AccrPedlPsd_UB, 9, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });
    signals_info.insert({ BrkPedlPsdSafeGroup_UB, { BrkPedlPsdSafeGroup_UB, 8, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr18, ParentType::FRAME } });

    signalgroups_info.insert({ AccrPedlPsd, { AccrPedlPsd, 0x48, { AccrPedlPsdAccrPedlPsd, AccrPedlPsdAccrPedlPsdChks, AccrPedlPsdAccrPedlPsdCntr, AccrPedlPsdAccrPedlPsdSts }, { E2EProfileType::P01a, AccrPedlPsdAccrPedlPsdChks, AccrPedlPsdAccrPedlPsdCntr }, VCU1Mid3CanFr18 } } );
    signalgroups_info.insert({ BrkPedlPsdSafeGroup, { BrkPedlPsdSafeGroup, 0x38, { BrkPedlNotPsdSafe, BrkPedlPsd, BrkPedlPsdChks, BrkPedlPsdCntr, BrkPedlPsdQf }, { E2EProfileType::P01a, BrkPedlPsdChks, BrkPedlPsdCntr }, VCU1Mid3CanFr18 } } );
    signalgroups_info.insert({ OvrdDecelByDrvr, { OvrdDecelByDrvr, 0x6E, { OvrdDecelByDrvrOvrdDecelByDrvr, OvrdDecelByDrvrOvrdDecelByDrvrChks, OvrdDecelByDrvrOvrdDecelByDrvrCntr }, { E2EProfileType::P01a, OvrdDecelByDrvrOvrdDecelByDrvrChks, OvrdDecelByDrvrOvrdDecelByDrvrCntr }, VCU1Mid3CanFr18 } } );

    frames_info.insert({ VCU1Mid3CanFr18, { VCU1Mid3CanFr18, 119, 8, 20, { AccrPedlPsd, BrkPedlPsdSafeGroup, OvrdDecelByDrvr }, { HvSysActvStsExt1_UB, AsySftyBrkDlyEstimd, HvSysActvStsExt1, OvrdDecelByDrvr_UB, AsySftyBrkDlyEstimd_UB, AccrPedlPsd_UB, BrkPedlPsdSafeGroup_UB } } });

    frame_ids.insert({ 119, VCU1Mid3CanFr18 });
}


}
}
