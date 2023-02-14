# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 11:15:49 by blefebvr          #+#    #+#              #
#    Updated: 2023/02/12 13:48:21 by blefebvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# compiler
CC			= gcc

# flags
CFLAGS		= -g -Wall -Wextra -Werror -pthread

# artifacts
NAME		=	philo

# source files
SRCS		=	main.c \
				actions.c \
				errors.c \
				initialization.c \
				utils.c \
				threads.c \
				free.c \
				monitoring.c

# object files
OBJS		=	${SRCS:.c=.o}

# so long library
PHILO		=	philo.h

# files 
INC			= 

# rules
all			: ${NAME}

${NAME}		: ${OBJS} philo.h 
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} 

%.o 		: %.c
			${CC} ${CFLAGS} -c $< -o $@ 

clean		:
			rm -rf ${OBJS}

fclean		: clean
			rm -rf ${NAME}

re			: fclean all

sanitize : ${OBJS} philo.h
		   ${CC} ${CFLAGS} ${OBJS} -fsanitize=thread -o ${NAME}

resanity : fclean sanitize

val			:${NAME}
			valgrind \
			--leak-check=full --tool=memcheck \
			--show-reachable=yes \
			--track-fds=yes \
			--errors-for-leak-kinds=all \
			--show-leak-kinds=all ./${NAME}

norme		:
			norminette ${SRCS} ${PHILO}

.PHONY		: all clean fclean re
