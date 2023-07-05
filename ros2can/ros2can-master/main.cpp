/* ROS2CAN Script */
/*
    Software written by Shaya Rahmanian and Simon Lindenfors.

    This script is the main function that executes all the other scripts.
*/
#include "rossocketCAN.h"
#include "databases/spa4710_configurations_spa3_ad_mid3_can_cfg_210226_.h"
#include "Crc/inc/Crc.h"
#include "E2E/inc/E2E.h"
#include "E2E/inc/E2E_P01.h"
#include "E2E/inc/E2E_P05.h"
//#include "roslisten.h"


//VCU1Mid3CanFr36
int main(int argc, char **argv){


    uint8_t dst_p[8];
    //uint8_t* dst_pointer = &dst_p;
    struct spa4710_configurations_spa3_ad_mid3_can_cfg_210226__etcvcu1_dev_send_mid3_fr1_t src_p; //declare structs
    src_p= { 0x03,0x05,0x02,0x03,0x04,0x05,0x07,0x08 }; //change here to change message

    struct spa4710_configurations_spa3_ad_mid3_can_cfg_210226__etcvcu1_dev_send_mid3_fr1_t* src_pointer = &src_p;
    size_t size = 8;
    
    struct can_frame frame;
    struct can_frame frame2;
    struct can_frame cfd;
    int nbytes;
    //structure to create frames with
    frame.can_id=0x123;
    frame.can_dlc = 4;  

    //declare integers
    frame.data[0] = 0x00; 
    frame.data[1] = 0x02; 
    frame.data[2] = 0x04; 
    frame.data[3] = 0x06;

    frame2.can_id= SPA4710_CONFIGURATIONS_SPA3_AD_MID3_CAN_CFG_210226__SSM_MID3_CAN_FR01_FRAME_ID;
    frame2.can_dlc = spa4710_configurations_spa3_ad_mid3_can_cfg_210226__etcvcu1_dev_send_mid3_fr1_pack(dst_p, src_pointer, size);
    
    memcpy(frame2.data, dst_p, sizeof(dst_p));

    struct sockaddr_can addr;
    socklen_t slen = sizeof(addr);
    int s;
    //int s2;
    uint8_t buffer[64];
    char stringarray[BUFLEN];
    char yes[BUFLEN];
    const char *can0 = "can0";
    //const char *can1 = "can1";
    
    s= socketOpen(addr, can0);
    //s2 = socketOpen(addr, can1);


    //frame2.data[5] =  Crc_CalculateCRC8(frame2.data, frame2.can_dlc, frame2.data[5], true);
    //printf("%d\n", frame2.data[5]);

    //uint16 computeOffsetP05(const E2E_P05ConfigType* ConfigPtr)
    //uint16 offsett = computeOffsetP05(ConfPtr);

    //uint16 computeCRCP05(const uint8* DataPtr, uint16 length, uint16 offset, uint16 dataId)
    //uint16 crc = computeCRCP05(frame2.data, frame2.can_dlc, );



    //typedef struct {
    /**
     * Bit offset of the first bit of the E2E header from the beginning of the Data (bit numbering: bit 0 is the least important).
     * The offset shall be a multiple of 8 and 0 ≤ Offset ≤ DataLength-(3*8).
     * Example: If Offset equals 8, then the low byte of the E2E Crc (16 bit) is written to Byte 1,
     * the high Byte is written to Byte 2.
     */
    //uint16 Offset;
    /**
     * Length of Data, in bits. The value shall be = 4096*8 (4kB) and shall be ≥ 3*8
     */
    //uint16 DataLength;
    /**
     * A system-unique identifier of the Data.
     */
    //uint16 DataID;
    /**
     * Maximum allowed gap between two counter values of two consecutively received valid Data. For example,
     * if the receiver gets Data with counter 1 and MaxDeltaCounter is 3,
     * then at the next reception the receiver can accept Counters with values 2, 3 or 4.
     */
    //uint8 MaxDeltaCounter;
    //} E2E_P05ConfigType;
    E2E_P05ConfigType ConfPtr;
    ConfPtr.Offset = 8; //TODO: Find correct offset
    ConfPtr.DataLength = frame2.can_dlc*8;
    ConfPtr.DataID = frame2.can_id;
    ConfPtr.MaxDeltaCounter = 4; //TODO: Find correct value

    //typedef struct {
    /**
     * Counter to be used for protecting the next Data. The initial value is 0,
     * which means that in the first cycle, Counter is 0.
     * Each time E2E_P05Protect() is called, it increments the counter up to 0xFF.
     */
    //uint8 Counter;
    //} E2E_P05ProtectStateType;
    E2E_P05ProtectStateType staPtr;
    staPtr.Counter = 0;

    //typedef struct {
    /**
     * Result of the verification of the Data in this cycle, determined by the Check function.
     */
    //E2E_P05CheckStatusType Status;
    /**
     * Counter of the data in previous cycle.
     */
    //uint8 Counter;
    //} E2E_P05CheckStateType;
    E2E_P05CheckStateType staChPtr;
    staChPtr.Counter = 0;
    
    //Std_ReturnType E2E_P05Protect(const E2E_P05ConfigType* ConfigPtr, E2E_P05ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length)
    Std_ReturnType e2eP5test = E2E_P05Protect(&ConfPtr, &staPtr, frame2.data, frame2.can_dlc);

    //Std_ReturnType E2E_P05Check(const E2E_P05ConfigType* ConfigPtr, E2E_P05CheckStateType* StatePtr, const uint8* DataPtr, uint16 Length)
    Std_ReturnType e2eP5testcheck = E2E_P05Check(&ConfPtr, &staChPtr, frame2.data, frame2.can_dlc);
    printf("Check %d\n", staChPtr.Status);

    //rosMain(argc, argv,s, si_other);

    bool send = true;
    while(send){
        printf("Enter message : ");
        fgets(stringarray, BUFLEN, stdin);

        //nbytes = write(s, &frame2, sizeof(struct can_frame));

        //printf("Wrote %d bytes\n", nbytes);

	nbytes = write(s, &frame2, sizeof(struct can_frame));

        printf("Wrote %d bytes\n", nbytes);

        //nbytes = write(s2, &frame2, sizeof(struct can_frame));

        //requestData(s, si_other);
    }

    nbytes = read(s, &cfd, sizeof(struct can_frame));
    //nbytes = write(s2, &cfd, sizeof(struct can_frame));

    
    printf("can_id: %X data length: %d data: ", cfd.can_id, cfd.can_dlc);
    for (size_t i = 0; i < cfd.can_dlc; i++){
        printf("%02X ", cfd.data[i]);
    }
    

    if (nbytes < 0) {
            perror("can raw socket read");
            return 1;
    }

    /* paranoid check ... */
    if (nbytes < sizeof(struct can_frame)) {
            fprintf(stderr, "read: incomplete CAN frame\n");
            return 1;
    }


    
    socketClose(s);
    
    return 0;
}


