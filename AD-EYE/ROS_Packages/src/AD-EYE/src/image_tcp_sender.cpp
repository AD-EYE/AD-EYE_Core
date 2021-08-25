#include <ros/ros.h>
#include "sensor_msgs/Image.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <poll.h>


#define BUFFER_SIZE 8000000
#define TCP_PORT "3490"  // the port users will be connecting to


// process to kill child threads (read http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html)
void sigchld_handler(int s)
{
    (void)s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

/*!
 * \brief A node that list the objects detected by the camera 1 and 2, and publish it
 * \details Publish a list of all the objects detected by the camera 1 and the camera 2. 
 * The purpuse is to fuse the objects detected by the two cameras in one message.
 */
class ImageTCPSender
{
private:

    int nb = 0;
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Subscriber sub;
    sensor_msgs::Image image_msg;


    socklen_t sin_size;
    struct sockaddr_storage their_addr; // connector's address information
    int socket_file_descriptor, new_socket_file_descriptor;  // listen on sock_fd, new connection on new_socket_file_descriptor
    char address_chars[INET6_ADDRSTRLEN];

    void *get_in_addr(struct sockaddr *sa)
    {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }


public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param inputTopic1 Name of the topic that connect the camera 1
     * \details Initialize the node and its components such as publishers and subscribers. It call msg1_callback and msg2_callback
     */
    ImageTCPSender(ros::NodeHandle &nh, std::string input_topic) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub = nh_.subscribe<sensor_msgs::Image>(input_topic, 1, &ImageTCPSender::msg_callback, this);

        struct addrinfo hints, *host_info, *p;
        
        int yes=1;
        
        int rv;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP

        if ((rv = getaddrinfo(NULL, TCP_PORT, &hints, &host_info)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        }

        
        // loop through all the results and bind to the first we can
        for(p = host_info; p != NULL; p = p->ai_next) {
            if ((socket_file_descriptor = socket(p->ai_family, p->ai_socktype,
                    p->ai_protocol)) == -1) {
                perror("server: socket");
                continue;
            }

            if (setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes,
                    sizeof(int)) == -1) {
                perror("setsockopt");
                exit(1);
            }

            if (bind(socket_file_descriptor, p->ai_addr, p->ai_addrlen) == -1) {
                close(socket_file_descriptor);
                perror("server: bind");
                continue;
            }

            break;
        }

        freeaddrinfo(host_info); // all done with this structure

        if (p == NULL)  {
            fprintf(stderr, "server: failed to bind\n");
            exit(1);
        }

        if (listen(socket_file_descriptor, 1) == -1) {
            perror("listen");
            exit(1);
        }


	    struct sigaction sa;
        // to reap child threads (read http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html)
        // sa.sa_handler = sigchld_handler; // reap all dead processes

        sa.sa_handler = &sigchld_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sa, NULL) == -1) {
            perror("sigaction");
            exit(1);
        }


        
    }

    /*!
     * \brief Callback call in the constructeur
     * \param msg Contain the list of object detected by camera 1
     * \details Identify the objects that have been detected by camera 1
     */
    void msg_callback(sensor_msgs::Image msg)
    {

        image_msg = msg;
        // std::cout << "received a message: ";
        // for (std::vector<uint8_t>::const_iterator i = image_msg.data.begin(); i != image_msg.data.end(); ++i)
        //                     std::cout << *i << ' ';
        std::cout << std::endl;

    }

    /*!
     * \brief Publish all the object detected
     * \details Publish the list of all the object detected by camera 1 and 2 to outputTopic.
     */
    void publish()
    {
        // every iteration we attemps to make accept new connection
		// when we get a new connection, we get the IP and a new socket
		sin_size = sizeof their_addr;
        struct pollfd pfds; // More if you want to monitor more
        pfds.fd = socket_file_descriptor;          // Standard input
        pfds.events = POLLIN; // Tell me when ready to read
        int num_events = poll(&pfds, 1, 5);
        std::cout << "poll   num_events" << num_events << std::endl;
        if(num_events != 0 && pfds.revents && POLLIN) // did not time out and we got pollin event
        {
            new_socket_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *)&their_addr, &sin_size);
            // if the connection attemps failed we continue (this translates to waiting for a connection to be established)
            if (new_socket_file_descriptor == -1) {
                perror("accept");
            }
            else{
                // geting IP address in a human readable format
                inet_ntop(their_addr.ss_family,
                    get_in_addr((struct sockaddr *)&their_addr),
                    address_chars, sizeof address_chars);
                printf("server: got connection from %s\n", address_chars);

                if (!fork()) { // this is the child process
                    close(socket_file_descriptor); // child doesn't need the listener

                    // printf("server: sending '%hhu'\n", value_to_send[0]);
                    if(image_msg.data.size()>0)
                    {
                        uint8_t data_to_send[image_msg.data.size()];
                        std::copy(image_msg.data.begin(), image_msg.data.end(), data_to_send); // conversion from uint8_t vector to uint8_t array
                        // std::cout << "vector of " << image_msg.data.size() << " elements" << std::endl;
                        std::cout << "sending " << sizeof data_to_send << " bytes of data" << std::endl;
                        if (send(new_socket_file_descriptor, &(data_to_send), sizeof data_to_send, 0) == -1)
                            perror("send");

                    }
                    close(new_socket_file_descriptor); //closes socket once done
                    exit(0); // exit the child thread
                }
                close(new_socket_file_descriptor);  // parent doesn't need this
            }
        }
		

		
    }

    /*!
     * \brief The main loop of the Node
     */
    void run()
    {
        ros::Rate rate(20);
        while(nh_.ok())
        {
            nb++;
            std::cout << "iteration" << nb << std::endl;
            ros::spinOnce();
            publish();
            rate.sleep();
        }
    }
};


/*!
* \brief Main function
*/
int main(int argc, char** argv)
{
    std::string input_topic = "/camera_1/image_raw";
    ros::init(argc, argv, "imageTCPsender");
    ros::NodeHandle nh;
    ImageTCPSender image_tcp_sender(nh, input_topic);
    image_tcp_sender.run();
    return 0;
}
