#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

#define OP_ADVERTISE "advertise"
#define OP_PUBLISH "publish"
#define OP_FRAGMENT "fragment"
#define OP_SUBSCRIBE "subscribe"
#define OP_UNADVERTISE "unadvertise"
#define OP_UNSUBSCRIBE "unsubscribe"

#define SMALL_EXTRA_SIZE 100
#define MEDIUM_EXTRA_SIZE 350
#define LARGE_EXTRA_SIZE 800

/* Helper functions */
int get_index_from_letter(char letter, int second_time);

/* Socket functions */
int create_connection(int port, int timeout);

/* Generic rosbridge functions */
int send_message_to_rosbridge(int sock, char *msg);
int advertise_topic(int sock, char *topic, char *message_type);
int unadvertise_topic(int sock, char *topic);
int subscribe_to_topic(int sock, char *topic, char *message_type);
int unsubscribe_from_topic(int sock, char *topic);
int publish_to_topic(int sock, char *topic, char *ros_msg);

/* Publishers */
int publish_to_topic_bool(int sock, char *topic, bool data);
int publish_to_topic_clock(int sock, char *topic, time_t secs, time_t nsecs);
int publish_to_topic_float32multiarray(int sock, char *topic, float data[], int size);
int publish_to_topic_image(int sock, char *topic, int height, int width, int encoding_length, int step, uint8_t data[], int data_length, char *frame_id, int frameId_length);
int publish_to_topic_imu(int sock, char *topic, int seq, int frameId_length, double orientW, double orientX, double orientY, double orientZ, double angularX, double linearAccX, double linearAccZ);
int publish_to_topic_int32(int sock, char *topic, int data);
int publish_to_topic_int32multiarray(int sock, char *topic, int data[], int size);
int publish_to_topic_odometry(int sock, char *topic, int seq, int frameId_length, int childFrameId_length, double positionX, double positionY, double positionZ, double orientW, double orientX, double orientY, double orientZ, double linearX, double linearY, double linearZ, double angularX, double angularY, double angularZ);
int publish_to_topic_pose(int sock, char *topic, double positionX, double positionY, double positionZ, double orientationW, double orientationX, double orientationY, double orientationZ);
int publish_to_topic_posearray(int sock, char *topic, int seq, int frame_id, int frameId_length, double positionX, double positionY, double positionZ, double orientationW, double orientationX, double orientationY, double orientationZ, int poses_length, double positionX1, double positionY1, double positionZ1, double orientationW1, double orientationX1, double orientationY1, double orientationZ1, double positionX2, double positionY2, double positionZ2, double orientationW2, double orientationX2, double orientationY2, double orientationZ2);
int publish_to_topic_posestamped(int sock, char *topic, int seq, int frame_id, int frameId_length, double positionX, double positionY, double positionZ, double orientationW, double orientationX, double orientationY, double orientationZ);
int publish_to_topic_twiststamped(int sock, char *topic, int seq, int frameId_length, double linearX, double linearY, double linearZ, double angularX, double angularY, double angularZ);

/* Subscribers */
int listen_to_topic_int16(int sock, int buffer_size);
void listen_to_topic_twiststamped(int sock, int buffer_size, float numbers[6]);
