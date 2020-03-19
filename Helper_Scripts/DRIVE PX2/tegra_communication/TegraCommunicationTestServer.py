#!/usr/bin/python
import socket

def server():
    i = 0
    HOST = "" #socket.gethostname()
    TCP_PORT = 11311 # standard port for ROS master
    MESSAGE = 'Hello Client {}'.format(i)

    server_socket = socket.socket()  # get instance
    server_socket.bind((HOST, TCP_PORT))  # bind host address and port together
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # configure how many client the server can listen simultaneously
    server_socket.listen(1)

    while True:
        conn, address = server_socket.accept()  # accept new connection

        message = conn.recv(1024).decode()

        print("Connection from: {}, Message: {}".format(address, message))

        conn.sendall(MESSAGE.encode('utf-8'))
        i = i + 1
        MESSAGE = 'Hello Client {}'.format(i)

        # close the connection
        conn.shutdown(socket.SHUT_RDWR)
        conn.close() 


if __name__ == '__main__':
    server()
