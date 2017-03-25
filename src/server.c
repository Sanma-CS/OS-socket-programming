#include "libserver.h"


int main(int argc, char *argv[]) {
	int sockfd = 0;
	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	struct sockaddr_in serv_addr, client_addr;
	
	FD_ZERO(&master);	//Initialize master to have zero bits for all fds
	FD_ZERO(&read_fds);	////Initialize read_fds to have zero bits for all fds
	
	//Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR! Could not create socket");
		exit(1);
	}
	
		
	connect_request(&sockfd, &serv_addr); //bind then listen
	FD_SET(sockfd, &master);	//Set the bit for sockfd in the fd set master
	
	fdmax = sockfd;
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		
		for (i = 0; i <= fdmax; i++){
			if (FD_ISSET(i, &read_fds)){
				if (i == sockfd)
					connection_accept(&master, &fdmax, sockfd, &client_addr);
				else
					send_recv(i, &master, sockfd, fdmax);
			}
		}
	}
	
	
	return 0;
}
