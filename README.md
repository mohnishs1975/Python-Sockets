# Sockets
TCP client and server in C and Python   

**Server Specification**
• Each server program should listen on a socket, wait for a client to connect, receive a
message from the client, print the message to stdout, and then wait for the next client
indefinitely.

• Each server should take one command-line argument: the port number to listen on for
client connections.

• Each server should accept and process client communications in an infinite loop,
allowing multiple clients to send messages to the same server. The server should only
exit in response to an external signal (e.g., SIGINT from pressing ctrl-c).

• Each server should maintain a short (5-10) client queue and handle multiple client
connection attempts sequentially. In real applications, a TCP server would fork a new
process to handle each client connection concurrently, but that is not necessary for this
assignment.

• Each server should gracefully handle error values potentially returned by socket
programming library functions (see specifics for each language below). Errors related to
handling client connections should not cause the server to exit after handling the error;
all others should.

**Client Specification**
• Each client program should contact a server, read a message from stdin, send the
message, and exit.

• Each client should read and send the message exactly as it appears in stdin until
reaching an EOF (end-of-file).

• Each client should take two command-line arguments: the IP address of the server and
the port number of the server.

• Each client must be able to handle arbitrarily large messages by iteratively reading and
sending chunks of the message, rather than reading the whole message into memory
first.

• Each client should handle partial sends (when a socket only transmits part of the data
given in the last “send” call) by attempting to re-send the rest of the data until it has all
been sent.

• Each client should gracefully handle error values potentially returned by socket
programming library functions.
