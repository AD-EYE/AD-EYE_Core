#ifndef __CAN_SOCKETCAN_H__
#define __CAN_SOCKETCAN_H__

#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

#include "spdlog/spdlog.h"

#include "can_interface.h"


namespace kcan {


using namespace std;


class SOCKETCANController: public CANInterface {
public:
    SOCKETCANController(string device_name, bool fd_on, bool receiving_log_on, bool sending_log_on) {
        spdlog::debug("Creating SOCKETCANController");
        device_name_ = device_name;
        is_can_fd_ = fd_on;
        receiving_log_on_ = receiving_log_on;
        sending_log_on_ = sending_log_on;

        socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);

        if (is_can_fd_) {
            int enable_canfd = 1;
            int st = setsockopt(
                socket_, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &enable_canfd, sizeof(enable_canfd)
            );
        }

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500000;
        setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

        ifreq ifr;
        strcpy(ifr.ifr_name, device_name_.c_str());
        ioctl(socket_, SIOCGIFINDEX, &ifr);

        sockaddr_can addr { };
        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;
        bind(socket_, (struct sockaddr *)&addr, sizeof(addr));
    }

    int send(CANFrame* fptr) {
        if (sending_log_on_) {
            fptr->log("Sending frame ");
        }
        sent_counter_++;
        canfd_frame frame;
        frame.len = fptr->getDataSize();
        frame.can_id = fptr->getFrameInfo().id;
        memcpy(frame.data, fptr->getData(), fptr->getDataSize());
        //cfd.flags = 0x4;
        write(socket_, &frame, is_can_fd_ ? 72 : 16);
    }

    int receive(CANFrame* fptr) {
        canfd_frame frame;
        size_t nbytes = read(socket_, &frame, sizeof(frame));
        if (nbytes != -1 && nbytes > 0) {
            received_counter_++;
            fptr->setId(frame.can_id);
            fptr->setRawData(frame.data, frame.len);
            if (receiving_log_on_) {
                fptr->log("Receiving frame ");
            }
            return frame.len;
        }
        return nbytes == -1 ? 0 : nbytes;
    }

    CANStatistics statistics() {
        CANStatistics s;
        s.frames_received = received_counter_;
        s.frames_sent = sent_counter_;
        return s;
    }

private:
    int socket_;
    bool is_can_fd_;
    bool receiving_log_on_;
    bool sending_log_on_;
    string device_name_;
    atomic<uint64_t> received_counter_ { 0 };
    atomic<uint64_t> sent_counter_ { 0 };
};


}

#endif
