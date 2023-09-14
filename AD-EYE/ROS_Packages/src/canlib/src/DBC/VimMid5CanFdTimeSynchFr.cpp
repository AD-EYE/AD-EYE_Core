#include "VimMid5CanFdTimeSynchFr.h"


namespace kcan {
namespace dbc {


void VimMid5CanFdTimeSynchFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {


    frames_info.insert({ VimMid5CanFdTimeSynchFr, { VimMid5CanFdTimeSynchFr, 53, 8, 0xFFFFFFFF, {  }, {  } } });

    frame_ids.insert({ 53, VimMid5CanFdTimeSynchFr });
}


}
}
