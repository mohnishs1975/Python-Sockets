/*****************************************************************************
 * server-c.c
 * Name:
 * BU ID:
 * Email:
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
*/
int server(char *server_port) {
  // create socket file descriptor
  char buffer[RECV_BUFFER_SIZE];
  int server_fd, client;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // create socket address
  // forcefully attach socket to the port
  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
  {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(atoi(server_port));

  int sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock == -1) {
		perror("initializing socket failed");
    	exit(1);
	}
  // bind socket to address
  if (bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress))<0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // listen to incoming connections
  if (listen(sock, QUEUE_LENGTH) < 0)
  {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  // accept a connection
  int S_addrlen = sizeof(serverAddress);
  int C_addrlen = sizeof(clientAddress);
  while(1) {
    if ((client = accept(sock, (struct sockaddr *)&clientAddress, (socklen_t*)&C_addrlen))<0)
    {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }
    
    int recv_bytes = recv(client, buffer, RECV_BUFFER_SIZE, 0);
    //fwrite(buffer, recv_bytes, 1, stdout);
    // receive message
    if (recv_bytes < 0) 
    {
		  break;
		}
    else{
      fwrite(buffer, recv_bytes, 1, stdout);
    }
    
    fflush(stdout);
  }
  close(sock);
  
}

/*
 * main():
 * Parse command-line arguments and call server function
*/
int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
