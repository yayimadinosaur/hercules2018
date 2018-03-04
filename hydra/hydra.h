/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hydra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:01:22 by wfung             #+#    #+#             */
/*   Updated: 2018/03/03 15:04:43 by wfung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HYDRA_H__
# define __HYDRA_H__

#include <unistd.h>	//to write to file descriptors
#include <stdio.h>	//to use printf
#include <sys/socket.h>	//to use socket
#include <string.h>	//for bzero
#include <netinet/in.h> //includes in_addr + to store
//#include <netinet/ip.h>
#include <sys/types.h>
#include <arpa/inet.h>	//for inet address + inetpton
#include <errno.h>
#include <string.h>
//struct from https://www.gta.ufrj.br/ensino/eel878/sockets/structs.html

/*struct in /usr/include/sys/socket.h

struct		sockaddr
{
	unsigned short	sa_family;	//address family, AF_xxx
	char			sa_data[14];	//14 bytes of protocol address
}			sockaddy;
*/

/* struct in <netinet/in.h>
struct		sockaddr_in
{
	short int			sin_family;	//address family
	unsigned short int	sin_port;	//port number
	struct in_addr		sin_addr;	//internet address
	unsigned char		sin_zero[8];	//same size as struct sockaddr
};
*/

#endif
