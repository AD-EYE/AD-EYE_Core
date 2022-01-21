#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <rosgraph_msgs/Clock.h>

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
#include <signal.h>


#include <chrono> // for time measurements


// to measure time
#include <sys/time.h>

#define TCP_PORT "3490"  // the port users will be connecting to

#define BACKLOG 10	 // how many pending connections queue will hold


#define BUFFER_SIZE 8000000

class TwistSender {
    public:

    ros::Subscriber subCurrentVelocity;
    ros::Subscriber subClock;
    float current_velocity = 0;
    float current_roation_speed = 0;
    float data_to_send[2] = {0,0};

    TwistSender(ros::NodeHandle &nh) {
        subCurrentVelocity = nh.subscribe("/TwistS", 1, &TwistSender::currentVelocityCallback, this);
        subClock = nh.subscribe("/clock", 1, &TwistSender::clockCallback, this);
        // int socket_file_descriptor, new_socket_file_descriptor;  // listen on sock_fd, new connection on new_socket_file_descriptor
        struct addrinfo hints, *host_info, *p;
        struct sockaddr_storage their_addr; // connector's address information
        socklen_t sin_size;
        struct sigaction sa;
        int yes=1;
        char s[INET6_ADDRSTRLEN];
        int rv;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP

        if ((rv = getaddrinfo(NULL, TCP_PORT, &hints, &host_info)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            exit;
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

        if (listen(socket_file_descriptor, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }


        // to reap child threads (read http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html)
        // sa.sa_handler = sigchld_handler; // reap all dead processes
        // sigemptyset(&sa.sa_mask);
        // sa.sa_flags = SA_RESTART;
        // if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        //     perror("sigaction");
        //     exit(1);
        // }





        printf("server: waiting for connections...\n");

        bool connected = false;
        while(!connected) {  // main accept() loop
            // every iteration we attemps to make accept new connection
            // when we get a new connection, we get the IP and a new socket
            sin_size = sizeof their_addr;
            new_socket_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *)&their_addr, &sin_size);
            // if the connection attemps failed we continue (this translates to waiting for a connection to be established)
            if (new_socket_file_descriptor == -1) {
                perror("accept");
                continue;
            }
            connected = true;

            // geting IP address in a human readable format
            inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s);
            printf("server: got connection from %s\n", s);

            sendData();
            sendData();
            // if (send(new_socket_file_descriptor, &current_velocity, sizeof data_to_send, 0) == -1)
            //             perror("send");

            // if (!fork()) { // this is the child process

            //     close(socket_file_descriptor); // child doesn't need the listener
            //     int nb_sent = 0;

            //     while(nb_sent < 21)
            //     {
            //         float value_to_send;
            //         value_to_send = 18.3 - 2 * nb_sent;

            //         struct timeval stop, start;
            //         gettimeofday(&start, NULL);
            //         printf("send time %lu ms\n", start.tv_sec * 1000 + start.tv_usec /1000);
            //         // printf("server: sending '%hhu'\n", value_to_send[0]);
            //         // if (send(new_socket_file_descriptor, &value_to_send, BUFFER_SIZE, 0) == -1)
            //         if (send(new_socket_file_descriptor, &value_to_send, sizeof value_to_send, 0) == -1)
            //             perror("send");

            //         sleep(0.05);
            //         nb_sent++;
            //         printf("sent once");
            //     }


                
            //     close(new_socket_file_descriptor); //closes socket once done
            //     exit(0); // exit the child thread
            // }
            // close(new_socket_file_descriptor);  // parent doesn't need this
        }

        ros::spin();
    }

    ~TwistSender() {
        close(socket_file_descriptor);
        close(new_socket_file_descriptor);
    }

    /*!
     * \brief currentVelocity Callback : Updates the knowledge about the car speed.
     * \param msg A smart pointer to the message from the topic.
     */
    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)
    {
        received_velocity = true;
        current_velocity = msg->twist.linear.x;
        data_to_send[0] = current_velocity;
        data_to_send[1] = msg->twist.angular.z;
        sendData();
        
    }

    void clockCallback(const rosgraph_msgs::Clock::ConstPtr& msg) {
        std::chrono::steady_clock::time_point time_of_last_clock_msg_received = std::chrono::steady_clock::now();
        if(!received_velocity)
        {
            std::cout << "not received velocity" << std::endl;
            sendData();
        }
            
    }

    void sendData() {
        counter++;
        std::cout << "sending data: " << counter << std::endl;
        if (send(new_socket_file_descriptor, &data_to_send, sizeof data_to_send, 0) == -1)
                        perror("send");
    }

    private:
    int socket_file_descriptor, new_socket_file_descriptor;
    bool received_velocity = false;
    int counter = 0;
    std::chrono::steady_clock::time_point time_of_last_clock_msg_received;


    // process to kill child threads (read http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html)
    void sigchld_handler(int s)
    {
        (void)s; // quiet unused variable warning

        // waitpid() might overwrite errno, so we save and restore it:
        int saved_errno = errno;

        while(waitpid(-1, NULL, WNOHANG) > 0);

        errno = saved_errno;
    }


    // get sockaddr, IPv4 or IPv6:
    void *get_in_addr(struct sockaddr *sa)
    {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }






};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "TwistSender");
    ros::NodeHandle nh;
    TwistSender scp = TwistSender(nh);
}