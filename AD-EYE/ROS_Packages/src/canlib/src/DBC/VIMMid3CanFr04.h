#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr04 { "VIMMid3CanFr04" };


// Groups
const std::string HmiAutnmsSts { "HmiAutnmsSts" };


// Signals
const std::string HmiAutnmsSts_UB { "HmiAutnmsSts_UB" };
const std::string HmiAutnmsStsHmiAutnmsSts { "HmiAutnmsStsHmiAutnmsSts" };
const std::string HmiAutnmsStsCounter { "HmiAutnmsStsCounter" };
const std::string HmiAutnmsStsChecksum { "HmiAutnmsStsChecksum" };
const std::string IDcDcAvlLoSideExt { "IDcDcAvlLoSideExt" };
const std::string IDcDcAvlLoSideExt_UB { "IDcDcAvlLoSideExt_UB" };
const std::string IDcDcAvlMaxLoSideExt_UB { "IDcDcAvlMaxLoSideExt_UB" };
const std::string UDcDcAvlLoSideExt_UB { "UDcDcAvlLoSideExt_UB" };
const std::string IDcDcAvlMaxLoSideExt { "IDcDcAvlMaxLoSideExt" };
const std::string UDcDcAvlLoSideExt { "UDcDcAvlLoSideExt" };


}
}
