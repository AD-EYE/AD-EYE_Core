#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

#include "rosbridge_functions.h"

/* Helper functions */

int get_index_from_letter(char letter, int second_time)
{
    if (letter == 'x')
    {
        return second_time * 3 + 0;
    }
    else if (letter == 'y')
    {
        return second_time * 3 + 1;
    }
    else if (letter == 'z')
    {
        return second_time * 3 + 2;
    }
}

/* Socket functions */

int create_connection(int port, int timeout)
{
    int sock, socket_result, connection_attempts;
    struct sockaddr_in address;
    struct timeval tv;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);

    tv.tv_sec = 0;
    tv.tv_usec = timeout;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);

    connection_attempts = 0;
    while ((socket_result = connect(sock, (struct sockaddr *)&address, sizeof(address))) < 0)
    {
        if (connection_attempts > 3)
        {
            break;
        }

#ifdef _WIN32
        printf("Couldn't connect to rosbridge: %d. Will retry...\n", WSAGetLastError());
        Sleep(1000);
#else
        perror("Couldn't connect to rosbridge. Will retry...");
        sleep(1);
#endif
        connection_attempts++;
    }

    return sock;
}

/* Generic rosbridge functions */

int send_message_to_rosbridge(int sock, char *msg)
{
    int result = send(sock, msg, strlen(msg), 0);
    free(msg);
    return result;
}

int advertise_topic(int sock, char *topic, char *message_type)
{
    int payload_size = strlen(OP_ADVERTISE) + strlen(topic) + strlen(message_type);
    char *msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));

    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"type\": \"%s\"}",
            OP_ADVERTISE, topic, message_type);
    return send_message_to_rosbridge(sock, msg);
}

int unadvertise_topic(int sock, char *topic)
{
    int payload_size = strlen(OP_UNADVERTISE) + strlen(topic);
    char *msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));

    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\"}", OP_UNADVERTISE, topic);
    return send_message_to_rosbridge(sock, msg);
}

int subscribe_to_topic(int sock, char *topic, char *message_type)
{
    int payload_size = strlen(OP_SUBSCRIBE) + strlen(topic) + strlen(message_type);
    char *msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));

    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"type\": \"%s\"}",
            OP_SUBSCRIBE, topic, message_type);
    return send_message_to_rosbridge(sock, msg);
}

int unsubscribe_from_topic(int sock, char *topic)
{
    int payload_size = strlen(OP_UNSUBSCRIBE) + strlen(topic);
    char *msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));

    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\"}", OP_UNSUBSCRIBE, topic);
    return send_message_to_rosbridge(sock, msg);
}

int publish_to_topic(int sock, char *topic, char *ros_msg)
{
    int payload_size = strlen(ros_msg) + strlen(topic);
    char *msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));

    sprintf(msg, "{\"op\": \"%s\", \"topic\": \"%s\", \"msg\": %s}", OP_PUBLISH, topic, ros_msg);
    free(ros_msg);
    return send_message_to_rosbridge(sock, msg);
}

/* Publishers */

int publish_to_topic_bool(int sock, char *topic, bool data)
{
    char *original_locale, *ros_msg;
    int bool_as_str_len = 10;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    ros_msg = malloc((bool_as_str_len + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"data\": %s}", data ? "true" : "false");

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_clock(int sock, char *topic, time_t secs, time_t nsecs)
{
    char *original_locale, *ros_msg;
    int payload_size, ind;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%ld", secs);
    payload_size += snprintf(NULL, 0, "%ld", nsecs);

    ros_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"clock\": {\"secs\": %ld, \"nsecs\": %ld}}", secs, nsecs);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_float32multiarray(int sock, char *topic, float data[], int size)
{
    char *original_locale, *data_array, *pos, *first_fragment, *frag_msg, *last_fragment;
    int payload_size, ind, id, n_fragments, part_number, msg_size, fragment_size,
        fragment_remainder, actual_fragment_size;
    float num;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = 0;
    for (ind = 0; ind < size; ind++)
    {
        payload_size += 5 + snprintf(NULL, 0, "%.1f", data[ind]);
    }

    data_array = malloc(payload_size * sizeof(char));
    pos = data_array;
    for (ind = 0; ind < size; ind++)
    {
        if (isinf(data[ind]) || isnan(data[ind]))
        {
            num = 0.0;
        }
        else
        {
            num = data[ind];
        }

        if (ind == 0)
        {
            pos += sprintf(pos, "[%.1f", num);
        }
        else if (ind == size - 1)
        {
            pos += sprintf(pos, ", %.1f]", num);
        }
        else
        {
            pos += sprintf(pos, ", %.1f", num);
        }
    }

    setlocale(LC_NUMERIC, original_locale);

    /* Fragment variables */
    id = rand();
    n_fragments = 100;

    /* Fragment 1 */
    payload_size = strlen(OP_PUBLISH) + strlen(topic);
    first_fragment = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(first_fragment, "{\\\"op\\\": \\\"%s\\\", \\\"topic\\\": \\\"%s\\\", "
                            "\\\"msg\\\": {\\\"data\\\": ",
            OP_PUBLISH, topic);

    payload_size = strlen(OP_FRAGMENT) + strlen(first_fragment);
    payload_size += snprintf(NULL, 0, "%d", id);
    payload_size += snprintf(NULL, 0, "%d", n_fragments);

    frag_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(frag_msg, "{\"op\": \"%s\", \"id\": \"%d\", \"data\": \"%s\", \"num\": 0, \"total\": %d}",
            OP_FRAGMENT, id, first_fragment, n_fragments);

    free(first_fragment);
    send_message_to_rosbridge(sock, frag_msg);

    /* Fragments 2 to N-1 */
    msg_size = strlen(data_array);
    fragment_size = msg_size / (n_fragments - 3);
    fragment_remainder = msg_size - fragment_size * (n_fragments - 3);

    actual_fragment_size = 0;
    for (part_number = 0; part_number < n_fragments - 2; part_number++)
    {
        if (part_number == n_fragments - 3)
        {
            actual_fragment_size = fragment_remainder;
        }
        else
        {
            actual_fragment_size = fragment_size;
        }

        payload_size = strlen(OP_FRAGMENT) + strlen(first_fragment);
        payload_size += snprintf(NULL, 0, "%d", id);
        payload_size += snprintf(NULL, 0, "%.*s", actual_fragment_size, data_array + part_number * fragment_size);
        payload_size += snprintf(NULL, 0, "%d", part_number + 1);
        payload_size += snprintf(NULL, 0, "%d", n_fragments);

        frag_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
        sprintf(frag_msg, "{\"op\": \"%s\", \"id\": \"%d\", \"data\": \"%.*s\", \"num\": %d, \"total\": %d}",
                OP_FRAGMENT, id, actual_fragment_size, data_array + part_number * fragment_size,
                part_number + 1, n_fragments);
        send_message_to_rosbridge(sock, frag_msg);
    }

    /* Fragment N */
    payload_size = snprintf(NULL, 0, "%d", size);
    last_fragment = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(last_fragment, ", \\\"layout\\\": {\\\"data_offset\\\": 0, \\\"dim\\\": "
                           "[{\\\"label\\\": \\\"\\\", \\\"size\\\": %d, \\\"stride\\\": 0}]}}}",
            size);

    payload_size = strlen(OP_FRAGMENT) + strlen(last_fragment);
    payload_size += snprintf(NULL, 0, "%d", id);
    payload_size += snprintf(NULL, 0, "%d", n_fragments - 1);
    payload_size += snprintf(NULL, 0, "%d", n_fragments);

    frag_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(frag_msg, "{\"op\": \"%s\", \"id\": \"%d\", \"data\": \"%s\", \"num\": %d, \"total\": %d}",
            OP_FRAGMENT, id, last_fragment, n_fragments - 1, n_fragments);
    free(last_fragment);
    send_message_to_rosbridge(sock, frag_msg);

    free(data_array);
}

int publish_to_topic_image(int sock, char *topic, int height, int width, int encoding_length, int step, uint8_t data[], int data_length, char *frame_id, int frameId_length)
{
    char *original_locale, *data_array, *pos, *first_fragment, *frag_msg, *last_fragment;
    int size, payload_size, ind, id, n_fragments, part_number, msg_size, fragment_size,
        fragment_remainder, actual_fragment_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    size = step * height;
    payload_size = 0;
    for (ind = 0; ind < size; ind++)
    {
        payload_size += 5 + snprintf(NULL, 0, "%d", data[ind]);
    }

    data_array = malloc(payload_size * sizeof(char));
    pos = data_array;
    for (ind = 0; ind < size; ind++)
    {
        if (ind == 0)
        {
            pos += sprintf(pos, "[%d", data[ind]);
        }
        else if (ind == size - 1)
        {
            pos += sprintf(pos, ",%d]", data[ind]);
        }
        else
        {
            pos += sprintf(pos, ",%d", data[ind]);
        }
    }

    setlocale(LC_NUMERIC, original_locale);

    /* Fragment variables */
    id = rand();
    n_fragments = 100;

    /* Fragment 1 */
    payload_size = strlen(OP_PUBLISH) + strlen(topic);
    first_fragment = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(first_fragment, "{\\\"op\\\": \\\"%s\\\", \\\"topic\\\": \\\"%s\\\", "
                            "\\\"msg\\\": {\\\"data\\\": ",
            OP_PUBLISH, topic);

    payload_size = strlen(OP_FRAGMENT) + strlen(first_fragment);
    payload_size += snprintf(NULL, 0, "%d", id);
    payload_size += snprintf(NULL, 0, "%d", n_fragments);

    frag_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(frag_msg, "{\"op\": \"%s\", \"id\": \"%d\", \"data\": \"%s\", \"num\": 0, \"total\": %d}",
            OP_FRAGMENT, id, first_fragment, n_fragments);

    free(first_fragment);
    send_message_to_rosbridge(sock, frag_msg);

    /* Fragments 2 to N-1 */
    msg_size = strlen(data_array);
    fragment_size = msg_size / (n_fragments - 3);
    fragment_remainder = msg_size - fragment_size * (n_fragments - 3);

    actual_fragment_size = 0;
    for (part_number = 0; part_number < n_fragments - 2; part_number++)
    {
        if (part_number == n_fragments - 3)
        {
            actual_fragment_size = fragment_remainder;
        }
        else
        {
            actual_fragment_size = fragment_size;
        }

        payload_size = strlen(OP_FRAGMENT) + strlen(first_fragment);
        payload_size += snprintf(NULL, 0, "%d", id);
        payload_size += snprintf(NULL, 0, "%.*s", actual_fragment_size, data_array + part_number * fragment_size);
        payload_size += snprintf(NULL, 0, "%d", part_number + 1);
        payload_size += snprintf(NULL, 0, "%d", n_fragments);

        frag_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
        sprintf(frag_msg, "{\"op\": \"%s\", \"id\": \"%d\", \"data\": \"%.*s\", \"num\": %d, \"total\": %d}",
                OP_FRAGMENT, id, actual_fragment_size, data_array + part_number * fragment_size,
                part_number + 1, n_fragments);
        send_message_to_rosbridge(sock, frag_msg);
    }

    /* Fragment N */
    payload_size = snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
    payload_size += snprintf(NULL, 0, "%s", frame_id);
    payload_size += snprintf(NULL, 0, "%d", height);
    payload_size += snprintf(NULL, 0, "%d", width);
    payload_size += snprintf(NULL, 0, "%d", step);

    last_fragment = malloc((payload_size + MEDIUM_EXTRA_SIZE) * sizeof(char));
    sprintf(last_fragment, ", \\\"header\\\": {\\\"stamp\\\": %lu, \\\"frame_id\\\": \\\"%s\\\", \\\"seq\\\": 0}, "
                           "\\\"height\\\": %d, \\\"width\\\": %d, \\\"step\\\": %d, \\\"encoding\\\": \\\"rgb8\\\", "
                           "\\\"is_bigendian\\\": 0}}",
            (unsigned long)time(NULL), frame_id, height, width, step);

    payload_size = strlen(OP_FRAGMENT) + strlen(last_fragment);
    payload_size += snprintf(NULL, 0, "%d", id);
    payload_size += snprintf(NULL, 0, "%d", n_fragments - 1);
    payload_size += snprintf(NULL, 0, "%d", n_fragments);

    frag_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(frag_msg, "{\"op\": \"%s\", \"id\": \"%d\", \"data\": \"%s\", \"num\": %d, \"total\": %d}",
            OP_FRAGMENT, id, last_fragment, n_fragments - 1, n_fragments);
    free(last_fragment);
    send_message_to_rosbridge(sock, frag_msg);

    free(data_array);
}

int publish_to_topic_imu(int sock, char *topic, int seq, int frameId_length,
                         double orientW, double orientX, double orientY, double orientZ,
                         double angularZ, double linearAccX, double linearAccZ)
{
    char *original_locale, *ros_msg;
    int payload_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%d", seq);
    payload_size += snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
    payload_size += snprintf(NULL, 0, "%.1f", orientX);
    payload_size += snprintf(NULL, 0, "%.1f", orientY);
    payload_size += snprintf(NULL, 0, "%.1f", orientZ);
    payload_size += snprintf(NULL, 0, "%.1f", orientW);
    payload_size += snprintf(NULL, 0, "%.1f", angularZ);
    payload_size += snprintf(NULL, 0, "%.1f", linearAccX);
    payload_size += snprintf(NULL, 0, "%.1f", linearAccZ);

    ros_msg = malloc((payload_size + MEDIUM_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"velodyne\"}, "
                     "\"orientation\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f, \"w\": %.1f}, "
                     "\"angular_velocity\": {\"x\": 0.0, \"y\": 0.0, \"z\": %.1f}, "
                     "\"linear_acceleration\": {\"x\": %.1f, \"y\": 0.0, \"z\": %.1f}}",
            seq, (unsigned long)time(NULL), orientX, orientY, orientZ,
            orientW, angularZ, linearAccX, linearAccZ);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_int32(int sock, char *topic, int data)
{
    char *original_locale, *ros_msg;
    int payload_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%d", data);

    ros_msg = malloc((payload_size + SMALL_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"data\": %d}", data);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_int32multiarray(int sock, char *topic, int data[], int size)
{
    char *original_locale, *ros_msg, *data_array, *pos;
    int payload_size, ind;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = 0;
    for (ind = 0; ind < size; ind++)
    {
        payload_size += 5 + snprintf(NULL, 0, "%d", data[ind]);
    }

    data_array = malloc(payload_size * sizeof(char));
    pos = data_array;
    for (ind = 0; ind < size; ind++)
    {
        if (ind == 0)
        {
            pos += sprintf(pos, "[%d", data[ind]);
        }
        else if (ind == size - 1)
        {
            pos += sprintf(pos, ", %d]", data[ind]);
        }
        else
        {
            pos += sprintf(pos, ", %d", data[ind]);
        }
    }

    payload_size = snprintf(NULL, 0, "%s", data_array);
    ros_msg = malloc((payload_size + MEDIUM_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"data\": %s, \"layout\": {\"data_offset\": 0, "
                     "\"dim\": [{\"label\": \"\", \"size\": %d, \"stride\": 0}]}}",
            data_array, size);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
    free(data_array);
}

int publish_to_topic_odometry(int sock, char *topic, int seq, int frameId_length, int childFrameId_length,
                              double positionX, double positionY, double positionZ,
                              double orientW, double orientX, double orientY, double orientZ,
                              double linearX, double linearY, double linearZ,
                              double angularX, double angularY, double angularZ)
{
    char *original_locale, *ros_msg, *covariance, *pos;
    int payload_size, ind;
    int covariance_size = 36; /* From ROS message definition */

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = 0;
    for (ind = 0; ind < covariance_size; ind++)
    {
        payload_size += 5 + snprintf(NULL, 0, "%1.f", 0.0);
    }

    covariance = malloc(payload_size * sizeof(char));
    pos = covariance;
    for (ind = 0; ind < covariance_size; ind++)
    {
        if (ind == 0)
        {
            pos += sprintf(pos, "[%.1f", 0.0);
        }
        else if (ind == covariance_size - 1)
        {
            pos += sprintf(pos, ", %.1f]", 0.0);
        }
        else
        {
            pos += sprintf(pos, ", %.1f", 0.0);
        }
    }

    payload_size = snprintf(NULL, 0, "%d", seq);
    payload_size += snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
    payload_size += snprintf(NULL, 0, "%.1f", positionX);
    payload_size += snprintf(NULL, 0, "%.1f", positionY);
    payload_size += snprintf(NULL, 0, "%.1f", positionZ);
    payload_size += snprintf(NULL, 0, "%.1f", orientX);
    payload_size += snprintf(NULL, 0, "%.1f", orientY);
    payload_size += snprintf(NULL, 0, "%.1f", orientZ);
    payload_size += snprintf(NULL, 0, "%.1f", orientW);
    payload_size += snprintf(NULL, 0, "%s", covariance);
    payload_size += snprintf(NULL, 0, "%.1f", linearX);
    payload_size += snprintf(NULL, 0, "%.1f", linearY);
    payload_size += snprintf(NULL, 0, "%.1f", linearZ);
    payload_size += snprintf(NULL, 0, "%.1f", angularX);
    payload_size += snprintf(NULL, 0, "%.1f", angularY);
    payload_size += snprintf(NULL, 0, "%.1f", angularZ);
    payload_size += snprintf(NULL, 0, "%s", covariance);

    ros_msg = malloc((payload_size + LARGE_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"/base_link\"}, "
                     "\"child_frame_id\": \"/base_link\", \"pose\": {\"pose\": {\"position\": "
                     "{\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \"orientation\": "
                     "{\"x\": %.1f, \"y\": %.1f, \"z\": %.1f, \"w\": %.1f}}, "
                     "\"covariance\": %s}, \"twist\": {\"twist\": {\"linear\": "
                     "{\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, \"angular\": "
                     "{\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}, \"covariance\": %s}}",
            seq, (unsigned long)time(NULL), positionX, positionY, positionZ,
            orientX, orientY, orientZ, orientW, covariance, linearX, linearY,
            linearZ, angularX, angularY, angularZ, covariance);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
    free(covariance);
}

int publish_to_topic_pose(int sock, char *topic,
                          double positionX, double positionY, double positionZ,
                          double orientationW, double orientationX, double orientationY, double orientationZ)
{
    char *original_locale, *ros_msg;
    int payload_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%.1f", positionX);
    payload_size += snprintf(NULL, 0, "%.1f", positionY);
    payload_size += snprintf(NULL, 0, "%.1f", positionZ);
    payload_size += snprintf(NULL, 0, "%.1f", orientationW);
    payload_size += snprintf(NULL, 0, "%.1f", orientationX);
    payload_size += snprintf(NULL, 0, "%.1f", orientationY);
    payload_size += snprintf(NULL, 0, "%.1f", orientationZ);

    ros_msg = malloc((payload_size + MEDIUM_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, "
                     "\"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}",
            positionX, positionY, positionZ, orientationW, orientationX, orientationY, orientationZ);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_posearray(int sock, char *topic, int seq, int frame_id, int frameId_length,
                               double positionX, double positionY, double positionZ,
                               double orientationW, double orientationX, double orientationY, double orientationZ,
                               int poses_length, double positionX1, double positionY1, double positionZ1,
                               double orientationW1, double orientationX1, double orientationY1, double orientationZ1,
                               double positionX2, double positionY2, double positionZ2,
                               double orientationW2, double orientationX2, double orientationY2, double orientationZ2)
{
    char *original_locale, *ros_msg;
    int payload_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%d", seq);
    payload_size += snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
    payload_size += snprintf(NULL, 0, "%.1f", positionX);
    payload_size += snprintf(NULL, 0, "%.1f", positionY);
    payload_size += snprintf(NULL, 0, "%.1f", positionZ);
    payload_size += snprintf(NULL, 0, "%.1f", orientationW);
    payload_size += snprintf(NULL, 0, "%.1f", orientationX);
    payload_size += snprintf(NULL, 0, "%.1f", orientationY);
    payload_size += snprintf(NULL, 0, "%.1f", orientationZ);
    payload_size += snprintf(NULL, 0, "%.1f", positionX1);
    payload_size += snprintf(NULL, 0, "%.1f", positionY1);
    payload_size += snprintf(NULL, 0, "%.1f", positionZ1);
    payload_size += snprintf(NULL, 0, "%.1f", orientationW1);
    payload_size += snprintf(NULL, 0, "%.1f", orientationX1);
    payload_size += snprintf(NULL, 0, "%.1f", orientationY1);
    payload_size += snprintf(NULL, 0, "%.1f", orientationZ1);
    payload_size += snprintf(NULL, 0, "%.1f", positionX2);
    payload_size += snprintf(NULL, 0, "%.1f", positionY2);
    payload_size += snprintf(NULL, 0, "%.1f", positionZ2);
    payload_size += snprintf(NULL, 0, "%.1f", orientationW2);
    payload_size += snprintf(NULL, 0, "%.1f", orientationX2);
    payload_size += snprintf(NULL, 0, "%.1f", orientationY2);
    payload_size += snprintf(NULL, 0, "%.1f", orientationZ2);

    ros_msg = malloc((payload_size + LARGE_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"/map\"}, \"poses\": "
                     "[{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, "
                     "\"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}, "
                     "{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, "
                     "\"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}, "
                     "{\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, "
                     "\"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}]}",
            seq, (unsigned long)time(NULL), positionX, positionY, positionZ,
            orientationW, orientationX, orientationY, orientationZ,
            positionX1, positionY1, positionZ1,
            orientationW1, orientationX1, orientationY1, orientationZ1,
            positionX2, positionY2, positionZ2,
            orientationW2, orientationX2, orientationY2, orientationZ2);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_posestamped(int sock, char *topic, int seq, int frame_id, int frameId_length,
                                 double positionX, double positionY, double positionZ,
                                 double orientationW, double orientationX, double orientationY, double orientationZ)
{
    char *original_locale, *ros_msg;
    int payload_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%d", seq);
    payload_size += snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
    payload_size += snprintf(NULL, 0, "%.1f", positionX);
    payload_size += snprintf(NULL, 0, "%.1f", positionY);
    payload_size += snprintf(NULL, 0, "%.1f", positionZ);
    payload_size += snprintf(NULL, 0, "%.1f", orientationW);
    payload_size += snprintf(NULL, 0, "%.1f", orientationX);
    payload_size += snprintf(NULL, 0, "%.1f", orientationY);
    payload_size += snprintf(NULL, 0, "%.1f", orientationZ);

    ros_msg = malloc((payload_size + MEDIUM_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"stamp\": %lu, \"frame_id\": \"world\"}, "
                     "\"pose\": {\"position\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, "
                     "\"orientation\": {\"w\": %.1f, \"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}}",
            seq, (unsigned long)time(NULL), positionX, positionY, positionZ,
            orientationW, orientationX, orientationY, orientationZ);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

int publish_to_topic_twiststamped(int sock, char *topic, int seq, int frameId_length,
                                  double linearX, double linearY, double linearZ,
                                  double angularX, double angularY, double angularZ)
{
    char *original_locale, *ros_msg;
    int payload_size;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    payload_size = snprintf(NULL, 0, "%d", seq);
    payload_size += snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
    payload_size += snprintf(NULL, 0, "%.1f", linearX);
    payload_size += snprintf(NULL, 0, "%.1f", linearY);
    payload_size += snprintf(NULL, 0, "%.1f", linearZ);
    payload_size += snprintf(NULL, 0, "%.1f", angularX);
    payload_size += snprintf(NULL, 0, "%.1f", angularY);
    payload_size += snprintf(NULL, 0, "%.1f", angularZ);

    ros_msg = malloc((payload_size + MEDIUM_EXTRA_SIZE) * sizeof(char));
    sprintf(ros_msg, "{\"header\": {\"seq\": %d, \"frame_id\": \"/base_link\", \"stamp\": %lu}, "
                     "\"twist\": {\"linear\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}, "
                     "\"angular\": {\"x\": %.1f, \"y\": %.1f, \"z\": %.1f}}}",
            seq, (unsigned long)time(NULL), linearX, linearY, linearZ, angularX, angularY, angularZ);

    setlocale(LC_NUMERIC, original_locale);
    publish_to_topic(sock, topic, ros_msg);
}

/* Subscribers */

int listen_to_topic_int16(int sock, int buffer_size)
{
    char msg[1024];
    char number[6];
    char *pos;
    int socket_result, ind, number_start;

    socket_result = recv(sock, msg, buffer_size, 0);

    number_start = 0;
    pos = number;
    for (ind = 0; ind < buffer_size - 2; ind++)
    {
        char c = *(msg + ind);
        char d = *(msg + ind + 1);
        char e = *(msg + ind + 2);
        if (c == 'x')
        {
            return 0;
        }
        if (c == 'a' && d == '"' && e == ':')
        {
            number_start = 1;
            continue;
        }
        else if (e == '}')
        {
            break;
        }
        if (number_start == 1)
        {
            pos += sprintf(pos, "%c", e);
        }
    }

    return atoi(number);
}

void listen_to_topic_twiststamped(int sock, int buffer_size, float numbers[6])
{
    char *original_locale, *pos;
    char msg[1024];
    char number[20];
    char letter;
    int socket_result, ind, number_ind, number_start, second_time;

    original_locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");

    socket_result = recv(sock, msg, buffer_size, 0);

    number_ind = 0;
    number_start = 0;
    pos = number;
    letter = 'y';
    second_time = 0;
    for (ind = 0; ind < buffer_size - 2; ind++)
    {
        char c = *(msg + ind);
        char d = *(msg + ind + 1);
        char e = *(msg + ind + 2);

        if ((c == 'x' || c == 'y' || c == 'z') && d == '"' && e == ':')
        {
            letter = c;
            number_start = 1;
            continue;
        }
        if (number_start == 1 && (e == ',' || e == '}'))
        {
            number_ind = get_index_from_letter(letter, second_time);
            numbers[number_ind] = atof(number);
            number_start = 0;
            memset(number, 0, 20);
            pos = number;

            if (e == '}')
            {
                second_time = 1;
            }

            continue;
        }
        if (number_start == 1)
        {
            pos += sprintf(pos, "%c", e);
        }
    }

    setlocale(LC_NUMERIC, original_locale);
}
