###############################################################################
# server-python.py
# Name:
# BU ID:
# Email:
###############################################################################

import sys
import socket

RECV_BUFFER_SIZE = 2048
QUEUE_LENGTH = 10

def server(server_port):
    """TODO: Listen on socket and print received message to sys.stdout"""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   #instance of socket
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(('127.0.0.1', server_port))                      #bind host address and port together
    s.listen(QUEUE_LENGTH)                                  #configures how many clients the server can listen to

    while True:
        conn, addr = s.accept()                             #accept new connection
        while True:
            data = conn.recv(RECV_BUFFER_SIZE).decode()
            sys.stdout.write(data)
            if not data:
                break
        sys.stdout.flush()
        conn.close()

def main():
    """Parse command-line argument and call server function """
    if len(sys.argv) != 2:
        sys.exit("Usage: python server-python.py [Server Port]")
    server_port = int(sys.argv[1])
    server(server_port)

if __name__ == "__main__":
    main()
