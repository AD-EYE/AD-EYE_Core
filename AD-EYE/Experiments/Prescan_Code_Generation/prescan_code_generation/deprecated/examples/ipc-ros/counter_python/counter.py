"""
Example of interprocess communication between ROS and Python non-ROS script
(Python non-ROS script part)
"""
import json
import logging
import socket
import time


class SocketCounter(object):
    OP_ADVERTISE = 'advertise'
    OP_PUBLISH = 'publish'
    OP_SUBSCRIBE = 'subscribe'
    OP_UNADVERTISE = 'unadvertise'
    OP_UNSUBSCRIBE = 'unsubscribe'
    SOCKET_BUFFER_SIZE = 1024

    def __init__(self, ip='localhost', port=9090, counter_limit=10, rate=10):
        self._ip = ip
        self._port = port
        self._counter_limit = counter_limit
        self._rate = rate

        self._counter = 0
        self._sock = socket.create_connection((self._ip, self._port))
        self._sock.settimeout(2)
        self.socket_disconnected = False

    def step(self):
        self._counter = (self._counter + 1) % self._counter_limit

    def close_socket(self):
        self._sock.close()

    def listen(self):
        try:
            msg = self._sock.recv(self.SOCKET_BUFFER_SIZE)
        except socket.timeout:
            logging.exception('No message from rosbridge')
            return

        try:
            subscriber_msg = json.loads(msg)
        except ValueError:
            logging.exception(
                'Error creating a subscriber JSON message from {}'
                .format(msg)
            )
            return

        logging.info('Data from rosbridge: {}'.format(subscriber_msg))

    def publish(self, topic):
        self._send_message_to_rosbridge(
            {'op': self.OP_PUBLISH, 'topic': topic, 'msg': {'data': self._counter}}
        )

    def subscribe(self, topic):
        self._send_message_to_rosbridge(
            {'op': self.OP_SUBSCRIBE, 'topic': topic}
        )

    def unsubscribe(self, topic):
        self._send_message_to_rosbridge(
            {'op': self.OP_UNSUBSCRIBE, 'topic': topic}
        )

    def advertise(self, topic, msg_type):
        self._send_message_to_rosbridge(
            {'op': self.OP_ADVERTISE, 'topic': topic, 'type': msg_type}
        )

    def unadvertise(self, topic):
        self._send_message_to_rosbridge(
            {'op': self.OP_UNADVERTISE, 'topic': topic}
        )

    def _send_message_to_rosbridge(self, msg_dict):
        self._sock.send(json.dumps(msg_dict))

    def sleep(self):
        time.sleep(1.0 / self._rate)


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)

    subscribe_topic = '/higher_counter'
    publish_topic = '/counter'
    publish_msg_type='std_msgs/UInt8'

    counter = SocketCounter()
    counter.subscribe(subscribe_topic)
    counter.advertise(publish_topic, publish_msg_type)

    try:
        while True:
            try:
                counter.listen()
                counter.step()
                counter.publish(publish_topic)
                counter.sleep()
            except KeyboardInterrupt:
                break
            except socket.error:
                counter.socket_disconnected = True
                logging.exception('Rosbridge error')
                break
    finally:
        if not counter.socket_disconnected:
            counter.unadvertise(publish_topic)
            counter.unsubscribe(subscribe_topic)
            counter.close_socket()
