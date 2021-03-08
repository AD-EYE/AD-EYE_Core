int send_message_to_rosbridge(int sock, char* msg);
int listen_to_topic(int sock, int buffer_size);
int advertise_topic(int sock);
int unadvertise_topic(int sock);
int publish_to_topic(int sock, float data);
int subscribe_to_topic(int sock);
int unsubscribe_from_topic(int sock);
int create_connection(int port, int timeout);
