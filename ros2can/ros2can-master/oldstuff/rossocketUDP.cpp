/* Socket UDP to CANoe */
/*
    Software written for the AD-EYE team by the HK group of KTH Mechatronics students 2022 
    Specifically written by Axel Hedvall, Ehab Raheem, Oscar Poveda and Shaya Rahmanian.

    This script is used to communicate to the CANoe software using an UDP port
    By using the socket structure and assembling a header, the datagram packet constructed will be accepted by the software
    Sending a specific command to the CANoe software, a request to read data can also be made and received
*/
#include "rossocketUDP.h"
using namespace std;

//defining the information that CANoe expect in every signal 
const uint64_t SIGNATURE = 0x584446656F4E4143;
unsigned char MAJOR_VERSION = 0x01;
unsigned char MINOR_VERSION = 0x00;
unsigned short NUMBER_OF_COMMANDS = 1;
unsigned short SEQUENCE_NUMBER = 0x8000;
unsigned short RESERVED = 0x0000;
unsigned short COMMAND_LENGTH = 4;

//Closes socket
void socketClose(int s){
    close(s);
}

//Not sure what this does but think it closes the socket on program error?
void die(char *s)
{
	perror(s);
	exit(1);
}

/** Open Socket
 * @brief 
 * Function opens up an UDP socket if it can, and returns the socket status as an integer
 * 
 * @param arg_si
 * The parameter follows the structure of the sockaddr_in from the socket.h
 * In this structure the address and the port of the opened socket is connected
 * 
 * @return int 
 * Socket Status 
 * 
 */
int socketOpen(struct sockaddr_in &arg_si){
    socklen_t slen=sizeof(arg_si);
    int s;

	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
   
	memset( (char*) &arg_si, 0, sizeof(arg_si) );
	arg_si.sin_family = AF_INET;
	arg_si.sin_port = htons(PORT);

	if (inet_aton(SERVER , &arg_si.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
    return s;
}

/** Receive Data on Socket
 * @brief 
 * Function receives data on the created socket
 * By passing in the sockaddr_in structure, the connected adress and port will be used
 * to receive data
 * 
 * @param s 
 * socket status
 * 
 * @param arg_si 
 * sockaddr_in structure
 * 
 * @return char*
 * returns a dynamic character array with the received data
 *  
 */
char *socketReceive(int s, struct sockaddr_in arg_si){
    char * buf = (char*)malloc(sizeof(char) * BUFLEN);

    socklen_t slen=sizeof(arg_si);
    //receive a reply and print it
    //clear the buffer by filling null, it might have previously received data
    memset(buf,'\0', BUFLEN);
    //try to receive some data, this is a blocking call
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &arg_si, &slen) == -1)
    {
        die("recvfrom()");
    }

    return buf;
}


/** DataExchange String Assembler
 * @brief 
 * This function assembles a C++ string from the group (frame) structure in order to create a datagram package. 
 * This is exclusively used by the dataExchange command in order to satisfy the CANoe message structure.
 * 
 * It will take the group structure and iterate through the member values and put them in their correct place
 * in the assembled string.
 * 
 * @param arg_acti 
 * The frame that is sent in, in this case a structure called group, devised by ourselves.
 * 
 * @return string
 * returns the assembled ASCII C++ string to be sent through the socket
 * 
 */
string sendActivate(struct group *arg_acti){
    string activate = "";

    //Add Command
    activate += uint2ASCII((uint16_t)(8 + arg_acti->cSize)); //size of command (8 + datasize
    activate += uint2ASCII((unsigned short) DataExchange);
    activate += uint2ASCII((arg_acti->cGroupID));
    activate += uint2ASCII(arg_acti->cSize);

    //string Activate, will loop through the group struct to add the uint8_t to the string
    
    for (size_t i = 0; i < arg_acti->cSize; i++)
    {
        printf("%d \n", arg_acti->commandlist[i]);
        activate += uint2ASCII(arg_acti->commandlist[i]);
    }
    

    return activate;
}


/** Sending Data to FDX (overloaded part 1)
 * @brief 
 * This function is the overloaded SocketSend_FDX function exclusively for the DataExchange command.
 * By passing in the socket status, address of sockaddr_in struct, the command option and the group structure,
 * the function will assemble a header for the CANoe datagram package and call the SendActivate function
 * to combine the header and the returned string into a character array that will be sent through the socket.
 * 
 * @param s 
 * @param si_other 
 * @param option 
 * @param p 
 * @return int 
 */
int socketSend_FDX(int s, struct sockaddr_in &si_other, int option, struct group p)
{
    //declare socket length
    socklen_t slen=sizeof(si_other);
    size_t size;

    ostringstream command;
    //create header
    command << uint2ASCII(SIGNATURE);
    command << uint2ASCII(MAJOR_VERSION);
    command << uint2ASCII(MINOR_VERSION);
    command << uint2ASCII(NUMBER_OF_COMMANDS);
    command << uint2ASCII(SEQUENCE_NUMBER);
    command << uint2ASCII(RESERVED);
    command << sendActivate(&p);

    size = 24 + p.cSize;
 
    //send message
    if (sendto(s, command.str().c_str(), size, 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    command.clear();
    return 0;
}

/** Sending Data to FDX (overloaded part 2)
 * @brief 
 * This function is the other part of the overloaded socketSend_FDX function. It will ignore the group structure,
 * and instead look through the option integer to determine which command it should send to the CANoe.
 * At this moment only the start and stop command exist, and what they will do is start the measurement inside
 * the CANoe software respectively terminate the measurement. 
 * 
 * @param s 
 * @param si_other 
 * @param option 
 * @return int 
 */
int socketSend_FDX(int s, struct sockaddr_in &si_other, int option)
{
    //declare socket length
    socklen_t slen=sizeof(si_other);
    size_t size;

    ostringstream command;
    //create header
    command << uint2ASCII(SIGNATURE);
    command << uint2ASCII(MAJOR_VERSION);
    command << uint2ASCII(MINOR_VERSION);
    command << uint2ASCII(NUMBER_OF_COMMANDS);
    command << uint2ASCII(SEQUENCE_NUMBER);
    command << uint2ASCII(RESERVED);

    //switch case for different commands
    switch (option)
    {
    case Start:
        command << uint2ASCII(COMMAND_LENGTH);
        command << uint2ASCII((unsigned short)Start);
        size = 20;
        break;
    case Stop:
        command << uint2ASCII(COMMAND_LENGTH);
        command << uint2ASCII((unsigned short)Stop);
        size = 20;
        break;
    }

    //sends the command on the socket
    if (sendto(s, command.str().c_str(), size, 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    //clears the command
    command.clear();
    return 0;
}


//datarequest per FDX structure
/**
 * @brief 
 * This function makes use of the DataRequest command. By executing this command, CANoe will
 * exectute it's own DataExchange command where it will send a datagram package from its side
 * to this software. This package must be treated like specified in the pdf for the FDX protocol.
 * This function is a prototype as we did not need to use it to enable our solution. Further work
 * on it is required as it would need a new parameter alongside the current two, containing the
 * group structure. The data should then be saved to the members inside the group structure.
 * 
 * @param s 
 * @param si_other 
 * @return int 
 */
int requestData(int s, struct sockaddr_in &si_other)
{
    socklen_t slen=sizeof(si_other);

    ostringstream convert;
    //Assemble Header
    convert << uint2ASCII(SIGNATURE);
    convert << uint2ASCII(MAJOR_VERSION);
    convert << uint2ASCII(MINOR_VERSION);
    convert << uint2ASCII(NUMBER_OF_COMMANDS);
    convert << uint2ASCII(SEQUENCE_NUMBER);
    convert << uint2ASCII(RESERVED);
    convert << uint2ASCII((uint16_t)6);
    convert << uint2ASCII((uint16_t)DataRequest);
    convert << uint2ASCII((uint16_t)0);
    

    printf("Sending: %s \n", convert.str().c_str());

    //Send the dataRequest command
    if (sendto(s, convert.str().c_str(), 22, 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }

    //Following the FDX protocol pdf on how to manage the datagram that is then received
    char * r = socketReceive(s, si_other);
    printf("Recived: %s\n", r);
    printf("Signature: 0x%llX\n", ReadUint64(&r));
    ReadByte(&r); // Major version
    ReadByte(&r); // Minor version
    uint16_t num = ReadUint16(&r);
    printf("Number of commands: 0x%X\n", num);
    ReadUint16(&r); // Sequence num
    ReadUint16(&r); // Reserved

    for (size_t i = 0; i < num; i++)
    {
        uint16_t size = ReadUint16(&r);
        printf("Size: 0x%X\n", size);
        uint16_t cmd = ReadUint16(&r);
        printf("Commad: 0x%X\n", cmd);
        switch (cmd)
        {
            //Simple status command from CANoe, will return status and timestamp of the CANoe Measurement
            case Status:
                printf("Measurement status: 0x%X\n", ReadByte(&r));
                ReadByte(&r); ReadByte(&r); ReadByte(&r); // Discard
                printf("Timestamp: %lli\n", ReadUint64(&r));
                break;
            
            //CANoe's DataExchange, where the requested data is collected
            case DataExchange:
                ReadUint16(&r); // Group id
                uint16_t dataSize = ReadUint16(&r);
                printf("Data size: 0x%X\n", dataSize);
                for (size_t i = 0; i < dataSize; i++)
                {
                    printf("\tData%i: 0x%X\n", i, ReadByte(&r));
                }
                break;
        }
    }

	return 0;
}



