/* Socket UDP to CANoe */
/*
    Software written for the AD-EYE team by the HK group of KTH Mechatronics students 2022 
    Specifically written by Axel Hedvall, Ehab Raheem, Oscar Poveda and Shaya Rahmanian.

    This script is used to communicate to the CANoe software using an UDP port
    By using the socket structure and assembling a header, the datagram packet constructed will be accepted by the software
    Sending a specific command to the CANoe software, a request to read data can also be made and received
*/
#include "rossocketCAN.h"



using namespace std;


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
int socketOpen(struct sockaddr_can arg_si, const char *ifname){
    int s;
 
    struct ifreq ifr;


	if ( (s=socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1)
	{
		perror("Error while opening socket");
        return -1;
	}

    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFINDEX, &ifr);

    arg_si.can_family = AF_CAN;
    arg_si.can_ifindex = ifr.ifr_ifindex;

    printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

    if (bind(s, (struct sockaddr *) &arg_si, sizeof(arg_si))== -1){
        perror("Error in socket bind");
        return -2;
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


/** Sending Data to CAN
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
int socketSend_VCAN(int s, struct sockaddr_in &si_other, struct group p)
{
    //declare socket length
    socklen_t slen=sizeof(si_other);
    size_t size;

    ostringstream command;
    //create header

    command << sendActivate(&p);

    size = p.cSize;
 
    //send message
    if (sendto(s, command.str().c_str(), size, 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    command.clear();
    return 0;
}




