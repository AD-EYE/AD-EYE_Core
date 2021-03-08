#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <signal.h>
#include <stdio.h>
#include <time.h>

#include "rosbridge_functions.h"
#include "counter.h"

static volatile sig_atomic_t keep_running = 1;

static void sig_handler(int _)
{
    (void)_;
    keep_running = 0;
}

int step_counter(int counter, int counter_limit) {
    return (counter + 1) % counter_limit;
}

void sleep_counter(int rate) {
    struct timespec ts;
    ts.tv_sec = 1 / rate;
    ts.tv_nsec = 1e9 / rate;

    nanosleep(&ts, &ts);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_handler);

    #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Failed. Error Code : %d", WSAGetLastError());
            return 1;
        }
    #endif

    int counter = 0;
    int counter_limit = 10;
    int rate = 10;
    int port = 9090;
    int socket_result = 0;
    int buffer_size = 1024;
    int timeout = 2;

    int sock = create_connection(port, timeout);

    socket_result = subscribe_to_topic(sock);
    if (socket_result < 0) {
        printf("Rosbridge error\n");
        return 1;
    }

    socket_result = advertise_topic(sock);
    if (socket_result < 0) {
        printf("Rosbridge error\n");
        return 1;
    }

    while(keep_running) {
        socket_result = listen_to_topic(sock, buffer_size);
        if (socket_result < 0) {
            printf("Rosbridge timout on listening\n");
        }

        counter = step_counter(counter, counter_limit);

        socket_result = publish_to_topic(sock, counter);
        if (socket_result < 0) {
            printf("Rosbridge error\n");
            return 1;
        }

        sleep_counter(rate);
    }

    socket_result = unsubscribe_from_topic(sock);
    if (socket_result < 0) {
        printf("Rosbridge error\n");
        return 1;
    }

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
