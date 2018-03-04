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
	/*
	 * create a socket
	 */
	int		socketfd;
	socketfd = socket(AF_INET, SOCK_STREAM, 0);

	/*
	 * specify an address for the socket
	 */
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5000);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	int connection_status = connect(socketfd, (struct sockaddr *) &server_address, sizeof(server_address));
	/*
	 * check for error w/ connection
	 */
	if (connection_status == -1)
	{
		printf("client socket connection error\nreason[%s]\n", strerror(errno));
		exit(0);
	}
	else
		printf("client connected to server! status [%i]\n", connection_status);
	printf("-----\nserver info\n-----\nsin_family [%u]\nsin_port [%i]\ns_addr [%u]\n-----\n",
			server_address.sin_family, server_address.sin_port, server_address.sin_addr.s_addr);
	/*
	 * receive data from server
	 */
	int	msg_size = 1000;
	char send_msg[msg_size + 1];
	char recv_msg[msg_size + 1];
	char *replace;
	while (1)
	{
		bzero(recv_msg, 1000);
		bzero(send_msg, 1000);
		if (fgets(send_msg, 1000, stdin))
		{
			replace = strchr(send_msg, '\n');
			*replace ='\0';
			printf("sending msg to server[%s]\n", send_msg);
		}
		if (strcmp(send_msg, "exit") == 0)
		{
			send(socketfd, "exit", 4, 0);
			printf("closing server properly\n");
			close(socketfd);
			exit(0);
		}
		else
			send(socketfd, send_msg, strlen(send_msg), 0);
		recv(socketfd, &recv_msg, sizeof(recv_msg), 0);
		printf("received from server[%s]\n", recv_msg);
		/*
		bzero(send_msg, 1000);
		recv(socketfd, &send_msg, sizeof(send_msg), 0);
		if (strcmp(send_msg, "exit") == 0)
		{
			printf("received [%s]\nclosing client socket\n", send_msg);
			close(socketfd);
			exit(0);
		}
		printf("server sent[%s]\n", send_msg);
		*/
	}
	close(socketfd);
	printf("client socket closed\n");
	return (0);
}
