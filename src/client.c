#include "libclient.h"



int main()
{
	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;
	
	printf("Type 'quit' to disconnect\n"); //????
	connect_request(&sockfd, &server_addr);
	FD_ZERO(&master);
        FD_ZERO(&read_fds);
        FD_SET(0, &master);
        FD_SET(sockfd, &master);
	fdmax = sockfd;
	
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("ERROR! unable to select");
			exit(4);
		}
		
		for(i=0; i <= fdmax; i++ )
			if(FD_ISSET(i, &read_fds))
				send_recv(i, sockfd);
	}
	//printf("client-quited\n");
	close(sockfd);
	return 0;
}

