#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int		main()
{
	//create a socket
	int		socketfd;
	socketfd = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;	//setting family
	server_address.sin_port = htons(5000);	//setting port
	server_address.sin_addr.s_addr = INADDR_ANY;//ip connecting to default 0.0.0.0
	
	int connection_status = connect(socketfd, (struct sockaddr *) &server_address, sizeof(server_address));
	//check for error w/ connection
	if (connection_status == -1)
	{
		printf("client socket connection error\nreason[%s]\n", strerror(errno));
		//exit(0);
	}
	else
		printf("client connected to server! status [%i]\n", connection_status);
	printf("-----\nserver info\n-----\nsin_family [%u]\nsin_port [%i]\ns_addr [%u]\n-----\n",
			server_address.sin_family, server_address.sin_port, server_address.sin_addr.s_addr);
	//receive data from server
	char server_response[256];
	int	connect = 5;
	while (1)
	{
		bzero(server_response, 256);
		recv(socketfd, &server_response, sizeof(server_response), 0);
	//print out server response
		if (strcmp(server_response, "exit") == 0)
		{
			printf("received [%s]\nclosing client socket\n", server_response);
			close(socketfd);
			exit(0);
		}
		printf("server sent[%s]\n", server_response);
	//	connect--;
	}
	close(socketfd);
	printf("client socket closed\n");
	return (0);
}