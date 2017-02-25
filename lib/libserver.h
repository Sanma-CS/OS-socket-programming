#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8888
#define BUFSIZE 1024

   /* Initialize socket structure
   	bind the host address
	listening for the cilents
	*/
void connect_request(int *sockfd, struct sockaddr_in *my_addr);
	
   /* Accept actual connection from the client */
void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr);

	/* */
void send_to_all(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master);

	/* send a notif and receive data from cilents*/
void send_recv(int i, fd_set *master, int sockfd, int fdmax);
