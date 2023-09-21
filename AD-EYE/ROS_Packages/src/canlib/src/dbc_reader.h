#ifndef __DBC_READER_H__
#define __DBC_READER_H__

#include "basic_types.h"


namespace kcan {


class DBCReader {
  public:
    static void init();
    static const FrameInfo &getFrameInfo(CANBus bus, uint id);
    static const FrameInfo &getFrameInfo(CANBus bus, const string &name);
    static const SignalGroupInfo &getSignalGroupInfo(CANBus bus, const string &name);
    static const SignalInfo &getSignalInfo(CANBus bus, const string &name);
};


} // namespace kcan

#endif