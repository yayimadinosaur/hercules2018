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

	/*
	 * create server socket
	 */
	int		server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	/*
	 * define server address
	 */
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	/*
	 * bind the socket to specific ip + port
	 */
	printf("-----\nserver address defined\n-----\n");
	int bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (bind_status < 0)
		printf("bind error reason[%s]\n", strerror(errno));
	else
		printf("bind status [%i] success!\n", bind_status);
	/*
	 * listen
	 */
	listen(server_socket, 5);	/*5 is backlog number, max num of connections */
	
	/*
	 * create client socket
	 */
	int	client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	
	/*
	 * send message
	 */
	int msg_size = 1000;
	char send_msg[msg_size + 1];
	char *replace;
	while (1)
	{
		bzero(send_msg, 1000);
		if (fgets(send_msg, 1000, stdin))
		{
			replace = strchr(send_msg, '\n');
			*replace = '\0';
			printf("sending msg to client[%s]\n", send_msg);
		if (strcmp(send_msg, "exit") == 0)
		{
			send(client_socket, "exit", 4, 0);
			printf("closing server properly\n");
			close(server_socket);
			exit(0);
		}
		if (strcmp(send_msg, "ping") == 0)
			send(client_socket, "pong\npong\n", 10, 0);
		else
			send(client_socket, send_msg, strlen(send_msg), 0);
		}
	}
	printf("closing socket to server\n");
	close(server_socket);
	return (0);
}
