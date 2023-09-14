#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr23_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr23 { "VCU1Mid3CanFr23" };


// Groups
const std::string TirePValFrntLe { "TirePValFrntLe" };
const std::string TirePValFrntRi { "TirePValFrntRi" };
const std::string TirePValReLe { "TirePValReLe" };
const std::string TirePValReRi { "TirePValReRi" };
const std::string TirePWarnCmn { "TirePWarnCmn" };
const std::string TirePWarnFrntLe { "TirePWarnFrntLe" };


// Signals
const std::string TirePMonSysFlt_UB { "TirePMonSysFlt_UB" };
const std::string TirePMonSysFlt { "TirePMonSysFlt" };
const std::string TirePValFrntLe_UB { "TirePValFrntLe_UB" };
const std::string TirePValFrntLeTirePPosn { "TirePValFrntLeTirePPosn" };
const std::string TirePValFrntLeTirePabsltValQF { "TirePValFrntLeTirePabsltValQF" };
const std::string TirePValFrntLeTirepabsltVal1 { "TirePValFrntLeTirepabsltVal1" };
const std::string TirePValReRi_UB { "TirePValReRi_UB" };
const std::string TirePValReLe_UB { "TirePValReLe_UB" };
const std::string TirePValFrntRi_UB { "TirePValFrntRi_UB" };
const std::string TirePValFrntRiTirePPosn { "TirePValFrntRiTirePPosn" };
const std::string TirePValFrntRiTirePAbsltValQF { "TirePValFrntRiTirePAbsltValQF" };
const std::string TirePValFrntRiTirePAbsltVal1 { "TirePValFrntRiTirePAbsltVal1" };
const std::string TirePWarnCmn_UB { "TirePWarnCmn_UB" };
const std::string TirePWarnCmnTirePWarn { "TirePWarnCmnTirePWarn" };
const std::string TirePWarnCmnTirePWarnType { "TirePWarnCmnTirePWarnType" };
const std::string TirePValReLeTirePPosn { "TirePValReLeTirePPosn" };
const std::string TirePValReLeTirePAbsltValQF { "TirePValReLeTirePAbsltValQF" };
const std::string TirePValReLeTirePAbsltVal1 { "TirePValReLeTirePAbsltVal1" };
const std::string TirePWarnFrntLe_UB { "TirePWarnFrntLe_UB" };
const std::string TirePWarnFrntLeTirePWarn { "TirePWarnFrntLeTirePWarn" };
const std::string TirePWarnFrntLeTirePWarnType { "TirePWarnFrntLeTirePWarnType" };
const std::string TirePValReRiTirePPosn { "TirePValReRiTirePPosn" };
const std::string TirePValReRiTirePAbsltValQF { "TirePValReRiTirePAbsltValQF" };
const std::string TirePValReRiTirePAbsltVal1 { "TirePValReRiTirePAbsltVal1" };


}
}
