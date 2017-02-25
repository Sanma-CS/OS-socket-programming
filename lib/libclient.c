
#include "libclient.h"

void connect_request(int *sockfd, struct sockaddr_in *server_addr)
{
	char buffer[BUFSIZE];
	
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR! Could not create socket");
		exit(1);
	}
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(8888);
	server_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(buffer, BUFSIZE);
	//memset(server_addr->sin_zero, '', sizeof server_addr->sin_zero);
	
	if(connect(*sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) == -1) {
		perror("ERROR! Has a problem with connection");
		exit(1);
	}
}
	
void send_recv(int i, int sockfd)
{
	char send_buf[BUFSIZE];
	char recv_buf[BUFSIZE];
	int nbyte_recvd;
	
	if (i == 0){
		fgets(send_buf, BUFSIZE, stdin); 	//get string from input and store into send_buf
		
		/*compares function, to check users wanna quit or not*/
		if (strcmp(send_buf , "quit\n") == 0) {
			printf("client-quited\n");
			exit(0);
		}else
			send(sockfd, send_buf, strlen(send_buf), 0); //calling send()
	}else {
		nbyte_recvd = recv(sockfd, recv_buf, BUFSIZE, 0); //calling recv()
		recv_buf[nbyte_recvd] = '\0';
		printf("%s\n" , recv_buf);
		fflush(stdout); // flushes the output buffer of sdtout
	}
}
	