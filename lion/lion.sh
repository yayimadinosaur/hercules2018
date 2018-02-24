# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lion.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wfung <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/23 21:03:30 by wfung             #+#    #+#              #
#    Updated: 2018/02/23 22:11:36 by wfung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

#install openssh
apt-get install openssh-server -y

#enable port
sed -i.bak 's/#Port 22/Port 54321/' /etc/ssh/sshd_config

#restart ssh
service ssh restart

#power off virtual machine
#add host ports and guest ports in virtualbox > settings > network
	#Adapter 1
		#green button Host Port - add 54321 Guest Port - add 54321
	#Adapter 2
		#Enable Network Adapter
		#Attached to Host-only Adapter
#Power On virtual machine
	#login as root

#local: ssh user@127.0.0.1 or user@virtualmachineip -p 54321 via ifconfig on local
#CONNECTED!

###TROUBLESHOOTING###
#if trying to ssh w/ root, keys in .ssh directory has to be removed
