#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#define OP_ADVERTISE "advertise"
#define OP_PUBLISH "publish"
#define OP_SUBSCRIBE "subscribe"
#define OP_UNADVERTISE "unadvertise"
#define OP_UNSUBSCRIBE "unsubscribe"

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#include <locale.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "rosbridge_functions.h"

int get_index_from_letter(char letter, int second_time) {
    if (letter == 'x') {
        return second_time * 3 + 0;
    }
    else if (letter == 'y') {
        return second_time * 3 + 1;
    }
    else if (letter == 'z') {
        return second_time * 3 + 2;
    }
}

int send_message_to_rosbridge(int sock, char *msg)
{
    return send(sock, msg, strlen(msg), 0);
}

int listen_to_topic_int16(int sock, int buffer_size)
{
    char msg[1024];

    int socket_result = recv(sock, msg, buffer_size, 0);
    
    int ind;
    int number_start = 0;
    char number[6];
    char* pos = number;
    for(ind = 0; ind < buffer_size; ind++) {
        char c = *(msg + ind);
        if (c == ':') {
            number_start = 1;
            continue;
        }
        else if (c == '}') {
            break;
        }
        if (number_start == 1) {
            pos += sprintf(pos, "%c", c);
        }
    }

    return atoi(number);
}

void listen_to_topic_twiststamped(int sock, int buffer_size, float numbers[6])
{
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char msg[1024];

    int socket_result = recv(sock, msg, buffer_size, 0);
    printf("Message from ROS: %s\n", msg);
    
    int ind;
    int number_ind = 0;
    int number_start = 0;
    char number[20];
    char* pos = number;
    char letter = 'y';
    int second_time = 0;
    for(ind = 0; ind < buffer_size - 2; ind++) {
        char c = *(msg + ind);
        char d = *(msg + ind + 1);
        char e = *(msg + ind + 2);

        if ((c == 'x' || c == 'y' || c == 'z') && d == '"' && e == ':') {
            letter = c;
            number_start = 1;
            continue;
        }
        if (number_start == 1 && (e == ',' || e == '}')) {
            number_ind = get_index_from_letter(letter, second_time);
            numbers[number_ind] = atof(number);
            number_start = 0;
            memset(number, 0, 20);
            pos = number;

            if (e == '}') {
                second_time = 1;
            }

            continue;
        }
        if (number_start == 1) {
            pos += sprintf(pos, "%c", e);
        }
    }

    setlocale(LC_NUMERIC, original_locale);

}

int advertise_topic(int sock, char *topic, char *message_type)
{
    char msg[200];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"type\": \"%s\"}", OP_ADVERTISE, topic, message_type);
    return send_message_to_rosbridge(sock, msg);
}

int unadvertise_topic(int sock, char *topic)
{
    char msg[200];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\"}", OP_UNADVERTISE, topic);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_bool(int sock, char *topic, bool data)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg[500];
    sprintf(ros_msg, "{\"data\": %s}", data ? "true" : "false");

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_clock(int sock, char *topic, time_t secs, time_t nsecs)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg[500];
    sprintf(ros_msg, "{\"clock\": {\"secs\": %d, \"nsecs\": %d}}", secs, nsecs);

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_float32multiarray(int sock, char *topic, float data[], int size)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char data_array[300];
    char *pos = data_array;
    
    int i;
    for(i = 0; i < size; i++){
        if (i == 0){
            pos += sprintf(pos, "[%.1f", data[i]);
        }
        else if (i == size-1){
            pos += sprintf(pos, ", %.1f]", data[i]);
        }
        else{
            pos += sprintf(pos, ",%.1f", data[i]);
        }
    }
    char ros_msg [500];
    sprintf(ros_msg, "{\"data\": %s, \"layout\": {\"data_offset\": 0, \"dim\": [{\"label\": \"\", \"size\": %d, \"stride\": 0}]}}", data_array, size);

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_image(int sock, char *topic, int height, int width, int encoding_length, int step, int data[], int data_length, int frameId_length)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");
    
    char data_array[1048576];
    char *pos = data_array;
    
    int i;
    int size = step * height;
    for(i = 0; i < size; i++){
        if (i == 0){
            pos += sprintf(pos, "[%d", data[i]);
        }
        else if (i == size-1){
            pos += sprintf(pos, ", %d]", data[i]);
        }
        else{
            pos += sprintf(pos, ",%d", data[i]);
        }
    }   
    
    char ros_msg[1049000];
    sprintf(ros_msg, "{\"header\": {\"stamp\": %lu, \"frame_id\": \"/camera_1\"}, \"height\": %d, \"width\": %d, \"step\": %d, \"data\": %s}", (unsigned long)time(NULL), height, width, step, data_array);

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[1050000];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_imu(int sock, char *topic, int seq, int frameId_length,
                     double orientW, double orientX, double orientY, double orientZ,
                     double angularZ, double linearAccX, double linearAccZ){
    
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg [500];
    
    double zero = 0.0;
    
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"velodyne\" }, \
                       \"orientation\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f, \"w\": %.1f}, \
                       \"angular_velocity\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \
                       \"linear_acceleration\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}",
                       seq, (unsigned long)time(NULL), orientX, orientY, orientZ, orientW, zero, zero, angularZ, linearAccX, zero, linearAccZ);
    
    setlocale(LC_NUMERIC, original_locale);
    /*printf("%s\n", ros_msg);
     */

    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);

    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_int32(int sock, char *topic, int data)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg[500];
    sprintf(ros_msg, "{\"data\": %d}", data);

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_int32multiarray(int sock, char *topic, int data[], int size)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");
    
    char data_array[300];
    char *pos = data_array;
    
    int i;
    for(i = 0; i < size; i++){
        if (i == 0){
            pos += sprintf(pos, "[%d", data[i]);
        }
        else if (i == size-1){
            pos += sprintf(pos, ", %d]", data[i]);
        }
        else{
            pos += sprintf(pos, ",%d", data[i]);
        }
    }
    char ros_msg[500];
    sprintf(ros_msg, "{\"data\": %s, \"layout\": {\"data_offset\": 0, \"dim\": [{\"label\": "", \"size\": %d, \"stride\": 0}]}}", data_array, size);
    
    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_odometry(int sock, char *topic, int seq, int frameId_length, int childFrameId_length,
                     double positionX, double positionY, double positionZ,
                     double orientW, double orientX, double orientY, double orientZ,
                     double linearX, double linearY, double linearZ,
                     double angularX, double angularY, double angularZ){
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg [3000];
    
    double a = 1.1;
    char covariance[300];
    char *pos = covariance;
    
    int size = 36;
    
    int i;
    for(i = 0; i < size; i++){
        if (i == 0){
            pos += sprintf(pos, "[%.1f", a);
        }
        else if(i == size-1){
            pos += sprintf(pos, ", %.1f]", a);
        }
        else{
            pos += sprintf(pos, ", %.1f", a);
        }
    }
    
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"/base_link\" }, \
                       \"child_frame_id\": \"/base_link\",\
                       \"pose\": {\"pose\": {\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \
                                             \"orientation\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f, \"w\": %.1f}}, \
                                  \"covariance\": %s}, \
                       \"twist\": {\"twist\": {\"linear\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \
                                               \"angular\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}, \
                                   \"covariance\": %s}}",
                       seq, (unsigned long)time(NULL), positionX, positionY, positionZ, orientX, orientY, orientZ, orientW, covariance, linearX, linearY, linearZ, angularX, angularY, angularZ, covariance);
    
    setlocale(LC_NUMERIC, original_locale);
    /*printf("%s\n", ros_msg);
     */
    char msg[3500];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_pose(int sock, char *topic,
                     double positionX, double positionY, double positionZ,
                     double orientationW, double orientationX, double orientationY, double orientationZ){
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg [500];
    sprintf(ros_msg, "{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \
                       \"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}", 
                       positionX, positionY, positionZ, orientationW, orientationX, orientationY, orientationZ);
    
    setlocale(LC_NUMERIC, original_locale);    
    /*printf("%s\n", ros_msg);
     */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);



    printf("Publishing to topic...\n");
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_posearray(int sock, char *topic, int seq, int frameId_length, double positionX, double positionY, double positionZ, double orientationW, double orientationX, double orientationY, double orientationZ, int poses_length)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg[500];
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"/map\"}, \"poses\": [{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}]}", seq, (unsigned long)time(NULL), positionX, positionY, positionZ, orientationW, orientationX, orientationY, orientationZ);

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_posestamped(int sock, char *topic, int seq, int frameId_length,
                     double positionX, double positionY, double positionZ,
                     double orientationW, double orientationX, double orientationY, double orientationZ){
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg [500];
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"world\"}, \
                       \"pose\":{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \
                                 \"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}}", 
                       seq, (unsigned long)time(NULL), positionX, positionY, positionZ, orientationW, orientationX, orientationY, orientationZ);
    
    setlocale(LC_NUMERIC, original_locale);    
    /*printf("%s\n", ros_msg);
     */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);

    printf("Publishing to topic...\n");
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic_twiststamped(int sock, char *topic, int seq, int frameId_length,
                     double linearX, double linearY, double linearZ,
                     double angularX, double angularY, double angularZ ){
    
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg [500];
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"frame_id\": \"/base_link\", \"stamp\": %lu}, \
                       \"twist\":{\"linear\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \
                                  \"angular\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}}", 
                       seq, (unsigned long)time(NULL), linearX, linearY, linearZ, angularX, angularY, angularZ);
    
    setlocale(LC_NUMERIC, original_locale);
    /*printf("%s\n", ros_msg);
    */
    /*char* op = "publish";
    char* topic = "/counter";
    */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    /*printf("Publishing to topic...\n");
    */
    return send_message_to_rosbridge(sock, msg);
}

int subscribe_to_topic(int sock, char *topic, char *message_type)
{
    char msg[200];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"type\": \"%s\"}", OP_SUBSCRIBE, topic, message_type);
    return send_message_to_rosbridge(sock, msg);
}

int unsubscribe_from_topic(int sock, char *topic)
{
    char msg[200];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\"}", OP_UNSUBSCRIBE, topic);
    return send_message_to_rosbridge(sock, msg);
}

int create_connection(int port, int timeout)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);

    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);

    int socket_result = connect(sock, (struct sockaddr *)&address, sizeof(address));

#ifdef _WIN32
    if (socket_result < 0)
    {
        printf("Couldn't connect to rosbridge: %d\n", WSAGetLastError());
        return -1;
    }
#endif

    return sock;
}
