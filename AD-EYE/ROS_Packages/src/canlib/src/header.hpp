#include <cstddef>
#include <string>
#include <vector>
#include <set>
#include <map>
//#include <variant>

#include "packer.h"
#include "dbc.h"

namespace kcan {

using namespace std;
using namespace kcan_dbc;



enum TrStatus {
    SUCCESS
};

enum Signals {
    Sig1Nmane = "Sig1Name",
};


class SignalValues {
public:
    void addSignal(const string& name, uint64_t val) {
        values_.insert({name, val});
    }
    uint64_t getValue(const string& name) {
        return values_.find(name)->second;
    }
private:
    map<string, uint64_t> values_;
};



// typedef uint16_t word;
// typedef uint8_t byte;
// typedef uint32_t dword;

// word CRC_INITIAL_VALUE16=0xFFFF; 
// word CRC_POLYNOMIAL_16=0x1021; 

// word Crc_CalculateCRC16(byte data[], dword Crc_Length, dword Crc_StartValue16, byte Crc_IsFirstCall);

// word E2E_P05ProtectMsg(byte data[], dword offs, dword length, word DataID)  { 

// 	byte temp[2]; 
// 	dword crc; 

// 	/* #16 CRC is positioned in first bytes of DataPtr. Calculate CRC over all residual bytes */ 
// 	crc = Crc_CalculateCRC16 (data, length, 0xffff, 0x1); 

// 	/* #20 Calculate CRC over DataID _after_ calculating CRC over the data. Use little endian byte order */ 
// 	temp[0] = (byte) (DataID & 0xff);  
// 	temp[1] = (byte) (DataID >> 8); 
// 	crc = Crc_CalculateCRC16 (temp, 2, crc, 0x0);  

// 	return crc; 
// } 


// word Crc_CalculateCRC16(byte data[], dword Crc_Length, dword Crc_StartValue16, byte Crc_IsFirstCall) { 
// 	dword Crc_Value; 
// 	dword Crc_DataPtrAddr; 
// 	word offset; 

// 	if (Crc_IsFirstCall == 0x1) { 
// 		Crc_Value = CRC_INITIAL_VALUE16; 
// 		offset=2; 
// 	} 
// 	else { 
// 		Crc_Value = Crc_StartValue16; 
// 		offset=0; 
// 	} 

// 	for (Crc_DataPtrAddr = offset; Crc_DataPtrAddr < Crc_Length; Crc_DataPtrAddr++) { //ignore the last byte, this is UB  
// 		dword Crc_LoopCounter; 

// 		/* #40 XOR next byte of Crc_DataPtr with current CRC value. This is equivalent to calculating CRC value of concatenated bytes */ 
// 		Crc_Value ^= ((dword)data[Crc_DataPtrAddr] << 8); 

// 		/* #50 Perform modulo-2 division, a bit at a time */ 
// 		for (Crc_LoopCounter = 0; Crc_LoopCounter < 8; Crc_LoopCounter++) { 

// 		/* #35 If MSB is 1, CRC value is XORed with polynomial */ 
// 		if ((Crc_Value & (dword)0x8000) > 0) { 
// 			Crc_Value = ( (dword)(Crc_Value << 1) ) ^ CRC_POLYNOMIAL_16; 
// 		} 
// 		else { 
// 			Crc_Value = Crc_Value << 1; 
// 		} 
// 		} 
// 	} 
// 	return Crc_Value; 
// } 



// Std_ReturnType E2E_P01Protect(const E2E_P01ConfigType* ConfigPtr, E2E_P01ProtectStateType* StatePtr, uint8* DataPtr) {

//     Std_ReturnType status;
//     status = E2E_E_OK;
//     Std_ReturnType returnValue = checkConfigP01(ConfigPtr);

//     if (E2E_E_OK != returnValue) {
//         status = returnValue;
//     }

//     else if ((StatePtr == NULL_PTR) || (DataPtr == NULL_PTR)) {
//         status = E2E_E_INPUTERR_NULL;
//     }

//     else {
//         /* Put counter in data*/
//         if ((ConfigPtr->CounterOffset % 8) == 0) {
//             DataPtr[ConfigPtr->CounterOffset/8] = (DataPtr[(ConfigPtr->CounterOffset/8)] & 0xF0u) | (StatePtr->Counter & 0x0Fu);
//         }
//         else {
//             DataPtr[ConfigPtr->CounterOffset/8] = (DataPtr[ConfigPtr->CounterOffset/8] & 0x0Fu) | ((StatePtr->Counter<<4) & 0xF0u);
//         }

//         /* Put counter in data for E2E_P01_DATAID_NIBBLE */ // ASR4.2.2
//         if (ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE) {
//             if ((ConfigPtr->DataIDNibbleOffset % 8) == 0) {
//                 DataPtr[ConfigPtr->DataIDNibbleOffset/8] = (DataPtr[(ConfigPtr->DataIDNibbleOffset/8)] & 0xF0u) | ((uint8)((ConfigPtr->DataID>>8) & 0x0Fu));
//             }
//             else {
//                 DataPtr[ConfigPtr->DataIDNibbleOffset/8] = (DataPtr[ConfigPtr->DataIDNibbleOffset/8] & 0x0Fu) | ((uint8)((ConfigPtr->DataID>>4) & 0xF0u));
//             }
//         }

//         /* Calculate CRC */
//         DataPtr[(ConfigPtr->CRCOffset/8)] = calculateCrcP01(ConfigPtr, StatePtr->Counter, DataPtr);

//         /* Update counter */
//         StatePtr->Counter = (StatePtr->Counter+1) % 15;
//     }

//     return status;
// }



void f() {
    SignalValues sv;
    sv.addSignal("sig1", 1);
    sv.addSignal("sig2", 3);

    FrameInfo fi { getFrameInfo() };
    for (auto sg_name : fi.signal_groups) {
        SignalGroupInfo sgi { getSignalGroupInfo(sg_name) };
        for (auto s_name : sgi.signals) {
            SignalInfo si { getSignalInfo(s_name) };
            Packer::pack(data, si.start_bit, si.length, sv.getValue());
        }
        crc = applyProfile(sgi.e2e_profile, sv)
        Packer::pack(data, crc_start_bit, crc_length, crc);
    }
}


// void protect(SignalGroupInfo& sgi, SignalValues& sv) {
//     vector<uint8_t> data((sgi.length + 7) / 8, 0xff);
//     for (auto s_name : sgi.signals) {
//         SignalInfo si { getSignalInfo(s_name) };
//         Packer::pack(data, si.start_bit, si.length, sv.getValue(si.name));
//     }
//     cout << E2E_P05ProtectMsg(data.data, 0, sqi.lenght, 5);
    
// }


class DBCReader {
public:
    

private:
    map<SginalName, SignalInfo> sname_sinfo_;

    map<FrameName, FrameInfo> fname_finfo_;
    map<FrameId, FrameName> fid_fname_;
};



/*
    int CounterOffset = 8; //Bits
    int CRCOffset = 0; //Bits
    int DataID = 0x0;
    int DataIDNibbleOffset = 0; //Not used in BOTH configuration
    int DataIDMode = E2E_P01_DATAID_BOTH;
    int DataLength = 0; //Bits
    int MaxDeltaCounterInit = 15;
    int MaxNoNewOrRepeatedData = 15;
    int SyncCounterInit = 15;

    int Offset = 0; //Bits
    int DataLength = 0; //Bits
    int MaxDeltaCounter = 20;


struct E2E_State {};


struct E2E_P01State: E2E_State {
    E2E_P01ProtectState protect;
    E2E_P01CheckState check;
}

struct E2E_P05State: E2E_State {
    E2E_P05ProtectState protect;
    E2E_P05CheckState check;
} */


class Frame {
public:
    Frame(string& name) {
        FrameInfo const& fi = getFrameInfo(name);
        for (auto sg_name : fi.signal_groups) {
            e2e_protectors_.insert({ sg_name, new CANE2EProtector(sg_name) });
        }
    }

    void setSignalGroup(string& name, SignalValues& values) {

        for (auto s_name : sgi.signals) {
            SignalInfo si { getSignalInfo(s_name) };
            Packer::pack(data, si.start_bit, si.length, sv.getValue(si.name));
        }
        uint16_t crc = protect(sgi, sv);
        Packer::pack(data, crc_start_bit, crc_length, crc);
                
        e2e_protectors_.find(sgi.name)->second->applyProfile(data_);

    }

    void setSignal(SignalInfo& si, uint64_t val) {
        validateSignal(si);
        Packer::pack(data_, si.start_bit, si.length, val);
        active_signals_.emplace(si.name);
    }

    void unsetSignal(signal_info& si) {
        validateSignal(si);
        if (active_signals_.count(si.name)) {
            active_signals_.erase(si.name);
            if (active_signals_.size() == 0) {
                stop();
            }
        }
    }

    void send() {
        lock_.acquire();
        for (signal_group in signal_groups_) {
            protect(signal_group)
        }
        lock_.release();
    }


    void protect(string& signal_group) {
        SignalGroupInfo sgi { getSignalGroupInfo(signal_group) };
        sgi.E2EProfile;
    }

    void loop() const {
        while (active_) {
            send(frame->payload);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval_));
        }
    }

    void start() {
        th_ = new thread { &Frame::loop, ref(*this) };
    }

    void stop() {
        active_ = false;
        // th_.join();
    }

    bool isActive() {
        return active_;
    }

private:
    void validateSignal(signal_info& si) {
        if (si.frame_name != fi_.name) {
            throw "Signal doesn't belong to the frame!";
        }
    }

    FrameInfo& frame_info_;
    set<std::string> active_signals_;
    thread* th_;
    bool active_ { true };
    std::vector<uint8_t> data_;
    map<std::string, CANE2EProtector*> e2e_protectors_;

};

class E2EProtector {
public:
    CANE2EProtector(string& sg_name) : sg_name_ { sg_name } {
        SignalGroupInfo const& sgi = getSignalGroupInfo(sg_name_);
        switch (sgi.e2e_profile) {
            case E2EProfileType::P05: 
                e2e_state_ = new E2E_P05State;
                break;
            case E2EProfileType::P01a: 
                e2e_state_ = new E2E_P01State;
                break;
        }
    }

    int applyProfile(vector<uint8_t>& data);
    int checkProfile(vector<uint8_t>& data);

private:
    string sg_name_;
    E2E_State* e2e_state_;
};

/*
class CANSendLoop {
public: 
    CANSendLoop(Frame* frame): frame_ { frame } { 
        th_ = new thread { &CANSendLoop::loop, ref(*this));
    }

    void loop () const {
        while (active_) {
            frame.lock.acquire();
            send(frame->payload);
            frame.lock.release();
            std::this_thread::sleep_for(std::chrono::milliseconds(frame->interval));
        }
    }

    void stop(signals) {
        active_ = false;
    }

private:
    bool active_ { true };
};
*/






}



