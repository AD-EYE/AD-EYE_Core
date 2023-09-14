#include "VimbMid6CanFdTimeSynchFr.h"


namespace kcan {
namespace dbc {


void VimbMid6CanFdTimeSynchFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {


    frames_info.insert({ VimbMid6CanFdTimeSynchFr, { VimbMid6CanFdTimeSynchFr, 64, 8, 0xFFFFFFFF, {  }, {  } } });

    frame_ids.insert({ 64, VimbMid6CanFdTimeSynchFr });
}


}
}
