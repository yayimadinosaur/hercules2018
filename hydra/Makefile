# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wfung <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/01 16:55:48 by wfung             #+#    #+#              #
#    Updated: 2018/03/01 17:07:04 by wfung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	hydra

CC		=	gcc

FLAG	=	-Wall -Wextra -Werror

SRCS	=	main.c\
		#	parse.c\

OBJ		=	${SRCS:.c=.o}

INCLUDE	=	-I hydra.h

all:	$(NAME)

$(OBJ):
	@$(CC) $(FLAG) -c $(SRCS)

$(NAME):	$(OBJ)
	@$(CC) $(FLAG) $(INCLUDE) $(OBJ) -o $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean:	clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
