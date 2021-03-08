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
#include <string.h>

#include "rosbridge_functions.h"

int send_message_to_rosbridge(int sock, char *msg)
{
    return send(sock, msg, strlen(msg), 0);
}

int listen_to_topic(int sock, int buffer_size)
{
    char msg[1024];

    int socket_result = recv(sock, msg, buffer_size, 0);
    printf("Data from rosbridge: %s\n", msg);

    return socket_result;
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

int publish_to_topic(int sock, char *topic, float data)
{
    /* Create JSON message */
    char *original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    char ros_msg[500];
    sprintf(ros_msg, "{\"data\": %.1f}", data);

    setlocale(LC_NUMERIC, original_locale);

    /* Publish to topic */
    char msg[600];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

int subscribe_to_topic(int sock, char *topic)
{
    char msg[200];
    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\"}", OP_SUBSCRIBE, topic);
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
