/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:15:49 by wfung             #+#    #+#             */
/*   Updated: 2018/03/02 14:53:26 by wfung            ###   ########.fr       */
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
	int		sockfd;
//	char	sendline[100];
//	char	recvline[100];
	struct sockaddr_in servaddr;

	if (ac >= 2)
	{
		printf("minimum args reached\n");
		printf("arg1[%s]\n", av[1]);
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		printf("[socketfd result = %i]\n", sockfd);
		bzero(&servaddr, sizeof servaddr);
		servaddr.sin_family = AF_INET;
		printf("sin_family = [%hhu]\n", servaddr.sin_family);
		servaddr.sin_port = htons(22000);
		printf("sin_family = [%hu]\n", servaddr.sin_port);
	}
	else if (ac == 1)
	{
		printf("missing args\n");
	}
	return (0);
}
