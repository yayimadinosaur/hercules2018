#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

int		main()
{
	char	server_message[256] = "Reached server!";

	//create server socket
	int		server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to specific ip + port
	printf("-----\nserver address defined\n-----\n");
	int bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (bind_status < 0)
		printf("bind error reason[%s]\n", strerror(errno));
	else
		printf("bind status [%i] success!\n", bind_status);
	//listen
	listen(server_socket, 5);	//5 is backlog number, max num of connections
	
	int	client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	
	//send message
	int bufsize = 1000;
	char buf[bufsize + 1];
	char custom_msg[1000];
	while (1)
	{
		bzero(custom_msg, 1000);
		if (fgets(custom_msg, 1000, stdin))
		{
			char *replace = strchr(custom_msg, '\n');
			*replace = '\0';
			printf("sending msg to client[%s]\n", custom_msg);
	//	fgets(buf, 1000, stdin);
		if (strcmp(custom_msg, "exit") == 0)
		{
			send(client_socket, "exit", 4, 0);
			printf("closing server properly\n");
			close(server_socket);
			exit(0);
		}
		if (strcmp(custom_msg, "ping") == 0)
			send(client_socket, "pong\npong\n", 10, 0);
		else
			send(client_socket, custom_msg, strlen(custom_msg), 0);
		//send(client_socket, server_message, sizeof(server_message), 0);
		//send(client_socket, server_message, sizeof(server_message), 0);
		}
	}
	printf("closing socket to server\n");
	//close socket
	close(server_socket);
	return (0);
}
