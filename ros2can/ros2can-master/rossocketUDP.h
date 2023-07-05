// 


#ifndef ADEYE_UDP_CLIENT_SERVER_H
#define ADEYE_UDP_CLIENT_SERVER_H


#define SERVER "localhost" //The IP of the host machine, in this case the PC containing the CANoe software
#define BUFLEN 512	//Max length of buffer
#define PORT 6666	//The port on which to send data


#include <fstream>
#include <iostream>
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include <unistd.h>
#include <iostream>
//#include <cstdint>
#include <unistd.h>
#include <net/if.h>

#include <sstream>


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "helpfuncs.h"

namespace FDxCommandE{
    enum Command
    {
        Start = 0x0001,
        Stop = 0x0002,
        Key = 0x0003,
        DataRequest = 0x0006,
        DataExchange = 0x0005,
        DataError = 0x0007,
        FreeRunning = 0x0008,
        FreeRunningCancel = 0x0009,
        Status = 0x0004,
        StatusRequest = 0x000A,
        SeqNumError = 0x000B,
    };
}

// Declaring commmands into their corresponding static variables
FDxCommandE::Command const static Start = FDxCommandE::Start;
FDxCommandE::Command const static Stop = FDxCommandE::Stop;
FDxCommandE::Command const static DataRequest = FDxCommandE::DataRequest;
FDxCommandE::Command const static DataExchange = FDxCommandE::DataExchange;
FDxCommandE::Command const static Status = FDxCommandE::Status;

//Frame Structure, important to follow notation
typedef struct group
{
  //cSize can at maximum be 8, groupID can maximum be the amount of groups you create
  uint16_t cGroupID;
  uint16_t cSize;

  uint8_t *commandlist;

};



int socketOpen(struct sockaddr_in &arg_si);
char *socketReceive(int s, struct sockaddr_in arg_si);
int socketSend_FDX(int s, struct sockaddr_in &si_other,  int option);
int socketSend_FDX(int s, struct sockaddr_in &si_other,  int option,  struct group p);
int requestData(int s, struct sockaddr_in &si_other);
void socketClose(int s);
void die(char *s);

#endif
