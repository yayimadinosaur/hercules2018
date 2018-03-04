/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:15:49 by wfung             #+#    #+#             */
/*   Updated: 2018/03/03 12:59:50 by wfung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hydra.h"

/*	selfmade parse, probably not necessary
int		setup_socket(char *ip_addr)
{
	parse(ip_addr);
}
*/

int		main(int ac, char **av)
{
	int		sockfd;	//socket to listen to
//	char	sendline[100];
//	char	recvline[100];
	struct sockaddr_in servaddr;	//rename of built in struct

	if (ac >= 2)
	{
		printf("minimum args reached\n");
		printf("arg1[%s]\n", av[1]);
		sockfd = socket(AF_INET, SOCK_STREAM, 0);	//try PF_INET instead?
		if (sockfd < 0)
		{
			printf("[socket error %i]\n", sockfd);
			return (-1);
		}
		else
			printf("[socket pass %i]\n", sockfd);
		bzero(&servaddr, sizeof servaddr);
		servaddr.sin_family = AF_INET;		//setting addressing scheme to AF_INET(ip)
		printf("sin_family = [%hhu]\n", servaddr.sin_family);
	//	servaddr.sin_addr.s_addr = htons(INADDY_ANY);
		//allow any address to connect?
		servaddr.sin_port = htons(22000);	//listen on port 22000
		printf("sin_family = [%u]\n", servaddr.sin_port);
		servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//network byte order
		printf("ip address = [%u]\n", servaddr.sin_addr.s_addr);
		if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
		{
			printf("could not bind socket\n");
			return (-1);
		}
	}
	else if (ac == 1)
	{
		printf("missing args\n");
	}
	return (0);
}
