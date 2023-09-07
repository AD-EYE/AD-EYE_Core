#include "VCU1Mid3CanFr13.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr13_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdActvnOkFromVehDyn, { AdActvnOkFromVehDyn, 5, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr13 } });
    signals_info.insert({ AdActvnOkFromVehDyn_UB, { AdActvnOkFromVehDyn_UB, 6, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr13 } });
    signals_info.insert({ AutnmsDrvModMngtGlbSafe1_UB, { AutnmsDrvModMngtGlbSafe1_UB, 2, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr13 } });
    signals_info.insert({ AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1, { AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1, 0, 2, SignalType::APP_UNSIGNED, AutnmsDrvModMngtGlbSafe1 } });
    signals_info.insert({ AutnmsDrvModMngtGlbSafe1AutnmsLowSpdModSts1, { AutnmsDrvModMngtGlbSafe1AutnmsLowSpdModSts1, 14, 2, SignalType::APP_UNSIGNED, AutnmsDrvModMngtGlbSafe1 } });
    signals_info.insert({ AutnmsDrvModMngtGlbSafe1Checksum, { AutnmsDrvModMngtGlbSafe1Checksum, 16, 8, SignalType::E2E_CHKS, AutnmsDrvModMngtGlbSafe1 } });
    signals_info.insert({ AutnmsDrvModMngtGlbSafe1Counter, { AutnmsDrvModMngtGlbSafe1Counter, 10, 4, SignalType::E2E_CNTR, AutnmsDrvModMngtGlbSafe1 } });
    signals_info.insert({ AutnmsDrvModMngtGlbSafe1VehOperModSts1, { AutnmsDrvModMngtGlbSafe1VehOperModSts1, 8, 2, SignalType::APP_UNSIGNED, AutnmsDrvModMngtGlbSafe1 } });
    signals_info.insert({ EngFltIndcn_UB, { EngFltIndcn_UB, 3, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr13 } });
    signals_info.insert({ EngFltIndcnEngFltIndcn1, { EngFltIndcnEngFltIndcn1, 31, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn10, { EngFltIndcnEngFltIndcn10, 38, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn11, { EngFltIndcnEngFltIndcn11, 37, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn12, { EngFltIndcnEngFltIndcn12, 36, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn13, { EngFltIndcnEngFltIndcn13, 35, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn14, { EngFltIndcnEngFltIndcn14, 34, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn15, { EngFltIndcnEngFltIndcn15, 32, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn16, { EngFltIndcnEngFltIndcn16, 32, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn17, { EngFltIndcnEngFltIndcn17, 47, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn18, { EngFltIndcnEngFltIndcn18, 46, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn19, { EngFltIndcnEngFltIndcn19, 45, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn2, { EngFltIndcnEngFltIndcn2, 30, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn20, { EngFltIndcnEngFltIndcn20, 44, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn21, { EngFltIndcnEngFltIndcn21, 43, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn22, { EngFltIndcnEngFltIndcn22, 42, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn23, { EngFltIndcnEngFltIndcn23, 41, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn24, { EngFltIndcnEngFltIndcn24, 40, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn25, { EngFltIndcnEngFltIndcn25, 55, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn26, { EngFltIndcnEngFltIndcn26, 54, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn27, { EngFltIndcnEngFltIndcn27, 53, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn3, { EngFltIndcnEngFltIndcn3, 29, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn4, { EngFltIndcnEngFltIndcn4, 28, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn5, { EngFltIndcnEngFltIndcn5, 27, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn6, { EngFltIndcnEngFltIndcn6, 26, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn7, { EngFltIndcnEngFltIndcn7, 25, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn8, { EngFltIndcnEngFltIndcn8, 24, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ EngFltIndcnEngFltIndcn9, { EngFltIndcnEngFltIndcn9, 39, 1, SignalType::APP_UNSIGNED, EngFltIndcn } });
    signals_info.insert({ PtTqAtAxleAvlReMaxLong, { PtTqAtAxleAvlReMaxLong, 40, 13, SignalType::APP_SIGNED, VCU1Mid3CanFr13 } });
    signals_info.insert({ PtTqAtAxleAvlReMaxLong_UB, { PtTqAtAxleAvlReMaxLong_UB, 4, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr13 } });


    signalgroups_info.insert(
    {
        AutnmsDrvModMngtGlbSafe1,
        {
            AutnmsDrvModMngtGlbSafe1,
            0x1B,
            {
                AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1,
                AutnmsDrvModMngtGlbSafe1AutnmsLowSpdModSts1,
                AutnmsDrvModMngtGlbSafe1Checksum,
                AutnmsDrvModMngtGlbSafe1Counter,
                AutnmsDrvModMngtGlbSafe1VehOperModSts1
            }, 
            { E2EProfileType::P01a, AutnmsDrvModMngtGlbSafe1Checksum, AutnmsDrvModMngtGlbSafe1Counter },
            VCU1Mid3CanFr13
        }
    });

    signalgroups_info.insert(
    {
        EngFltIndcn,
        {
            EngFltIndcn,
            0x0,
            {
                EngFltIndcnEngFltIndcn1,
                EngFltIndcnEngFltIndcn10,
                EngFltIndcnEngFltIndcn11,
                EngFltIndcnEngFltIndcn12,
                EngFltIndcnEngFltIndcn13,
                EngFltIndcnEngFltIndcn14,
                EngFltIndcnEngFltIndcn15,
                EngFltIndcnEngFltIndcn16,
                EngFltIndcnEngFltIndcn17,
                EngFltIndcnEngFltIndcn18,
                EngFltIndcnEngFltIndcn19,
                EngFltIndcnEngFltIndcn2,
                EngFltIndcnEngFltIndcn21,
                EngFltIndcnEngFltIndcn22,
                EngFltIndcnEngFltIndcn23,
                EngFltIndcnEngFltIndcn24,
                EngFltIndcnEngFltIndcn25,
                EngFltIndcnEngFltIndcn26,
                EngFltIndcnEngFltIndcn27,
                EngFltIndcnEngFltIndcn3,
                EngFltIndcnEngFltIndcn4,
                EngFltIndcnEngFltIndcn5,
                EngFltIndcnEngFltIndcn6,
                EngFltIndcnEngFltIndcn7,
                EngFltIndcnEngFltIndcn8,
                EngFltIndcnEngFltIndcn9
            }, 
            E2EProfileType::None,
            VCU1Mid3CanFr13
        }
    });

    frames_info.insert({ VCU1Mid3CanFr13, { VCU1Mid3CanFr13, 277, 8, 50, { AutnmsDrvModMngtGlbSafe1, EngFltIndcn }, { AdActvnOkFromVehDyn, AdActvnOkFromVehDyn_UB, AutnmsDrvModMngtGlbSafe1_UB, EngFltIndcn_UB, PtTqAtAxleAvlReMaxLong, PtTqAtAxleAvlReMaxLong_UB } } });

    frame_ids.insert({ 277, VCU1Mid3CanFr13 });
}


}
}