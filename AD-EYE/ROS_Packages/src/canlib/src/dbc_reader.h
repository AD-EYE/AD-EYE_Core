#ifndef __DBC_READER_H__
#define __DBC_READER_H__

#include "basic_types.h"


namespace kcan {


class DBCReader {
public:
    static void init();
    static const FrameInfo& getFrameInfo(uint id);
    static const FrameInfo& getFrameInfo(const string& name);
    static const SignalGroupInfo& getSignalGroupInfo(const string& name);
    static const SignalInfo& getSignalInfo(const string& name);
};


}

#endif