#ifndef HELP_FUNCTIONS
#define HELP_FUNCTIONS




#include <fstream>
#include <iostream>
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include <unistd.h>
#include <iostream>
//#include <cstdint>
#include <sstream>
using namespace std;



string uint2ASCII(unsigned long a);
string uint2ASCII(unsigned int a);
string uint2ASCII(unsigned short a);
string uint2ASCII(unsigned char a);
string float2ASCII(float f);
uint8_t ReadByte(char **arg_str);
uint16_t ReadUint16(char **arg_str);
uint64_t ReadUint64(char **arg_str);

#endif
