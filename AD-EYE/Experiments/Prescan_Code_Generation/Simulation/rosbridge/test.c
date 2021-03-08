#include <arpa/inet.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define PORT 9090
#define TIMEOUT 10
#define SKIP_TESTS 17
#define TOTAL_TESTS 19
#define TOTAL_RUNS 3

/* clang-format off */
#define FUNC_DEF(func) {&func, #func}
/* clang-format on */

/* Test definitions */
void test_advertise_topic(int sock);
void test_unadvertise_topic(int sock);
void test_subscribe_to_topic(int sock);
void test_unsubscribe_from_topic(int sock);
void test_publish_to_topic(int sock);
void test_publish_to_topic_bool(int sock);
void test_publish_to_topic_clock(int sock);
void test_publish_to_topic_imu(int sock);
void test_publish_to_topic_int32(int sock);
void test_publish_to_topic_int32multiarray(int sock);
void test_publish_to_topic_odometry(int sock);
void test_publish_to_topic_pose(int sock);
void test_publish_to_topic_posearray(int sock);
void test_publish_to_topic_posestamped(int sock);
void test_publish_to_topic_twiststamped(int sock);
void test_publish_to_topic_float32multiarray_small(int sock);
void test_publish_to_topic_float32multiarray_large(int sock);
void test_publish_to_topic_image_small(int sock);
void test_publish_to_topic_image_large(int sock);

/* Global variables / types */
extern int errno;
static pthread_mutex_t printf_mutex;
typedef void (*f)(int);
struct
{
    f func;
    const char *name;
} test_funcs[] = {
    FUNC_DEF(test_advertise_topic),
    FUNC_DEF(test_unadvertise_topic),
    FUNC_DEF(test_subscribe_to_topic),
    FUNC_DEF(test_unsubscribe_from_topic),
    FUNC_DEF(test_publish_to_topic),
    FUNC_DEF(test_publish_to_topic_bool),
    FUNC_DEF(test_publish_to_topic_clock),
    FUNC_DEF(test_publish_to_topic_imu),
    FUNC_DEF(test_publish_to_topic_int32),
    FUNC_DEF(test_publish_to_topic_int32multiarray),
    FUNC_DEF(test_publish_to_topic_odometry),
    FUNC_DEF(test_publish_to_topic_pose),
    FUNC_DEF(test_publish_to_topic_posearray),
    FUNC_DEF(test_publish_to_topic_posestamped),
    FUNC_DEF(test_publish_to_topic_twiststamped),
    FUNC_DEF(test_publish_to_topic_float32multiarray_small),
    FUNC_DEF(test_publish_to_topic_float32multiarray_large),
    FUNC_DEF(test_publish_to_topic_image_small),
    FUNC_DEF(test_publish_to_topic_image_large)};

/* Tests */

void test_advertise_topic(int sock)
{
    advertise_topic(sock, "/my_topic", "my_message_type");
}

void test_unadvertise_topic(int sock)
{
    unadvertise_topic(sock, "/my_topic");
}

void test_subscribe_to_topic(int sock)
{
    subscribe_to_topic(sock, "/my_topic", "my_message_type");
}

void test_unsubscribe_from_topic(int sock)
{
    unsubscribe_from_topic(sock, "/my_topic");
}

void test_publish_to_topic(int sock)
{
    char *ros_msg = malloc(50 * sizeof(char));
    sprintf(ros_msg, "{\"data\": \"%s\"}", "Fake ROS message");
    publish_to_topic(sock, "/my_topic", ros_msg);
}

void test_publish_to_topic_bool(int sock)
{
    publish_to_topic_bool(sock, "/my_topic", false);
}

void test_publish_to_topic_clock(int sock)
{
    publish_to_topic_clock(sock, "/my_topic", LONG_MAX, LONG_MAX);
}

void test_publish_to_topic_imu(int sock)
{
    publish_to_topic_imu(sock, "/my_topic", INT_MAX, INT_MAX, DBL_MAX,
                         DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);
}

void test_publish_to_topic_int32(int sock)
{
    publish_to_topic_int32(sock, "/my_topic", INT_MAX);
}

void test_publish_to_topic_int32multiarray(int sock)
{
    int data[] = {1, 2, INT_MAX, 4, 5, -INT_MAX};
    publish_to_topic_int32multiarray(sock, "/my_topic", data, 6);
}

void test_publish_to_topic_odometry(int sock)
{
    publish_to_topic_odometry(sock, "/my_topic", INT_MAX, INT_MAX, INT_MAX, DBL_MAX,
                              DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX,
                              DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);
}

void test_publish_to_topic_pose(int sock)
{
    publish_to_topic_pose(sock, "/my_topic", DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX,
                          DBL_MAX, DBL_MAX, DBL_MAX);
}

void test_publish_to_topic_posearray(int sock)
{
    publish_to_topic_posearray(sock, "/my_topic", INT_MAX, INT_MAX, INT_MAX, DBL_MAX,
                               DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX,
                               INT_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX,
                               DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX,
                               DBL_MAX, DBL_MAX, DBL_MAX);
}

void test_publish_to_topic_posestamped(int sock)
{
    publish_to_topic_posestamped(sock, "/my_topic", INT_MAX, INT_MAX, INT_MAX, DBL_MAX,
                                 DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);
}

void test_publish_to_topic_twiststamped(int sock)
{
    publish_to_topic_twiststamped(sock, "/my_topic", INT_MAX, INT_MAX, DBL_MAX, DBL_MAX,
                                  DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);
}

void test_publish_to_topic_float32multiarray_small(int sock)
{
    float data[10] = {0.0};
    publish_to_topic_float32multiarray(sock, "/my_topic", data, 10);
}

void test_publish_to_topic_float32multiarray_large(int sock)
{
    float data[300000] = {0.0};
    publish_to_topic_float32multiarray(sock, "/my_topic", data, 300000);
}

void test_publish_to_topic_image_small(int sock)
{
    uint8_t data[9] = {0};
    publish_to_topic_image(sock, "/my_topic", 3, 3, 1, 3, data, 9, "/camera", 7);
}

void test_publish_to_topic_image_large(int sock)
{
    uint8_t data[90000] = {0};
    publish_to_topic_image(sock, "/my_topic", 300, 300, 1, 300, data, 90000, "/camera", 7);
}

/* Threads and main functions */

void *run_fake_server(void *args)
{
    char client_msg[900000];
    int read_size, sock, client_sock, c, option;
    struct sockaddr_in address, client;
    struct timeval tv;

    printf("Starting server...\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0)
    {
        perror("(Server error) socket");
    }

    /* Release port as soon as code stops (instead of default up to 4 minutes) */
    option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&address, sizeof(address)))
    {
        perror("(Server error) bind");
    }

    listen(sock, 1);

    c = sizeof(struct sockaddr_in);
    while (1)
    {
        client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);

        if (client_sock <= 0)
        {
            perror("(Server error) accept");
        }

        while (1)
        {
            memset(client_msg, 0, sizeof(client_msg));

            read_size = recv(client_sock, client_msg, 900000, 0);
            if (read_size == 0)
            {
                break;
            }
            else if (read_size < 0)
            {
                perror("(Server error) receive");
                break;
            }

            pthread_mutex_lock(&printf_mutex);
            printf("Server read: %s\n", client_msg);
            pthread_mutex_unlock(&printf_mutex);
        }
    }

    close(sock);
}

void *run_main_thread(void *args)
{
    int function_index, sock, run;

    function_index = SKIP_TESTS;
    while (1)
    {
        if (function_index == TOTAL_TESTS)
        {
            continue;
        }

        sock = create_connection(PORT, TIMEOUT);
        if (sock < 0)
        {
            perror("(Test client error) socket");
        }

        pthread_mutex_lock(&printf_mutex);
        printf("-----> Starting %s\n", test_funcs[function_index].name);
        printf("----------------------------------------------------------\n");
        pthread_mutex_unlock(&printf_mutex);

        for (run = 0; run < TOTAL_RUNS; run++)
        {
            sleep(1);
            pthread_mutex_lock(&printf_mutex);
            test_funcs[function_index].func(sock);
            pthread_mutex_unlock(&printf_mutex);
        }

        function_index++;
        close(sock);
    }
}

int main()
{
    pthread_t fake_server_thread_id, main_thread;

    signal(SIGPIPE, SIG_IGN);
    pthread_mutex_init(&printf_mutex, NULL);

    pthread_create(&fake_server_thread_id, NULL, run_fake_server, NULL);
    pthread_create(&main_thread, NULL, run_main_thread, NULL);

    pthread_join(fake_server_thread_id, NULL);
    pthread_join(main_thread, NULL);

    return 0;
}
