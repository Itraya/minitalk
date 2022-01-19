# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 10:27:26 by mlagrang          #+#    #+#              #
#    Updated: 2022/01/18 11:35:13 by mlagrang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= srcs/server.c

SRCC	= srcs/client.c

HEADERS	= ./minitalk.h

OBJS	= ${SRCS:.c=.o}

OBJC	= ${SRCC:.c=.o}

NAMES	= server

NAMEC	= client

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

%.o:%.c	minitalk.h Makefile
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	server client

server:	${OBJS}
		${CC} ${OBJS} -o ${NAMES}

client:	${OBJC}
		${CC} ${OBJC} -o ${NAMEC}

clean:
		rm -f ${OBJS} ${OBJC}

fclean:	clean
		rm -f ${NAMES} ${NAMEC}

re:		fclean all

.PHONY:	all clean fclean re