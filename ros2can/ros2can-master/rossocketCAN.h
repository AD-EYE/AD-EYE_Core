// 


#ifndef ADEYE_UDP_CLIENT_SERVER_H
#define ADEYE_UDP_CLIENT_SERVER_H


#define SERVER "130.229.140.176" //The IP of the host machine, in this case the PC containing the CANoe software
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




//Frame Structure, important to follow notation
struct group
{
  //cSize can at maximum be 8, groupID can maximum be the amount of groups you create
  uint16_t cGroupID;
  uint16_t cSize;

  uint8_t *commandlist;

};



int socketOpen(struct sockaddr_can addr, const char *ifname);
char *socketReceive(int s, struct sockaddr_in arg_si);
int socketSend_VCAN(int s, struct sockaddr_in &si_other, struct group p);
void socketClose(int s);
void die(char *s);

#endif
