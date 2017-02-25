#include "libserver.h"



void connect_request(int *sockfd, struct sockaddr_in *serv_addr)
{
	/* Initialize socket structure */
	int yes = 1;
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(PORT);
	serv_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
	char buffer[BUFSIZE];
	bzero(buffer, BUFSIZE);
	//memset(serv_addr->sin_zero, '', sizeof serv_addr->sin_zero);
	if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	
	/* Bind the host address using bind() call.*/
	if (bind(*sockfd, (struct sockaddr *)serv_addr, sizeof(struct sockaddr)) == -1) {
    	perror("ERROR! Could not binding");
    	exit(1);
   	}
	
	/* Listen to clients */
	if (listen(*sockfd, 5) == -1) {
		perror("ERROR! Could not listen");
		exit(1);
	}
	printf("\nTCPServer Waiting for client on port 8888\n");
	fflush(stdout);
}

void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
	socklen_t addrlen; 	//data byte count
	int newsockfd;
	
	addrlen = sizeof(struct sockaddr_in);
	if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
		perror("ERROR! Unable to accept");
		exit(1);
	}else {
		FD_SET(newsockfd, master); 	//Set the bit for newsockfd in the fd set master
		if(newsockfd > *fdmax){
			*fdmax = newsockfd;
		}
		printf("new connection from %s on port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
	}
}

void send_to_all(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master)
{
	if (FD_ISSET(j, master)){
		if (j != sockfd && j != i) {
			if (send(j, recv_buf, nbytes_recvd, 0) == -1) {
				perror("ERROR! Sending failed");
			}
		}
	}
}

void send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
	int nbytes_recvd, j;
	char recv_buf[BUFSIZE], buf[BUFSIZE];
	
	if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) <= 0) {
		if (nbytes_recvd == 0) {
			printf("socket %d hung up\n", i);
		}else {
			perror("ERROR! receive failed");
		}
		close(i);
		FD_CLR(i, master); //Clear the bit fror the fd i in the fd set master
	}else { 
	//	printf("%s\n", recv_buf);
		for(j = 0; j <= fdmax; j++){
			send_to_all(j, i, sockfd, nbytes_recvd, recv_buf, master );
		}
	}	
}