/* Small library containing help functions */
/*
    Software written for the AD-EYE team by the HK group of KTH Mechatronics students 2022 
    Specifically written by Axel Hedvall, Ehab Raheem, Oscar Poveda and Shaya Rahmanian.

    This script is used to communicate to the CANoe software using an UDP port
    By using the socket structure and assembling a header, the datagram packet constructed will be accepted by the software
    Sending a specific command to the CANoe software, a request to read data can also be made and received
*/

#include "helpfuncs.h"

/** 64 bit (8 byte) to ASCII
 * @brief 
 * Function that converts an unsigned long (uint64_t) to a C++ string
 * 
 * @param uint64_t
 * @return returnstring
 * Returns the ASCII string
 */
string uint2ASCII(unsigned long a){
    unsigned char bytes[8];
    string returnstring;

    //extract the individual bytes
    for ( int i = 0; i < 8; i++ )
    {
        bytes[i] = a >> (8 * i) & 0xFF;
    }

    //print the individual bytes
    for ( int i = 0; i < 8; i++ )
    {
        returnstring = returnstring + (char) bytes[i] ;
    }
    //printf("%s", returnstring.c_str());
    return returnstring;
}

/** 32 bit (4 byte) to ASCII
 * @brief 
 * Function that converts an unsigned int (uint32_t) to a C++ string
 * 
 * @param uint32_t
 * @return returnstring
 * Returns the ASCII string
 */
string uint2ASCII(unsigned int a){
    unsigned char bytes[4];
    string returnstring;

    //extract the individual bytes
    for ( int i = 0; i < 4; i++ )
    {
        bytes[i] = a >> (8 * i) & 0xFF;
    }

    //print the individual bytes
    for ( int i = 0; i < 4; i++ )
    {
        returnstring = returnstring + (char) bytes[i] ;
    }
    //printf("%s", returnstring.c_str());
    return returnstring;
}

/** 16 bit (2 byte) to ASCII
 * @brief 
 * Function that converts an unsigned long (uint16_t) to a C++ string
 * 
 * @param uint16_t
 * @return returnstring
 * Returns the ASCII string
 */
string uint2ASCII(unsigned short a){
    unsigned char bytes[2];
    string returnstring;

    //extract the individual bytes
    for ( int i = 0; i < 2; i++ )
    {
        bytes[i] = a >> (8 * i) & 0xFF;
    }

    //print the individual bytes
    for ( int i = 0; i < 2; i++ )
    {
        returnstring = returnstring + (char) bytes[i] ;
    }
    //printf("%s", returnstring.c_str());
    return returnstring;
}

/** 8 bit (1 byte) to ASCII
 * @brief 
 * Function that converts an unsigned long (uint8_t) to a C++ string
 * 
 * @param uint8_t
 * @return returnstring
 * Returns the ASCII string
 */
string uint2ASCII(unsigned char a){
    unsigned char bytes[1];
    string returnstring;

    //extract the individual bytes
    for ( int i = 0; i < 1; i++ )
    {
        bytes[i] = a >> (8 * i) & 0xFF;
    }

    //print the individual bytes
    for ( int i = 0; i < 1; i++ )
    {
        returnstring = returnstring + (char) bytes[i] ;
    }
    //printf("%s", returnstring.c_str());
    return returnstring;
}

/** Float 32 bit to ASCII
 * @brief 
 * Function that converts a 32 bit float to ASCII
 * Defunct and not really working
 * 
 * @param f
 */
string float2ASCII(float f)
{
    uint32_t *a = (uint32_t *)&f;
    return uint2ASCII(*a);
}

/** Read a byte
 * @brief 
 * Function that reads a byte from a character array, and then cuts it out
 * and returns the byte. The character array will then have the byte removed.
 * 
 * @param arg_str
 * @return byteboi
 * Returns a byte
 */
uint8_t ReadByte(char **arg_str)
{
    uint8_t byteboi = (*arg_str)[0];
    (*arg_str) = (*arg_str) +1;
    return byteboi;
}

/** Read two bytes
 * @brief 
 * Function that reads two bytes from a character array, and then cuts it out
 * and returns the two bytes. The character array will then have the two bytes removed.
 * 
 * @param arg_str
 * @return twobyteboi
 * Returns two bytes
 */
uint16_t ReadUint16(char **arg_str)
{
    uint16_t twobyteboi = 0;
    for (size_t i = 0; i < 2; i++)
    {
        twobyteboi =  (uint16_t)(*arg_str)[i] << (8 * i) | twobyteboi ;
    }
    
    (*arg_str) = (*arg_str) +2;
    return twobyteboi;
}

/** Read 8 bytes
 * @brief 
 * Function that reads 8 bytes from a character array, and then cuts it out
 * and returns 8 bytes. The character array will then have the 8 bytes removed.
 * 
 * @param arg_str
 * @return siddyfourbyteboi
 * Returns 8 bytes
 */
uint64_t ReadUint64(char **arg_str)
{
    uint64_t siddyfourbyteboi = 0;
    for (size_t i = 0; i < 8; i++)
    {
        siddyfourbyteboi =  (uint64_t)(*arg_str)[i] << (8 * i)  | siddyfourbyteboi ;
    }

    (*arg_str) = (*arg_str) +8;
    return siddyfourbyteboi;
}