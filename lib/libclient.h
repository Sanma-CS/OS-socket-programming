#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define BUFSIZE 1024

/* CREATE SOCKET, CONNECT USING CONNECT() */
void connect_request(int *sockfd, struct sockaddr_in *server_addr);

/* CLIENT SEND AND RECVIE */
void send_recv(int i, int sockfd);